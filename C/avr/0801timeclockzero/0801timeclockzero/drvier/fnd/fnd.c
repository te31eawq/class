#include "fnd.h"

uint16_t data;
uint16_t fndlight;

void fndinit()
{
	DDRE = 0xff;
	DDRF = 0xff;
}

void fndsystem(uint16_t dir)
{
	static uint8_t fndround = 0;
	uint16_t fndfont[10] = {0b00111111, 0b00000110,0b01011011,0b01001111, 0b01100110, 0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
	
	fndround = (fndround+1) % 4;
	switch(fndround)
	{
		case 0:
		PORTE = 0b01110000;
		PORTF = fndfont[fndlight%10];
		_delay_ms(1);
		break;
		case 1:
		PORTE = 0b10110000;
		PORTF = fndfont[fndlight/10%10];
		_delay_ms(1);
		break;
		case 2:
		PORTE = 0b11010000;
		PORTF = fndfont[fndlight/100%10];
		_delay_ms(1);
		break;
		case 3:
		PORTE = 0b11100000;
		PORTF = fndfont[(fndlight/1000)%10];
		_delay_ms(1);
		break;
	}
}

void fndtime()
{
	fndsystem(data);
}

void FND_setFndData(uint16_t data)
{
	fndlight = data;
}