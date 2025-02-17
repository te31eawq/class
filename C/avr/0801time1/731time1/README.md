## 오버플로우 인터럽트

```c
void TIM0init() // 1ms overflow Interrupt, FND Display 용도 
{
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));	// 128 PreScaler 설정
	TIMSK |= (1<<TOIE0);							// TIMSK Timer/Counter0 overflow Interrupt Enable
	TCNT0 = 130;									// 130부터 시작하라고 선언
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

이 코드는 **AVR 마이크로컨트롤러**에서 타이머 0과 타이머 2를 설정하여 특정 주기마다 인터럽트를 발생시키도록 하는 코드입니다. 각 타이머에 대한 설명을 추가하여 코드를 자세히 설명하겠습니다.

### 1. `TIM0init()` 함수

이 함수는 타이머 0을 초기화하여 **1ms마다 오버플로우 인터럽트**를 발생시키는 설정을 합니다. FND (7세그먼트 디스플레이)와 같은 장치의 주기적인 업데이트에 사용할 수 있습니다.

#### 코드 분석:

```c
TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));  // 128 PreScaler 설정
```
- `TCCR0`는 타이머/카운터 0의 제어 레지스터입니다.
- `CS02`, `CS01`, `CS00`는 타이머의 클럭 선택 비트입니다. 이 비트들을 설정하여 타이머의 클럭 소스를 결정합니다.
- `CS02=1`, `CS01=0`, `CS00=1`로 설정하면 **128 프리스케일러**를 사용합니다. 즉, 타이머가 시스템 클럭을 128로 나누어 동작하도록 설정됩니다.
  - 이 설정은 타이머의 카운터 속도를 줄여주어 더 긴 시간 동안 카운트를 할 수 있게 합니다.

```c
TIMSK |= (1<<TOIE0);  // Timer/Counter 0 overflow Interrupt Enable
```
- `TIMSK`는 타이머 인터럽트 마스크 레지스터입니다.
- `TOIE0`는 타이머 0의 오버플로우 인터럽트를 활성화하는 비트입니다. 이 비트를 1로 설정하면 타이머 0이 오버플로우될 때 인터럽트가 발생합니다.

```c
TCNT0 = 130;  // 130부터 시작하라고 선언
```
- `TCNT0`는 타이머 0의 카운터 값을 설정하는 레지스터입니다.
- 타이머 0은 8비트 카운터이기 때문에 카운트는 0부터 255까지 가능합니다. 여기서는 **130부터 시작**하도록 설정했습니다.
  - `128` 프리스케일러와 결합하여 약 1ms마다 오버플로우가 발생하도록 할 수 있습니다. (타이머의 카운터는 255에서 0으로 넘어가는데, 카운트 시작 값으로 130을 설정함으로써 타이머가 130에서 시작되어 255까지 카운트하고 오버플로우가 발생하게 됩니다.)

### 2. `TIM2init()` 함수

이 함수는 타이머 2를 초기화하여 **1ms마다 비교매치 인터럽트**를 발생시키는 설정을 합니다.

#### 코드 분석:

```c
TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));  // 128 PreScaler 설정
```
- `TCCR2`는 타이머/카운터 2의 제어 레지스터입니다.
- `CS22`, `CS21`, `CS20`는 타이머 2의 클럭 선택 비트입니다.
- `CS22=0`, `CS21=1`, `CS20=1`로 설정하면 **64 프리스케일러**를 사용합니다. 즉, 타이머 2가 시스템 클럭을 64로 나누어 동작하도록 설정됩니다.

```c
TIMSK |= (1<<OCIE2);  // Timer/Counter 2 Output Compare Interrupt Enable
```
- `TIMSK`는 타이머 인터럽트 마스크 레지스터입니다.
- `OCIE2`는 타이머 2의 출력 비교 인터럽트를 활성화하는 비트입니다. 이 비트를 1로 설정하면 타이머 2의 **비교매치**가 발생할 때 인터럽트가 발생합니다.

```c
TCCR2 |= ((1<<WGM21) | (0<<WGM20));  // CTC 모드 설정
```
- `TCCR2`에서 `WGM21`과 `WGM20` 비트는 타이머의 모드를 설정하는 비트입니다.
- `WGM21=1`, `WGM20=0`으로 설정하면 **CTC (Clear Timer on Compare Match) 모드**로 설정됩니다. 이 모드에서는 타이머의 카운터가 `OCR2` 레지스터에 설정된 값에 도달하면 카운터가 0으로 리셋됩니다.

```c
OCR2 = 250-1;  // OCR2에 비교할 값 설정
```
- `OCR2`는 타이머 2의 **출력 비교 레지스터**입니다. 이 값은 타이머의 카운터 값이 비교할 값으로 사용됩니다.
- `OCR2 = 250 - 1`로 설정하면 타이머가 카운트하다가 249에 도달할 때마다 **비교매치**가 발생하고, 인터럽트가 발생합니다. 이 설정은 약 1ms 주기마다 비교매치 인터럽트가 발생하도록 합니다.

### 결론

- **타이머 0 (`TIM0init()`)**: 이 함수는 타이머 0을 설정하여 **128 프리스케일러**를 사용하고, 카운터 130에서 시작하여 1ms마다 **오버플로우 인터럽트**를 발생시킵니다.
- **타이머 2 (`TIM2init()`)**: 이 함수는 타이머 2를 설정하여 **64 프리스케일러**를 사용하고, 카운터 값이 `OCR2`와 비교될 때마다 **비교매치 인터럽트**를 발생시킵니다.

각 타이머는 **1ms**마다 인터럽트를 발생시키도록 설정되어 있으며, 주로 시간 지연 또는 주기적인 작업을 처리하는 데 사용됩니다.