# stream-deck

Stream Deck é um painel de controle personalizável para streaming ao vivo que pode incluir **N** teclas para: alternar cenas, iniciar mídia e ajustar áudio em tempo real. Você pode criar binds personalizadas, como, por exemplo: abrir programas específicos, iniciar/pausar músicas, aumentar/diminuir volume e um monte de outras coisas que você normalmente teria que fazer com Alt-Tab.

A ideia do projeto é criar um painel de controle customizável com botões dedicados para algumas funções especificas para ganhar agilidade e deixar as coisas mais simples.


## :page_facing_up: Componentes Necessários

* Arduino leonardo ou arduino pro micro;
* N botões de pressão (push-button);
* Módulo Encoder Rotativo (Rotary Decoder Sensor);
* Jumpers;
* Cabo micro-usb;
* Ferro de solda, solda, etc.


## 🔥 Instalação e execução

1. Utilizando o [PlataformIO](https://platformio.org/platformio-ide)
    1. Faça um clone desse repositório;
    2. Dentro da interface do PlataformIO navegue até `Projects` e depois selecione `Add Existing`;
    3. Selecione a pasta `cd stream-deck` que foi clonada anteriormente.
    
2. Utilizando a [IDE ARDUINO](https://www.arduino.cc/en/software)
    1. Faça um clone desse repositório;
    2. Abra o arquivo `.ino` dentro da pasta `sketch_deck_arduino`.
    
    **OBSERVAÇÕES**:
    1. Certifique-se que tenha instalado as [bibliotecas](#Bibliotecas);
    2. Certifique-se de selecionar a Placa: `Arduino Leonardo` ou `Arduino Micro` e a Porta na aba `Ferramentas` da IDE Arduino antes de Compilar/Carregar o sketch.


## :mag_right: Curiosidade

Já deve ter visto que alguns teclados USB possuem teclas multimídias, como por exemplo aumentar/diminuir volume, reproduzir/pausar. Alguns também possui teclas de atalhos para aplicativos, como e-mail e navegador.

As teclas não enviam um caractere para o computador, existe um processador que identifica as teclas pressionadas e converte essa informação em códigos de varredura para envio serial ao PC. Cada tecla gera dois sinais diferentes: um quando a tecla é pressionada e outro quando volta à posição original (é liberada). O uso dos dois códigos permite que o PC saiba quando uma tecla foi ou não mantida pressionada. A existência de teclas multimídia implica que elas também têm códigos de varredura, então concluí que deveria ser fácil programar um Arduino para enviá-las, já que o Leonardo e o Pro Micro **(Atmega32u4)** podem emular um teclado ou mouse por meio de sua porta USB.

A biblioteca **Keyboard/Mouse** do arduino permite apenas enviar as teclas encontradas no teclado **IBM PC** padrão original. As teclas de multimídia e do sistema (Hibernação/Despertar/Suspensão) incluem conjuntos separados que não são suportados. Embora os movimentos e cliques da biblioteca Mouse possuem suporte. Por causa disso foi utilizada a biblioteca [**HID-Project**](https://github.com/NicoHood/HID) que libera novos **recursos HID**.


## :warning: Observações

1. O projeto **necessita** de um **arduino leonardo** ou **arduino pro micro** porque eles possuem **MCU** (microcontrolador) **ATmega32U4** que contem **controlador USB embutido**;
2. O **arduino leonardo** possui **20 E/S Digital** então a quantidade de botões é **limitada**. (Pode utilizar CI's para expandir os pinos E/S Digital);
3. O projeto foi feito em uma **protoboard**, então sinta-se à vontade para criar um **case personalizado** para ficar mais `elegante`.

## :hammer: Criando um Atalho

Para facilitar, o código está separado em três seções:
  1. `VOLUME` - Destinado ao controle de Volume +/- e botão de Pause/Resume utilizando o encoder rotativo.
  2. `OBSBTNS` (OBS botões) - Destinado a configuração dos botões e shortkeys relacionados com o OBS.
  3. `WINBTNS` (Windows botões) - Destinado a configuração dos botões e shortkeys relacionados ao sistema WINDOWS.
  
  ### Criando Atalhos voltados ao OBS
  
  Primeiramente entre nas `configurações` de `teclas de atalho` do OBS e crie atalhos para as funções que deseja.
  Como por exemplo: transições de cenas/telas, Ocultar Cenas, Mutar/Desmutar.
  
  ![OBS CONFIG](https://i.imgur.com/ETwHmAw.png)
  
  1. Defina um **nome** e um **pino** para o botão. Exemplo:
  
  ```c++
#ifdef OBSBTNS // Pinagem dos botões que vão ser utilizados para atalhos do OBS ... (Nome Botão e Pino)
#define BTN1 2 // Botão BTN1 no pin 2
#define BTN2 3 // Botão BTN2 no pin 3
#define BTN3 4 // Botão BTN3 no pin 4
  ```
  
  2. Em `SIZEOBSBTNS` coloque a quantidade de botões que criou no passo anterior e inclua eles no vetor `btnsOBS[SIZEOBSBTNS]`. Exemplo:
  
  ```c++
#define SIZEOBSBTNS 3                          // Quantidade de botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)
int btnsOBS[SIZEOBSBTNS] = {BTN1, BTN2, BTN3}; // Nome dos botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)
  ```
  
  3. Em `OBSBTNS` dentro da função `void loop()` inclua um `case X` dentro do `switch`, onde **X** é um número de 0 até o tamanho do seu vetor `SIZEOBSBTNS`. Exemplo:
  ```c++
  case 0: // Atalho para mudar de Cena OBS
          {
            BootKeyboard.press(KEY_LEFT_CTRL);  // Tecla CTRL
            BootKeyboard.press(KEY_LEFT_ALT);   // Tecla ALT
            BootKeyboard.press(KEY_LEFT_SHIFT); // Tecla SHIFT
            BootKeyboard.write(KEY_A);          // Tecla "A"
            BootKeyboard.releaseAll();          // Soltar as teclas CTRL, ALT, SHIFT
            break;
          }
  ```
  
  1. Utilize a função `press()` para "segurar" uma tecla. Geralmente utilizada para teclas como: `Ctrl`, `Alt`, `Shift` e `Tecla Windows`;
  2. A função `write()` serve para enviar um único caractere. Como se você pressionasse um botão no teclado e o soltasse;
  3. A função `releaseAll()` serve para "soltar" todas as teclas que "segurou". **Função obrigatoria** caso utilize a função `press()`;
  4. Troque os parâmetros das funções pela combinação de teclas que criou nos atalhos do OBS. (a lista de KEYS encontra-se nas tabelas abaixo).
  
  
  ### Criando Atalhos para funcionalidades do WINDOWS
  
  1. Defina um **nome** e um **pino** para o botão. Exemplo:
  
  ```c++
#ifdef WINBTNS  // Pinagem dos botões que vão ser utilizados para atalhos do WINDOWS ... (Nome Botão e Pino)
#define BTN4 8  // Botão BTN8 no pin 8
#define BTN5 9  // Botão BTN9 no pin 9
#define BTN6 10 // Botão BTN10 no pin 10
#define BTN7 11 // Botão BTN11 no pin 11
#define BTN8 12 // Botão BTN11 no pin 12
  ```
  
  2. Em `SIZEWINBTNS` coloque a quantidade de botões que criou no passo anterior e inclua eles no vetor `btnsWIN[SIZEWINBTNS]`. Exemplo:
  
  ```c++
  #define SIZEWINBTNS 5                                      // Quantidade de botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)
  int btnsWIN[SIZEWINBTNS] = {BTN4, BTN5, BTN6, BTN7, BTN8}; // Nome dos botões que foi declarado em cima (ATUALIZAR CASO VOCE ALTERE)
  ```
  
  3. Em `WINBTNS` dentro da função `void loop()` inclua um `case X` dentro do `switch`, onde **X** é um número de 0 até o tamanho do seu vetor `SIZEWINBTNS`. Exemplo:
  ```c++
  case 0: // Abrir o aplicativo GITHUB DESKTOP
    {
      BootKeyboard.press(KEY_LEFT_CTRL);  // Tecla CTRL
      BootKeyboard.press(KEY_LEFT_ALT);   // Tecla ALT
      BootKeyboard.press(KEY_LEFT_SHIFT); // Tecla SHIFT
      BootKeyboard.write(KEY_G);          // Tecla "G"
      BootKeyboard.releaseAll();          // Soltar as teclas CTRL, ALT, SHIFT
      break;
    }
  ```
  
  1. Utilize a função `press()` para "segurar" uma tecla. Geralmente utilizada para teclas como: `Ctrl`, `Alt`, `Shift` e `Tecla Windows`;
  2. A função `write()` serve para enviar um único caractere. Como se pressionasse um botão no teclado e o soltasse;
  3. A função `releaseAll()` serve para "soltar" todas as teclas que "segurou". **Função obrigatoria** caso utilize a função `press()`;
  4. Troque os parâmetros das funções pela combinação de teclas. (a lista de KEYS encontra-se nas tabelas abaixo).
  
  
  Para abrir um programa com **shortkey** clique em `Propriedades` no atalho do programa e em seguida selecione a aba `Atalho`.
  ![Propriedades Programa](https://i.imgur.com/3SrnC7a.png)


## :triangular_flag_on_post: Tabelas KEY

A tabela abaixo representa os atalhos da classe **BootKeyboard**. Se for utilizar alguma **KEY** dessa tabela precisa invocá-la usando a classe `BootKeyboard`. Exemplo: Ativando/Desativando o **CAPS LOCK**:

```bash
BootKeyboard.write(KEY_CAPS_LOCK);
```

Key	            | Hexadecimal	| Decimal
--------------- | :---------: | :-----:
KEY_LEFT_CTRL	  |    0x80	    |  128
KEY_LEFT_SHIFT	|    0x81	    |  129
KEY_LEFT_ALT	  |    0x82	    |  130
KEY_LEFT_GUI    |	   0x83	    |  131
KEY_RIGHT_CTRL	|    0x84	    |  132
KEY_RIGHT_SHIFT	|    0x85	    |  133
KEY_RIGHT_ALT	  |    0x86	    |  134
KEY_RIGHT_GUI	  |    0x87	    |  135
KEY_UP_ARROW	  |    0xDA	    |  218
KEY_DOWN_ARROW	|    0xD9	    |  217
KEY_LEFT_ARROW	|    0xD8	    |  216
KEY_RIGHT_ARROW	|    0xD7	    |  215
KEY_BACKSPACE	  |    0xB2	    |  178
KEY_TAB	        |    0xB3	    |  179
KEY_RETURN	    |    0xB0	    |  176
KEY_ESC	        |    0xB1	    |  177
KEY_INSERT	    |    0xD1	    |  209
KEY_DELETE	    |    0xD4	    |  212
KEY_PAGE_UP	    |    0xD3	    |  211
KEY_PAGE_DOWN	  |    0xD6	    |  214
KEY_HOME	      |    0xD2	    |  210
KEY_END	        |    0xD5	    |  213
KEY_CAPS_LOCK	  |    0xC1	    |  193
KEY_F1	        |    0xC2	    |  194
KEY_F2	        |    0xC3	    |  195
KEY_F3	        |    0xC4	    |  196
KEY_F4	        |    0xC5	    |  197
KEY_F5	        |    0xC6	    |  198
KEY_F6	        |    0xC7	    |  199
KEY_F7	        |    0xC8	    |  200
KEY_F8	        |    0xC9	    |  201
KEY_F9	        |    0xCA	    |  202
KEY_F10	        |    0xCB	    |  203
KEY_F11	        |    0xCC	    |  204
KEY_F12	        |    0xCD	    |  205


A tabela abaixo representa os atalhos da classe **Consumer**. Se for utilizar alguma **KEY** da tabela precisa invocá-la usando a classe `CONSUMER`. Exemplo abrindo uma calculadora:

```bash
Consumer.write(CONSUMER_CALCULATOR);
```

Key Definitions (Consumer) | ConsumerKeycode
-------------------------- | :-------------:
MEDIA_FAST_FORWARD         |   0xB3 
MEDIA_REWIND	             |   0xB4 
MEDIA_NEXT	               |   0xB5 
MEDIA_PREVIOUS	           |   0xB6 
MEDIA_STOP	               |   0xB7 
MEDIA_PLAY_PAUSE	         |   0xCD
MEDIA_VOLUME_MUTE	         |   0xE2 
MEDIA_VOLUME_UP	           |   0xE9 
MEDIA_VOLUME_DOWN	         |   0xEA
CONSUMER_EMAIL_READER	     |   0x18A 
CONSUMER_CALCULATOR	       |   0x192 
CONSUMER_EXPLORER	         |   0x194
CONSUMER_BROWSER_HOME	     |   0x223 
CONSUMER_BROWSER_BACK	     |   0x224 
CONSUMER_BROWSER_FORWARD	 |   0x225 
CONSUMER_BROWSER_REFRESH	 |   0x227 
CONSUMER_BROWSER_BOOKMARKS |   0x22A

**OBS**: Para uma lista mais completa consulte o arquivo [ImprovedKeylayouts.txt](ImprovedKeylayouts.txt).


## :package: Bibliotecas

1. Rotary Encoder by: Matthias Hertel
[RotaryEncoder@1.3.0](https://github.com/mathertel/RotaryEncoder)
2. HID-Project by: NicoHood
[HID-Project@2.6.1](https://github.com/NicoHood/HID)

OBS: Se tiver usando a **IDE Arduino** ambas estão disponíveis no **gerenciador de bibliotecas**.


## :link: Links Úteis

1. [Pinout Arduino Leonardo](http://marcusjenkins.com/wp-content/uploads/2014/06/leonardov2.pdf)
2. [Pintout Arduino Micro](https://arduino.pinout.guide/arduino_micro_pinout_and_ISP_pins.png)


## ⚡️ Como contribuir

- Faça um fork desse repositório;
- Cria uma branch com a sua feature: `git checkout -b minha-feature`;
- Faça commit das suas alterações: `git commit -m 'feat: Minha nova feature'`;
- Faça push para a sua branch: `git push origin minha-feature`.

Depois que o merge da sua pull request for feito, você pode deletar a sua branch.


## :memo: Licença

Esse projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
