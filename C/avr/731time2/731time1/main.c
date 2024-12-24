#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ap/upcounter/upcounter.h"
#include "Periph/timer/TIM.h"

ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0 = 130;
}
int main(void)
{
	fndinit();
	TIM0init();
	upcounterinit();
	sei();
	
	while (1)
	{
		upcounterexecute();
	}
}