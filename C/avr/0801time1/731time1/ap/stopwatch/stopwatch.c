#include "stopwatch.h"

button_t btnrunstop, btnresetbt;

uint16_t milisec;
uint16_t sec, min, hour;
uint8_t stopwatchState;
void stopwatchinit()
{
	milisec = 0;
	sec = 0;
	min = 0;
	hour = 0;
	
	fndinit();
	TIM0init();
	TIM2init();
	stopwatchState = 0;
	button_init(&btnrunstop,&DDRA, &PINA,0);
	button_init(&btnresetbt,&DDRA, &PINA,1);
	

}

void stopwatchincmilisec()
{
	
	if(stopwatchState == 0)
	{
		milisec = (milisec + 1) % 1000;
	}
	else return;
	
	if(milisec) return;
	
	sec = (sec+1) % 60;
	if(sec) return;
	
	min = (min + 1) % 60;
	if(min) return;
	
	hour = (hour + 1) % 24;
}

void stopWatchexecute()
{
	stopwatcheventcheck();
	stoprun();
}

void stopwatcheventcheck()
{
	switch(stopwatchState)
	{
		case 0:
		if(Button_GetState(&btnrunstop) == 1)
		{
			stopwatchState = 1;
		}
		if(Button_GetState(&btnresetbt) == 1)
		{
			stopwatchState = 2;
		}
		break;
		case 1:
		if(Button_GetState(&btnrunstop) == 1)
		{
			stopwatchState = 0;
		}
		if(Button_GetState(&btnresetbt) == 1)
		{
			stopwatchState = 2;
		}
		break;
		case 2:
		stopwatchState = 1;
		break;
	}
	
}

void stoprun()
{
	uint16_t stopwatchData;
	if(stopwatchState == 2)
	{
		milisec = 0;
		sec = 0;
		min = 0;
		hour = 0;
	}
	stopwatchData = (min%10*1000)+(sec*10)+(milisec/100%10);
	FND_setFndData(stopwatchData);
	
	
}