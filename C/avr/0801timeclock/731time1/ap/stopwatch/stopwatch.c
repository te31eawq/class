#include "stopwatch.h"

button_t btnmode,btnmodify,btnhour,btnmin;
uint16_t stopwatchData;
uint16_t milisec;
uint8_t change, change2,fndColonFlag;
uint16_t sec, min, hour;
uint8_t stopwatchState;

void stopwatchinit()
{
	milisec = 0;
	sec = 0;
	min = 42;
	hour = 16;
	fndinit();
	TIM0init();
	TIM2init();
	LCDinit();
	button_init(&btnmode, &DDRA, &PINA, 0);
	button_init(&btnmodify, &DDRA, &PINA, 1);
	button_init(&btnhour, &DDRA, &PINA, 2);
	button_init(&btnmin, &DDRA, &PINA, 3);
	stopwatchState = 0;
	change = 0;
	change2 = 1;
}
void stopwatchincmilisec()
{
	
	
	milisec = (milisec + 1) % 1000;
	
	if(milisec >= 500)
	{
		fndColonFlag = 1;
	}
	else
	{
		fndColonFlag = 0;
	}
	
	if(milisec) return;
	
	sec = (sec+1) % 60;
	if(sec) return;
	
	min = (min + 1) % 60;
	if(min) return;
	
	hour = (hour + 1) % 24;
}

void stopWatchexecute()
{
	static uint8_t prevsec = 0xff;
	
	char buff[30];
	sprintf(buff, "Time Clock");
	LCDwrtiestringxy(0,3,buff);
	if(sec != prevsec)
	{
		prevsec = sec;
		sprintf(buff, "%02d:%02d:%02d", hour, min, sec);
		LCDwrtiestringxy(1,4,buff);
		
	}
		
	
	
	stopwatcheventcheck();
	stoprun();
}

void stoprun()
{
	if(hour == 24)
	{
		hour = 0;
	}
	if(min == 60)
	{
		min = 0;
	}
}
void stopwatcheventcheck()
{
	switch(stopwatchState)
	{
		
		case 0 : // 분초, 시분 표시
		FND_setFndData(stopwatchData);
		hourminchange();
		break;
		case 1: // 수정하기
		clockmodify();
		break;	
	}
}

void hourminchange()
{
	if(Button_GetState(&btnmode) == 1)
	{
		change++;
		if(change == 2)
		{
			change = 0;
		}
	}
	if(change == 0)
	{
		stopwatchData = (hour*100)+(min);
		if(Button_GetState(&btnmodify) == 1)
		{
			change2 = 0;
			stopwatchState = 1;
		}
	}
	else
	{
		stopwatchData = (min%100*100)+(sec);
	}
}

void clockmodify()
{
	if(fndColonFlag == 0)
	{
		FND_setFndData(stopwatchData);
		stopwatchData = (hour*100)+(min);
		DDRF = 0xff;
	}
	else if(fndColonFlag == 1)
	{
		DDRF = 0x00;
	}
	if(Button_GetState(&btnmodify) == 1)
	{
		DDRF = 0xff;
		stopwatchState = 0;
	}
	if(Button_GetState(&btnhour) == 1)
	{
		hour = hour + 1;
	}
	if(Button_GetState(&btnmin) == 1)
	{
		min = min + 1;
	}
}