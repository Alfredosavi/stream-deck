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

RotaryEncoder encoder(S_ONE, S_TWO);
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

bool buttonPressed(byte PinButton);

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
  static int pos = 0;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos)
  {
    if (newPos > pos)
    {
      Serial.println("UP");
      Consumer.write(MEDIA_VOL_UP);
    }
    else
    {
      Serial.println("DOWN");
      Consumer.write(MEDIA_VOL_DOWN);
    }
    pos = newPos;
  }

  if (buttonPressed(KEY))
  {
    Serial.println("BUTTON");
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
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

bool buttonPressed(byte PinButton)
{
  static unsigned long swDebounce;
  bool SW = digitalRead(PinButton);
  static bool swBefore = 1;

  if (millis() - swDebounce > DEBOUNCE)
  {
    if (!SW && swBefore)
    {
      swDebounce = millis();
      swBefore = SW;

      return true;
    }

    else if (SW && !swBefore)
    {
      swDebounce = millis();
      swBefore = SW;
    }
  }

  return false;
}

// ISR(PCINT1_vect)
// {
//   encoder.tick();
// }