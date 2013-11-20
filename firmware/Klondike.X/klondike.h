/********
 * Klondike ASIC Miner - klondike.h - data structures and function prototypes 
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

#ifndef KLONDIKE_H
#define KLONDIKE_H

#ifdef  __cplusplus
extern "C" {
#endif

#define FWPWD               "KlondikeRocks"

#define MASTER_ADDRESS      0x00
#define MAX_WORK_COUNT      4   // must be binary multiple
#define WORKMASK            MAX_WORK_COUNT-1
#define MAX_RESULT_COUNT    2
#define USB_RECORD_SIZE     15

// set values for ASIC PLL, we use R=16 N=Freq in MHz
#define WORK_TICKS          16384   // 2^32 total / 2^18 hashes per tick
#define TICK_TOTAL          12292   // 2^18 / 21.33uS TMR0 period (adjusted down for push time)
#define CLOCK_R_VALUE       16
#define DEFAULT_HASHCLOCK   256
#define CLOCK_NOCHG_MASK    0x00000002
#define CLOCK_LOW_CHG       0x00030007
#define CLOCK_HALF_CHG      0x00030017
#define CLOCK_HIGH_CFG      0x00000172
#define MIN_HASH_CLOCK      128
#define HALF_HASH_CLOCK     250
#define MAX_HASH_CLOCK      450

// default temp/fan values
#define DEFAULT_TEMP_TARGET     60 
#define DEFAULT_TEMP_CRITICAL   80 
#define DEFAULT_FAN_TARGET      230 // is 90%

// number of hashes to delay results while test work pushed
// 390uS push time @ 256 MHz startup clock = 99840 hashes
#define DETECT_DELAY_COUNT  109980
#define GOOD_NONCE          0xe3d69bc9
#define GOOD_MIDSTATE       { 0x5fddb5bc,0x00bdafd2,0x144684c7,0x19c68fa2,0x27d0a8e3,0x34ad84b2,0xa92c66be,0x3e99a4fd }
#define GOOD_DATA           { 0xf64684bb,0x51bc1508,0x1a011337 }

// for controlling how bits are adjusted per bank
#define DATA_ZERO   0x48
#define DATA_ONE    0x90
#define DATA_SPLIT  0x50

typedef struct _id {
    BYTE version;
    char product[7];    
    DWORD serial;
} IDENTITY;

typedef struct _workstatus {
    BYTE State;
    BYTE ChipCount;
    BYTE SlaveCount;
    BYTE WorkQC;
    BYTE WorkID;
    BYTE Temp;
    BYTE FanSpeed;
    BYTE ErrorCount;
    WORD HashCount, MaxCount;
    BYTE Noise;
} WORKSTATUS;

typedef struct _workcfg {
    WORD HashClock;
    BYTE TempTarget, TempCritical;
    BYTE FanTarget, pad;
} WORKCFG;

typedef struct _worktask {
    BYTE WorkID;
    DWORD MidState[8];
    DWORD Merkle[3];
} WORKTASK;

typedef struct _i2c {
    BYTE Next : 5;
    BYTE Slave : 1;
    BYTE Master : 1;
} I2CSTATE;

#define I2C_READ        1
#define I2C_WRITE       10
#define I2C_SLAVE       13

void ProcessCmd(char *cmd);
void AsicPushWork(void);

void CheckFanSpeed(void);
void DetectAsics(void);

void ResultRx(void);
void WorkTick(void);
void UpdateTemp(void);
void UpdateFanSpeed(void);

void I2CRelay(char *data, BYTE count);
void I2CPoll(void);
void I2CDetect(void);
void I2CRead(void);
void I2CWrite(void);
void I2CSlave(void);

void InitI2CSlave(void);
void InitI2CMaster(void);
void InitFAN(void);
void InitTempSensor(void);
void InitWorkTick(void);
void InitResultRx(void);

void SendAsicData(WORKTASK *work, BYTE split);
void Send32(void);
void AsicPreCalc(WORKTASK *work);

void SendCmdReply(char *cmd, BYTE *ReplyBuf, BYTE count);

#ifdef  __cplusplus
}
#endif

#define CLOCK_FREQ      48000000

// PIC Pin Allocations
#define LED0             LATDbits.LATD3 // LED 1 - D3
#define LED1             LATDbits.LATD2 // LED 2 - D2
#define LED2             LATDbits.LATD1 // LED 3 - D1
#define LED3             LATDbits.LATD0 // LED 4 - D0

#define InitLEDs()            \
    {                         \
        TRISDbits.TRISD3 = 0; \
        TRISDbits.TRISD3 = 0; \
        TRISDbits.TRISD3 = 0; \
        TRISDbits.TRISD3 = 0; \
        LED0 = 1;             \
        LED1 = 1;             \
        LED2 = 1;             \
        LED3 = 1;             \\\
    }

//#define LED_On()        LED = 1;
//#define LED_Off()       LED = 0;
//#define LED_Toggle()    LED = !LED;

#define MIN_FAN_SPEED   64
#define FAN_PWM         LATCbits.LATC5
#define FAN_TRIS        TRISCbits.TRISC5
#define FAN_Speed(x)    { PWM1DCH = x; }
#define TACH_FACTOR     87890	// rpm = TACH_FACTOR / count @ 170uS each

#define TEMP_INTERNAL   29
#define TEMP_THERMISTOR 6
#define THERM_TRIS      TRISCbits.TRISC2
#define TEMP_INIT       { asm("BSF FVRCON,4");asm("BSF FVRCON,5"); }

#define I2C_TRIS_DATA   TRISBbits.TRISB4
#define I2C_TRIS_CLK    TRISBbits.TRISB6
#define I2C_DATA        LATBbits.LATB4
#define I2C_CLK         LATBbits.LATB6

#define HASH_CLK_EN     LATAbits.LATA4
#define HASH_CLK_TRIS   TRISAbits.TRISA4

#define HASH_TRIS_0P    TRISCbits.TRISC7
#define HASH_TRIS_0N    TRISCbits.TRISC6
#define HASH_TRIS_1P    TRISCbits.TRISC4
#define HASH_TRIS_1N    TRISCbits.TRISC3
#define HASH_IDLE()     LATC = 0xD8;

#define RESET_RX()      { RCSTAbits.SPEN = 0;RCSTAbits.SPEN = 1;ResultQC = 0; }
#define INPUT_PIN 1
#define OUTPUT_PIN 0

#define  UART_PIN       LATBbits.LATB7
#define  TRIS_UART      TRISBbits.TRISB7
#define _XTAL_FREQ      48000000

#endif  /* KLONDIKE_H */

