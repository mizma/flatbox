# 1 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
# 2 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 3 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 4 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2

# 6 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 7 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 8 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2


# 9 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
/* in case you want to disable one type of gamepad */
//#define DISABLE_NSWITCH
//#define DISABLE_XINPUT

//use real analog sticks
//#define WITH_ANALOG
//#define DEADZONE     50

// Enable on-the-fly SOCD config. If disabled, it'll lock in
// the default configuration but still use the SOCD resolution code.


//make it so holding start+select triggers the HOME button
//#define HOME_HOTKEY
//delay in ms for start+select to become HOME in HOME_HOTKEY mode


/* PINOUT (follows Nintendo naming (X=up, B=down)) */
# 68 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
/* Buttons declarations */

unsigned long startAndSelTime = 0;
unsigned long currTime = 0;

byte internalButtonStatus[4];

Bounce joystickUP = Bounce();
Bounce joystickDOWN = Bounce();
Bounce joystickLEFT = Bounce();
Bounce joystickRIGHT = Bounce();
Bounce buttonA = Bounce();
Bounce buttonB = Bounce();
Bounce buttonX = Bounce();
Bounce buttonY = Bounce();
Bounce buttonL = Bounce();
Bounce buttonR = Bounce();
Bounce buttonZL = Bounce();
Bounce buttonZR = Bounce();
Bounce buttonLS = Bounce();
Bounce buttonRS = Bounce();
Bounce buttonPLUS = Bounce();
Bounce buttonMINUS = Bounce();
Bounce buttonHOME = Bounce();

/* MODE DECLARATIONS */
typedef enum {
  RIGHT_ANALOG_MODE,
  ANALOG_MODE,
  DIGITAL,
} State_t;
State_t state;

typedef enum {
  NEUTRAL, // LEFT/UP + DOWN/RIGHT = NEUTRAL
  NEGATIVE, // LEFT/UP beats DOWN/RIGHT
  POSITIVE, // DOWN/RIGHT beats LEFT/UP
  LAST_INPUT, //Last input has priority; not a valid state if being used for initial_input
} Socd_t;
Socd_t x_socd_type = NEUTRAL; // controls left/right and up/down resolution type
Socd_t y_socd_type = NEGATIVE;
Socd_t x_initial_input, y_initial_input = NEUTRAL;

/* mode selectors */
bool xinput;
bool modeChanged;

void checkModeChange() {
  if (buttonStatus[12] && buttonStatus[13])
  {

    if (buttonStatus[18] && buttonStatus[19])
    {
      if (!modeChanged)
      {
        // read inputs at time of press
        bool up = !joystickUP.read();
        bool down = !joystickDOWN.read();
        bool left = !joystickLEFT.read();
        bool right = !joystickRIGHT.read();

        if (up && down)
          y_socd_type = LAST_INPUT;
        else if (up)
          y_socd_type = NEGATIVE;
        else if (down)
          y_socd_type = POSITIVE;
        else if (!up && !down)
          y_socd_type = NEUTRAL;

        if (left && right)
          x_socd_type = LAST_INPUT;
        else if (left)
          x_socd_type = NEGATIVE;
        else if (right)
          x_socd_type = POSITIVE;
        else if (!left && !right)
          x_socd_type = NEUTRAL;

        EEPROM.put(4, x_socd_type);
        EEPROM.put(6, y_socd_type);
        modeChanged = true;
      }
    }
    else

    if ( !modeChanged )
    {
        bool need_update = true;
        if (internalButtonStatus[2])
          state = ANALOG_MODE;
        else if (internalButtonStatus[3])
          state = RIGHT_ANALOG_MODE;
        else if (internalButtonStatus[0])
          state = DIGITAL;
        else need_update = false;

        if (need_update) EEPROM.put(0, state);
        modeChanged = true;
    }
    else
    {
      modeChanged = false;
    }
  }
}

