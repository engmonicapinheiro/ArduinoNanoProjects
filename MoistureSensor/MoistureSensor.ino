#include <avr/io.h>
#include <util/delay.h>


void redLEDToggle(void);
void greenLEDON(void);
void yellowLEDToggle(void);
void greenLEDOFF(void);
void toggleRedAndYellow(void);
void initADC(void);

int main(void)
{  
    DDRB |= (1 << 0);    //set PB0 as output -->red led
    DDRB |= (1 << 1);   //set PB1 as output --> yellow led
    DDRB |= (1 << 2);   //set PB2 as output --> green led

    initADC();
 
    uint8_t adc_lobyte; // to hold the low byte of the ADC register (ADCL)
    uint16_t raw_adc;
    uint16_t adcValue;

    while (1)
    {
       ADCSRA |= (1 << ADSC); //start ADC measurement

       while(ADCSRA & (1 << ADSC)); //wait until the conversion is completed - polling

           // for 10-bit resolution:
      adc_lobyte = ADCL; // get the sample value from ADCL
      raw_adc = ADCH << 8 | adc_lobyte;   // add lobyte and hibyte

       // adcValue = (raw_adc * 1023)/5;
        
       if((raw_adc > 0) && (raw_adc < 301)) //dry soil
       {
         greenLEDOFF();
         redLEDToggle();
       }
       else if((raw_adc > 302) && (raw_adc < 402)) //attention!
       {
         greenLEDOFF();
         yellowLEDToggle();
       }
       else if((raw_adc > 403) && (raw_adc < 702)) //humid soil
       {
         greenLEDON();
       }
       else if(raw_adc > 703) //sensor in water
       {
         greenLEDOFF();
         toggleRedAndYellow();
       }   
    }
}


void redLEDToggle()     //PB0
{
    PORTB |= 0x01;
    _delay_ms(200);
    PORTB &= ~0x01;
    _delay_ms(200);
}


void greenLEDON() //PB2
{
    PORTB |= 0x4;
}


void greenLEDOFF()
{
    PORTB &= ~(0x4);
}


void yellowLEDToggle() //PB1
{
    PORTB |= 0x02;
    _delay_ms(400);
    PORTB &= ~0x02;
    _delay_ms(400);
}

void toggleRedAndYellow()
{
    PORTB |= 0x01;
    PORTB |= 0x02;
    _delay_ms(200);
    PORTB &= ~0x01;
    PORTB &= ~0x02;
    _delay_ms(200);  
}

void initADC()
{

  /* this function initialises the ADC 
  
  // 10-bit resolution
  // set ADLAR to 0 to disable left-shifting the result (bits ADC9 + ADC8 are in ADC[H/L] and 
  // bits ADC7..ADC0 are in ADC[H/L])
  // use uint16_t variable to read ADC (intead of ADCH or ADCL) 
  
  */

  ADMUX =
            (0 << ADLAR) |     // left shift result 
          //  (0 << REFS2) |     // Sets ref. voltage to Vcc, bit 2
            (0 << REFS1) |     // Sets ref. voltage to Vcc, bit 1   
            (0 << REFS0) |     // Sets ref. voltage to Vcc, bit 0
            (0 << MUX3)  |     // use ADC2 for input (PB5), MUX bit 3
            (0 << MUX2)  |     // use ADC2 for input (PB5), MUX bit 2
            (1 << MUX1)  |     // use ADC2 for input (PB5), MUX bit 1
            (0 << MUX0);       // use ADC2 for input (PB5), MUX bit 0

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADPS2) |     // set prescaler to 16, bit 2 
            (0 << ADPS1) |     // set prescaler to 16, bit 1 
            (0 << ADPS0);      // set prescaler to 16, bit 0  
}
