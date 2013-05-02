klondike
========

Bitcoin ASIC mining board project

WARNING:

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.
  
SUMMARY:

  This is an open source effort to design and build a Bitcoin mining board based on the Avalon ASIC. The final goal is to have a small 10cm x 10cm board that holds 16 ASIC chips. This board can be controlled via USB or I2C communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Avalon one and the board via USB. The I2C interface allows chaining together more than one board consolidating control by the host system using only one USB connection.
    
  
  Each board has a 6 pin PCI Express power connecctor allowing efficient powering of many boards from a decent ATX PSU. A 16 chip board should be capable of 4512 MH/s and consume about 32W power. A low cost Corsair CX-600 PSU should easily power 16 boards using readily available power splitters. This provides for 72 GH/s off one low cost ATX PSU.
  
STATUS:

  I've completed the conversion from Eagle to Kicad and bumped the board up to 4 layers. The schematic is mostly done and I'm just waiting on Avalon documentation for final chip I/O connections. 
  
  On board layout the power supply is mostly done and I just need to add some ground planes. The PIC, USB and fan control parts are done. Next I'll add 3.3V supply connections on the second layer, clock routing and the GND planes on the bottom layer and under the power supplies. This should leave just data routing on the third layer to complete - pending documentation.
  
  After this and while waiting for Avalon docs I'll set up the PIC firmware project and start putting down some code outlines.
  
COMING SOON:

  Kicad Schematic and Board files
  
  MPLAB-X Project and source files
  
  