void setupPins() {
  joystickUP.attach(9, 0x2);
  joystickDOWN.attach(7, 0x2);
  joystickLEFT.attach(6, 0x2);
  joystickRIGHT.attach(8, 0x2);
  buttonA.attach(MISO /*XBOX B*/, 0x2); // XBOX B
  buttonB.attach(10 /*XBOX A  */, 0x2); // XBOX A
  buttonX.attach(15 /*XBOX Y*/, 0x2); // XBOX Y
  buttonY.attach(MOSI /*XBOX X     */, 0x2); // XBOX X
  buttonL.attach(21 /*XBOX LB*/, 0x2); // XBOX LB
  buttonR.attach(19 /*XBOX RB*/, 0x2); // XBOX RB
  buttonZL.attach(20 /*XBOX LT*/, 0x2); // XBOX LT
  buttonZR.attach(18 /*XBOX RT*/, 0x2); // XBOX RT
  buttonLS.attach(5 /*XBOX LS (left analog click)*/, 0x2); // XBOX LS
  buttonRS.attach(3 /*XBOX RS (right analog click)*/, 0x2); // XBOX RS
  buttonPLUS.attach(1 /*XBOX START*/, 0x2); // XBOX START
  buttonMINUS.attach(2 /*XBOX BACK*/, 0x2); // XBOX BACK
  buttonHOME.attach(0, 0x2);

  joystickUP.interval(1 /*Debounce time in milliseconds*/);
  joystickDOWN.interval(1 /*Debounce time in milliseconds*/);
  joystickLEFT.interval(1 /*Debounce time in milliseconds*/);
  joystickRIGHT.interval(1 /*Debounce time in milliseconds*/);
  buttonA.interval(1 /*Debounce time in milliseconds*/);
  buttonB.interval(1 /*Debounce time in milliseconds*/);
  buttonX.interval(1 /*Debounce time in milliseconds*/);
  buttonY.interval(1 /*Debounce time in milliseconds*/);
  buttonL.interval(1 /*Debounce time in milliseconds*/);
  buttonR.interval(1 /*Debounce time in milliseconds*/);
  buttonZL.interval(1 /*Debounce time in milliseconds*/);
  buttonZR.interval(1 /*Debounce time in milliseconds*/);
  buttonLS.interval(1 /*Debounce time in milliseconds*/);
  buttonRS.interval(1 /*Debounce time in milliseconds*/);
  buttonPLUS.interval(1 /*Debounce time in milliseconds*/);
  buttonMINUS.interval(1 /*Debounce time in milliseconds*/);
  buttonHOME.interval(1 /*Debounce time in milliseconds*/);
}

void setup() {

  modeChanged = false;
  EEPROM.get(0, state);
  EEPROM.get(2, xinput);

  EEPROM.get(4, x_socd_type);
  EEPROM.get(6, y_socd_type);

  setupPins();
  delay(500);
# 235 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
  /* set xinput mode according to held button */
  // if select is held on boot, NSWitch mode
  int value = digitalRead(2 /*XBOX BACK*/);
  if (value == 0x0)
  {
    xinput = false;
    EEPROM.put(2, xinput);
  }
  // if start is held on boot, XInput mode
  else {
    value = digitalRead(1 /*XBOX START*/);
    if (value == 0x0)
    {
      xinput = true;
      EEPROM.put(2, xinput);
    }
  }
# 280 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
  SetupHardware(xinput);
  GlobalInterruptEnable();
}


