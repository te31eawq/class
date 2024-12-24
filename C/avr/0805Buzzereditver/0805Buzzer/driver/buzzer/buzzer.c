#include "buzzer.h"

void Buzzer_soundOn()
{
	TCCR3A |= ((1<<COM3A1) | (0<<COM3A0));
}

void Buzzer_soundOff()
{
	TCCR3A &= ~((1<<COM3A1) | (1<<COM3A0));
}

void Buzzer_makehz(uint16_t hertz)
{
	if (hertz < 100) hertz = 100;
	else if(hertz > 5000) hertz = 5000;
	BUZZER_ICR = (250000/  hertz)-1;
	BUZZER_OCR = BUZZER_ICR / 2;				//Duty Cycle 50%
}

void Buzzer_init()
{
	TCCR3B |= (0<<CS32) | (1<<CS31) | (1<<CS30); // 주기값
	
	TCCR3B |= ((1<<WGM33) | (1<<WGM32));
	TCCR3A |= ((1<<WGM31) | (0<<WGM30));		// Fast PWM mode
	
	DDRE |= (1<<3);								// 핀 값 제공
}

void Buzzer_buttonOn()
{
	Buzzer_makehz(1318);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makehz(1174);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makehz(1046);
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makehz(1174);
	_delay_ms(100);
	TCNT3 = 0;
}