#include <Arduino.h>
#include "HID-Project.h"
#include "RotaryEncoder.h"

#define VOLUME
#define OBSBTNS
#define WINBTNS

#ifdef VOLUME
#define S_ONE 5
#define S_TWO 6
#define KEY 7

boolean ONE_IN, TWO_IN, KEY_IN, ONE_NEW, KEY_NEW = false;
#endif

#ifdef OBSBTNS
#define BTN1 4
#define BTN2 5
#define BTN3 6

#define SIZEOBSBTNS 3
int btns[SIZEOBSBTNS] = {BTN1, BTN2, BTN3};
#endif

void setup()
{
#ifdef VOLUME
  pinMode(S_ONE, INPUT_PULLUP);
  pinMode(S_TWO, INPUT_PULLUP);
  pinMode(KEY, INPUT_PULLUP);

  Consumer.begin();
  BootKeyboard.begin();
#endif
}

void loop()
{
#ifdef VOLUME
  ONE_IN = digitalRead(S_ONE) == LOW;
  TWO_IN = digitalRead(S_TWO) == LOW;
  KEY_IN = digitalRead(KEY) == LOW;

  if (ONE_IN && !ONE_NEW)
  {
    if (TWO_IN)
    {
      Consumer.write(MEDIA_VOL_UP);
    }
    else
    {
      Consumer.write(MEDIA_VOL_DOWN);
    }
  }
  ONE_NEW = ONE_IN;

  if (KEY_IN && !KEY_NEW)
  {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
  KEY_NEW = KEY_IN;

#endif
}