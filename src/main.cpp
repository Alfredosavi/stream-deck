#include <Arduino.h>
#include "HID-Project.h"
#include "RotaryEncoder.h"

#define DEBOUNCE 60 // Tempo de debounce para os botões

#define VOLUME  // Definindo recurso volume (encoder)
#define OBSBTNS // Definindo os atalhos do OBS (botões)
#define WINBTNS // Definindo os atalhos do Windows (botões)

#ifdef VOLUME   // Pinagem do encoder ... (Nome pino e Pino)
#define S_ONE 5 // S1
#define S_TWO 6 // S2
#define KEY 7   // Botão tactil do encoder

RotaryEncoder encoder(S_ONE, S_TWO);
#endif

#ifdef OBSBTNS // Pinagem dos botões que vão ser utilizados para atalhos do OBS ... (Nome Botão e Pino)
#define BTN1 2 // Botão BTN1 no pin 2
#define BTN2 3 // Botão BTN2 no pin 3
#define BTN3 4 // Botão BTN3 no pin 4

#define SIZEOBSBTNS 3                          // Quantidade de botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)
int btnsOBS[SIZEOBSBTNS] = {BTN1, BTN2, BTN3}; // Nome dos botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)

unsigned long timeOBSBTNS[SIZEOBSBTNS];
bool pressOBS[SIZEOBSBTNS];
#endif

#ifdef WINBTNS  // Pinagem dos botões que vão ser utilizados para atalhos do WINDOWS ... (Nome Botão e Pino)
#define BTN4 8  // Botão BTN8 no pin 8
#define BTN5 9  // Botão BTN9 no pin 9
#define BTN6 10 // Botão BTN10 no pin 10
#define BTN7 11 // Botão BTN11 no pin 11
#define BTN8 12 // Botão BTN11 no pin 12

#define SIZEWINBTNS 5                                      // Quantidade de botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)
int btnsWIN[SIZEWINBTNS] = {BTN4, BTN5, BTN6, BTN7, BTN8}; // Nome dos botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)

unsigned long timeWINBTNS[SIZEWINBTNS];
bool pressWIN[SIZEWINBTNS];
#endif

bool buttonPressed(byte PinButton); // Escopo da função

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
    pressWIN[j] = false;
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
      Consumer.write(MEDIA_VOL_UP); // Aumentar volume (encoder)
    }
    else
    {
      Consumer.write(MEDIA_VOL_DOWN); // Diminuir volume (encoder)
    }
    pos = newPos;
  }

  if (buttonPressed(KEY))
  {
    Consumer.write(MEDIA_PLAY_PAUSE); // Tocar/Pausar (botão tactil encoder)
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
        if ((millis() - timeOBSBTNS[i]) > DEBOUNCE && !pressOBS[i])
        {
          pressOBS[i] = true;
          switch (i)
          {
          case 0: // Atalho para mudar de Cena OBS
          {
            BootKeyboard.press(KEY_LEFT_CTRL);
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.press(KEY_LEFT_SHIFT);
            BootKeyboard.write(KEY_A);
            BootKeyboard.releaseAll();
            break;
          }

          case 1: // Atalho para mutar OBS
          {
            BootKeyboard.press(KEY_LEFT_CTRL);
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.press(KEY_LEFT_SHIFT);
            BootKeyboard.write(KEY_M);
            BootKeyboard.releaseAll();
            break;
          }

          case 2: // Atalho para desmutar OBS
          {
            BootKeyboard.press(KEY_LEFT_CTRL);
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.press(KEY_LEFT_SHIFT);
            BootKeyboard.write(KEY_U);
            BootKeyboard.releaseAll();
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
        if ((millis() - timeWINBTNS[k]) > DEBOUNCE && !pressWIN[k])
        {
          pressWIN[k] = true;
          switch (k)
          {
          case 0: // Abrir o aplicativo GITHUB DESKTOP
          {
            BootKeyboard.press(KEY_LEFT_CTRL);
            BootKeyboard.press(KEY_LEFT_ALT);
            BootKeyboard.press(KEY_LEFT_SHIFT);
            BootKeyboard.write(KEY_G);
            BootKeyboard.releaseAll();
            break;
          }

          case 1: // Abrir o GERENCIADOR DE TAREFAS do WINDOWS
          {
            BootKeyboard.press(KEY_LEFT_CTRL);
            BootKeyboard.press(KEY_LEFT_SHIFT);
            BootKeyboard.write(KEY_ESC);
            BootKeyboard.releaseAll();
            break;
          }

          case 2: // Abrir uma nova janela em branco do seu navegador padrão
          {
            Consumer.write(CONSUMER_BROWSER_HOME);
            break;
          }

          case 3: // Abrir Explorador de Arquivos (explorer) Windows
          {
            Consumer.write(CONSUMER_EXPLORER);
            break;
          }

          case 4: // Abrir a calculadora padrão do WINDOWS
          {
            Consumer.write(CONSUMER_CALCULATOR);
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
