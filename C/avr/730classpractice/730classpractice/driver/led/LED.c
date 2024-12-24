#include "LED.h"

void LEDinit(volatile uint8_t *DDR)
{
	Gpio_initport(DDR, OUTPUT);
}

void LEDallon(volatile uint8_t *PORT)
{
	Gpio_writeport(PORT, 0xff);
}

void LEDalloff(volatile uint8_t *PORT)
{
	Gpio_writeport(PORT, 0x00);
}

void LEDwritedata(volatile uint8_t *PORT, uint8_t data)
{
	Gpio_writeport(PORT, data);
}