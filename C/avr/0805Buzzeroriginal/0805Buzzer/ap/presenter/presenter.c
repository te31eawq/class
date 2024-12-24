#include "presenter.h"

void presenterinit()
{
	fndinit();
	LCDinit();
}

void Presenter_dispstopwatchdata(uint8_t hour,uint8_t min,uint8_t sec,uint16_t milisec)
{
	uint16_t stopwatch2data;
	
	stopwatch2data = (min*100)+(sec);
	FND_setFndData(stopwatch2data);
	
	char buff[30];
	LCDwrtiestringxy(0,3,"STOP WATCH");
	sprintf(buff, "%02d:%02d:%02d:%02d", hour, min, sec, milisec/10%100);
	LCDwrtiestringxy(1,3,buff);
	
}

void Presenter_dispstopwatchdata2(uint8_t hour2,uint8_t min2,uint8_t sec2,uint16_t milisec2)
{
	uint8_t timeclockdispstate;
	uint16_t stopwatchdata;
	timeclockdispstate = model_getwindtimerdata();
	switch(timeclockdispstate)
	{
		case 0:
		stopwatchdata = (hour2*100)+(min2);
		FND_setFndData(stopwatchdata);
		break;
		case 1:
		stopwatchdata = (sec2*100)+(milisec2/10);
		FND_setFndData(stopwatchdata);
		break;
	}
	
	char buff[30];
	LCDwrtiestringxy(0,3,"WHAT TIME ");
	sprintf(buff, "%02d:%02d:%02d:%02d", hour2, min2, sec2, milisec2/10%100);
	LCDwrtiestringxy(1,3,buff);
	
}