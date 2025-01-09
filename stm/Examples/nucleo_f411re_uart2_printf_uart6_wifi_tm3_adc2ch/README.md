# 프로젝트 개요

이 프로젝트는 STM32 기반의 마이크로컨트롤러에서 Wi-Fi 기능을 사용하여 데이터를 송수신하는 프로그램입니다. 이 코드는 ADC를 통해 데이터를 읽고, 주기적으로 Wi-Fi를 통해 데이터를 전송하며, 외부 장치와 통신을 위한 명령을 처리합니다. 또한 타이머와 DMA를 사용하여 주기적인 작업을 처리하고, GPIO를 통해 LED 상태를 제어합니다.

## 주요 기능
1. **Wi-Fi 통신**: ESP 모듈과의 통신을 통해 명령을 송수신합니다.
2. **ADC 값 측정**: ADC를 사용하여 센서 값을 읽어옵니다.
3. **타이머 기능**: 주기적으로 1초 및 5초 간격으로 작업을 수행합니다.
4. **LED 제어**: 외부 명령에 따라 LED를 켜거나 끕니다.

## 파일 구조

- `main.c`: 시스템 초기화, 메인 루프, 타이머 및 ADC 인터럽트 처리 등을 담당하는 코드입니다.
- `esp.c`: ESP 모듈과의 통신을 담당하는 코드입니다.
- `drv_uart.c`: UART 초기화 및 데이터 송수신을 담당합니다.

## 코드 설명

### 1. **초기화 및 설정**
- `HAL_Init()`: HAL 라이브러리 초기화.
- `SystemClock_Config()`: 시스템 클럭 설정.
- `MX_GPIO_Init()`, `MX_DMA_Init()`, `MX_TIM3_Init()`, `MX_ADC1_Init()`: GPIO, DMA, 타이머, ADC 초기화.

### 2. **UART 및 ESP 초기화**
- `drv_uart_init()`와 `drv_esp_init()`를 호출하여 UART와 ESP 모듈을 초기화합니다.
- `AiotClient_Init()`는 AIoT 클라이언트 초기화 함수입니다.

### 3. **메인 루프**
메인 루프에서는 다음과 같은 작업을 처리합니다:
- `rx2Flag`가 설정되면 UART에서 받은 데이터를 출력합니다.
- `tim3Flag1Sec`가 설정되면 1초마다 작업을 수행합니다.
  - ADC 값을 읽어와 출력합니다.
  - 5초마다 DMA를 사용하여 ADC 값을 읽어옵니다.
- 수신된 데이터에 "+IPD" 문자열이 포함되면, 이를 파싱하여 LED 상태를 제어하는 등의 작업을 합니다.

### 4. **타이머 인터럽트**
- `HAL_TIM_PeriodElapsedCallback()`: 타이머 인터럽트가 발생할 때마다 호출되며, 1초마다 `tim3Flag1Sec`을 설정합니다.

### 5. **ADC 인터럽트**
- `HAL_ADC_ConvCpltCallback()`: ADC 변환이 완료되면 호출되며, 변환된 데이터를 출력합니다.

### 6. **Wi-Fi 명령 처리 (`esp_event`)**
- Wi-Fi 모듈로부터 수신한 명령을 파싱하여 LED를 켜거나 끄는 등의 작업을 처리합니다.
- 명령 포맷은 `[ID]LED@ON` 또는 `[ID]LED@OFF` 형식입니다.
- 명령을 처리한 후 응답을 다시 ESP 모듈로 전송합니다.

### 7. **LED 제어**
- `MX_GPIO_LED_ON()`와 `MX_GPIO_LED_OFF()` 함수를 통해 LED를 제어합니다. 이 함수들은 GPIO 핀을 설정하여 LED를 켜거나 끕니다.

## 함수 설명

### `void esp_event(char *recvBuf)`
Wi-Fi 모듈로부터 수신한 명령을 처리합니다. 명령을 파싱하고, 필요한 작업을 수행한 후 응답을 전송합니다.

### `void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)`
타이머 인터럽트 콜백 함수입니다. 1초마다 타이머 플래그를 설정하고, 이를 통해 주기적인 작업을 수행합니다.

### `void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)`
ADC 변환 완료 콜백 함수입니다. ADC 변환이 완료되면 플래그를 설정하여 ADC 값을 출력합니다.

### `void MX_GPIO_LED_ON(int pin)` / `void MX_GPIO_LED_OFF(int pin)`
LED를 켜고 끄는 함수입니다. `LD2` GPIO 핀을 사용하여 상태를 제어합니다.

## 하드웨어 요구 사항
- STM32 마이크로컨트롤러
- ESP8266 또는 ESP32 Wi-Fi 모듈
- ADC 센서 (예: 온도 센서)
- LED 및 버튼

## 빌드 및 플래시
1. STM32CubeMX를 사용하여 프로젝트를 설정하고, 필요한 라이브러리를 추가합니다.
2. Keil 또는 다른 IDE를 사용하여 프로젝트를 빌드합니다.
3. 프로그램을 STM32 보드에 플래시하고, Serial Terminal에서 출력을 확인합니다.

## 디버깅 및 출력
이 코드는 `printf`를 사용하여 UART를 통해 디버깅 출력을 합니다. 이를 통해 Wi-Fi 명령, ADC 값, 타이머 상태 등을 모니터링할 수 있습니다.

---

이와 같은 방식으로 `main.c` 파일을 설명하는 `README.md` 파일을 작성할 수 있습니다.