/********************************************************************
 FileName:      HardwareProfile.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, dsPIC33, or PIC32 USB Microcontrollers
 Hardware:      This demo is natively intended to be used on Microchip USB demo
                boards supported by the MCHPFSUSB stack.  See release notes for
                support matrix.  The firmware may be modified for use on
                other USB platforms by editing this file (HardwareProfile.h)
                and adding a new hardware specific 
                HardwareProfile - [platform name].h file.
 Compiler:      Microchip C18 (for PIC18), C30 (for PIC24/dsPIC33), or C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC� Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************/

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//#define DEMO_BOARD USER_DEFINED_BOARD

#if !defined(DEMO_BOARD)
    #if defined(__C32__)
        #if defined(__32MX460F512L__)
            #if defined(PIC32MX460F512L_PIM)
                #include "HardwareProfile - PIC32MX460F512L PIM.h"
            #elif defined(PIC32_USB_STARTER_KIT)
                #include "HardwareProfile - PIC32 USB Starter Kit.h"
            #endif
        #elif defined(__32MX795F512L__)
            #if defined(PIC32MX795F512L_PIM)
                #include "HardwareProfile - PIC32MX795F512L PIM.h"
            #elif defined(PIC32_USB_STARTER_KIT)
                //PIC32 USB Starter Kit II
                #include "HardwareProfile - PIC32 USB Starter Kit.h"
            #endif
        #endif
    #endif

    #if defined(__C30__) || defined __XC16__
        #if defined(__PIC24FJ256GB110__)
            #include "HardwareProfile - PIC24FJ256GB110 PIM.h"
        #elif defined(__PIC24FJ256GB210__)
            #include "HardwareProfile - PIC24FJ256GB210 PIM.h"
        #elif defined(__PIC24FJ256GB106__)
            #include "HardwareProfile - PIC24F Starter Kit.h"
        #elif defined(__PIC24FJ64GB004__)
            #include "HardwareProfile - PIC24FJ64GB004 PIM.h"
        #elif defined(__PIC24FJ64GB502__)
            #include "HardwareProfile - PIC24FJ64GB502 Microstick.h"
        #elif defined(__PIC24FJ256DA210__)
            #include "HardwareProfile - PIC24FJ256DA210 Development Board.h"
        #elif defined(__dsPIC33EP512MU810__)
            #if defined(DSPIC33EP512MU810_PIM)
                #include "HardwareProfile - dsPIC33EP512MU810 PIM.h"
            #elif defined(DSPIC33E_USB_STARTER_KIT)
                #include "HardwareProfile - dsPIC33E USB Starter Kit.h"
            #endif
        #elif defined(__PIC24EP512GU810__)
            #if defined(PIC24EP512GU810_PIM)
                #include "HardwareProfile - PIC24EP512GU810 PIM.h"
            #endif
        #endif
    #endif

    #if defined(__18CXX)
        #if defined(__18F4550)
            #include "HardwareProfile - PICDEM FSUSB.h"
        #elif defined(__18F45K50)
            #include "HardwareProfile - PICDEM FSUSB K50.h"
        #elif defined(__18F87J50)
            #include "HardwareProfile - PIC18F87J50 PIM.h"
        #elif defined(__18F97J94)
            #include "HardwareProfile - PIC18F97J94 PIM.h"
        #elif defined(__18F87J94)
            #include "HardwareProfile - PIC18F87J94 PIM.h"
        #elif defined(__18F14K50)
            #include "HardwareProfile - LPC USB Development Kit - PIC18F14K50.h"
        #elif defined(__18F46J50)
            #if defined(PIC18F_STARTER_KIT_1)
                #include "HardwareProfile - PIC18F Starter Kit 1.h"
            #else
                #include "HardwareProfile - PIC18F46J50 PIM.h"
            #endif
        #elif defined(__18F47J53)
            #include "HardwareProfile - PIC18F47J53 PIM.h"
        #endif
    #endif

    #if defined(_PIC14E)
        #if defined (_16F1459)
    		#include "HardwareProfile - LPC USB Development Kit - PIC16F1459.h"
        #endif
        #if defined (_16LF1459)
    		#include "HardwareProfile - Klondike.h"
        #endif
    #endif
#endif

#endif  //HARDWARE_PROFILE_H
