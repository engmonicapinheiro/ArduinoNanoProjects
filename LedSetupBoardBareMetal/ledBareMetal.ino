#include <avr/io.h>

#define BLUEBUTTON  (1 << 0) //A0 - PC0
#define WHITEBUTTON (1 << 1)  //A1 - PC1
#define BLUELED (1 << 2) //D2 - PD2
#define WHITELED (1 << 3) //D3 - PD3


unsigned char blueButtonFlag = 0x0;
unsigned char whiteButtonFlag = 0x0;


void setup() 
{
  //Definir o botao azul como entrada
  DDRC &= ~BLUEBUTTON;

  //definir o botao branco como entrada
  DDRC &= ~WHITEBUTTON;

  //definir o led azul como saida
  DDRD |= BLUELED;

  //definir o led branco como saida
  DDRD |= WHITELED;

// usar resistores de pullup para os botoes
  PORTC |= BLUEBUTTON;
  PORTC |= WHITEBUTTON;

}

void loop() 
{

  //ACAO PARA O BOTAO AZUL:
  if(!(PINC & BLUEBUTTON))
  {
    blueButtonFlag = 0x01;  
  }

  if((PINC & BLUEBUTTON) && blueButtonFlag) //a acao que se realiza quando eu pressiono o botao
  {
   blueButtonFlag = 0x00;
   PORTD ^= BLUELED; 
  }



  //PARA O BOTAO BRANCO
  if(!(PINC & WHITEBUTTON))
  {
    whiteButtonFlag = 0x1;  
  }
  
  if((PINC & WHITEBUTTON) && whiteButtonFlag)
  {
    whiteButtonFlag = 0x0;
    PORTD ^= WHITELED;
    
    }


}
