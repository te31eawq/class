#include "upcounter.h"

uint32_t timetick = 0;
uint32_t prevtime = 0;
button_t btnrun, btnstop, btnreset;
uint8_t ledState;
uint16_t counter = 0;
void upcounterinit()
{
	ledState = 0;
	button_init(&btnrun, &DDRA, &PINA, 0);
	button_init(&btnstop, &DDRA, &PINA, 1);
	button_init(&btnreset, &DDRA, &PINA, 2);
}

void upcounterexecute()
{
	switch(ledState)
	{
		case 0:
		FND_setFndData(counter);
		if(timetick - prevtime >= 500)
		{
			counter ++;
			timetick = 0;
		}
		if(Button_GetState(&btnstop) == 1)
		{
			ledState = 1;
		}
		if(Button_GetState(&btnreset) == 1)
		{
			counter = 0;
		}
		break;
		case 1:
		FND_setFndData(counter);
		if(Button_GetState(&btnrun) == 1)
		{
			ledState = 0;
		}
		if(Button_GetState(&btnreset) == 1)
		{
			ledState = 2;
		}
		break;
		case 2:
		counter = 0;
		FND_setFndData(counter);
		if(Button_GetState(&btnrun) == 1)
		{
			ledState = 0;
		}
		break;
	}
	_delay_ms(1);
	timetick++;
}