void loop() {
  currTime = millis();



  buttonRead();
  checkModeChange();
  convert_dpad();
  send_pad_state();
}
# 397 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
void convert_dpad() {
  byte cleanButtonStatus[4] = {0};
  // Prevent SOCD inputs (left+right or up+down) from making it to the logic below.
  clean_all_socd(internalButtonStatus, cleanButtonStatus, x_socd_type, y_socd_type);
# 411 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
  switch (state)
  {
    case DIGITAL:
      buttonStatus[14] = 128;
      buttonStatus[15] = 128;
      buttonStatus[16] = 128;
      buttonStatus[17] = 128;
      buttonStatus[0] = cleanButtonStatus[0];
      buttonStatus[1] = cleanButtonStatus[1];
      buttonStatus[2] = cleanButtonStatus[2];
      buttonStatus[3] = cleanButtonStatus[3];
      break;

    case RIGHT_ANALOG_MODE:
      buttonStatus[14] = 128;
      buttonStatus[15] = 128;
      buttonStatus[0] = 0;
      buttonStatus[1] = 0;
      buttonStatus[2] = 0;
      buttonStatus[3] = 0;

      if ((cleanButtonStatus[0]) && (cleanButtonStatus[3])) {
        buttonStatus[17] = 0;
        buttonStatus[16] = 255;
      }
      else if ((cleanButtonStatus[0]) && (cleanButtonStatus[2])) {
        buttonStatus[17] = 0;
        buttonStatus[16] = 0;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[3])) {
        buttonStatus[17] = 255;
        buttonStatus[16] = 255;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[2])) {
        buttonStatus[17] = 255;
        buttonStatus[16] = 0;
      }
      else if (cleanButtonStatus[0]) {
        buttonStatus[17] = 0;
        buttonStatus[16] = 128;
      }
      else if (cleanButtonStatus[1]) {
        buttonStatus[17] = 255;
        buttonStatus[16] = 128;
      }
      else if (cleanButtonStatus[2]) {
        buttonStatus[16] = 0;
        buttonStatus[17] = 128;
      }
      else if (cleanButtonStatus[3]) {
        buttonStatus[16] = 255;
        buttonStatus[17] = 128;
      }
      else {
        buttonStatus[16] = 128;
        buttonStatus[17] = 128;
      }

      break;

    case ANALOG_MODE:
    /* fallthrough */
    default:
      buttonStatus[16] = 128;
      buttonStatus[17] = 128;
      buttonStatus[0] = 0;
      buttonStatus[1] = 0;
      buttonStatus[2] = 0;
      buttonStatus[3] = 0;

      if ((cleanButtonStatus[0]) && (cleanButtonStatus[3])) {
        buttonStatus[15] = 0;
        buttonStatus[14] = 255;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[3])) {
        buttonStatus[15] = 255;
        buttonStatus[14] = 255;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[2])) {
        buttonStatus[15] = 255;
        buttonStatus[14] = 0;
      }
      else if ((cleanButtonStatus[0]) && (cleanButtonStatus[2])) {
        buttonStatus[15] = 0;
        buttonStatus[14] = 0;
      }
      else if (cleanButtonStatus[0]) {
        buttonStatus[15] = 0;
        buttonStatus[14] = 128;
      }
      else if (cleanButtonStatus[1]) {
        buttonStatus[15] = 255;
        buttonStatus[14] = 128;
      }
      else if (cleanButtonStatus[2]) {
        buttonStatus[14] = 0;
        buttonStatus[15] = 128;
      }
      else if (cleanButtonStatus[3]) {
        buttonStatus[14] = 255;
        buttonStatus[15] = 128;
      }
      else {
        buttonStatus[14] = 128;
        buttonStatus[15] = 128;
      }

      break;


  }
}

