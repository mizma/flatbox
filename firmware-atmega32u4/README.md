This is Arduino code for a USB arcade controller, meant to be used with ATmega32U4-based boards like the Arduino Pro Micro.

It works with Flatbox-ACR [rev1](../hardware-rev1)

## Change Points from [original](https://github.com/jfedor2/flatbox/blob/master/firmware-atmega32u4)

* None

### TODO

* fix SOCD Cleaning code (original code does not work the same as original Hitbox)
    * Implement the N Type SOCD Cleaner (Up+Down=Up, Left+Right=Neutral)
    * Implement P Type as option (Up+Down=Up, Left+Right=Last input wins)
* change to XInput?
    * add support for Switch??

