이 코드는 Bluetooth 모듈 HC-06을 Arduino와 연결하여 간단한 Bluetooth 통신을 테스트하는 예제입니다. Bluetooth 모듈은 기본적으로 슬레이브 모드로 동작하며, AT 명령어를 통해 설정할 수 있습니다.

### 1. 하드웨어 연결

- **VCC** : 5V (Arduino 5V 핀에 연결)
- **GND** : GND (Arduino GND 핀에 연결)
- **TXD** : RX(10번 핀) (HC-06의 TXD 핀을 Arduino의 RX 핀에 연결)
- **RXD** : TX(11번 핀) (HC-06의 RXD 핀을 Arduino의 TX 핀에 연결)

### 2. 코드 설명

#### 2.1. 라이브러리 포함 및 시리얼 객체 설정

```cpp
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX
```

- `SoftwareSerial` 라이브러리를 사용하여 Arduino의 다른 핀을 시리얼 통신에 사용할 수 있게 합니다.
- `BTSerial`은 10번 핀을 RX로, 11번 핀을 TX로 설정하여 HC-06과의 통신을 관리합니다.

#### 2.2. `setup()` 함수

```cpp
void setup(){
    Serial.begin(9600);
 
    Serial.print("Sketch : ");
    Serial.println(__FILE__);
    Serial.print("Uploaded : ");
    Serial.println(__DATE__);
    Serial.println("HM-06 is ready for AT commands:");
 
    BTSerial.begin(9600);  // HC-06 모듈의 기본 Baud Rate 설정
    pinMode(9, OUTPUT);    // 9번 핀을 출력 모드로 설정
}
```

- `Serial.begin(9600)` : Arduino와 PC 간의 시리얼 통신을 9600bps로 설정합니다.
- `BTSerial.begin(9600)` : HC-06과의 시리얼 통신을 9600bps로 설정합니다.
- 9번 핀을 출력 모드로 설정하여, Bluetooth 신호에 따라 제어할 수 있도록 합니다.

#### 2.3. `loop()` 함수

```cpp
void loop(){
    int ch;
    // HC-06으로부터 데이터를 읽고 시리얼 모니터에 출력
    if (BTSerial.available())
    {
      ch = BTSerial.read();
      Serial.write(ch);
      if(ch == '0')          // Bluetooth로 '0' 수신 시 9번 핀을 LOW로 설정
        digitalWrite(9, LOW);
      else if(ch == '1')     // Bluetooth로 '1' 수신 시 9번 핀을 HIGH로 설정
        digitalWrite(9, HIGH);
    }

    // 시리얼 모니터로부터 데이터를 읽고 HC-06으로 전송
    if (Serial.available())
        BTSerial.write(Serial.read());
}
```

- Bluetooth 모듈로부터 데이터를 읽고, 읽은 값에 따라 시리얼 모니터에 출력합니다.
- `ch == '0'`일 경우, 9번 핀을 LOW로 설정하여 9번 핀에 연결된 장치를 끕니다.
- `ch == '1'`일 경우, 9번 핀을 HIGH로 설정하여 9번 핀에 연결된 장치를 켭니다.
- 시리얼 모니터에서 입력을 받으면, 해당 데이터를 Bluetooth 모듈을 통해 전송합니다.

### 3. HC-06 AT 명령어 사용

이 코드는 HC-06 모듈을 AT 명령어를 통해 설정할 수 있도록 준비된 코드입니다. AT 명령어를 사용하여 HC-06의 설정을 변경할 수 있습니다.

- **AT 명령어 예시**
  - `AT+VERSION`: Bluetooth 모듈의 버전 정보를 확인합니다.
  - `AT+NAMEiot08`: Bluetooth 모듈의 이름을 "iot08"로 변경합니다.
  
시리얼 모니터에서 `AT` 명령어를 입력하면, HC-06 모듈이 응답합니다. 예를 들어, `AT+VERSION`을 입력하면 "BT SPP V3.0"와 같은 버전 정보가 응답으로 돌아옵니다.

### 4. 코드 요약

이 코드의 주요 목적은 Bluetooth HC-06 모듈을 사용하여 무선으로 Arduino와 통신하고, 수신된 데이터를 기반으로 9번 핀을 제어하는 것입니다. 시리얼 모니터와 Bluetooth 간의 데이터를 실시간으로 송수신할 수 있습니다.