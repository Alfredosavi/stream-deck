#include <Arduino.h>
#include "HID-Project.h"
#include "RotaryEncoder.h"

void teste();

#define VOLUME
#define OBSBTNS
#define WINBTNS

#ifdef VOLUME
#define S_ONE 5
#define S_TWO 6
#define KEY 7

boolean ONE_IN, TWO_IN, KEY_IN, ONE_NEW, KEY_NEW = false;
RotaryEncoder Encoder(KEY, S_ONE);
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

  attachInterrupt(digitalPinToInterrupt(S_ONE), teste, CHANGE);

  Serial.begin(9600);
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
      Serial.println("UP");
      Consumer.write(MEDIA_VOL_UP);
    }
    else
    {
      Serial.println("DOWN");
      Consumer.write(MEDIA_VOL_DOWN);
    }
  }
  ONE_NEW = ONE_IN;

  if (KEY_IN && !KEY_NEW)
  {
    Serial.println("BUTTON");
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
  KEY_NEW = KEY_IN;
#endif
}

void teste()
{
  Encoder.tick();
}