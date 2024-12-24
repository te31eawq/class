#include "LED.h"

uint8_t LED_PORT;

void LEDinit()
{
	LEDDDR = 0xff;
}

void LEDallon()
{
	
	LEDPORT = 0xff;
}

void LEDwritedata(uint8_t data)
{
	LEDPORT = data;
}