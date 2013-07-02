klondike
========

Bitcoin ASIC Miner Project

WARNING:

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.
  
  See LICENSE and COPYING files for terms and warranty disclaimer.
  
  See RELEASE notes for known problems, and issues.
  
SUMMARY:

  This is an open source effort to design and build a Bitcoin mining board based on the Avalon ASIC. The final goal is to have a small 10cm x 10cm board that holds 16 ASIC chips. This board can be controlled via USB or I2C communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Avalon one and control the board via USB. The I2C interface allows chaining together more than one board consolidating control by the host system using only one USB connection.
    
  
  Each board has a 6 pin PCI Express power connector allowing efficient powering of many boards from an ATX PSU. A 16 chip board should be capable of 4512 MH/s and consume about 32W power. A low cost Corsair CX-600 PSU should easily power 16 boards using readily available power splitters. This provides for 72 GH/s off one low cost ATX PSU.
  
STATUS:

  This project is under active development. Some circuit boards have been ordered and/or arrived for testing.
  Some prototyping has been completed to verify some aspects of the design and develop firmware.
  ASIC communication works and more work i sunderway to improve reliability.
  Firmware has been developed and now released under the terms of the GPLv3 license.
  A new cgminer-klondike repo has been created for development with only changed files echoed here in cgminer directory.
  An initial cgminer driver release has been pushed for testing.
  
TODO:

  More hardware testing  including ASIC communication, chaining and overall board operation.

  Testing and debugging I2C chaining firmware.

  Creating firmware configurations for K1 and K64 that optimize code.

  Combined USB / I2C bootloader firmware.
  
  Set up HEXMATE scripting to insert serial# for supporting I2C arbitration.

  Write cgminer driver and support for other host miner software.

  Integrate cgminer into the repository properly for ARM cross compiling as right now it's not forked.

  Testing cgminer with driver on a Raspberry Pi for a low-cost, low-power platform.

  Testing with a TL-WR703N router containing purpose built OpenWrt firmware.

  Stress testing and reliability in over-clocking situations.
  
  

  
  
