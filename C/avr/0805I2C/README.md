이 코드는 **I2C 통신**을 사용하기 위한 **AVR 마이크로컨트롤러**의 함수들을 정의한 코드입니다. I2C (Inter-Integrated Circuit) 통신은 여러 장치 간에 데이터를 교환할 수 있는 직렬 통신 프로토콜로, 주로 **마스터-슬레이브 구조**로 동작합니다. 이 코드에서는 **마스터**(MCU)가 **슬레이브** 장치와 통신을 하기 위한 기능들을 제공합니다.

### 주요 함수 설명

#### 1. `I2C_init()`
- **목적**: I2C 통신을 초기화합니다.
- **동작**:
  - `I2C_DDR &= ~((1<<I2C_SCL) | (1<<I2C_SDA));`: **SCL(Clock)**과 **SDA(Data)** 핀을 **입력 모드**로 설정합니다. 이 두 핀은 I2C 통신의 핵심적인 역할을 하므로, 이들을 먼저 설정해주어야 합니다.
  - `TWBR = 72;`: I2C 통신의 **비트 전송 속도**를 설정합니다. 이 값은 **100 kHz**의 I2C 속도를 만들기 위해 계산된 값입니다. (`TWBR`은 **타이머 제어 레지스터**로, I2C의 속도를 조정합니다.)
  - `TWSR = 0;`: **프리스케일러** 값을 설정합니다. `TWSR`은 **SCL 주파수를 제어**하는 레지스터로, 기본값은 `0`으로 설정합니다.
  ```c
  void I2C_init()
    {
        I2C_DDR &= ~((1<<I2C_SCL) | (1<<I2C_SDA));
        TWBR = 72;				// 100khz SCL
        // TWRC = 32;			// 200khz SCL
        // TWBR = 12;			// 400khz SCL
        TWSR = 0;
    }
  ```

#### 2. `I2C_start()`
- **목적**: I2C 통신에서 **시작 비트(Start Condition)**를 전송합니다. 마스터가 통신을 시작할 때 필요합니다.
- **동작**:
  - `TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);`: **TWINT** 플래그를 설정하여 I2C 전송을 시작하고, **TWSTA** 비트를 통해 **시작 비트(Start Condition)**를 전송합니다. `TWEN`은 I2C 인터페이스를 활성화하는 비트입니다.
  - `while (!(TWCR & (1<<TWINT)));`: 시작 비트가 전송될 때까지 대기합니다. `TWINT` 플래그가 설정되면 시작 비트가 정상적으로 전송된 것입니다.
  ```c
  void I2C_start()
    {
        //Send START condition
        TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
        
        // Wait for TWINT flag set. This indicates that the
        // START condition has been transmitted
        while (!(TWCR & (1<<TWINT)));
    }
  ```

#### 3. `I2C_txDevAddr(uint8_t SLA_W)`
- **목적**: I2C 슬레이브 장치의 **주소(Slave Address)**와 **쓰기 비트**(W)를 전송합니다.
- **동작**:
  - `TWDR = SLA_W;`: **슬레이브 주소**를 **데이터 레지스터**(TWDR)에 로드합니다. `SLA_W`는 7비트 슬레이브 주소와 **쓰기 비트**(0)가 포함된 값입니다.
  - `TWCR = (1<<TWINT) | (1<<TWEN);`: **전송 시작**을 위한 설정을 하고, `TWINT` 플래그를 통해 주소 전송을 시작합니다.
  - `while (!(TWCR & (1<<TWINT)));`: 주소가 전송될 때까지 대기합니다.
  ```c
  void I2C_txDevAddr(uint8_t SLA_W)
    {
        //Load SLA_W into TWDR Register. Clear
        //TWINT bit in TWCR to start transmission of
        //address
        TWDR = SLA_W;
        TWCR = (1<<TWINT) | (1<<TWEN);
        //잘 보내졌는지 기다리는 소스
        while (!(TWCR & (1<<TWINT)));
    }
    ```

