#include "listener.h"

button_t btnmode,btnauto,btntimer,timerstart;
uint8_t windstate,automode,timersel,startsw;

void listen_init()
{
	button_init(&btnmode, &DDRA, &PINA, 0);
	button_init(&btnauto, &DDRA, &PINA, 1);
	button_init(&btntimer, &DDRA, &PINA, 2);
	button_init(&timerstart, &DDRA, &PINA, 3);
	model_setwindstatedata(0);
	model_setwindautodata(0);
	model_setwindtimerdata(0);
	model_settimestartdata(0);
	automode = 0;
	windstate = 0;
	timersel = 1;
	startsw = 0;
}

void listen_execute()
{
	if(Button_GetState(&btnmode) == 1)
	{
		timersel = 0;
		model_setwindtimerdata(timersel);
		automode = 0;
		model_setwindautodata(automode);
		startsw = 0;
		model_settimestartdata(startsw);
		windstate++;
		model_setwindstatedata(windstate);
		if(windstate >= 4)
		{
			windstate = 0;
			model_setwindstatedata(windstate);
		}
	}
	
	if(Button_GetState(&btnauto) == 1)
	{
		timersel = 0;
		automode = 1;
		model_setwindautodata(automode);
		model_setwindstatedata(windstate);
	}
	
	if(Button_GetState(&btntimer) == 1)
	{
		timersel++;
		model_setwindtimerdata(timersel);
		windstate = 0;
		model_setwindstatedata(windstate);
		automode = 2;
		model_setwindautodata(automode);
		if(timersel == 5)
		{
			timersel = 1;
			model_setwindtimerdata(timersel);
		}
	}
	if(Button_GetState(&timerstart) == 1)
	{
		timersel = 0;
		startsw++;
		model_settimestartdata(startsw);
		if(startsw >= 2)
		{
			startsw = 0;
			model_settimestartdata(startsw);
		}
	}
}
