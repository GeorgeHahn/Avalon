/********
 * Klondike ASIC Miner - asic.c - ASIC serial data shifting support
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

extern BYTE BankSize;
extern DWORD ClockCfg[2];
extern DWORD NonceRanges[8];

DWORD PrecalcHashes[6];

bank2 WORD send32_data; // place in same bank as latc registers!
bank2 BYTE send32_count; // count DWORDS
bank2 BYTE last_bit0, last_bit1;

void SendAsicData(WORKTASK *work, BYTE split)
{
    GIE = 0;
    last_bit0 = DATA_ZERO; last_bit1 = DATA_ONE;
    send32_data = (WORD)&ClockCfg; send32_count = 2;
    Send32();
    send32_data = (WORD)&work->Merkle; send32_count = 3;
    Send32();
    send32_data = (WORD)&PrecalcHashes[1]; send32_count = 5;
    Send32();
    send32_data = (WORD)&work->MidState; send32_count = 8;
    Send32();
    send32_data = (WORD)&PrecalcHashes; send32_count = 1;
    Send32();
    last_bit0 = last_bit1 = split;
    send32_data = (WORD)&NonceRanges; send32_count = BankSize;
    Send32();
    HASH_IDLE();
    GIE = 1;
}

void Send32(void)
{
    #asm
    BANKSEL(LATC) 
    MOVF (_send32_data) & 0x7F, W
    MOVWF FSR1L
    MOVF (_send32_data+1) & 0x7F, W
    MOVWF FSR1H

next_word:
    // bit 0
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,0
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 1
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,1
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 2
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,2
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 3
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,3
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 4
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,4
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 5
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,5
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 6
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,6
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 7
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,7
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // select next byte
    ADDFSR FSR1, 0x01 & 0x3F

    // bit 8
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,0
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 9
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,1
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 10
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,2
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 11
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,3
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 12
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,4
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 13
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,5
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 14
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,6
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 15
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,7
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // select next byte
    ADDFSR FSR1, 0x01 & 0x3F

    // bit 16
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,0
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 17
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,1
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 18
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,2
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 19
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,3
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 20
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,4
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 21
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,5
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 22
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,6
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 23
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,7
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // select next byte
    ADDFSR FSR1, 0x01 & 0x3F

    // bit 24
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,0
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 25
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,1
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 26
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,2
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 27
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,3
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 28
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,4
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 29
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,5
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 30
    MOVLW DATA_ZERO
    CLRF LATC & 0x7F
    BTFSC INDF1,6
    MOVLW DATA_ONE
    MOVWF LATC & 0x7F

    // bit 31
    MOVF _last_bit0 & 0x7F,W
    CLRF LATC & 0x7F
    BTFSC INDF1,7
    MOVF _last_bit1 & 0x7F,W
    MOVWF LATC & 0x7F

    // select next byte
    ADDFSR FSR1, 0x01 & 0x3F

    // check if done
    DECFSZ _send32_count & 0x7F, F
    GOTO next_word
    #endasm
    
}

#define r(x) ((x-n)&7)

DWORD rotate(DWORD x, BYTE y)
{
    return ((x<<y) | (x>>(32-y)));
}

void AsicPreCalc(WORKTASK *work)
{
    const DWORD K[3] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf };
    DWORD x, y, z;
    DWORD m[8];
    BYTE n;
    
    for(n = 0; n < 8; n++)
        m[n] = work->MidState[n];

    for(n = 0; n < 3; n++) {

        x = m[5-n] ^ m[6-n];
        x = x & m[4-n];
        x = m[6-n] ^ x;
        x += K[n];
        x += work->Merkle[n];
        x += m[7-n];
        y = rotate(m[4-n], 26);
        z = rotate(m[4-n], 21);
        z = y^z;
        y = rotate(m[4-n], 7);
        z = y^z;
        m[7-n] = z+x;
        m[3-n] = m[3-n] + m[7-n];
        x = rotate(m[r(0)], 30);
        y = rotate(m[r(0)], 19);
        y = y^x;
        x = rotate(m[r(0)], 10);
        y = x^y;
        x = m[r(0)] | m[r(1)];
        x = m[r(2)] & x;
        z = m[r(0)] & m[r(1)];
        x = x | z;
        m[7-n] += y + x;

        PrecalcHashes[2-n] = m[7-n];
        PrecalcHashes[5-n] = m[3-n];
    }
}

//#define R(a, b, c, d, e, f, g, h, w, k) \
//    h = h + (rotate(e, 26) ^ rotate(e, 21) ^ rotate(e, 7)) + (g ^ (e & (f ^ g))) + k + w; \
//    d = d + h; \
//    h = h + (rotate(a, 30) ^ rotate(a, 19) ^ rotate(a, 10)) + ((a & b) | (c & (a | b)))

/* this version uses too much stack and causes overflow
 * re-written above to be more flat and as first step to
 * assembly optimization
 *
DWORD rotate(DWORD x, BYTE y)
{
    return ((x<<y) | (x>>(32-y)));
}

void R1(DWORD *m, DWORD w, DWORD k)
{
    m[7] = m[7] + (rotate(m[4], 26) ^ rotate(m[4], 21) ^ rotate(m[4], 7)) + (m[6] ^ (m[4] & (m[5] ^ m[6]))) + k + w;
    m[3] = m[3] + m[7];
    m[7] = m[7] + (rotate(m[0], 30) ^ rotate(m[0], 19) ^ rotate(m[0], 10)) + ((m[0] & m[1]) | (m[2] & (m[0] | m[1])));
}

void R2(DWORD *m)
{
    DWORD hold = m[7];
    for(BYTE x=7; x > 0; x--)
        m[x] = m[x-1];
    m[0] = hold;
}

extern BYTE WorkNow;
extern WORKTASK WorkQue[MAX_WORK_COUNT];

DWORD precalc_hash[6];

void HasherPreCalc(void)
{
    const DWORD K[3] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf };
    DWORD m[8];
    BYTE n;
    for(n = 0; n < 8; n++)
        m[n] = WorkQue[WorkNow].MidState[n];

    R1(m, WorkQue[WorkNow].Merkle[0], K[0]);
    precalc_hash[0] = m[7];
    precalc_hash[3] = m[3];
    R2(m);
    R1(m, WorkQue[WorkNow].Merkle[1], K[1]);
    precalc_hash[1] = m[7];
    precalc_hash[4] = m[3];
    R2(m);
    R1(m, WorkQue[WorkNow].Merkle[2], K[2]);
    precalc_hash[2] = m[7];
    precalc_hash[5] = m[3];
}
*/
