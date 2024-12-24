#include "tim.h"

void time0()
{
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));
	TIMSK |= (1<<TOIE0);
	TCNT0 = 130;
}

void time2()
{
	TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));
	TIMSK |= (1<<OCIE2);
	TCCR2 |= ((1<<WGM21) | (0<<WGM20));
	OCR2 = 250-1;
}