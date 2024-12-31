## 오버플로우 인터럽트

```c
void TIM0init() // 1ms overflow Interrupt, FND Display 용도 
{
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));	// 128 PreScaler 설정
	TIMSK |= (1<<TOIE0);							// TIMSK Timer/Counter0 overflow Interrupt Enable
	TCNT0 = 130;									// 130부터 시작하라고 선언
}
```

### 프리스케일러(Prescaler)란?
- **Prescaler**는 시스템 클럭을 나누어 주는 역할을 합니다. 예를 들어 시스템 클럭이 16MHz일 경우, 프리스케일러를 128로 설정하면 128배 느린 신호로 카운팅하게 됩니다
- 128 Prescaler => 16,000,000(16MHz) / 128 = 125,000의 신호를 1초동안 받게 됩ㅂ니다 
- TCNT0 = 130으로 255까지 126
- 타이머 주파수 = 16,000,00 / 128 = 125,000Hz.
- 1 / 125,000 = 8μs (마이크로초)
- 카운트 시간 = (255 - 130 + 1) x 8μs = 126 x 8 = 1.008ms
