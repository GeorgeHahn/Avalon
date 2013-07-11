/********
 * Klondike ASIC Miner - klondike.c - cmd processing and host protocol support 
 * 
 * (C) Copyright 2013 Chris Savery. 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include <xc.h>
#include "klondike.h"

const IDENTITY ID = { 0x10, "K16", 0xDEADBEEF };

DWORD BankRanges[8] = { 0, 0x40000000, 0x2aaaaaaa, 0x20000000, 0x19999999, 0x15555555, 0x12492492, 0x10000000 };
BYTE WorkNow, BankSize, ResultQC, SlowTick;
BYTE SlaveAddress = MASTER_ADDRESS;
BYTE HashTime = 256 - ((WORD)TICK_TOTAL/DEFAULT_HASHCLOCK);
volatile WORKSTATUS Status = {'I',0,0,0,0,0,0,0,0, WORK_TICKS, 0 };
WORKCFG Cfg = { DEFAULT_HASHCLOCK, DEFAULT_TEMP_TARGET, DEFAULT_TEMP_CRITICAL, DEFAULT_FAN_TARGET, 0 };
WORKTASK WorkQue[MAX_WORK_COUNT];
volatile BYTE ResultQue[MAX_RESULT_COUNT*4];
DWORD ClockCfg[2] = { (((DWORD)DEFAULT_HASHCLOCK) << 18) | CLOCK_LOW_CHG, CLOCK_HIGH_CFG };

DWORD NonceRanges[8];

extern I2CSTATE I2CState;
extern DWORD PrecalcHashes[6];

void ProcessCmd(char *cmd)
{
    // cmd is one char, dest address 1 byte, data follows
    // we already know address is ours here
    switch(cmd[0]) {
        case 'W': // queue new work
            if( Status.WorkQC < MAX_WORK_COUNT-1 ) {
                WorkQue[ (WorkNow + Status.WorkQC++) & WORKMASK ] = *(WORKTASK *)(cmd+2);
                if(Status.State == 'R') {
                    AsicPreCalc(&WorkQue[WorkNow]);
                    AsicPushWork();
                }
            }
            SendCmdReply(cmd, (char *)&Status, sizeof(Status));
            break;
        case 'A': // abort work, reply status has hash completed count
            Status.WorkQC = WorkNow = 0;
            Status.State = 'R';
            SendCmdReply(cmd, (char *)&Status, sizeof(Status));
            break;
        case 'I': // return identity 
            SendCmdReply(cmd, (char *)&ID, sizeof(ID));
            break;
        case 'S': // return status 
            SendCmdReply(cmd, (char *)&Status, sizeof(Status)); 
            break;
        case 'C': // set config values 
            if( *(WORD *)&cmd[2] != 0 ) {
                Cfg = *(WORKCFG *)(cmd+2);
                if(Cfg.HashClock < MIN_HASH_CLOCK)
                    Cfg.HashClock = MIN_HASH_CLOCK;
                if(Cfg.HashClock <= HALF_HASH_CLOCK && Cfg.HashClock >= MAX_HASH_CLOCK/2)
                    Cfg.HashClock = MAX_HASH_CLOCK/2-1;
                if(Cfg.HashClock >= MAX_HASH_CLOCK)
                    Cfg.HashClock = MAX_HASH_CLOCK-1;
                if(Cfg.HashClock <= HALF_HASH_CLOCK)
                    ClockCfg[0] = (((DWORD)Cfg.HashClock*2) << 18) | CLOCK_HALF_CHG;
                else
                    ClockCfg[0] = ((DWORD)Cfg.HashClock << 18) | CLOCK_LOW_CHG;
                HashTime = 256 - ((WORD)TICK_TOTAL/Cfg.HashClock);
                PWM1DCH = Cfg.FanTarget;
                Status.ErrorCount = 0;
            }
            SendCmdReply(cmd, (char *)&Cfg, sizeof(Cfg));
            break;
        case 'E': // enable/disable work
            HASH_CLK_EN = (cmd[2] == '1');
            Status.State = (cmd[2] == '1') ? 'R' : 'D';
            SendCmdReply(cmd, (char *)&Status, sizeof(Status));
            break;
        case 'D':
            SendCmdReply(cmd, (char *)&ResultQC, sizeof(ResultQC));
        default:
            break;
        }
    LED_On();
}

void AsicPushWork(void)
{
    Status.WorkID = WorkQue[WorkNow].WorkID;
    SendAsicData(&WorkQue[WorkNow], DATA_SPLIT);
    WorkNow = (WorkNow+1) & WORKMASK;
    Status.HashCount = 0;
    TMR0 = HashTime;
    Status.State ='W';
    if(--Status.WorkQC > 0)
        AsicPreCalc(&WorkQue[WorkNow]);
}

// Housekeeping functons

void CheckFanSpeed(void)
{
    if(PWM1OE == 0) { // failed read attempt, abort
        FAN_PWM = 0;
        PWM1OE = 1;
        Status.FanSpeed = 0;
    }
    else if( IOCAF3 == 1) { // only check if NegEdge else no Tach present
        IOCAF3 = 0; // reset Tach detection
        FAN_PWM = 1; // force PWM fan output to ON
        PWM1OE=0;
        T1CONbits.TMR1CS = 0;
        T1CONbits.T1CKPS = 3;
        T1CONbits.TMR1ON = TMR1GE = 1;
        T1GCONbits.T1GPOL = 1;
        T1GCONbits.T1GSS = T1GCONbits.T1GTM = 0;
        T1GSPM = 1;
        TMR1H = TMR1L = 0;
        TMR1ON = 1;
        TMR1GIE = TMR1IE = 1;
        T1GCONbits.T1GGO_nDONE = 1;
    }
}

void DetectAsics(void)
{
/* disabled for now, not fully worked out yet
   const WORKTASK TestWork = { 0xFF, GOOD_MIDSTATE, GOOD_DATA };
    const DWORD GoodNonce = GOOD_NONCE;
    const DWORD StartNonce = (GOOD_NONCE - DETECT_DELAY_COUNT);
    BankSize = 8;
    Status.ChipCount = 0;
    for(BYTE x = 0; x < BankSize; x++)
        NonceRanges[x] = StartNonce;
    WorkQue[0] = TestWork;
    AsicPreCalc(&WorkQue[0]);
    
    //SendAsicData(&WorkQue[0], (StartNonce & 0x80000000) ? DATA_ONE : DATA_ZERO);
    // wait for "push work time" for results to return and be counted*/
    
    Status.ChipCount = 4; // just for testing
    
    // pre-calc nonce range values
    BankSize = Status.ChipCount; //(Status.ChipCount+1)/2;
    Status.MaxCount = WORK_TICKS / BankSize;
    NonceRanges[0] = 0;
    for(BYTE x = 1; x < BankSize; x++)
        NonceRanges[x] = NonceRanges[x-1] + 2*BankRanges[BankSize-1];  // single bank, double range size
    Status.State ='R';
    Status.HashCount = 0;
}