#### 4. `I2C_txData(uint8_t data)`
- **목적**: I2C 슬레이브 장치에 데이터를 전송합니다.
- **동작**:
  - `TWDR = data;`: 전송할 **데이터**를 **데이터 레지스터**에 로드합니다.
  - `TWCR = (1<<TWINT) | (1<<TWEN);`: 데이터를 전송하기 위해 **TWINT** 비트를 설정합니다.
  - `while (!(TWCR & (1<<TWINT)));`: 데이터가 정상적으로 전송될 때까지 대기합니다.
  ```c
  void I2C_txData(uint8_t data)
    {
        //Load DATA into TWDR Register. Clear TWINT
        //bit in TWCR to start transmission of data
        TWDR = data;
        TWCR = (1<<TWINT) | (1<<TWEN);
        // 잘 보내졌는지 체크
        while (!(TWCR & (1<<TWINT)));
    }
  ```

#### 5. `I2C_stop()`
- **목적**: I2C 통신을 종료하는 **종료 비트(Stop Condition)**를 전송합니다.
- **동작**:
  - `TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);`: **종료 비트(Stop Condition)**를 전송하고, `TWEN`을 통해 I2C 인터페이스를 활성화합니다.
  ```c
    void I2C_stop()
    {
        // Transmit STOP condition
        TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
    }
  ```

#### 6. `I2C_txByte(uint8_t SLA_W, uint8_t data)`
- **목적**: 1바이트 데이터를 I2C 슬레이브 장치에 전송합니다.
- **동작**:
  - `I2C_start();`: 시작 비트를 보내어 통신을 시작합니다.
  - `I2C_txDevAddr(SLA_W);`: 슬레이브 주소와 쓰기 비트를 전송합니다.
  - `I2C_txData(data);`: 데이터를 전송합니다.
  - `I2C_stop();`: 통신을 종료합니다.
  ```c
    void I2C_txByte(uint8_t SLA_W, uint8_t data)
    {
        // 1byte의 data 를 송수신 하는 상황, AVR(Master) -> Device(Slave)
        // 1. Start bit 송신(M->S)
        I2C_start();
        // 2. SLA + W 송신 (M->S)
        I2C_txDevAddr(SLA_W);
        // 3. ACK bit 송신 (S->M)
        // 4. 1btye Data 송신(M->S)
        I2C_txData(data);
        // 5. ACK bit 송신 (S->M)
        // 6. Stop bit 송신 (M->S)
        I2C_stop();
    }
  ```

### I2C 통신의 흐름

1. **Start Condition**: `I2C_start()` 함수에서 시작 비트가 전송됩니다.
2. **Device Address + Write**: `I2C_txDevAddr(SLA_W)` 함수에서 슬레이브 장치의 주소와 쓰기 비트가 전송됩니다.
3. **Data Transmission**: `I2C_txData(data)` 함수에서 데이터를 전송합니다.
4. **Stop Condition**: `I2C_stop()` 함수에서 종료 비트가 전송됩니다.

### I2C 통신에서 각 비트의 의미

- **Start Condition**: 통신을 시작할 때, **SCL**과 **SDA**가 동시에 낮아지는 상태로 **시작 비트**가 전송됩니다.
- **Device Address**: 마스터가 슬레이브 장치와 통신을 할 때 **슬레이브의 주소**와 읽기/쓰기 모드를 전달합니다.
- **Data**: 실제로 마스터에서 슬레이브로 보내거나, 슬레이브에서 마스터로 보내는 **데이터**입니다.
- **Stop Condition**: 통신을 종료할 때, **SCL**과 **SDA**가 동시에 높아지는 상태로 **종료 비트**가 전송됩니다.

### 결론

이 코드는 AVR 마이크로컨트롤러에서 **I2C 통신을 구현**하는 함수들을 모아놓은 코드입니다. 주로 **I2C 마스터**에서 **슬레이브 장치로 데이터를 전송**하는 기능을 담당합니다. 이 코드를 통해, I2C 통신을 사용하여 다른 장치와 데이터를 주고받을 수 있습니다.