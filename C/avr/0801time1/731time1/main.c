#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ap/stopwatch/stopwatch.h"
#include "Periph/timer/TIM.h"

uint8_t ledState = 0;
button_t btnrun, btnstop, btnreset;
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
	//button_init(&btnrun,&DDRA, &PINA,0);
	//button_init(&btnstop,&DDRA, &PINA,1);
	//button_init(&btnreset,&DDRA, &PINA,2);

	sei();
	
	while (1)
	{
		//stopwatchexecute();
		/*res = (milisec/100);
		if(res >= 600)
		{
				min = 1000;
				res = 0;
				milisec = 0;
		}
		result = min + res;
		*/
		stopWatchexecute();
		/*switch(ledState)
		{
			case 0:
			FND_setFndData(milisec);
			if(Button_GetState(&btnrun)== 1)
			{
				ledState = 1;
			}
			if(Button_GetState(&btnreset)== 1)
			{
				milisec = 0;
			}
			break;
			case 1:
			FND_setFndData(milisec);
			if(Button_GetState(&btnrun) == 1)
			{
				ledState = 0;
			}
			if(Button_GetState(&btnreset) == 1)
			{
				milisec = 0;
			}
			break;
			case 2:
			milisec = 0;
			FND_setFndData(milisec);
			if(Button_GetState(&btnrun) == 1)
			{
				ledState = 0;
			}
			break;
		}
		_delay_ms(1);
		timetick++;*/
	}
}