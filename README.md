# PicoCalc "southbridge" custom BIOS

This is my personnal rewrite of the [original](https://github.com/clockworkpi/PicoCalc/tree/master/Code/picocalc_keyboard)
PicoCalc STM32F103R8T6 firmware.

## Features differences
The main differences with the original firmware are the followings:

- drastic reduction in the STM32's electricity consumption when running (~3.5 mA),
- clean up (by removing stm32duino dependencies, use STM32HAL instead, maybe I'll switch to libopencm3 someday...) to reduce binary size (~25 KB) and allow more features to be implemented,
- added configuration saving solution (using internal flash, including backlight option),
- new I2C registers to access extended features (pico I2C driver updated to handle this version along with official),
- interrupt event output to pico board can be configured during runtime (for keyboard event or RTC alarm),
- rewriten or added some debug UART interface message (only when compiled in DEBUG release type),
- internal RTC access through dedicated I2C registers,
- auto wake-up using RTC (WIP),
- Pico reset using power button (Shift + short press on PWR button),
- lighten AXP2101 PMIC driver (based on X-PowersLib).

## Tools version

- ARM GNU GCC: 14.3-rel1_arm-none-eabi

## Compile
This source code can be compiled using ARM gcc toolchain in path and using make program.

```
git clone --recurse-submodules https://git.jcsmith.fr/jackcartersmith/picocalc_BIOS.git
cd picocalc_BIOS
make -j
```

## Programming

1. Unplug the picocalc and disconnect the batteries.
2. Open the picocalc to access the DIP switch (SW701), put the 1 pin to ON.
3. Connect the USB from the motherboard to the computer and press the power button.
4. Open STM32CubeProgrammer, look for the UART access and connect.
5. Use the compiled .bin/.elf firmware in the build folder and flash it on the STM32.
6. Put the 1 pin of SW701 to OFF.
7. Power reset everything like step 1.

## TODO
- Add a Pico test program for registers/features implemented
- add few wiki page to detail the I2C protocol, added features, etc.

## Important notes
The current implementation of this firmware is subject to change until the v1 release.

Some features can be unstable or buggy and are marked as pre-release. A test program will be developped soon to provide some regression testing.

The permanent settings (EEPROM) save can be broken between 0.x version, it is recommanded to make a full flash erase before updating, as 
EEPROM configuration survives update.

## Credits
- STM32-HAL: [link](https://github.com/STMicroelectronics/stm32f1xx-hal-driver)
- STM32-CMSIS: [link](https://github.com/STMicroelectronics/cmsis-device-f1)
- X-PowersLib: [link](https://github.com/lewisxhe/XPowersLib)
- Emulated EEPROM: [link](https://github.com/ScorpionX5/STM32F1XX-EEPROM-Emulation-Library/tree/master/V2.0)