// ISR functions

void WorkTick(void)
{
    TMR0 += HashTime;
    TMR0IF = 0;
    //RCREG = 0xFF;
    if(RCSTAbits.SPEN == 0) {
        RCSTAbits.SPEN = 1; // renable Rx
        ResultQC = 0;       // resync Rx
    }
    if((Status.State == 'W') && (++Status.HashCount == Status.MaxCount)) {
        if(Status.WorkQC > 0) {
            Status.State = 'P'; // set state to push data and do asap
            return;
        }
        else
            Status.State = 'R';
    }

   if(++SlowTick == 0) {
        LED_Off();
        Status.Temp = ADRESH;
        // todo: adjust fan speed for target temperature
        ADCON0bits.GO_nDONE = 1;
        //CheckFanSpeed();
    }
   //if((SlowTick & 3) == 0)
   //I2CPoll();
}

void ResultRx(void)
{
    //ResultQue[2+ResultQC++] = ~RCREG;
    BYTE TimeOut = 0;
    ResultQC = 0;
    while(ResultQC < 4) {

        if(RCIF) {
            ResultQue[2+ResultQC++] = ~RCREG;
            TimeOut = 0;
        }
        if(TimeOut++ > 32 ) {
            Status.Noise++;
            goto outrx;
        }

        if(RCSTAbits.OERR) { // error occured, either overun or no more bits
            if(Status.State == 'W')
                Status.ErrorCount++;
            RCSTAbits.SPEN = 0; // clear error, don't re-enable until next tick TMR0, 21.3uS
            goto outrx;
        }
    }
    
    if(Status.State == 'W') {
        ResultQue[0] = '=';
        ResultQue[1] = Status.WorkID;
        SendCmdReply(&ResultQue, &ResultQue+1, sizeof(ResultQue)-1);
    }
outrx:
    //RCREG = 0xFF;
    RCSTAbits.SPEN = 0; RCSTAbits.SPEN = 1;
    IOCBF = 0;
}

void UpdateFanSpeed(void)
{
    TMR1GIF = TMR1IF = 0;
    IOCAF3 = 0; // skip one cycle
    TMR1ON = 0;
    Status.FanSpeed = TMR1H; // rollover below 330 rpm, not measured
    FAN_PWM = 0; // re-enable PWM fan output
    PWM1OE=1;
}

// Init functions

void InitFAN(void)
{
    FAN_TRIS = 1;
    PWM1CON = 0;
    PR2 = 0xFF;
    PWM1CON = 0xC0;
    PWM1DCH = DEFAULT_FAN_TARGET;
    PWM1DCL = 0;
    TMR2IF = 0;
    T2CONbits.T2CKPS = 0;
    TMR2ON = 1;
    FAN_TRIS = 0;
    PWM1OE=1;

    // for Fan Tach reading
    T1GSEL = 1;
    IOCAN3 = 1;
    IOCAF3 = 0;
}

void InitTempSensor(void)
{ 
    THERM_TRIS=1;
    //TEMP_INIT;
    //FVREN = 1;
    ADCON0bits.CHS = TEMP_THERMISTOR;
    ADCON0bits.ADON = 1;
    ADCON1bits.ADFM = 0;
    ADCON1bits.ADCS = 6;
    ADCON1bits.ADPREF = 0;
    ADCON2bits.TRIGSEL = 0;
}

void InitWorkTick(void)
{
    TMR0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 7;
    TMR0 = HashTime;
    //TMR0IE = 1;

    HASH_TRIS_0P = 0;
    HASH_TRIS_0N = 0;
    HASH_TRIS_1P = 0;
    HASH_TRIS_1N = 0;
    HASH_IDLE();
    HASH_CLK_TRIS = 0;
    HASH_CLK_EN = 1;
}

void InitResultRx(void)
{
    ResultQC = 0;
    TXSTAbits.SYNC = 1;
    RCSTAbits.SPEN = 1;
    TXSTAbits.CSRC = 0;
    BAUDCONbits.SCKP = 1;
    ANSELBbits.ANSB5 = 0;
    //PIE1bits.RCIE = 1;
    IOCBPbits.IOCBP7 = 1;
    INTCONbits.IOCIE = 1;
    IOCBF = 0;
    //INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    RCSTAbits.CREN = 1;
    RCREG = 0xFF;
}
