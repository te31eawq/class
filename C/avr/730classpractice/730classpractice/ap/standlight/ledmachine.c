#include "ledmachine.h"

button_t btnMod, btnOff;
uint8_t ledState;
uint8_t ledplus;

void StandLightinit()
{
	ledState = 0;
	ledplus = 0;
	LEDinit(&LED_DDR);
	
	button_init(&btnMod, &BUTTON_DDR, &BUTTON_PIN, BUTTON_MODE);
	button_init(&btnOff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
	
}

void StandLightrun()
{
	StandLight_eventCheck();
	StandLight_execute();
	_delay_ms(1);
}

void StandLight_eventCheck()
{
	if(Button_GetState(&btnMod) == 1)
	{
		ledState++;
	}
	if(Button_GetState(&btnOff) == 1)
	{
		ledState = 0;
	}
}

void StandLight_execute()
{
	switch(ledState)
	{
		case 0 :
		LEDwritedata(&LED_PORT, 0x00);
		break;
		case 1 :
		LEDwritedata(&LED_PORT, 0b00000011);
		break;
		case 2 :
		LEDwritedata(&LED_PORT, 0b00001111);
		break;
		case 3 :
		LEDwritedata(&LED_PORT, 0b00111111);
		break;
		case 4 :
		LEDwritedata(&LED_PORT, 0xff);
		break;
		case 5:
		ledState = 0;
		break;
	}
}