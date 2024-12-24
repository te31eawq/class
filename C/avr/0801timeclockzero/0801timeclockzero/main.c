#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "drvier/fnd/fnd.h"

uint32_t milisec;

ISR(TIMER0_OVF_vect)
{
	fndtime();
	TCNT0 = 130;
}

ISR(TIMER2_COMP_vect)
{
	milisec++;
}

int main(void)
{
	time0();
	time2();
	
	sei();
	
	fndinit();
	
    while (1) 
    {
		FND_setFndData(milisec);
    }
}

