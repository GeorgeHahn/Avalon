/********
 * Klondike ASIC Miner - i2c.c - i2c master / slave support with arbitration
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

extern const IDENTITY ID;
extern BYTE SlaveAddress;
extern WORKSTATUS Status;

I2CSTATE I2CState;
BYTE I2CCmd, I2CAddr, I2CCount;
BYTE *I2CInBuf;

BYTE ptr = 0;
BYTE buf[16];

void I2CRelay(char *data, BYTE count)
{
    //while(I2CState.Next != 0);  // wait for I2C available
    I2CAddr = data[2];
    I2CInBuf = data;
    I2CCount = count;
    I2CState.Next = I2C_WRITE;
    SSPCON2bits.SEN = 1;
}

void I2CPoll(void)
{
    if(I2CState.Next == 0) {
        I2CCmd = 'P';
        I2CCount = 0;
        I2CState.Next = I2C_READ;
        SSPCON2bits.SEN = 1;
    }
}

void I2CDetect(void)
{
    I2CCmd = '?';
    I2CCount = 4;
    I2CState.Next = I2C_READ;
    SSPCON2bits.SEN = 1;
}

void I2CRead(void)
{
    if(SSPSTATbits.P)
        I2CState.Next = 0;
    switch(I2CState.Next)
        {
        case I2C_READ: SSPBUF = 0; I2CState.Next++; ptr = 0; break;
        case I2C_READ+1:
            if(SSPCON2bits.ACKSTAT)
                { SSPCON2bits.PEN = 1; break; }
            SSPBUF = I2CCmd; I2CState.Next++; break;
        case I2C_READ+2:
            if(SSPCON2bits.ACKSTAT)
                { SSPCON2bits.PEN = 1; break; }
            I2CState.Next++;
        case I2C_READ+3:
            SSPCON2bits.RCEN = 1; I2CState.Next++; break;
        case I2C_READ+4:
            if(I2CCount == 0) {
                if(SSPBUF == '=') I2CCount = sizeof(DWORD)+3;
                else if (SSPBUF == 'I') I2CCount = sizeof(IDENTITY)+2;
                else if (SSPBUF == 'C') I2CCount = sizeof(WORKCFG)+2;
                else I2CCount = sizeof(WORKSTATUS)+2;
            }
            buf[ptr++] = SSPBUF;
            SSPCON2bits.ACKDT = (I2CCount-- == 1);
            SSPCON2bits.ACKEN = 1;
            if(I2CCount > 0)
                I2CState.Next--;
            else if(I2CCmd == 'P')
                I2CState.Next = I2C_READ+8;
            else
                I2CState.Next++;
            break;
        case I2C_READ+5: SSPBUF = ++Status.SlaveCount; I2CState.Next++; break;
        case I2C_READ+6: SSPCON2bits.PEN = 1; I2CState.Next++; break;
        case I2C_READ+7: SSPCON2bits.SEN = 1; I2CState.Next = I2C_READ; break;
        case I2C_READ+8: SSPCON2bits.PEN = 1; I2CState.Next++; break;
        //case I2C_READ+9: SendCmdReply(buf, buf+2, ptr-3); I2CState.Next = 0; break;
        default:
            break;
        }
}

void I2CWrite(void)
{
    switch(I2CState.Next)
        {
        case I2C_WRITE:
            SSPBUF = I2CAddr; // slave address
            ptr = 0; I2CState.Next++;
            break;
        case I2C_WRITE+1:
            SSPBUF = I2CInBuf[ptr++]; // data stream
            if(--I2CCount == 0)
                I2CState.Next++; break;
        case I2C_WRITE+2: SSPCON2bits.PEN = 1; break;
        default:
            break;
        }
}

extern char INPacket[64];
extern char OUTPacket[64];

void I2CSlave(void)
{
    if(SSPSTATbits.P) {
        I2CState.Next = 0;
        if(I2CCmd != '?' && I2CCmd != 'P')
            I2CCount = ptr;
    }
    switch(I2CState.Next)
        {
        case I2C_SLAVE: I2CAddr = SSPBUF; I2CState.Next++; ptr = 0; break;
        case I2C_SLAVE+1: OUTPacket[ptr++] = I2CCmd = SSPBUF;
            if(I2CCmd == '?') I2CState.Next = I2C_SLAVE+3;
            else if(I2CCmd == 'P') I2CState.Next = (I2CCount > 0) ? I2C_SLAVE+6 : 0;
            else I2CState.Next++;
            break;
        case I2C_SLAVE+2: if(ptr < sizeof(OUTPacket)) OUTPacket[ptr++] = SSPBUF; break;
        
        case I2C_SLAVE+3: *(DWORD *)buf = ID.serial; ptr = 0; I2CState.Next++;
        case I2C_SLAVE+4: SSPBUF = buf[ptr++]; SSPCON1bits.CKP = 1; 
            if(ptr == 4) I2CState.Next++; break;
        case I2C_SLAVE+5: SlaveAddress = SSPBUF; break;

        case I2C_SLAVE+6: I2CCount = ptr = 0; I2CState.Next++;
        case I2C_SLAVE+7: SSPBUF = INPacket[ptr++]; SSPCON1bits.CKP = 1; break;
        default:
            break;
        }
}

// Init functions

void InitI2CSlave(void)
{
    I2CState.Slave = 1; I2CState.Master = 0;
    SSPADD = SlaveAddress;
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB6 = 1;
    SSPCON1bits.SSPM = 6; // slave 7-bit mode
    SSPCON2bits.GCEN = 1; // enable general call address 0
    SSPCON3bits.SBCDE = 1; // enable bus collision interrupts
    SSPSTATbits.SMP = 1;
    SSP1EN = 1;
    SSP1IF = 1;
}

void InitI2CMaster(void)
{
    I2CState.Master = 1; I2CState.Slave = 0;
    SlaveAddress = 0;
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB6 = 1;
    SSPADD = 0x77; // 100kHz @ 48MHz Fosc.
    SSPCON1bits.SSPM = 8; // master mode
    SSPSTATbits.SMP = 1;
    SSP1EN = 1;
    SSP1IF = 1;
    I2CDetect();
}
