### 1. **WiFi 연결 설정**
WiFi 연결을 위한 설정입니다. `WiFiEsp` 라이브러리를 사용하여 ESP8266 모듈을 설정하고 네트워크에 연결합니다.

```cpp
#define AP_SSID "embA"  // Wi-Fi SSID
#define AP_PASS "embA1234"  // Wi-Fi 비밀번호
#define SERVER_NAME "10.10.14.48"  // 서버 주소
#define SERVER_PORT 5000  // 서버 포트

SoftwareSerial wifiSerial(WIFIRX, WIFITX);  // ESP8266과의 시리얼 통신
WiFiEspClient client;  // Wi-Fi 클라이언트 객체
```

- **`WiFiEspClient`**는 ESP8266을 통해 서버와 통신하는 데 사용됩니다.
- **`wifiSerial`** 객체는 소프트웨어 시리얼 포트를 통해 ESP8266과 통신합니다.

### 2. **WiFi 연결 함수**

WiFi 연결을 초기화하고, 서버에 연결하는 함수입니다.

```cpp
void wifi_Setup() {
  wifiSerial.begin(38400);
  wifi_Init();
  server_Connect();
}

void wifi_Init() {
  do {
    WiFi.init(&wifiSerial);
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
    }
    else
      break;
  } while (1);
  
  while (WiFi.begin(AP_SSID, AP_PASS) != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(AP_SSID);
  }

  Serial.println("Connected to Wi-Fi!");
  Serial.println(WiFi.localIP());  // Wi-Fi IP 출력
}
```

- **`WiFi.begin()`**로 Wi-Fi 네트워크에 연결하고, 연결이 완료될 때까지 기다립니다.
- **`WiFi.localIP()`**로 연결된 Wi-Fi의 IP 주소를 출력합니다.

### 3. **서버 연결 함수**

서버에 연결하는 함수입니다. 연결 후 서버에 간단한 인증 정보를 전송합니다.

```cpp
int server_Connect() {
  if (client.connect(SERVER_NAME, SERVER_PORT)) {
    client.print("["LOGID":"PASSWD"]");  // 서버에 로그인 정보 전송
  } else {
    Serial.println("Server connection failure");
  }
}
```

- **`client.connect()`**는 서버와의 연결을 시도합니다. 연결이 성공하면 로그인 정보를 전송합니다.

### 4. **센서 데이터 처리**

센서 데이터를 읽고, 일정 시간 간격으로 서버로 전송합니다. 여기에 사용된 센서들:
- **LDR(조도 센서)**
- **DHT11(온도 및 습도 센서)**

```cpp
cds = map(analogRead(CDS_PIN), 0, 1023, 0, 100);  // 조도 센서 값 읽기
humi = dht.readHumidity();  // 습도 센서 값 읽기
temp = dht.readTemperature();  // 온도 센서 값 읽기
```

- **`analogRead(CDS_PIN)`**: 아날로그 핀에서 조도 센서 값을 읽고, 이를 0~100 범위로 변환합니다.
- **`dht.readHumidity()`**와 **`dht.readTemperature()`**는 DHT11 센서를 통해 습도와 온도를 읽어옵니다.

### 5. **LCD 디스플레이 업데이트**

센서 값이나 상태 정보를 LCD 화면에 표시하는 함수입니다.

```cpp
sprintf(lcdLine2, "C:%2d,T:%2d,H:%2d", cds, (int)temp, (int)humi);
lcdDisplay(0, 1, lcdLine2);
```

- **`sprintf()`**는 센서 데이터를 문자열로 포맷하여 `lcdLine2`에 저장합니다.
- **`lcdDisplay()`**는 LCD 화면에 값을 표시합니다.

### 6. **서버에서 명령 처리**

서버로부터 받은 명령을 처리하는 부분입니다. 예를 들어, LED 제어 명령을 처리하는 코드입니다.

```cpp
if (!strcmp(pArray[1], "LED")) {
  if (!strcmp(pArray[2], "ON")) {
    digitalWrite(LED_BUILTIN_PIN, HIGH);  // LED 켜기
  }
  else if (!strcmp(pArray[2], "OFF")) {
    digitalWrite(LED_BUILTIN_PIN, LOW);  // LED 끄기
  }
  sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
}
```

- **`digitalWrite(LED_BUILTIN_PIN, HIGH)`**: LED를 켭니다.
- **`digitalWrite(LED_BUILTIN_PIN, LOW)`**: LED를 끕니다.

서버에서 받은 **LED ON/OFF** 명령을 처리하여, 해당 상태를 클라이언트에 응답으로 보내는 코드입니다.

### 7. **서보 모터 제어**

서버에서 받은 명령에 따라 서보 모터를 제어합니다.

```cpp
else if (!strcmp(pArray[1], "SERVO")) {
  myservo.attach(SERVO_PIN);  // 서보 모터 제어
  if (!strcmp(pArray[2], "ON"))
    myservo.write(180);  // 서보 모터를 180도로 회전
  else
    myservo.write(0);  // 서보 모터를 0도로 회전
}
```

- **`myservo.attach(SERVO_PIN)`**: 서보 모터를 지정된 핀에 연결합니다.
- **`myservo.write(180)`**: 서보 모터를 180도 위치로 이동시킵니다.
- **`myservo.write(0)`**: 서보 모터를 0도 위치로 이동시킵니다.

### 8. **타이머 및 시간 관리**

1초마다 타이머가 작동하여 **`secCount`**를 증가시키고, 이를 바탕으로 센서 데이터를 주기적으로 보내거나 LCD 디스플레이를 업데이트합니다.

```cpp
void timerIsr() {
  timerIsrFlag = true;
  secCount++;
}
```

- **`MsTimer2::set(1000, timerIsr)`**는 1초마다 `timerIsr()` 함수를 호출하도록 설정합니다.

### 9. **버튼 디바운싱 처리**

버튼을 눌렀을 때, 디바운싱을 통해 정확한 버튼 상태를 처리합니다.

```cpp
currentButton = debounce(lastButton);
if (lastButton == LOW && currentButton == HIGH) {
  ledOn = !ledOn;  // LED 상태 반전
  digitalWrite(LED_BUILTIN_PIN, ledOn);
}
lastButton = currentButton;  // 이전 버튼 상태를 현재 상태로 설정
```

- **`debounce()`** 함수는 버튼을 눌렀을 때, 버튼이 여러 번 눌려서 발생하는 중복 이벤트를 방지합니다.

### 결론

이 코드는 아두이노와 ESP8266 WiFi 모듈을 사용하여 다양한 IoT 장치를 제어하고 데이터를 처리하는 시스템입니다. 주요 작업은 Wi-Fi를 통해 서버와 연결하고, 센서 데이터를 읽고, 서버에서 명령을 받아 처리하며, LCD에 정보를 표시하는 것입니다.