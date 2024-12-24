#include "fnd.h"

uint16_t fndData = 0;

void fndinit()
{
	FND_DIGIT_DDR = 0xff;
	FND_DATA_DDR = 0xff;
}

void FND_dispNum(uint16_t dir)
{
	uint8_t fndfont[10] = {0b00111111, 0b00000110,0b01011011, 0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111 };
	
	static uint8_t fndDigitState = 0;
	
	fndDigitState = (fndDigitState+1) % 4; // 0 1 2 3을 무한 반복
	
	switch(fndDigitState)
	{
		case 0 :
		PORTE |= ((1<<FND_DIGIT_4) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_1));
		PORTE = 0b11100000;
		PORTF = (fndfont[fndData/1000%10] | 0b10000000);
		_delay_ms(1);
		break;
		case 1:
		PORTE |= ((1<<7) | (1<<6) | (1<<5) | (1<<4));
		PORTE = 0b11010000;
		PORTF = (fndfont[fndData/100%10]);
		_delay_ms(1);
		break;
		case 2:
		PORTE |= ((1<<7) | (1<<6) | (1<<5) | (1<<4));
		PORTE = 0b10110000;
		PORTF = (fndfont[fndData/10%10] | 0b10000000);
		_delay_ms(1);
		break;
		case 3:
		PORTE |= ((1<<7) | (1<<6) | (1<<5) | (1<<4));
		PORTE = 0b01110000;
		PORTF = fndfont[fndData%10];
		_delay_ms(1);
		break;
	}

}

void FND_setFndData(uint16_t data)
{
	fndData = data;
}

void FND_ISR_Process()
{
	FND_dispNum(fndData);
}