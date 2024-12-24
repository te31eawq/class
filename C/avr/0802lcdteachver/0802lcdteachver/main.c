#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "driver/lcd/lcd.h"


int main(void)
{
    LCD_init();
	
	char buff[30];
	uint16_t counter = 0;
    while (1) 
    {
		sprintf(buff,"counter : %d", counter++);
		LCD_writeStringXY(0,4,buff);
		_delay_ms(1000);
    }
}

