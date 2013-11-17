/********************************************************************
 FileName:      HardwareProfile - Klondike.h
 Dependencies:  See INCLUDES section
 Processor:     PIC16LF145x USB Microcontrollers
 Hardware:      Klondike
 Compiler:      Microchip XC8
 Company:       Klondike Systems.

********************************************************************/

    #define USE_INTERNAL_OSC  

    #if (__XC8_VERSION == 1000)
        #define ACTCON  CRCON   //Compiler workaround, definition was missing in 1.0 release header
    #endif
    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO	
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #if defined(USE_SELF_POWER_SENSE_IO)
    #define self_power          PORTAbits.RA2
    #else
    #define self_power          1
    #endif

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISAbits.TRISA1    // Input
    #if defined(USE_USB_BUS_SENSE_IO)
    #define USB_BUS_SENSE       PORTAbits.RA1
    #else
    #define USB_BUS_SENSE       1
    #endif

    
