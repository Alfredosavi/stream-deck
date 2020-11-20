# stream-deck


Stream Deck é um painel de controle personalizável para streaming ao vivo que pode incluir **N** teclas para: alternar cenas, iniciar mídia e ajustar áudio em tempo real. Você pode criar binds personalizadas, como, por exemplo: abrir programas específicos, iniciar/pausar musicas, aumentar/diminuir volume e um monte de outras coisas que você normalmente teria que fazer com Alt-Tab.

A ideia do projeto é criar um painel de controle customizável com botões dedicados para algumas funções especificas para ganhar agilidade e deixar as coisas mais simples.


## Componentes Necessários
* Arduino Leonardo ou arduino pro micro
* N botões de pressão (push-button)
* Módulo Encoder Rotativo (Rotary Decoder Sensor)
* Jumpers
* Cabo micro-usb
* Caixa de projeto pequena
* Ferro de solda, solda, etc


## Curiosidade

Já deve ter visto que alguns teclados USB possuem teclas multimídias, como por exemplo aumentar/diminuir volume, reproduzir/pausar. Alguns também possui teclas de atalhos para aplicativos, como e-mail e navegador.

As teclas não enviam um caractere para o computador, existe um processador que identifica as teclas pressionadas e converte essa informação em códigos de varredura para envio serial ao PC. Cada tecla gera dois sinais diferentes: um quando a tecla é pressionada e outro quando volta à posição original (é liberada). O uso dos dois códigos permite que o PC saiba quando uma tecla foi ou não mantida pressionada. A existência de teclas multimídia implica que elas também têm códigos de varredura, então concluí que deveria ser fácil programar um Arduino para enviá-las, já que o Leonardo e o Pro Micro **(Atmega32u4)** podem emular um teclado ou mouse por meio de sua porta USB.

A biblioteca **Keyboard/Mouse** do arduino permite apenas enviar as teclas encontradas no teclado **IBM PC** padrão original. As teclas de multimida e do sistema (Hibernação/Despertar/Suspensão) incluem conjuntos separados que não são suportados. Embora os movimentos e cliques da biblioteca Mouse possuem suporte. Por causa disso foi utilizada a biblioteca [**HID-Project**](https://github.com/NicoHood/HID) que libera novos **recursos HID**.


## Observações

1. O projeto necessita de um arduino leonardo ou arduino pro micro porque eles possuem MCU (microcontrolador) ATmega32U4 que contem controlador USB imbutido.
2. O arduino leonardo possui 20 E/S Digital então a quantidade de botões é limitada. (Pode utilizar CI's para expandir os pinos E/S Digital)
3.


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

## :memo: Licença

Esse projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
