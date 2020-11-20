#include <Arduino.h>
#include "HID-Project.h"
#include "RotaryEncoder.h"

#define DEBOUNCE 60

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
#define BTN1 2
#define BTN2 3
#define BTN3 4

#define SIZEOBSBTNS 3
int btns[SIZEOBSBTNS] = {BTN1, BTN2, BTN3};
unsigned long timeOBSBTNS[SIZEOBSBTNS];
bool press[SIZEOBSBTNS];
#endif

void setup()
{
  Serial.begin(9600);

#ifdef VOLUME
  pinMode(S_ONE, INPUT_PULLUP);
  pinMode(S_TWO, INPUT_PULLUP);
  pinMode(KEY, INPUT_PULLUP);

  Consumer.begin();
#endif

#ifdef OBSBTNS
  int i;
  for (i = 0; i < SIZEOBSBTNS; i++)
  {
    pinMode(btns[i], INPUT_PULLUP);
    timeOBSBTNS[i] = 0;
    press[i] = false;
  }

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

#ifdef OBSBTNS
  int i;
  for (i = 0; i < SIZEOBSBTNS; i++)
  {
    if (digitalRead(btns[i]))
    {
      if (timeOBSBTNS[i] == 0)
      {
        timeOBSBTNS[i] = millis();
      }
      else
      {
        if (millis() - timeOBSBTNS[i] > DEBOUNCE && !press[i])
        {
          press[i] = true;
          switch (i)
          {
          case 0:
            Serial.println("caiu aqui dentro");
            // BootKeyboard.press(KEY_LEFT_ALT);
            // BootKeyboard.write(KEY_F4);
            // BootKeyboard.releaseAll();
            break;

          default:
            break;
          }
        }
      }
    }
    else
    {
      if (timeOBSBTNS[i] != 0)
      {
        timeOBSBTNS[i] = 0;
        press[i] = false;
      }
    }
  }
#endif
}