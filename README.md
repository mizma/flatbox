# Flatbox-ACR: Low profile hitbox-layout fightstick with Acrylic shell

This flatbox design is based on [jfedor2/flatbox](https://github.com/jfedor2/flatbox) but with a few tweaks:

* Replaced the 3D printed case with Acrylic shell, allowing to insert printed artwork.
* modified button layout to
    * Accomodate for the clearance needed for acrylic cutting
    * To mimic the layout of the original Hitbox button layout
* Silk screen update
    * Added small logo
    * added legends for each buttons (SQUARE, CIRCLE etc.)
    * moved logo to edge to minimize see-through when adding artwork on top
* Patter changes
    * GND Fill
    * add vias to join gnd fill
    * moved traces slightly to avoid GND islands and thin GND fills
    * added reset button for Pro Micro board

Final product when assembled will look something like the following:

![Assembled Flatbox](hardware-rev1/images/Flatbox-rev1-finished-product.jpg)

**TODO: replace with actual photo**

There are four major versions of the Flatbox. They all use Kailh low profile (choc v1) mechanical keyboard switches. The table below lists their main features. See the README for each version for details on how to make them.

version | [rev1](hardware-rev1) |
------- | ------------------------- |
case dimensions | 210x123.58x10mm |
compatibility (using provided firmware) | PC, PS3 |
add-on board | Arduino Pro Micro |
onboard chip | - |
port | micro USB or USB-C |
SMT assembly required | no |
firmware | [ATmega32U4](firmware-atmega32u4) |
