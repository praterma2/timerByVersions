/*
 * f22ClassInterruptByV2.cpp
 *
 * Created: 11/1/2022 10:34:57 AM
 * Author : prate
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000 

volatile int cycleCtr = 0;

ISR (TIMER0_OVF_vect)    // Timer1 ISR
{
	if(cycleCtr == 61){
		PORTB ^= (1 << PB5);
		cycleCtr = 0;
	} else {
		cycleCtr++;
	}
	//put in your value here
	TCNT0 = 0;   // for 1 sec at 16 MHz
}

void initInt(){
	TCNT0 = 0;   // for 1 sec at 16 MHz

	TCCR0A = 0x00;
	TCCR0B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
	TIMSK0 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	sei();					// Enable global interrupts by setting global interrupt enable bit in SREG
}

int main(void)
{
    DDRB = (0x01 << PB5);     //Configure the PORTD4 as output
    initInt();
        
    while (1) 
    {
    }
}

