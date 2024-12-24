#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ap/wind/wind.h"

int main(void)
{
	wind_init();
	
	sei();
	while (1)
	{
		
		wind_execute();
		
	}
}


