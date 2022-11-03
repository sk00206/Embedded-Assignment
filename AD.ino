#include "ad.h"

void Adc_Init(void)
// enable the ADC from the ADCSRA register by setting ADEN



{

    //Select the reference voltage from the ADMUX register
    // We'll use the arduino refrence do Set REFS0 and Clear REFS1
    ADMUX = (1<<REFS0);
 
    //Select ADC prescaler from ADCSRA register
    //BY setting l ADPS2 , ADPS1 , ADPS0 
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned short Adc_ReadChannel(unsigned char ch)
{
  //Clear the MUX bits in ADMUX register
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
 

  //Start ADC conversion using ADSC bit in ADCSRA register
  //SET BIT 6 
  ADCSRA |= (1<<ADSC);
 
  //Wait for conversion to complete 
  //This can be done using a while loop that checks if the ADSC bit turned to 0
  while(ADCSRA & (1<<ADSC));

  // return ADC value
  return (ADC);

}