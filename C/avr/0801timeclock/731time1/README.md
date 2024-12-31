## 오버플로우 인터럽트

- **타이머의 오버플로우**는 타이머의 카운터가 최댓값(예: 8비트 타이머의 경우 255)을 초과하여 다시 0으로 리셋되는 시점입니다.
- 이 인터럽트는 타이머가 지정된 값(최댓값)에 도달하여 "오버플로우" 현상이 발생할 때 발생합니다. 예를 들어, 8비트 타이머의 경우 255에서 카운트가 다시 0으로 되돌아가는 순간에 인터럽트가 발생합니다.
- **용도**: 오버플로우 인터럽트는 주로 주기적인 시간 지연이나 주기적인 작업을 실행할 때 사용됩니다. 예를 들어, 1ms마다 인터럽트를 발생시켜 일정 시간 간격으로 작업을 처리할 수 있습니다.
```c
ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0 = 130;
}


void TIM0init() // 1ms overflow Interrupt, FND Display 용도 
{
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));	// 128 PreScaler 설정
	TIMSK |= (1<<TOIE0);							// TIMSK Timer/Counter0 overflow Interrupt Enable
	TCNT0 = 130;									// 130부터 시작하라고 선언
}
```


## CTC (비교 매치 인터럽트)

- **비교 매치**는 타이머의 카운터 값과 **비교 레지스터(OCRx)**에 설정된 값이 일치할 때 발생합니다.
- 예를 들어, 타이머가 카운트하는 동안 카운터 값이 설정된 비교 값(예: OCR2)과 같아지면 **비교매치 인터럽트**가 발생합니다.
- **용도**: 비교매치 인터럽트는 특정 시간 주기마다 정확하게 작업을 실행할 수 있도록 하며, 더 정밀한 시간 제어가 필요한 경우 유용합니다.
```c
ISR(TIMER2_COMP_vect)
{
	stopwatchincmilisec();
}


void TIM2init()
{
	// Timer/Counter 2 1/64 1ms period interrupt enable
	TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));	// 128 PreScaler 설정
	TIMSK |= (1<<OCIE2);
	TCCR2 |= ((1<<WGM21) | (0<<WGM20));
	OCR2 = 250-1;		// TIMSK Timer/Counter0 overflow Interrupt Enable
}
```