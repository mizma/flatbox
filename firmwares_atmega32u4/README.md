# ATMEGA32U4 Firmwares

There are currently two firmwares that work with ATMEGA32U4 5V AVR boards (3.3V board are not supported).

Both controllers should work similarly in terms of SOCD cleaning configuration and Up/Down inversion configuration.

## Configuration

All following settings are persistent and will be kept over power cycles.

### Common configuration

* Up/Down inversion
    * Press Up key at start to invert
    * Press Down key at start to set to normal
* SOCD Cleaning mode
    * Hold R3(RS) at start to set to Hitbox mode
    * Hold L3(LS) at start to set to Gafro mode
    * Hold PS(Home) at start to set to NEUTRAL mode (not yet supported on DINPUT firmware)

### LUFA specific configuration

* XInput/Switch setting
    * Hold "Select" at start to set to Switch mode
    * Hold "Start" at start to set to XInput mode
* Directional button mode: press the following buttons and press "Start" + "Select" to switch emulation mode. (This can be done anytime)
    * UP: DPAD 
    * LEFT: Fake Left Analog (DPad is mapped to L-Analog)
    * RIGHT: Fake Right Analog (DPad is mapped to R-Analog)

## [DINPUT](./DINPUT/)

This firmware is based on the original Flatbox firmware and is configured to work as Dinput device.
Simple firmware to work on if you only need Dinput support (Should work as PC Dinput and PS3 controller)

## [LUFA](./LUFA/)

This firmware is based on the [LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick) by [CrazyRedMachine](https://github.com/CrazyRedMachine)
and supports XInput mode and Switch controller mode (gets detected as Pokken Controller).

This firmware can be switched between Xinput (consoles not supported, only PCs) mode and Switch controller mode.
