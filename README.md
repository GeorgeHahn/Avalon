klondike
========

Bitcoin ASIC mining board project

WARNING:

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.
  
SUMMARY:

  This is an open source effort to design and build a Bitcoin mining board based on the Avalon ASIC. The final goal is to have a small 10cm x 10cm board that holds 16 ASIC chips. This board can be controlled via USB or I2C communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Avalon one and control the board via USB. The I2C interface allows chaining together more than one board consolidating control by the host system using only one USB connection.
    
  
  Each board has a 6 pin PCI Express power connector allowing efficient powering of many boards from an ATX PSU. A 16 chip board should be capable of 4512 MH/s and consume about 32W power. A low cost Corsair CX-600 PSU should easily power 16 boards using readily available power splitters. This provides for 72 GH/s off one low cost ATX PSU.
  
STATUS:

  The PCB routing is currently done and I'm making small changes to tidy up, improve and double check the design while waiting on the Avalon communication protocol docs. After they come out I'll finalize any changes and order first prototype boards. During the waiting period for boards to arrive I'll be coding / debugging the firmware and hope to have something workable to program into a test board when it arrives.
  
COMING SOME DAY:

  Kicad Schematic and Board files
  
  MPLAB-X Project and source files
  
  
