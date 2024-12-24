#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ap/standlight/ledmachine.h"





int main(void)
{
	StandLightinit();

	while (1)
	{
		StandLightrun();
	}
}

