#include "windservice.h"

uint16_t milisec3, sec3, min3, hour3;
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
	uint8_t timersetting;
	timerstate = model_gettimestartdata();
	timersetting = model_getwindtimerdata();
	if(timerstate == 1 && timersetting >=1)
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

void setInitialTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds)
{
	hour3 = hours;
	min3 = minutes;
	sec3 = seconds;
	milisec3 = milliseconds;
}

void timerdecmilisec()
{
	uint8_t timerstate;
	uint8_t timersetting;
	timerstate = model_gettimestartdata();
	timersetting = model_getwindtimerdata();
	if(timerstate == 1 && timersetting >= 1)
	{
		if (milisec3 == 0)
		{
			milisec3 = 999;
			if (sec3 == 0)
			{
				sec3 = 59;
				if (min3 == 0)
				{
					min3 = 59;
					if (hour3 == 0)
					{
						// 타이머가 0에 도달
						hour3 = 0;
						min3 = 0;
						sec3 = 0;
						milisec3 = 0;
						return;
					}
					else
					{
						hour3--;
					}
				}
				else
				{
					min3--;
				}
			}
			else
			{
				sec3--;
			}
		}
		else
		{
			milisec3--;
		}
	}
	else
	{
		return;
	}
}


 void fndshow()
 {
	 showtime = model_getwindtimerdata();
	 timestart = model_gettimestartdata();
	 if(timestart == 1 && showtime == 0)
	 {
		 showtime = 1;
		 timestart = 0;
		 model_settimestartdata(timestart);
		 model_setwindtimerdata(showtime);
	 }
	 if(timestart == 1)
	 {

		 switch(showtime)
		 {
			 case 1:
			 clear();
			 break;
			 case 2:
			 hour2 = 3;
			 Presenter_dispstopwatchdata(hour2, min2, sec2, milisec2);
			 if(sec2 == 3)
			 {
				 showtime = 0;
				 clear();
				 timezerofnd(0, 0,0,0);
			 }
			 break;
			 case 3:
			 hour2 = 5;
			 Presenter_dispstopwatchdata(hour2, min2, sec2, milisec2);
			 if(sec2 == 5)
			 {
				 showtime = 0;
				 clear();
				 timezerofnd(0, 0,0,0);
			 }
			 break;
			 case 4:
			 hour2 = 7;
			 Presenter_dispstopwatchdata(hour2, min2, sec2, milisec2);
			 if(sec2 == 7)
			 {
				 showtime = 0;
				 clear();
				 timezerofnd(0, 0,0,0);
			 }
			 break;
			 case 5:
			 Presenter_dispstopwatchdata(hour3, min3, sec3, milisec3);
			 break;
		 }
	 }
	 else if(timestart == 0)
	 {
		 switch(showtime)
		 {
			 case 1:
			 {
				 Presenter_dispstopwatchdata2(0, 0, 0, 0);
				 stopreset();
				 clear();
			 }
			 break;
			 case 2:
			 {
				 stopreset();
				 Presenter_dispstopwatchdata2(0, 3, 0, 0);
				 showtime = 2;
				 model_setwindtimerdata(showtime);

			 }
			 break;
			 case 3:
			 {
				 stopreset();
				 Presenter_dispstopwatchdata2(0, 5, 0, 0);
				 showtime = 3;
				 model_setwindtimerdata(showtime);

			 }
			 break;
			 case 4:
			 {
				 stopreset();
				 Presenter_dispstopwatchdata2(0, 7, 0, 0);
				 showtime = 4;
				 model_setwindtimerdata(showtime);
			 }
			 break;
			 case 5:
			 setInitialTime(0,0,3,0);
			 break;
		 }
	 }
 }

void clear()
{
	model_setwindtimerdata(0);
	model_settimestartdata(0);
	model_setwindstatedata(0);
	model_setwindautodata(0);
}

void stopreset()
{
	milisec2 = 0;
	sec2 = 0;
	min2 = 0;
	hour2 = 0;
}