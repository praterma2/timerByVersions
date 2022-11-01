/*
 * timerByV1.cpp
 *
 * Created: 11/1/2022 7:52:42 AM
 * Author : prate
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000


ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	PORTB ^= (1 << PB5);
	TCNT1 = 63974;   // for 1 sec at 16 MHz
}

int main(void)
{
    DDRB = (0x01 << PB5);     //Configure the PORTD4 as output
    
    TCNT1 = 63974;   // for 1 sec at 16 MHz

    TCCR1A = 0x00;
    TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
    TIMSK1 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
    sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
    
    while (1) 
    {
    }
}

