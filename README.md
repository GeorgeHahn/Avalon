klondike
========

Bitcoin ASIC Miner Project

WARNING:

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.
  
  See LICENSE and COPYING files for terms and warranty disclaimer.
  
  See RELEASE NOTES for known problems, and issues.
  
SUMMARY:

  This is an open source effort to design and build a Bitcoin mining board based on the Avalon ASIC. The final goal is to have a small 10cm x 10cm board that holds 16 ASIC chips. This board can be controlled via USB or I2C communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Avalon one and control the board via USB. The I2C interface allows chaining together more than one board consolidating control by the host system using only one USB connection.
    
  
  Each board has a 6 pin PCI Express power connector allowing efficient powering of many boards from an ATX PSU. A 16 chip board should be capable of 4512 MH/s and consume about 32W power. A low cost Corsair CX-600 PSU should easily power 16 boards using readily available power splitters. This provides for 72 GH/s off one low cost ATX PSU.
  
STATUS:

  This project is under active development. 
  
  Firmware has been developed and now released under the terms of the GPLv3 license.
  
  A new cgminer-klondike repo has been created for development with only changed files echoed here in the cgminer directory.
  
  The first prototype board indicated several areas for improvement and a second "Final Beta" is being produced to test full functionality.
  
  The cgminer-klondike driver and firmware have both been tested working, but need additional refinement and bug fixes to be ready for general release.
  
  
TODO:

  Bootloader firmware allowing updating via USB/I2C connection.

  Integration and debugging of I2C chaining firmware.

  Creating firmware configurations for K1, K16 and K64 that optimize code.
 
  Set up HEXMATE scripting to insert serial# for supporting I2C arbitration.

  Testing with a TL-WR703N router containing purpose built OpenWrt firmware.

  Stress testing and reliability in over-clocking situations.
  
  

  
  
