Release Notes

July 23, 2013 - K1 Board Revised - v0.3.0 - Final Beta

The "Final Beta" Revision of K1 has been pushed up to GitHub.

- **Added Dual NOR gate and Inverters from testing on K16 to improve result capture.**
- Changed PIC to use QFN version.
- **Added 2mm holes for fastening heat sink.**
- Made both LEDs flashable under software control for better blinkies.
- **Added thermistor for sensing temperature.**
- **Added another PIC decoupling capacitor.**
- **Fixed issues with buck regulator traces.**
- I2C chain conn. now non-thru hole pads - fits 3 pin header.
- **Added ferrite beads to ASIC power and USB signals.**

July 15, 2013 - K16 Board Revised - v0.3.0 - Final testing

- **Dual NOR gate replaces Single NOR gate**
- **Inverters added before PIC on result data, clk**
- **Schottky Diode added across Fan terminals**
- **1K resistor added to pull down FET gate**
- **Ferrite beads added to AVDD on ASIC PLL supply**
- **Ferrite beads added to USB D+/D-/GND and shield to GND**
- **moved PIC decoupling capacitor to be closer to PIC**
- **added 2 more decoupling capacitors near PIC and inverters**
- added NPTh for PICe connector to support horizontal version
- Phoenix 2 pin power connector removed
- new logo added (thanks Laserhorse!)
- **moved thermistor to between U7,U8**
- moved large input capacitors a little for better PCIe clearance
- small edits to clean up traces here and there
- repositioned a few parts
- footprints verified and updated against data sheets

June 14, 2013 - Original Release - 0.1.0

The kicad files originated from Eagle CAD files through a conversion. This has caused some weird side effects that make the schematic a nuisance to work with. The parts co-ordinates were placed on a 1 mil grid during conversion making them both very small and very difficult to edit. You must always choose the 1 mil grid option if you hope to do any editing of the wires and parts and even then it's difficult. 

My recommendation: if you ever find yourself using Eagle and wanting to use Kicad - start over fresh, do not convert. I would not have used less than a 10 mil grid and would have used several pages instead of one large one. But here it is, painful glory, and all. I planned to revamp it all later, and maybe that will get done but not in time for this rushed initial release.

One part is known to be missing here from the original Avalon design. That is the ferrite beads on the AVDD power line to each chip. This was missed by me when viewing the Avalon reference docs and the first version of the PCB does not have them. So we'll see if they are absolutely required, or just precautionary niceties to ensure better EMI behaviour.

The Klondike firmware was developed using Microchips MPLAB-X IDE 1.7 under Ubuntu 12.04 (Linux) with the XC-8 Compiler 1.12, PRO trial mode enabled.

It cannot be compiled in FREE mode as, with super-lousy code generation and the massive bloat it creates, it will not fit in the 8K code space available.

At the time of current testing, incomplete, the code uses 5595 code space (8192 max) and 816 data space (1024 max).

The ktest utility is very rudimentary but provides a way to feed the klondike until a driver for cgminer is written. It will be enhanced to allow feeding actual test midstate and merkle data.

