This is Arduino code for a USB arcade controller, meant to be used with ATmega32U4-based boards like the Arduino Pro Micro.

It works with Flatbox-ACR [rev1.1](../hardware-rev1.1)

## Change Points from [original](https://github.com/jfedor2/flatbox/blob/master/firmware-atmega32u4)

* Implemented SOCD Cleaner with selection of Hitbox style and Gafro-Controller style cleaning
    * Hold R3 when connecting to set to Hitbox Style SOCD Cleaner
    * Hold L3 when connecting to set to Gafro-controller style SOCD Cleaner
    * Hold PS when connecting to set to All Neutral SOCD Cleaner
    * Settings are saved in EEPROM so it will not change after power cycle
* Implement Up/Down Inversion (for playing normal arcade games)
    * Hold DOWN to set to Hitbox style
    * Hold UP to invert Up and Down buttons.
    * Settings are saved in EEPROM

## How to Install

### Using Arduino IDE (Only for the first time you flash the board.)

You can use the Arduino IDE to flash the firmware, but this is somewhat convoluted since you need
to time your board reset to the Arduino IDEs flash timing (Arduino doesn't allow you to just flash .hex files,
and insist that flashing happen with a compile process)

1. Load the .ino file in Arduino IDE
2. In board selection, select Sparkfun ProMicro, or some other ProMicro that you chose.
3. In Processor selection, select the appropriate processor (ATMega32U4 3.3V or 5V)
4. Press the button on top left (the → button)
5. When you see Flashing Board or some message, double-click the SW_RST1 button on the Flatbox-ACR
    * Pressing Reset is not necessary for the very first time you flash a board.
    * For re-flashing a board already flashed with HID type firmware, I recommend using QMKToolbox as described below.

### Using [QMKToolbox](https://github.com/qmk/qmk_toolbox)

You can use QMKToolbox to write the .hex files which is easier for timing the write process.

1. Prepare the .hex file to flash (you can use the one included in the repository)
2. Install QMKToolbox
3. from QMKToolbox tools menu, select Install Drivers (only needed first time)
4. OPEN the hex file you prepared in 1.
5. select ATMega32U4 from dropdown (below "MCU AVR Only")
6. double click the SW_RST1 switch on the Flatbox-ACR board and wait to see the yellow text
   saying "Caterina device connected (usbser)"
7. Right after you see the above message, click on Flash button.
8. If you see "Flash Complete" you are done.

#### To make your own .hex file

1. To obtain the .hex file, use the Arduino IDE and press verify.
2. after verify is complete, navigate to "%LOCALAPPDATA%\Temp\arduino_build_XXXXXXX" (XXXXXX is a random number)
3. Find the .hex file inside the folder and copy to some location that is easy to find.
4. Use QMKToolbox to flash the .hex file as explained above.
