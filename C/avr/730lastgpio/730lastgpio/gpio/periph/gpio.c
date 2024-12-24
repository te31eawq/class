#include "GPIO.h"

// DDR 1. port 2. pin

void Gpio_initport(volatile uint8_t* DDR, uint8_t dir)
{
	if(dir == OUTPUT)
	{
		*DDR = 0xff;
	}
	else
	{
		*DDR = 0x00;
	}
}
void Gpio_initpin(volatile uint8_t *DDR, uint8_t dir, uint8_t pinNum)
{
	if (dir == OUTPUT)
	{
		*DDR |= (1<<pinNum);
	}
	else
	{
		*DDR &= ~(1<<pinNum);
	}
}
void Gpio_writeport(volatile uint8_t* PORT, uint8_t data)
{
	*PORT = data;
}
void Gpio_writepin(volatile uint8_t* PORT, uint8_t pinNum, uint8_t state)
{
	if(state == GPIO_PIN_SET)
	{
		*PORT |= (1<<pinNum);
	}
	else
	{
		*PORT &= ~(1<<pinNum);
	}
}
uint8_t Gpio_readport(volatile uint8_t* PIN)
{
	return *PIN;
}
uint8_t Gpio_readpin(volatile uint8_t* PIN, uint8_t pinNum)
{
	return ((*PIN & (1<<pinNum)) != 0);
}
