이 코드는 STM32 마이크로컨트롤러에서 ADC(Digital-to-Analog Converter) 값을 DMA(Direct Memory Access)를 사용하여 읽어들이고, 읽은 값을 UART를 통해 전송하는 예제입니다. 각 주요 부분에 대해 설명하겠습니다.

### 1. **전처리기 및 헤더 파일**
```c
#include "main.h"
```
- `main.h`는 이 프로젝트에서 필요한 헤더 파일들을 포함합니다. 이는 STM32 HAL 라이브러리와 마이크로컨트롤러에 맞는 설정을 포함합니다.

### 2. **전역 변수 선언**
```c
__IO uint16_t ADCxConvertValue[2] = {0};
__IO int adcFlag = 0;
```
- `ADCxConvertValue[2]` 배열은 DMA를 통해 ADC 변환 결과를 저장합니다. 배열의 크기는 2로, 두 개의 ADC 채널 값을 저장합니다.
- `adcFlag`는 ADC 변환이 완료되었음을 나타내는 플래그입니다. `HAL_ADC_ConvCpltCallback` 함수에서 이 값이 설정됩니다.

### 3. **시스템 초기화**
```c
HAL_Init();
SystemClock_Config();
MX_GPIO_Init();
MX_DMA_Init();
MX_USART2_UART_Init();
MX_ADC1_Init();
```
- `HAL_Init()`는 STM32 HAL 라이브러리의 초기화 함수로, 시스템의 기본 설정을 합니다.
- `SystemClock_Config()`는 시스템 클럭을 설정합니다.
- `MX_GPIO_Init()`, `MX_DMA_Init()`, `MX_USART2_UART_Init()`, `MX_ADC1_Init()`은 각각 GPIO, DMA, USART2(직렬 통신), ADC1을 초기화하는 함수입니다.

### 4. **ADC와 DMA 설정**
```c
if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADCxConvertValue, 2) != HAL_OK)
{
    Error_Handler();
}
```
- 이 코드는 **DMA**를 사용하여 ADC1에서 변환된 두 개의 아날로그 값을 `ADCxConvertValue` 배열에 자동으로 저장하도록 설정합니다.
- `HAL_ADC_Start_DMA()` 함수는 ADC 변환이 시작되며, DMA로 데이터를 전송하고, 변환이 완료되면 `HAL_ADC_ConvCpltCallback` 콜백 함수가 호출됩니다.

### 5. **무한 루프에서 ADC 값 처리**
```c
while (1)
{
    if (adcFlag)
    {
        adcFlag = 0;
        printf("VAR=%4d, CDS=%4d\r\n", ADCxConvertValue[0], ADCxConvertValue[1]);
        if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADCxConvertValue, 2) != HAL_OK)
        {
            Error_Handler();
        }
    }
}
```
- 이 코드에서는 `adcFlag`가 설정되면, 즉 ADC 변환이 완료되면 `ADCxConvertValue[0]`과 `ADCxConvertValue[1]` 값을 UART를 통해 출력합니다.
- 출력 후, 다시 DMA를 통해 ADC를 시작하여 지속적으로 값을 읽어옵니다.

### 6. **ADC 초기화**
```c
hadc1.Instance = ADC1;
hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
hadc1.Init.Resolution = ADC_RESOLUTION_12B;
hadc1.Init.ScanConvMode = ENABLE;
hadc1.Init.NbrOfConversion = 2;
hadc1.Init.DMAContinuousRequests = ENABLE;
```
- `ADC1`을 초기화하여 **12비트 해상도**로 아날로그 값을 디지털 값으로 변환하도록 설정합니다.
- `ScanConvMode`가 활성화되어 여러 개의 채널을 한 번에 읽을 수 있습니다. 두 채널(`ADC_CHANNEL_0`과 `ADC_CHANNEL_1`)을 읽습니다.
- `DMAContinuousRequests`를 활성화하여 DMA가 지속적으로 데이터를 요청하도록 설정합니다.

### 7. **DMA 초기화**
```c
__HAL_RCC_DMA2_CLK_ENABLE();
HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
```
- `DMA2` 클럭을 활성화하고, DMA 스트림0에 대한 인터럽트 우선순위를 설정하여 **DMA 인터럽트**를 활성화합니다. 이를 통해 DMA 전송이 완료되면 `HAL_ADC_ConvCpltCallback` 함수가 호출됩니다.

### 8. **USART 초기화 (UART)**
```c
huart2.Instance = USART2;
huart2.Init.BaudRate = 115200;
huart2.Init.Mode = UART_MODE_TX_RX;
if (HAL_UART_Init(&huart2) != HAL_OK)
{
    Error_Handler();
}
```
- USART2를 직렬 통신을 위해 설정합니다. **115200 보율**로 데이터 전송 및 수신을 설정하고, `TX`와 `RX` 모드를 활성화하여 데이터를 송수신할 수 있습니다.

### 9. **ADC 변환 완료 콜백 함수**
```c
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
    adcFlag = 1;
}
```
- 이 함수는 ADC 변환이 완료되면 호출됩니다. 이때 `adcFlag`를 1로 설정하여 메인 루프에서 변환 완료된 값을 처리할 수 있도록 합니다.

### 10. **에러 핸들러**
```c
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
```
- 이 함수는 에러가 발생했을 때 호출됩니다. `__disable_irq()`는 인터럽트를 비활성화하여 프로그램이 중단되지 않도록 하고, 무한 루프에 빠져 무한 대기합니다.

### 11. **GPIO 설정**
```c
GPIO_InitStruct.Pin = B1_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
```
- 이 코드는 `B1` 버튼이 눌리면 인터럽트를 발생시키도록 설정합니다. 버튼이 눌리면 `GPIO_MODE_IT_FALLING` 모드로 설정하여 하강 에지를 감지합니다.

### 12. **전송을 위한 `fputc` 구현 (Retargeting printf)**
```c
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
```
- 이 함수는 `printf` 함수가 호출될 때, 데이터를 `USART2`로 송신하도록 합니다. 이 방식은 `printf` 출력을 UART로 리디렉션하는 방법입니다.

---

### 주요 기술 설명

1. **DMA (Direct Memory Access)**  
   DMA는 CPU의 개입 없이 주변 장치와 메모리 간에 데이터를 직접 전송하는 방법입니다. 이 코드는 ADC 값을 DMA를 통해 자동으로 메모리로 전송하여, CPU의 부하를 줄이고 효율적인 데이터 처리를 가능하게 합니다.

2. **ADC (Analog-to-Digital Converter)**  
   ADC는 아날로그 신호를 디지털 값으로 변환하는 장치입니다. STM32에서 제공하는 ADC를 사용하여 아날로그 값을 읽어 디지털 값으로 변환하고, 이를 DMA를 통해 처리합니다.

3. **USART (Universal Asynchronous Receiver-Transmitter)**  
   UART는 직렬 데이터 통신을 위한 프로토콜입니다. 이 코드는 `USART2`를 사용하여 ADC 값을 외부로 출력합니다.

4. **콜백 함수**  
   `HAL_ADC_ConvCpltCallback`와 같은 콜백 함수는 하드웨어 인터럽트나 이벤트가 발생했을 때 호출됩니다. 이 함수는 ADC 변환이 완료되었을 때, DMA가 데이터를 처리할 수 있게 합니다.

---

이 코드는 STM32에서 ADC, DMA, UART를 활용한 효율적인 데이터 처리 예시로, 외부 장치와의 빠르고 효율적인 데이터 송수신이 가능하도록 구성되어 있습니다.