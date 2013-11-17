Avalon
========

Public Domain Bitcoin ASIC Miner Project

Firmware and driver based on Klondike Project
  
## SUMMARY

  This is an open source effort to design and build a Bitcoin mining board based on the second generation Avalon ASIC. The final goal is to have a small board that holds 10 ASIC chips. This board can be controlled via USB communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Avalon one and control the board via USB.
    
  
  Each board has a barrel jack power connector. A 10 chip board should be capable of 15000 MH/s and consume about 30W power. Alternatively, the switching power supply onboard can be turned to a lower voltage, trading hashrate for power efficiency. The supply is variable from 0.700V to 1.708V. Each board can be easily powered by a low cost power adapter.
  
  
  Power for this board is supplied via a barrel jack connector (2.5mm ID, 5.5mm OD). For future revisions, Molex PCI-e or 4 pin power connectors may be added. Another limit on the first revision design is the data connection - these boards are USB only for now. In the future, CAN may be added to make it possible to chain multiple miners together.
  
  The design is currently in Cadence OrCAD + Allegro format, but will be completely backported to [Upverter](https://upverter.com/GeorgeHahn/0bb015271a32ca8e/Avalon/) once tested.
  
## STATUS

 - ☑ Layout
 - ▢ Prototype
  - ▢ PCB - Ordered, waiting on arrival
  - ☑ Stencil
  - ▢ Parts - Ordered, waiting on arrival
  - ▢ Assembly  - Will commence when PCBs arrive on Tuesday 11/19.
  
 - ▢ Initial firmware
  - ▢ Port Klondike firmware to PIC18F45K50
  - ▢ Testing with a Raspberry Pi
  - ▢ Tune settings for unique SMPS

 - ▢ Future
  - ▢ Try a prototype with metal substrate board (for better heat dissipation)
  
## WARNINGS

  This project has an advanced switched mode power supply that can supply between 0.700V and 1.708V. NEVER set the SMPS above the Avalon ASICs' rated maximum voltage.

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.
  
  See LICENSE and COPYING files for terms and warranty disclaimer.
  
  See RELEASE NOTES for known problems, and issues.

## THANKS

Special thanks to [CUI Inc](http://www.cui.com/) for going the extra mile to get me a sample of their PJ-037BH connector. Additional thanks to TI for samples of ICs used in the SMPS module.
