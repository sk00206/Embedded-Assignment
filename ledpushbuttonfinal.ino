#include <avr/io.h>
#include <util/delay.h>
//Preprocessor Directives
//Pre-defined header files




////////////////////////Decleration Section////////////////////////


// int is the main fuction return type
// main() is program main function 

int main(void){

  //BODY OF MAIN FUNCTION//

  init(); // For initialization
  unsigned char buffer [4];



 while (1) //Never Ending while loop (so it can keep on working all the time)
  {
    //Reading the ADC value//
   

    // a function to read the ADC component and expecting an integer 
    int read = Adc_ReadChannel(0); 

    //To convert a 10-bit ADC value into a string of readable numbers
    // We  use a function called ITOA (short for Integer TO ASCII)
    // This function takes three input parameters
    //(value we want to convert, input parameter of base of conversion 10 in this case (decimal in this case))
    //The string is placed in the buffer passed, which must be large enough to hold the output.
    itoa(read, buffer, 10);
    Uart_SendString(buffer);
    // output array must have at least space for the maximum number of chars that our number as plus one for the NULL
    Uart_SendString("  ");
    _delay_ms(500);
    Uart_SendChar('\r');
    Uart_SendChar('\n');

    //PORTB = PORTB & ~ (1 << 5);   
    

    if((PIND & (1 << 7))!= 0)  // if switch not pressed 
    {
      PORTB = PORTB & ~(1 << 5);    // Switch OFF lED 
      
    }  
    else
    {
      
      PORTB = PORTB | (1 << 5);   // if switch is pressed
      Uart_SendChar('k');
      Uart_SendChar('e');
      Uart_SendChar('y');
      Uart_SendChar(' ');
      Uart_SendChar('i');
      Uart_SendChar('s');
      Uart_SendChar(' ');
      Uart_SendChar('p');
      Uart_SendChar('r');
      Uart_SendChar('e');
      Uart_SendChar('s');
      Uart_SendChar('s');
      Uart_SendChar('e');
      Uart_SendChar('d');
      Uart_SendChar('\n');
         // Switch ON lED (red one) and send "key is pressed" only when button is pressed
      _delay_ms(1000);
    }
    
    if(read < 30){ // if adc value less than threshhold
        PORTB = PORTB  &! (1 << 0); // led stays off
        Uart_SendChar('S');
        Uart_SendChar('a');
        Uart_SendChar('f');
        Uart_SendChar('e');
        Uart_SendChar(' ');
        Uart_SendChar('=');
        Uart_SendChar(' ');
        // send safe on serial monitor if below threshhold
     }
    else{
      PORTB = PORTB | (1 << 0); // if LED ON (blue one)
      Uart_SendChar('E');
      Uart_SendChar('M');
      Uart_SendChar('E');
      Uart_SendChar('R');
      Uart_SendChar('G');
      Uart_SendChar('E');
      Uart_SendChar('N');
      Uart_SendChar('C');
      Uart_SendChar('Y');
      Uart_SendChar(' ');
      Uart_SendChar('=');
      Uart_SendChar(' ');
      // send "EMERGENCY" when above threshhold
   }
  }
  return 0; // main function return value
}



void init(){ // initializing the output/input pins or ports and the libraries used
  DDRB = DDRB | (1 << 5);   // Make PB5 output
  Uart_Init();
  Adc_Init(); 
  DDRD = DDRD & ~(1 << 7);    // Make PD7 input
  PORTD = PORTD | (1 << 7);   // Activate pull up resistance
}


