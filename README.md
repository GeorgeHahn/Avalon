Avalon
========

Public Domain Bitcoin ASIC Miner Project

Firmware and driver based on Klondike Project

Donations: 14kf3rM66cLMrhR3eXHMjh4B5W5Xko1jJr

![First prototype](https://raw.github.com/GeorgeHahn/Avalon/master/img_angle.JPG)

## SUMMARY

  This is an open source effort to design and build a Bitcoin mining board based on the second generation Avalon ASIC. The final goal is to have a small board that holds 10 ASIC chips. This board can be controlled via USB communication. An example host would be a PC, Raspberry Pi or TP-Link WR703N router. The host will run cgminer with a custom driver based on the Klondike one and control the board via USB.
    
  
  A 10 chip board should be capable of 15000 MH/s and consume about 30W of power. Alternatively, the switching power supply onboard can be turned to a lower voltage, trading hashrate for power efficiency. The supply is variable from 0.700V to 1.708V. Each board can be easily powered by a low cost power adapter, like [this](http://www.amazon.com/gp/product/B005IUV60U/ref=as_li_ss_il?ie=UTF8&camp=1789&creative=390957&creativeASIN=B005IUV60U&linkCode=as2&tag=generi0c-20).
  
  
  Power for this board is supplied via a barrel jack connector (2.5mm ID, 5.5mm OD). For future revisions, Molex PCI-e or 4 pin power connectors may be added. Another limit on the first revision design is the data connection - these boards are USB only for now. In the future, CAN may be added to make it possible to chain multiple miners together.
  
  The design is currently in Cadence OrCAD + Allegro format, but will be completely backported to [Upverter](https://upverter.com/GeorgeHahn/0bb015271a32ca8e/Avalon/) once tested.

## STATUS

 - ☑ Layout
 - ▢ Prototype
  - ☑ PCB - First prototype has arrived
  - ☑ Stencil
  - ☑ Parts
  - ☑ Assembly
  - ▢ Debug first prototype - in progress
  
 - ▢ Initial firmware
  - ▢ Port Klondike firmware to PIC18F45K50
  - ▢ Testing with a Raspberry Pi
  - ▢ Tune settings for unique SMPS

 - ▢ Future
  - ▢ Try a prototype with metal substrate board (for better heat dissipation)
  - ▢ Measure current on 3.3v and 5v rails; switch to switching regulators if current is significant


## [SCHEMATIC](https://raw.github.com/GeorgeHahn/Avalon/master/hardware/Schematic.pdf) / [LAYOUT](https://github.com/GeorgeHahn/Avalon/tree/master/hardware/allegro/gerbers)
![First prototype](https://raw.github.com/GeorgeHahn/Avalon/master/img_top.JPG)

## [ISSUES](https://github.com/GeorgeHahn/Avalon/issues)
First prototype has the following issues. Serious issues are bolded, optional improvements are italicized.

 - ▢ [#2](https://github.com/GeorgeHahn/Avalon/issues/2) **Switching FET (U21) has an incorrect footprint**
 - ▢ [#3](https://github.com/GeorgeHahn/Avalon/issues/3) **D1 and Q1 have suboptimal footprints**
 - ▢ [#4](https://github.com/GeorgeHahn/Avalon/issues/4) **C1 and C2 have incorrectly sized footprints**
 - ☑ [#5](https://github.com/GeorgeHahn/Avalon/issues/5) **Ground for some pins on U5 are not connected**
 - ▢ [#6](https://github.com/GeorgeHahn/Avalon/issues/6) Vcore SMPS overvoltage level should be set to A3255 maximum voltage (set by R3)
 - ☑ [#7](https://github.com/GeorgeHahn/Avalon/issues/7) Via-in-pads can be eliminated
 - ☑ [#8](https://github.com/GeorgeHahn/Avalon/issues/8) Status LEDs and D1 don't have polarity indicators on silkscreen
 - ▢ [#9](https://github.com/GeorgeHahn/Avalon/issues/9) Some parts are missing silkscreen reference designators
 - ☑ [#10](https://github.com/GeorgeHahn/Avalon/issues/10) The 3.3v regulator should take 5v input rather than VIN or be switched to a regulator that can handle higher input voltage
 - ▢ [#11](https://github.com/GeorgeHahn/Avalon/issues/11) *Barrel jack is a through hole part, should be switched to SMT*
 - ▢ [#12](https://github.com/GeorgeHahn/Avalon/issues/12) *Should have more input capacitors*
 - ▢ [#13](https://github.com/GeorgeHahn/Avalon/issues/13) *Should switch away from micro USB connectors for improved durability*
 - ☑ *Location for C2, C25-27, C15 is suboptimal*


## WARNINGS

  This project has an advanced switched mode power supply that can supply between 0.700V and 1.708V. NEVER set the SMPS above the Avalon ASICs' rated maximum voltage.

  This project is incomplete and in progress. There may be errors, mistakes, incomplete portions at this time. Do NOT use these project files to order circuit boards until they have been finished and confirmed to work.
  
  See LICENSE and COPYING files for terms and warranty disclaimer.
  
  See RELEASE NOTES for known problems, and issues.

## THANKS

Special thanks to [CUI Inc](http://www.cui.com/) for going the extra mile to get me a sample of their PJ-037BH connector. Thanks to TI for samples of ICs used in the SMPS module. Thanks to AVX for samples of the SMPS output capacitors.

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/GeorgeHahn/avalon/trend.png)](https://bitdeli.com/free "Bitdeli Badge")
