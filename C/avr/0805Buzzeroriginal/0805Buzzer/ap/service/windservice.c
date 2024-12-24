#include "windservice.h"

uint16_t milisec, stsec, milisec2;
uint16_t sec, min, hour, sec2, min2, hour2;
uint8_t flagoff, timestart, showtime;

void stopwatchinit()
{
	milisec = 0;
	sec = 0;
	min = 0;
	hour = 0;
	
	milisec2 = 0;
	sec2 = 0;
	min2 = 0;
	hour2 = 0;

}

void stopwatchincmilisec()
{
	uint8_t stopwatchstate;
	stopwatchstate = model_getwindautodata();
	if(stopwatchstate == 1)
	{
		milisec = (milisec + 1) % 1000;
	}
	
	if(milisec) return;
	
	sec = (sec+1) % 60;
	/*if(sec == 2)
	{
	model_setwindnextdata(sec);
	sec = 0;
	milisec = 0;
	
	}*/
	if(sec) return;
	
	min = (min + 1) % 60;
	if(min) return;
	
	hour = (hour + 1) % 24;
}
void timerincmilisec()
{
	uint8_t timerstate;
	timerstate = model_gettimestartdata();
	if(timerstate == 1)
	{
		milisec2 = (milisec2 + 1) % 1000;
	}
	else return;
	
	if(milisec2) return;
	
	sec2 = (sec2+1) % 60;
	if(sec2) return;
	
	min2 = (min2 + 1) % 60;
	if(min2) return;
	
	hour2 = (hour2 + 1) % 24;
}

void fndshow()
{
	showtime = model_getwindtimerdata();
	timestart = model_gettimestartdata();
	switch(showtime)
	{
		case 0:
		{

			milisec2 = 0;
			sec2 = 0;
			min2 = 3;
			hour2 = 0;
			Presenter_dispstopwatchdata(hour2, min2, sec2, milisec2);
		}
		break;
		case 1:
		{
			milisec2 = 0;
			sec2 = 0;
			min2 = 3;
			hour2 = 0;
			Presenter_dispstopwatchdata(hour2, min2, sec2, milisec2);
		}
		break;
		case 2:
		{
			milisec2 = 0;
			sec2 = 0;
			min2 = 7;
			hour2 = 0;
			Presenter_dispstopwatchdata(hour2, min2, sec2, milisec2);
		}
		break;
		case 3:
		break;
	}

}