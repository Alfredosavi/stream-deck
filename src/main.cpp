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
int btnsOBS[SIZEOBSBTNS] = {BTN1, BTN2, BTN3};

unsigned long timeOBSBTNS[SIZEOBSBTNS];
bool pressOBS[SIZEOBSBTNS];
#endif

#ifdef WINBTNS
#define BTN4 8
#define BTN5 9
#define BTN6 10
#define BTN7 11
#define BTN8 12

#define SIZEWINBTNS 5
int btnsWIN[SIZEWINBTNS] = {BTN4, BTN5, BTN6, BTN7, BTN8};

unsigned long timeWINBTNS[SIZEWINBTNS];
bool pressWIN[SIZEWINBTNS];
#endif

bool buttonPressed(byte PinButton);

void setup()
{
  Consumer.begin();
  BootKeyboard.begin();

#ifdef VOLUME
  pinMode(S_ONE, INPUT_PULLUP);
  pinMode(S_TWO, INPUT_PULLUP);
  pinMode(KEY, INPUT_PULLUP);
#endif

#ifdef OBSBTNS
  int i;
  for (i = 0; i < SIZEOBSBTNS; i++)
  {
    pinMode(btnsOBS[i], INPUT_PULLUP);
    timeOBSBTNS[i] = 0;
    pressOBS[i] = false;
  }
#endif

#ifdef WINBTNS
  int j;
  for (j = 0; j < SIZEWINBTNS; j++)
  {
    pinMode(btnsWIN[j], INPUT_PULLUP);
    timeWINBTNS[j] = 0;
    pressWIN[i] = false;
  }
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
      Consumer.write(MEDIA_VOL_UP);
    }
    else
    {
      Consumer.write(MEDIA_VOL_DOWN);
    }
    pos = newPos;
  }

  if (buttonPressed(KEY))
  {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
#endif

#ifdef OBSBTNS
  int i;
  for (i = 0; i < SIZEOBSBTNS; i++)
  {
    if (digitalRead(btnsOBS[i]))
    {
      if (timeOBSBTNS[i] == 0)
      {
        timeOBSBTNS[i] = millis();
      }
      else
      {
        if (millis() - timeOBSBTNS[i] > DEBOUNCE && !pressOBS[i])
        {
          pressOBS[i] = true;
          switch (i)
          {
          case 0:
          {
            BootKeyboard.press(KEY_LEFT_CTRL);
            BootKeyboard.press(KEY_LEFT_SHIFT);
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.write(KEY_A);
            BootKeyboard.releaseAll();
            break;
          }

          case 1:
          {
            break;
          }

          case 2:
          {
            break;
          }

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
        pressOBS[i] = false;
      }
    }
  }
#endif

#ifdef WINBTNS
  int k;
  for (k = 0; k < SIZEWINBTNS; k++)
  {
    if (digitalRead(btnsWIN[k]))
    {
      if (timeWINBTNS[k] == 0)
      {
        timeWINBTNS[k] = millis();
      }
      else
      {
        if (millis() - timeWINBTNS[k] > DEBOUNCE && !pressWIN[k])
        {
          pressWIN[k] = true;
          switch (k)
          {
          case 0:
          {
            break;
          }

          case 1:
          {
            break;
          }

          case 2:
          {
            break;
          }

          case 3:
          {
            break;
          }

          case 4:
          {
            break;
          }

          case 5:
          {
            break;
          }

          default:
            break;
          }
        }
      }
    }
    else
    {
      if (timeWINBTNS[k] != 0)
      {
        timeWINBTNS[k] = 0;
        pressWIN[k] = false;
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
