#include "TIM.h"

void TIM0init() // 1ms overflow Interrupt, FND Display 용도 
{
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));	// 128 PreScaler 설정
	TIMSK |= (1<<TOIE0);							// TIMSK Timer/Counter0 overflow Interrupt Enable
	TCNT0 = 130;									// 130부터 시작하라고 선언
}