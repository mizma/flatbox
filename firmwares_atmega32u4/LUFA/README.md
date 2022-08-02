## LUFA Switch/XInput hybrid Fightstick firmware

This firmware is a direvative of the awesome [LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick) by [CrazyRedMachine](https://github.com/CrazyRedMachine)

## Acknowledgments

This work is a fork of [LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick) by [CrazyRedMachine](https://github.com/CrazyRedMachine) and
is based on [fluffymadness' ATMega32U4-Switch-Fightstick](https://github.com/fluffymadness/ATMega32U4-Switch-Fightstick)
and [bootsector's XInputPadMicro](https://github.com/bootsector/XInputPadMicro), with a QoL features added by CrazyRedMachine.

This fork is customized for the needs of Flatbox-ACR features

* Removed support for analog stick
* reorganized the customization button settings for SOCD and other features
 
## Features

### Gamepad modes

Hold "select" as you plug the controller to make it a Nintendo Switch controller.

Hold "start" as you plug the controller to make it an XInput controller.

Gamepad mode is persistent across plugging and unplugging the controller, so if you don't press anything while plugging the controller, it will stay in the last used mode. 

### DPAD modes

You can switch seamlessly between the 3 stick modes by pressing START+SELECT+(LEFT/UP/RIGHT)

- UP: DPAD 
- LEFT: Fake Left Analog (DPad is mapped to L-Analog)
- RIGHT: Fake Right Analog (DPad is mapped to R-Analog)

DPAD mode is also persistent.

### Real analog support

This function has been removed since Flatbox-ACR has no plans of adding analog inputs

### Simulated home button

This is also removed since we have custom hardware that support home buttons

### SOCD Cleaning

TODO: Somehow, the SOCD configuration feature did not seem to work, so will need to work on some other implementation.  probably only on start up since Flatbox-ACR has dedicated Reset switch.
Also, we don't need this Entire flexibility, so we may stick to some common configurations.

* UP+DOWN=NEUTRAL, LEFT+RIGHT=NEUTRAL (All Neutral SOCD)
* UP+DOWN=UP, LEFT+RIGHT=NEUTRAL (normal Hitbox style SOCD)
* UP+DOWN=UP, LEFT+RIGHT=Last one wins (Gafro-controller style SOCD)

### UP-DOWN inverse

**TODO**

Since Hitbox style dpad is unique in Up/Down key arrangements, it is not very intuitive outside the intended Fighting games.

This configuration allows to swap the Up and Down keys so middle button is Up instead of down to make it a little more manageable in normal games.

## Building Instructions

- Download Arduino IDE, 
- Download the Bounce2 Library inside the Arduino IDE
- Add `https://github.com/CrazyRedMachine/Arduino-Lufa/raw/master/package_arduino-lufa_index.json` as an Additional Board Manager URL (in `File -> Preferences` menu)
- Install LUFA AVR Boards from the Board Manager
- Select Arduino Leonardo (LUFA) as your board type (Pro-Micro is a compatible board to Leonardo)
- Upload the code and Have Fun

## Pinout

Configurable in the .ino

The key config is already setup to match Flatbox-ACR wiring.

```C
/* PINOUT (follows Nintendo naming (X=up, B=down)) */
#define PIN_UP    9
#define PIN_DOWN  7
#define PIN_LEFT  6
#define PIN_RIGHT 8
#define PIN_A     MISO         //XBOX B
#define PIN_B     10           //XBOX A  
#define PIN_X     15           //XBOX Y
#define PIN_Y     MOSI         //XBOX X     
#define PIN_L     21           //XBOX LB
#define PIN_R     19           //XBOX RB
#define PIN_ZL    20           //XBOX LT
#define PIN_ZR    18           //XBOX RT
#define PIN_LS    5            //XBOX LS (left analog click)
#define PIN_RS    3            //XBOX RS (right analog click)
#define PIN_PLUS  1            //XBOX START
#define PIN_MINUS 2            //XBOX BACK
#define PIN_HOME  0
```

## Donation

If this project helped you, please consider going to the original work and donate to the source work ;)