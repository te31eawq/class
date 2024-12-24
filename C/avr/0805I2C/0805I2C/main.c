#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "driver/LCD_I2C/LCD_I2C.h"

int main(void)
{
	LCDinit();
	
	char buff[30];
	uint16_t counter = 0;
	
    while (1) 
    {
		sprintf(buff, "counter = %5d", counter++);
		LCDwrtiestringxy(0,1, buff);
		_delay_ms(10);
    }
}

