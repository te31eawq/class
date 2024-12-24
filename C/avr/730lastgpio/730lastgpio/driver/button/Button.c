#include "Button.h"

TRAFFIC_BUTTON_PORT = 0xff;
TRAFFIC_BUTTON_DDR &= ~((1<<TRAFFIC_BUTTON_AUTO) | (1<<TRAFFIC_BUTTON_MANUAL) | (1<<TRAFFIC_BUTTON_CONTROL)); //DDRA = DDRA & 0bxxxxx000
uint8_t trafficModeState = AUTO;

void button_init(button_t *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
{
	btn->DDR = ddr;
	btn->PIN = pin;
	btn->pinNum = pinNum;
	btn->prevState = 1;
	*btn->DDR &= ~(1<<btn->pinNum);
}

uint8_t Button_GetState(button_t *btn)
{
	uint8_t curState = *btn->PIN & (1<<btn->pinNum);
	if((curState ==0) && btn->prevState == 1)
	{
		_delay_ms(10);
		btn->prevState = PUSHED;
		return ACT_PUSHED;
	}
	else if((curState != 0) && btn->prevState == 0)
	{
		_delay_ms(10);
		btn->prevState = RELEASED;
		return ACT_RELEASED;
	}
	return ACT_NONE;
}
