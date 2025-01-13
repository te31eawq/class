### 주요 코드와 개념 설명

---

### 1. **타이머 인터럽트 설정 (TIM3)**

```c
htim3.Instance = TIM3;
htim3.Init.Prescaler = 84-1;        // 84MHz / 84 = 1MHz => 1us 타이머 주기
htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
htim3.Init.Period = 1000-1;         // 1000 * 1us = 1ms => 1ms마다 인터럽트 발생
htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
{
    Error_Handler();
}
```

**개념**: 타이머는 하드웨어에서 특정 간격으로 시간을 측정하고, 그 주기마다 인터럽트를 발생시킬 수 있는 기능을 제공합니다. 이 코드는 타이머 `TIM3`를 설정하는 부분입니다.

- **Prescaler (84-1)**: STM32의 시스템 클럭은 84 MHz로 설정되어 있는데, 이를 84로 나누어 타이머 주기를 1us로 설정합니다. 즉, 타이머는 1us마다 카운팅을 합니다.
- **Period (1000-1)**: 1ms마다 인터럽트를 발생시키기 위해 1ms에 해당하는 주기인 1000 카운트를 설정합니다.
- **타이머 초기화**: `HAL_TIM_Base_Init()`을 통해 타이머를 초기화하고 설정을 적용합니다.

---

### 2. **인터럽트 발생 및 처리 (HAL_TIM_PeriodElapsedCallback)**

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static int tim3Cnt = 0;
    tim3Cnt++;
    if (tim3Cnt == 1000)  // 1초가 경과
    {
        tim3Flag1Sec = 1;   // 1초 플래그 설정
        tim3Sec++;           // 1초가 경과할 때마다 초 수 증가
        tim3Cnt = 0;         // 카운터 리셋
    }
}
```

**개념**: `HAL_TIM_PeriodElapsedCallback` 함수는 타이머 인터럽트가 발생했을 때 호출됩니다. 이 함수 내에서 타이머가 1초마다 수행할 동작을 정의합니다.

- **타이머 카운터 관리**: `tim3Cnt`는 타이머 인터럽트가 발생할 때마다 카운트가 증가하며, 1000번 카운트되면 1초가 경과한 것으로 판단하여 `tim3Flag1Sec`를 1로 설정합니다.
- **1초 플래그**: 1초가 경과할 때마다 `tim3Sec` 변수를 증가시키고, `tim3Flag1Sec`를 1로 설정하여 메인 루프에서 1초마다 해야 할 작업(예: LED 토글)을 수행합니다.

---

### 3. **LED 토글 및 UART 출력**

```c
if(tim3Flag1Sec)
{
    tim3Flag1Sec = 0;  // 플래그 리셋
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); // LED 토글
    printf("tim3Sec : %d\r\n", tim3Sec); // 현재 초 값 출력
}
```

**개념**: `tim3Flag1Sec`가 1이면 1초가 경과한 것이므로, 그때마다 LED를 토글하고, `tim3Sec` 값을 UART로 출력합니다.

- **LED 토글**: `HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);`는 `LD2` 핀에 연결된 LED를 토글합니다. 즉, LED가 켜져 있으면 끄고, 꺼져 있으면 킵니다.
- **UART 출력**: `printf()` 함수는 UART를 통해 문자열을 전송할 수 있습니다. `tim3Sec`의 값을 매초 출력하여 현재 경과 시간을 확인할 수 있습니다.

---

### 4. **USART 설정 (UART 통신)**

```c
huart2.Instance = USART2;
huart2.Init.BaudRate = 115200;
huart2.Init.WordLength = UART_WORDLENGTH_8B;
huart2.Init.StopBits = UART_STOPBITS_1;
huart2.Init.Parity = UART_PARITY_NONE;
huart2.Init.Mode = UART_MODE_TX_RX;
huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
huart2.Init.OverSampling = UART_OVERSAMPLING_16;
if (HAL_UART_Init(&huart2) != HAL_OK)
{
    Error_Handler();
}
```

**개념**: `USART`는 UART 통신을 설정하는 하드웨어 모듈입니다. `USART2`를 사용하여 컴퓨터나 다른 장치와 데이터를 송수신할 수 있습니다.

- **Baud Rate (115200)**: 데이터 전송 속도를 설정합니다. 여기서는 115200bps(초당 115200 비트)를 사용하여 데이터를 송수신합니다.
- **Word Length (8비트)**: 1개의 데이터 비트 길이를 8비트로 설정합니다.
- **Parity (없음)**: 패리티 비트를 사용하지 않도록 설정합니다.
- **Mode (TX/RX)**: 송수신 모드로 설정하여 데이터 송수신이 가능하도록 합니다.

---

### 5. **GPIO 설정 (LD2 핀 제어)**

```c
HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);  // LED 초기 상태 OFF
HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct); // LD2 핀 초기화
```

**개념**: GPIO는 외부 장치(예: LED, 버튼 등)를 제어하는 하드웨어입니다. 이 코드는 LD2 핀을 출력 모드로 설정하여 LED를 제어하는 부분입니다.

- **핀 초기화**: `HAL_GPIO_Init()`을 사용하여 `LD2` 핀을 출력 모드로 설정하고, 초기 상태를 **OFF**로 설정합니다.

---

### 6. **메인 루프 (동작의 흐름)**

```c
while (1)
{
    if(tim3Flag1Sec)
    {
        tim3Flag1Sec = 0;
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        printf("tim3Sec : %d\r\n", tim3Sec);
    }
}
```

**개념**: `while(1)`은 무한 루프이며, 이 루프는 계속해서 실행됩니다. 1초가 경과할 때마다 LED를 토글하고, 타이머 값을 UART로 출력하는 작업을 수행합니다.

- **조건 확인**: `tim3Flag1Sec`가 1이면 1초가 경과한 것이므로, LED를 토글하고 타이머 값을 출력합니다. 그 후 `tim3Flag1Sec`를 0으로 리셋하여 다음 1초가 경과할 때까지 기다립니다.

---

### 결론:

이 코드는 **STM32**의 타이머와 인터럽트 기능을 활용하여 **1ms마다 타이머 인터럽트를 발생시키고, 1초마다 LED를 토글**하며, **타이머 값을 UART로 출력**하는 예제입니다. 타이머 설정, 인터럽트 처리, GPIO 제어, UART 통신 등의 주요 기능을 사용하는 방법을 보여주고 있습니다.

- **타이머**와 **인터럽트**는 시간 기반 이벤트 처리에 매우 유용합니다.
- **UART**를 통해 외부 장치와 통신할 수 있습니다.
- **GPIO**를 사용하여 물리적 장치를 제어할 수 있습니다.

이 코드는 기본적인 타이머와 인터럽트 기반의 동작을 설정하는 데 유용한 예제입니다.