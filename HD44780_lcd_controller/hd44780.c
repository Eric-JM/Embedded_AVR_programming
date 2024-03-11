/*
 * hd44780.c
 *
 * Created: 13/01/2022 14:18:43
 *  Author: eric
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


int main(void)
{
   
   char buffer[7];
   uint16_t data;
   double toto;
  
  ADCSRA|=((1<<ADEN)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADATE)); //enable ADC, prescale its clock to fcpu/8, enable interrupts for ADC
ADMUX=0x07; //choose pin PA5 as input
ADMUX|=(1<<REFS0);  // use AVCC as reference (=Vcc)

 //start conversion
   


    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);

                        /* loop forever */
        /* 
         * Test 1:  write text to display
         */

        /* clear display and home cursor */
        lcd_clrscr();
      
        /* put string to display (line 1) with linefeed */
  /*    while(toto<500)
	   {
		   toto++;
		
		   itoa( toto , buffer, 10);
		   lcd_gotoxy(8,0);
		   lcd_puts(buffer);
		   _delay_ms(80);
	   
	   }  */
  
  
	ADCSRA|=(1<<ADSC); 
	
	while(1)
	{
		data=ADC;
		toto=(data*3.3)/1024;
		dtostrf(toto,4,2,buffer);
		lcd_gotoxy(0,0);
		lcd_puts("Voltage:");
	//	lcd_gotoxy(9,0);
		lcd_puts(buffer);
		lcd_puts("V");
		   _delay_ms(500);
		    lcd_clrscr();
		
	}
	
}	
