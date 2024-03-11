/*
 * pwm.c
 *
 * Created: 07/01/2021 15:22:35
 *  Author: eric
 For Atmega1284P
 PWM motor controller with rotary encoder
 
 PWM output is on pin PD7 (OC2A)
 An encoder is attached to pin PA0(A) and PA1(B). 
 Phase correct mode is used, an interrupt routine is sensitive to pin PA0
 The routine changes the value of OCR2A; which change the duty cycle and the motor speed
 A drive transistor is used between the pwm output and the motor
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t dir=1;
int main(void)
{ 

DDRD|=(1<<DDD7);  // pin pd7 as pwm output (OC2A)
DDRA&=~(1<<DDA0); // pin A0 as input
DDRA&=~(1<<DDA1); // pin A1 as input
PORTA|=((1<<PORTA0)|(1<<PORTA1)); // turn on pullup resistor
PCICR|=(1<<PCIE0); // interrupt for group of pins pcie0
PCMSK0|=(1<<PCINT0); // interrupt on pin change for pin A0
	
TCCR2A|=(1<<COM2A1); //timer2 pwm phase correct non inverting
TCCR2A|=(1<<WGM20); // pwm phase correct, top=FF
ASSR&=~(1<<AS2); //select internal clk
OCR2A=0x01;
//TCCR2B|=(1<<CS20);
TCCR2B|=(1<<CS21);  //
sei();	
    while(1)
    {
		
}


	}

ISR(PCINT0_vect)
{
	if(!(PINA&(1<<PINA0)))  //detects falling edge of encoder channel A
	{ 
if((PINA&(1<<PINA1))==0x02) //if encoder channel B=1, increment duty cycle
	
	{ if(dir<250) //checks whether duty cycle has reached maximum
{dir=dir+5;
OCR2A=dir;}
	}
	else  if((PINA&(1<<PINA1))==0x00)   // if encoder channel B=0, decrement duty cycle
	{ if(dir>5)							//checks whether duty cycle has reached maximum
	{	dir=dir-5;
		OCR2A=dir;}
	
	}
	
	}	
}


/*  using the ADC
DDRD|=0xFF;
ADCSRA|=((1<<ADEN)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADATE)); //enable ADC, prescale its clock to fcpu/8, enable interrupts for ADC
ADMUX=0x05; //choose pin PA5 as input
ADMUX|=(1<<REFS0);  // use AVCC as reference (=Vcc)

ADCSRA|=(1<<ADSC);  //start conversion

while(1)
{
	the_low=ADC; //put the 15 bits result into 8 bits, LSB first
	PORTD=the_low;
	


}
} */
