#include <avr/io.h>

/* leitura de dois botoes com interrupcao
* INT0 (D2 na placa; PD2 no uc)  e INT1 (D3 na placa; PD3 no uc)
* led azul: D13 -> PB5
* led branco: D10 -> PB2
* 
* o que faz o codigo: botoes acendem os respectivos leds
*/

void GPIOSetup(void)
{
  //the port D Data direction register
  DDRD &= ~(1 << DDD2); //configures PD2 as input for the white button (input = 0)
  DDRD &= ~(1 << DDD3); //configures PD3 as input for the blue button (input = 0)
  
  DDRB |= (1 << DDB2);  //configures PB2 (D10 at the board) as output to be the white led (output = 1)
  DDRB |= (1 << DDB5);  //configures PB5 (D13 at the board) as output to be the blue led (output = 1)
  
  PORTD |= (1 << PORTD2);  //sets the internal pull-up resistor for PD2 (the white button)
  PORTD |= (1 << PORTD3); //sets the internal pull-up resistor for PD3 (the blue button)
}


void InterruptConfiguration(void)
{
  /*  //external control register A for INT1: */
  EICRA |= (1 << ISC11) | (0 << ISC10); //falling edge

  /* external interrupt mask register for INT1 */
  EIMSK |= (1 << INT1);

  /* //external control register A for INT0: */
  EICRA |= (1 << ISC01) | (1 << ISC00); //sets external interrupt 0 - table 13-2

  /* external interrupt mask register for INT0 */
  EIMSK |= (1 << INT0);
  
  sei();  //globally turns interrupts
}

/* the interrupt for the white button */
ISR(INT0_vect)
{
  //PORTB |= (1 << PORTB2);
  PORTB ^= (1 << PORTB2); //toggles the white led
}

/* the interrupt for the blue button */
ISR(INT1_vect)
{
 // PORTB &= ~(1 << PORTB2);
   PORTB ^= (1 << PORTB5);  //toggles the blue led
}

void setup() 
{
  GPIOSetup();
  InterruptConfiguration();

}

void loop() 
{
  //nothing here until an interrupt is triggered.

}