void buttonRead()
{
  // for SOCD cleaning to work properly we need directions to update
  // on any change instead of on fall
  joystickUP.update(); joystickDOWN.update(); joystickLEFT.update(); joystickRIGHT.update();
  if (joystickUP.changed() || joystickDOWN.changed() || joystickLEFT.changed() || joystickRIGHT.changed())
  {
    internalButtonStatus[0] = !joystickUP.read();
    internalButtonStatus[1] = !joystickDOWN.read();
    internalButtonStatus[2] = !joystickLEFT.read();
    internalButtonStatus[3] = !joystickRIGHT.read();
  }
  if (buttonA.update()) {
    buttonStatus[4] = buttonA.fell();
  }
  if (buttonB.update()) {
    buttonStatus[5] = buttonB.fell();
  }
  if (buttonX.update()) {
    buttonStatus[6] = buttonX.fell();
  }
  if (buttonY.update()) {
    buttonStatus[7] = buttonY.fell();
  }
  if (buttonL.update()) {
    buttonStatus[8] = buttonL.fell();
  }
  if (buttonR.update()) {
    buttonStatus[9] = buttonR.fell();
  }
  if (buttonZL.update()) {
    buttonStatus[10] = buttonZL.fell();
  }
  if (buttonZR.update()) {
    buttonStatus[11] = buttonZR.fell();
  }
  if (buttonLS.update()) {
    buttonStatus[18] = buttonLS.fell();
  }
  if (buttonRS.update()) {
    buttonStatus[19] = buttonRS.fell();
  }
  if (buttonPLUS.update()) {
    buttonStatus[12] = buttonPLUS.fell();
  }
  if (buttonMINUS.update()) {
    buttonStatus[13] = buttonMINUS.fell();
  }
  if (buttonHOME.update()) {
    buttonStatus[20] = buttonHOME.fell();
  }
# 589 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
}


void clean_all_socd(byte *internalButtonStatus, byte *cleanButtonStatus, Socd_t x_socd_type, Socd_t y_socd_type)
{
  clean_socd(internalButtonStatus[2], &cleanButtonStatus[2], internalButtonStatus[3], &cleanButtonStatus[3], x_socd_type, &x_initial_input);
  clean_socd(internalButtonStatus[0], &cleanButtonStatus[0], internalButtonStatus[1], &cleanButtonStatus[1], y_socd_type, &y_initial_input);
}
/**

   Cleans the given (possible) simultaneous opposite cardinal direction inputs according to the preferences provided.



   @note Given two simultaneous opposite cardinal direction inputs, clean_socd will

   make sure that both are not actually sent. The method used to resolve this conflict

   is determined by input_priority. The x (LEFT/RIGHT) and y (UP/DOWN) axes can be

   handled with the same logic as long as the negative and positive inputs are correctly

   arranged, so pointers are used to make the same function handle both.



   @param[in] negative_in The LEFT/UP input variable.

   @param[out] negative_out The LEFT/UP resulting value.

   @param[in] positive_in  The DOWN/RIGHT input variable.

   @param[out] positive_out  The DOWN/RIGHT resulting value.

   @param[in] input_priority Determines the SOCD resolution method used. @see Socd_t for how each resolution method works.

   @param[in,out] initial_input If input_priority = LAST_INPUT and SOCD cleaning is needed, this is used to determine

    which input was made last. If only one input is made, this variable is set to that input, even if input_priority != LAST_INPUT.

*/
# 614 "d:\\work\\LUFAHybridFightstick\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
void clean_socd(byte negative_in, byte *negative_out, byte positive_in, byte *positive_out, Socd_t input_priority, Socd_t *initial_input)
{
  if (negative_in && positive_in) // SOCD that needs to be resolved
  {
    switch (input_priority)
    {
      case NEUTRAL:
        *negative_out = *positive_out = false;
        break;
      case NEGATIVE:
        *negative_out = true;
        *positive_out = false;
        break;
      case POSITIVE:
        *negative_out = false;
        *positive_out = true;
        break;
      case LAST_INPUT:
        // Check which input was made first to figure out which input was made last, which wins.
        switch (*initial_input)
        {
          case NEGATIVE:
            *negative_out = false;
            *positive_out = true;
            break;
          case POSITIVE:
            *negative_out = true;
            *positive_out = false;
            break;
          // This is a fallback case for when there hasn't been an input since starting up.
          case NEUTRAL:
            *negative_out = *positive_out = false;
            break;
        }
    }
  }
  else // no SOCD to resolve, which means our current input (if any) can be output as is, but also should be remembered as the initial input.
  {
    *positive_out = positive_in;
    *negative_out = negative_in;
    if (negative_in && !positive_in)
      *initial_input = NEGATIVE;
    if (positive_in && !negative_in)
      *initial_input = POSITIVE;
  }
}
