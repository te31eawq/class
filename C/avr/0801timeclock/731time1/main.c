#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ap/stopwatch/stopwatch.h"
#include "Periph/timer/TIM.h"

uint8_t ledState = 0;
uint16_t milisec;
ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0 = 130;
}

ISR(TIMER2_COMP_vect)
{
	stopwatchincmilisec();
}

int main(void)
{
	
	stopwatchinit();

	sei();
	
	while (1)
	{
		stopWatchexecute();
	}
}