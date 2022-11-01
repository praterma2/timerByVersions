/*
 * timerByV2.cpp
 *
 * Created: 11/1/2022 8:33:42 AM
 * Author : prate
 * ref: https://www.youtube.com/watch?v=5HgQkHzQc3o
 * to use time counter https://forum.arduino.cc/t/timer2-with-prescaler-1024-too-fast/3413
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000


ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	PORTB ^= (1 << PB5);
	TCNT1 = 65535 - ((F_CPU/1024)/2);   // for 1 sec at 16 MHz
}

int main(void)
{
    DDRB = (0x01 << PB5);     //Configure the PORTD4 as output
    
	//for 1 a sec, we need effective clock rate divided by prescalar
    TCNT1 = 65535 - ((F_CPU/1024)/2);   // for 1 sec at 16 MHz

	
    TCCR1A = 0x00;
    TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
    TIMSK1 = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
    sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
    
    while (1) 
    {
    }
}

