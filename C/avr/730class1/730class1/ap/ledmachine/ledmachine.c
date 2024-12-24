#include "ledmachine.h" 

uint8_t ledData;
button_t btnNext, btnPrev;
uint8_t ledState;

void ledmachineinit()
{
	ledData = 0x00;
	DDRA = 0x00;
	PORTA = 0xff;
	button_init(&btnNext, &DDRA, &PINA, 0);
	button_init(&btnPrev, &DDRA, &PINA, 1);
	
	LEDinit();
}

void LED1()
{
	ledData ^= 0x01;
	LEDwritedata(ledData);
}
void LED2()
{
	ledData ^= 0x02;
	LEDwritedata(ledData);
}
void LED3()
{
	ledData ^= 0x04;
	LEDwritedata(ledData);
}
void LED4()
{
	ledData ^= 0x08;
	LEDwritedata(ledData);
}

void ledmachineexecute()
{
	
	switch(ledState)
	{
		case 0:
		LED1();
		if(Button_GetState(&btnNext)==ACT_PUSHED)
		{
			ledState = 1;
			ledData = 0x00;
		}
		else if(Button_GetState(&btnPrev)==ACT_RELEASED)
		{
			ledState = 3;
			ledData = 0x00;
		}
		break;
		case 1:
		LED2();
		if(Button_GetState(&btnNext)==ACT_PUSHED)
		{
			ledState = 2;
			ledData = 0x00;
		}
		else if(Button_GetState(&btnPrev)==ACT_RELEASED)
		{
			ledState = 0;
			ledData = 0x00;
		}
		break;
		case 2:
		LED3();
		if(Button_GetState(&btnNext)==ACT_PUSHED)
		{
			ledState = 3;
			ledData = 0x00;
		}
		else if(Button_GetState(&btnPrev)==ACT_RELEASED)
		{
			ledState = 1;
			ledData = 0x00;
		}
		break;
		case 3:
		LED4();
		if(Button_GetState(&btnNext)==ACT_PUSHED)
		{
			ledState = 0;
			ledData = 0x00;
		}
		else if(Button_GetState(&btnPrev)==ACT_RELEASED)
		{
			ledState = 2;
			ledData = 0x00;
		}
		break;
	}
	_delay_ms(100);
}
