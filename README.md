Avalon
========

Public Domain Bitcoin ASIC Miner Project

Firmware and driver based on Klondike Project
  
## SUMMARY

  This is an open source effort to design and build a Bitcoin mining board based on the second generation Avalon ASIC. The final goal is to have a small board that holds 10 ASIC chips. This board can be controlled via USB communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Avalon one and control the board via USB.
    
  
  Each board has a barrel jack power connector. A 10 chip board should be capable of 15000 MH/s and consume about 30W power. Alternatively, the switching power supply onboard can be turned to a lower voltage, trading hashrate for power efficiency. The supply is variable from 0.700V to 1.708V. Each board can be easily powered by a low cost power adapter. In production quantities, this board should cost under $60, depending on the cost of second-gen Avalon chips. This gives it a price per performance ration of $4/GH.
  
## STATUS

  This project is under active development. 
  
  Firmware has been developed and now released under the terms of the GPLv3 license.
  
  A new cgminer-klondike repo has been created for development with only changed files echoed here in the cgminer directory.
  
  The first prototype should be ready for order within the week. The power supply prototype has already been ordered.
  
  The cgminer-klondike driver and firmware have both been tested working, but need additional refinement and bug fixes to be ready for general release.
  
  
## TODO

 - Finish hardware design.

 - Adapt firmware for alternate microprocessor

 - Testing with a Raspberry Pi

 - Stress testing and reliability in over-clocking and under-clocking situations.
  
## WARNING

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.
  
  See LICENSE and COPYING files for terms and warranty disclaimer.
  
  See RELEASE NOTES for known problems, and issues.
