#include "wind.h"

uint8_t autonext, automode,sec,fndstate;
uint16_t milisec2, sec2 ,min2, hour2;
ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0 = 130;
}

ISR(TIMER2_COMP_vect)
{
	stopwatchincmilisec();
	timerincmilisec();
}




void wind_init()
{
	TIM0init();
	TIM2init();
	Gpioinit();
	listen_init();
	presenterinit();
	Buzzer_init();
	stopwatchinit();
	milisec2 = 0;
	sec2 = 0;
	min2 = 0;
	hour2 = 0;
}

void wind_execute()
{

	listen_execute();
	uint8_t state;
	state = model_getwindstatedata();
	sec = model_getwindautodata();
	automode = model_getwindautodata();
	fndshow();
	if(automode == 1)
	{
		switch(state)
		{
			case 0:
			Buzzer_soundOff();
			model_setwindstatedata(state);
			if(sec == 2)
			{
				state = 1;
				model_setwindstatedata(state);
				sec = 0;
			}
			break;
			case 1:
			Buzzer_soundOn();
			Buzzer_buttonOn(4, 1000);
			model_setwindstatedata(state);
			if(sec == 2)
			{
				state = 2;
				model_setwindstatedata(state);
				sec = 0;
			}
			break;
			case 2:
			Buzzer_soundOn();
			Buzzer_buttonOn(2, 1600);
			model_setwindstatedata(state);
			if(sec == 2)
			{
				state = 3;
				model_setwindstatedata(state);
				sec = 0;
			}
			break;
			case 3:
			Buzzer_soundOn();
			Buzzer_buttonOn(1, 2000);
			model_setwindstatedata(state);
			if(sec == 2)
			{
				state = 0;
				model_setwindstatedata(state);
				sec = 0;
			}
			break;
		}
	}
	else
	{

		switch(state)
		{
			case 0:
			Buzzer_soundOff();
			model_setwindstatedata(state);
			break;
			case 1:
			Buzzer_soundOn();
			Buzzer_buttonOn(4, 1000);
			model_setwindstatedata(state);
			break;
			case 2:
			Buzzer_soundOn();
			Buzzer_buttonOn(2, 1600);
			model_setwindstatedata(state);
			break;
			case 3:
			Buzzer_soundOn();
			Buzzer_buttonOn(1, 2000);
			model_setwindstatedata(state);
			break;
		}
	}
	//switch(timerset)
	//{
		//case 1:
		//fndshow();
		//break;
	//}
}