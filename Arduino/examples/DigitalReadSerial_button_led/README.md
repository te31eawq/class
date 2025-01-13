이 코드는 버튼의 입력을 처리하고, 시리얼 모니터를 통해 LED의 상태를 제어하는 예제입니다. 버튼이 눌릴 때마다 LED 상태를 변경하고, 시리얼 모니터에서 LED 상태를 변경하는 명령을 받을 수 있습니다. 간단히 말해, 버튼 입력을 카운팅하고, 시리얼 입력을 통해 LED를 제어하는 코드입니다.

### 1. 하드웨어 구성

- **버튼** : 2번 핀에 연결
- **LED** : 13번 핀에 연결 (내장 LED)

### 2. 코드 설명

#### 2.1. 변수 선언

```cpp
int pushButton = 2;   // 버튼이 연결된 핀
int ledPin = 13;      // LED가 연결된 핀
char ledState = 0;    // LED 상태(켜짐/꺼짐)
int buttonStatePre = 0; // 이전 버튼 상태
int buttonCount = 0;  // 버튼이 눌린 횟수
```

- **pushButton**: 버튼이 연결된 핀 번호 (2번 핀)
- **ledPin**: LED가 연결된 핀 번호 (13번 핀)
- **ledState**: LED의 현재 상태 (0이면 꺼짐, 1이면 켜짐)
- **buttonStatePre**: 마지막으로 읽은 버튼 상태를 저장하여 버튼 상태 변화를 감지
- **buttonCount**: 버튼이 눌린 횟수를 셈

#### 2.2. `setup()` 함수

```cpp
void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600);
  
  // 버튼 핀을 입력 모드로 설정
  pinMode(pushButton, INPUT);
  
  // LED 핀을 출력 모드로 설정
  pinMode(ledPin, OUTPUT);
  
  // LED를 처음에는 끈 상태로 설정
  digitalWrite(ledPin, LOW);
}
```

- **Serial.begin(9600)**: 시리얼 통신을 9600bps로 시작합니다.
- **pinMode(pushButton, INPUT)**: 버튼이 연결된 핀을 입력으로 설정합니다.
- **pinMode(ledPin, OUTPUT)**: LED가 연결된 핀을 출력으로 설정합니다.
- **digitalWrite(ledPin, LOW)**: LED를 끄기 위해 LOW 신호를 보냅니다.

#### 2.3. `loop()` 함수

```cpp
void loop() {
  // 버튼 상태를 읽음
  int buttonState = digitalRead(pushButton);
  
  // 버튼 상태가 변했을 때
  if(buttonState != buttonStatePre) {
    if(buttonState) { // 버튼이 눌렸을 때
      buttonCount++;  // 버튼 누른 횟수 증가
      ledState = !ledState;  // LED 상태를 반전시킴 (켜졌다가 꺼지게 함)
      
      // 버튼 눌린 횟수를 시리얼 모니터에 출력
      Serial.print("buttonCount : ");
      Serial.println(buttonCount);
      
      // LED 상태를 반영하여 LED를 켬/끔
      digitalWrite(ledPin, ledState);
    }
    buttonStatePre = buttonState; // 이전 상태 업데이트
  }
  
  // 시리얼 모니터에서 입력이 있을 경우
  if(Serial.available()) {
    ledState = Serial.read(); // 시리얼로 받은 값을 LED 상태로 설정
    
    // 시리얼로 '1'을 받으면 LED를 켬, '0'을 받으면 LED를 끔
    if(ledState == '1') {
      digitalWrite(ledPin, HIGH);
    } else if(ledState == '0') {
      digitalWrite(ledPin, LOW);
    }
    
    // LED 상태를 시리얼 모니터에 출력
    Serial.print("ledState : ");
    Serial.println(ledState);
  }
}
```

- **buttonState = digitalRead(pushButton)**: 버튼의 상태를 읽습니다.
- **if(buttonState != buttonStatePre)**: 버튼 상태가 변경되었을 때만 동작하도록 하여 중복 실행을 방지합니다.
- **if(buttonState)**: 버튼이 눌렸을 때, `buttonCount`를 증가시키고, LED 상태를 반전시킵니다. 또한 시리얼 모니터에 버튼 누른 횟수를 출력합니다.
- **if(Serial.available())**: 시리얼 모니터에서 데이터를 받았을 때, 해당 데이터를 `ledState`에 저장하고, '1'이면 LED를 켜고, '0'이면 LED를 끕니다. 이 값을 시리얼 모니터에 출력합니다.

### 3. 동작 설명

1. **버튼 누르기**: 버튼을 누르면 LED의 상태가 반전되고, 버튼을 누른 횟수가 시리얼 모니터에 출력됩니다. 예를 들어, 첫 번째 버튼을 누르면 LED가 켜지고, 두 번째 버튼을 누르면 LED가 꺼집니다.
2. **시리얼 통신**: 시리얼 모니터에서 '1'을 입력하면 LED가 켜지고, '0'을 입력하면 LED가 꺼집니다. 입력한 값을 시리얼 모니터에 다시 출력하여 LED의 상태를 확인할 수 있습니다.

### 4. 코드 요약

이 코드는 버튼의 입력을 통해 LED 상태를 제어하며, 버튼이 눌릴 때마다 버튼 누른 횟수를 시리얼 모니터에 출력합니다. 또한, 시리얼 모니터를 통해 LED를 제어할 수 있도록 합니다.