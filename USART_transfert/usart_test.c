/*
 * usart_test.c
 *
 * Created: 15/01/2019 14:31:10
 *  Author: eric
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);
int main(void)
{  uint16_t data;
	float toto;
	char buffer[20];
	ADCSRA|=((1<<ADEN)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADATE));
	ADMUX|=0x07;
	ADMUX|=(1<<REFS0); 

    UBRR0=25;
	  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
	  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
	  ADCSRA|=(1<<ADSC);
	while(1)
	{  
data=ADC;
toto=(data/1024)*3.3;

itoa(toto, buffer, 10);


USART_putstring(buffer);
USART_send('\n');
_delay_ms(500);

	}
}


unsigned char USART_receive(void){
	 
	 while(!(UCSR0A & (1<<RXC0)));
	 return UDR0;
	 
	}
	 
	void USART_send( unsigned char data){
	 
	 while(!(UCSR0A & (1<<UDRE0)));
	 UDR0 = data;
	 
	}
	 
	void USART_putstring(char* StringPtr){
	 
	while(*StringPtr != 0x00){
	 USART_send(*StringPtr);
	 StringPtr++;}
	 
	}
