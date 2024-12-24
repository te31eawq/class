#include "wind.h"
uint8_t state;
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
	timerdecmilisec();
}

ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}



void wind_init()
{
	
	UART0_init();
	TIM0init();
	TIM2init();
	Gpioinit();
	listen_init();
	presenterinit();
	stopwatchinit();
	Buzzer_init();
	milisec2 = 0;
	sec2 = 0;
	min2 = 0;
	hour2 = 0;
}

void wind_execute()
{
	UART0_execute();

	listen_execute();
	
	uint8_t timerfan, timerset;
	timerset = model_getwindtimerdata();
	timerfan = model_gettimestartdata();
	state = model_getwindstatedata();
	sec = model_getwindautodata();
	automode = model_getwindautodata();
	fndshow();
	if(timerset >= 1)
	{
		if(timerfan != 0)
		{
			Buzzer_soundOn();
			Buzzer_buttonOn(4, 1000);
			return;
		}
	}
	if(automode == 1)
	{
		windauto();
	}
	else if(automode == 0)
	{
		windhand();	
	}
}

void windauto()
{
	switch(state)
	{
		case 0:
		
		showstrength(state);
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
		showstrength(state);
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
		showstrength(state);
		Buzzer_soundOn();
		Buzzer_buttonOn(2,1600);
		model_setwindstatedata(state);
		if(sec == 2)
		{
			state = 3;
			model_setwindstatedata(state);
			sec = 0;
		}
		break;
		case 3:
		showstrength(state);
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

void windhand()
{
	switch(state)
	{
		case 0:
		showstrength(state);
		Buzzer_soundOff();
		model_setwindstatedata(state);
		break;
		case 1:
		showstrength(state);
		Buzzer_soundOn();
		Buzzer_buttonOn(4, 1000);
		model_setwindstatedata(state);
		break;
		case 2:
		showstrength(state);
		Buzzer_soundOn();
		Buzzer_buttonOn(2, 1600);
		model_setwindstatedata(state);
		break;
		case 3:
		showstrength(state);
		Buzzer_soundOn();
		Buzzer_buttonOn(1, 2000);
		model_setwindstatedata(state);
		break;
	}
}

void UART0_execute()
{
	if(UART0_GetRxFlag())
	{
		UART0_clearRxFlag();
		uint8_t *rxString = UART0_readRxBuff();
		
		if(!strcmp((char *)rxString, "WIND_OFF\n"))
		{
			state = 0;
			model_setwindstatedata(state);
			automode = 0;
			model_setwindautodata(automode);
			if(state == 0)
			{
				printf("STATE : WIND_OFF\n");
			}
		}
		else if(!strcmp((char *)rxString, "WICK\n"))
		{
			state = 1;
			model_setwindstatedata(state);
			if(state == 1)
			{
				printf("STATE : WICK\n");
			}
		}
		else if(!strcmp((char *)rxString, "NORMAL\n"))
		{
			state = 2;
			model_setwindstatedata(state);
			if(state == 2)
			{
				printf("STATE : NORMAL\n");
			}
		}
		else if(!strcmp((char *)rxString, "STRONG\n"))
		{
			state = 3;
			model_setwindstatedata(state);
			if(state == 3)
			{
				printf("STATE : STRONG\n");
			}
		}
		else if(!strcmp((char *)rxString, "AUTOMODE\n"))
		{
			automode = 1;
			model_setwindautodata(automode);
			if(automode == 1)
			{
				printf("STATE : AUTOMODE\n");
			}
		}
	}
}