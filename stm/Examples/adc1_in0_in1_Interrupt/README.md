이 코드는 STM32 마이크로컨트롤러에서 **ADC (Analog-to-Digital Converter)** 값을 읽고, **UART (Universal Asynchronous Receiver/Transmitter)**를 통해 전송하는 예제입니다. ADC는 아날로그 신호를 디지털 값으로 변환하며, UART는 외부 장치와 데이터를 송수신하는 통신 방법입니다. 주요 기능은 ADC 값을 읽고, 읽은 값을 UART를 통해 출력하는 것입니다.

### 코드 설명:

#### 1. **헤더 파일 및 매크로 정의**

```c
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
```
- 이 부분은 **`printf`** 출력 리디렉션을 위해 사용되는 매크로입니다. **`__io_putchar`** 또는 **`fputc`** 함수는 **USART**를 통해 문자 출력 기능을 제공합니다. `printf` 함수가 호출되면, 이 함수가 실제로 데이터를 UART로 전송합니다.

#### 2. **전역 변수**

```c
__IO uint16_t ADCxConvertValue[2]={0};
__IO int adcFlag=0;
```
- `ADCxConvertValue[2]`는 두 개의 ADC 채널 값을 저장하는 배열입니다. ADC 변환이 완료되면 DMA나 인터럽트를 통해 값이 이 배열에 저장됩니다.
- `adcFlag`는 ADC 변환이 완료되었음을 알리는 플래그입니다. 메인 루프에서 이 플래그를 확인하여 변환된 값을 출력합니다.

#### 3. **시스템 초기화 및 설정**
```c
HAL_Init();
SystemClock_Config();
MX_GPIO_Init();
MX_USART2_UART_Init();
MX_ADC1_Init();
```
- **`HAL_Init()`**: STM32 HAL 라이브러리의 초기화 함수로, 시스템 초기화 및 설정을 수행합니다.
- **`SystemClock_Config()`**: 시스템 클럭을 설정하는 함수입니다.
- **`MX_GPIO_Init()`**: GPIO 포트 초기화 함수입니다.
- **`MX_USART2_UART_Init()`**: USART2 직렬 통신 초기화 함수입니다.
- **`MX_ADC1_Init()`**: ADC1 초기화 함수입니다.

#### 4. **ADC1 초기화**
```c
hadc1.Instance = ADC1;
hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
hadc1.Init.Resolution = ADC_RESOLUTION_12B;
hadc1.Init.ScanConvMode = ENABLE;
hadc1.Init.NbrOfConversion = 2;
```
- **`hadc1.Instance = ADC1;`**: ADC1 인스턴스를 사용하여 ADC를 초기화합니다.
- **`Resolution = ADC_RESOLUTION_12B;`**: ADC 해상도를 12비트로 설정합니다.
- **`ScanConvMode = ENABLE;`**: 여러 채널을 순차적으로 읽을 수 있도록 **Scan Mode**를 활성화합니다.
- **`NbrOfConversion = 2;`**: 2개의 ADC 채널을 읽도록 설정합니다.

#### 5. **ADC 채널 설정**
```c
sConfig.Channel = ADC_CHANNEL_0;
sConfig.Rank = 1;
sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
HAL_ADC_ConfigChannel(&hadc1, &sConfig);

sConfig.Channel = ADC_CHANNEL_1;
sConfig.Rank = 2;
HAL_ADC_ConfigChannel(&hadc1, &sConfig);
```
- 두 개의 ADC 채널(채널 0과 채널 1)을 설정하고, 각 채널의 순위와 샘플링 시간을 지정합니다.

#### 6. **UART2 초기화**
```c
huart2.Instance = USART2;
huart2.Init.BaudRate = 115200;
huart2.Init.WordLength = UART_WORDLENGTH_8B;
huart2.Init.StopBits = UART_STOPBITS_1;
huart2.Init.Mode = UART_MODE_TX_RX;
```
- **USART2**를 직렬 통신을 위해 설정합니다. `115200` 보율로 송수신을 설정하며, 8비트 단어 길이와 1비트 정지 비트를 사용합니다.

#### 7. **ADC 변환 완료 인터럽트 처리**

```c
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
	static int ch=0;

	if(ch == 0)
	{
		ADCxConvertValue[ch] = HAL_ADC_GetValue(AdcHandle);
		ch = 1;
	}
	else if(ch == 1)
	{
		ADCxConvertValue[ch] = HAL_ADC_GetValue(AdcHandle);
		ch = 0;
		adcFlag = 1;
	}
}
```
- 이 함수는 **ADC 변환이 완료되었을 때** 호출됩니다. 두 개의 ADC 채널을 순차적으로 읽어 `ADCxConvertValue` 배열에 저장합니다.
- `ch` 변수를 사용하여 채널 0과 채널 1의 값을 번갈아 저장합니다. 두 채널의 변환이 모두 완료되면, `adcFlag`를 1로 설정하여 메인 루프에서 처리할 수 있게 합니다.

#### 8. **메인 루프**

```c
while (1)
{
	if(adcFlag)
	{
		adcFlag = 0;
		printf("VAR=%4d, CDS=%4d\r\n", ADCxConvertValue[0], ADCxConvertValue[1]);
		if(HAL_ADC_Start_IT(&hadc1) != HAL_OK)
		{
			Error_Handler();
		}
	}
}
```
- `adcFlag`가 설정되면, 두 개의 ADC 값(`ADCxConvertValue[0]`과 `ADCxConvertValue[1]`)을 **UART**를 통해 출력합니다.
- 출력한 후, **ADC 변환을 다시 시작**합니다. `HAL_ADC_Start_IT()`는 **ADC 인터럽트** 모드에서 변환을 시작합니다. 이를 통해 ADC 값이 변환될 때마다 인터럽트가 발생하여, 변환된 값을 읽고 처리합니다.

#### 9. **에러 핸들러**

```c
void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}
}
```
- 이 함수는 에러가 발생했을 때 호출됩니다. 인터럽트를 비활성화하고 무한 루프에 빠져 프로그램을 중단시킵니다.

#### 10. **GPIO 설정**
```c
GPIO_InitStruct.Pin = B1_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
```
- **B1 버튼**에 하강 에지 인터럽트를 설정하여, 버튼을 누르면 인터럽트가 발생합니다.

---

### 전체 흐름 요약:
1. **시작**: STM32 마이크로컨트롤러가 초기화되고, 시스템 클럭, GPIO, UART, ADC가 설정됩니다.
2. **ADC 변환**: `HAL_ADC_Start_IT()`를 호출하여 **ADC 변환**을 시작합니다.
3. **ADC 값 읽기**: 변환이 완료되면, `HAL_ADC_ConvCpltCallback` 콜백 함수에서 두 개의 채널 값을 읽고 `adcFlag`를 설정합니다.
4. **UART 출력**: 메인 루프에서 `adcFlag`가 설정되면 ADC 값을 UART를 통해 외부로 출력합니다.
5. **반복**: 변환이 끝나면 다시 ADC 변환을 시작하여 값을 지속적으로 읽습니다.

이 코드는 **ADC 값을 읽고** **UART를 통해 전송**하는 기본적인 예제입니다.