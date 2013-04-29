klondike
========

Bitcoin ASIC mining board project

WARNING:

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.

SUMMARY:

  This is an open source effort to design and build a Bitcoin mining board based on the Avalon ASIC. The final goal is to have a small 8cm x 10cm board that holds 16 ASIC chips. This board can be controlled via USB or I2C communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Avalon one and the board via USB. The I2C interface allows chaining together more than one board into management by the host system.
    
  
  Each board has a 6 pin PCI Express power connecctor allowing efficient powering of many boards from a decent ATX PSU. A 16 chip board should be capable of 4512 MH/s and consume about 32W power. A low cost Corsair CX-600 PSU should easily power 16 boards using readily available power splitters. This provides for 72 GH/s off one low cost ATX PSU.
  
  

COMING SOON:

  Kicad Schematic and Board files
  
  Parts list with prices
  
  Data sheets and reference materials
  
  MPLAB-X Project and source files
  
  
