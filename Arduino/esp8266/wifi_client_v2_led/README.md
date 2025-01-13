## **wifi_client_v2_led**

### 1. WiFi 및 서버 설정

```cpp
#define AP_SSID "embB"
#define AP_PASS "embB1234"
#define SERVER_NAME "10.10.14.48"
#define SERVER_PORT 5000  
#define LOGID "KSH_ARD"
#define PASSWD "PASSWD"
```

이 부분에서는 WiFi 네트워크와 서버 연결에 필요한 정보를 설정합니다. `AP_SSID`와 `AP_PASS`는 WiFi의 SSID와 비밀번호를, `SERVER_NAME`과 `SERVER_PORT`는 서버의 IP 주소와 포트를 설정합니다. `LOGID`와 `PASSWD`는 서버에 연결할 때 사용할 로그인 ID와 비밀번호입니다.

---

### 2. 핀 설정

```cpp
#define WIFITX 8  // 7:TX -->ESP8266 RX
#define WIFIRX 7  // 6:RX-->ESP8266 TX
#define LED_TEST_PIN 12
#define LED_BUILTIN_PIN 13
#define MOTOR_PIN 9
#define CMD_SIZE 50
#define ARR_CNT 5
```

- `WIFITX`와 `WIFIRX`는 ESP8266 모듈과 Arduino 간의 시리얼 통신 핀을 설정합니다.
- `LED_TEST_PIN`과 `LED_BUILTIN_PIN`은 각각 테스트용 LED와 내장 LED의 핀 번호입니다.
- `MOTOR_PIN`은 모터를 제어하는 핀 번호입니다.
- `CMD_SIZE`는 데이터 송수신에 사용할 버퍼 크기입니다.
- `ARR_CNT`는 문자열을 분리하여 저장할 배열의 크기입니다.

---

### 3. 라이브러리 및 객체 정의

```cpp
#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include <MsTimer2.h>

char sendBuf[CMD_SIZE];
bool timerIsrFlag = false;
unsigned int secCount;
int sensorTime;
int pwm = 0;

SoftwareSerial wifiSerial(WIFIRX, WIFITX); 
WiFiEspClient client;
```

- `WiFiEsp.h`는 ESP8266을 Arduino와 연결하는 데 필요한 라이브러리입니다.
- `SoftwareSerial.h`는 다른 핀을 사용하여 시리얼 통신을 할 수 있게 해주는 라이브러리입니다.
- `MsTimer2.h`는 타이머 기능을 구현하는 라이브러리입니다.
- `sendBuf`는 서버로 전송할 데이터를 저장하는 버퍼입니다.
- `timerIsrFlag`는 타이머 인터럽트 플래그로, 일정 시간이 지난 후 플래그를 통해 `loop()` 함수에서 특정 작업을 수행하게 합니다.
- `secCount`는 타이머 인터럽트가 호출될 때마다 증가하는 카운터입니다.
- `sensorTime`과 `pwm`은 각각 센서 시간과 PWM 값에 사용되는 변수입니다.
- `wifiSerial`은 ESP8266과의 시리얼 통신을 위한 객체입니다.
- `client`는 서버와의 연결을 위한 WiFi 클라이언트 객체입니다.

---

### 4. `setup()` 함수

```cpp
void setup() {
  pinMode(LED_TEST_PIN, OUTPUT);    // D12
  pinMode(LED_BUILTIN_PIN, OUTPUT); // D13
  Serial.begin(115200); // DEBUG
  wifi_Setup();
  MsTimer2::set(1000, timerIsr);
  MsTimer2::start();
}
```

- `setup()` 함수에서는 디지털 핀들을 출력 모드로 설정하고, 시리얼 모니터를 시작합니다.
- `wifi_Setup()` 함수로 WiFi 연결을 설정하고, `MsTimer2::set()`으로 1초마다 호출될 타이머를 설정합니다.
- `MsTimer2::start()`는 타이머를 시작하는 함수입니다.

---

### 5. `loop()` 함수

```cpp
void loop() {
  if(client.available()) {
    socketEvent();
  }
  if (timerIsrFlag)
  {
    timerIsrFlag = false; 
    if(!(secCount % 5))
    {
      if (!client.connected()) { 
        server_Connect();
      }
    }
  }
}
```

- `loop()` 함수는 반복적으로 실행되며, `client.available()`로 서버로부터 데이터가 있는지 확인합니다. 데이터가 있다면 `socketEvent()` 함수가 호출됩니다.
- 타이머가 1초마다 호출되면 `timerIsrFlag`가 `true`로 설정되고, `secCount`를 5로 나누었을 때 나머지가 0이면 서버와 연결을 재시도합니다.

---

### 6. `socketEvent()` 함수

```cpp
void socketEvent() {
  int i=0;
  char * pToken;
  char * pArray[ARR_CNT] = {0};
  char recvBuf[CMD_SIZE] = {0}; 
  int len;

  len = client.readBytesUntil('\n', recvBuf, CMD_SIZE);
  client.flush();
  
  pToken = strtok(recvBuf, "[@]");
  while(pToken != NULL) {
    pArray[i] = pToken;
    if(++i >= ARR_CNT) break;
    pToken = strtok(NULL, "[@]");
  }

  if(!strncmp(pArray[1], " New", 4)) {
    return;
  }
  else if(!strncmp(pArray[1], " Alr", 4)) {
    client.stop();
    server_Connect();
    return;
  }   
  else if(!strcmp(pArray[1], "LED")) {
    if(!strcmp(pArray[2], "ON")) {
      digitalWrite(LED_BUILTIN_PIN, HIGH);
    }
    else if(!strcmp(pArray[2], "OFF")) {
      digitalWrite(LED_BUILTIN_PIN, LOW);
    }
    sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
  } 
  else if(!strcmp(pArray[1], "LAMP")) {
    if(!strcmp(pArray[2], "ON")) {
      digitalWrite(LED_TEST_PIN, HIGH);
    }
    else if(!strcmp(pArray[2], "OFF")) {
      digitalWrite(LED_TEST_PIN, LOW);
    }
    sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
  }
  else if(!strcmp(pArray[1], "MOTOR")) {
    pwm = atoi(pArray[2]);
    pwm = 255 / 100.0 * pwm;
    analogWrite(MOTOR_PIN, (int)pwm);
    sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
  }
  else if(!strcmp(pArray[1], "GETSTATE")) {
    if(!strcmp(pArray[2], "DEV")) {
      sprintf(sendBuf, "[%s]DEV@%s@%s\n", pArray[0], digitalRead(LED_BUILTIN_PIN) ? "ON" : "OFF", digitalRead(LED_TEST_PIN) ? "ON" : "OFF");
    }
  }

  client.write(sendBuf, strlen(sendBuf));
  client.flush();
}
```

- `socketEvent()` 함수는 서버로부터 수신한 데이터를 분석하고, 명령에 따라 LED, 램프, 모터 등을 제어합니다.
- 수신된 명령이 `LED`, `LAMP`, `MOTOR`, `GETSTATE`에 해당하면 해당 핀의 상태를 변경하고, 서버로 결과를 전송합니다.

---

### 7. `timerIsr()` 함수

```cpp
void timerIsr() {
  timerIsrFlag = true;
  secCount++;
}
```

- `timerIsr()` 함수는 타이머 인터럽트가 1초마다 호출되며, `secCount`를 증가시키고 `timerIsrFlag`를 `true`로 설정하여 `loop()`에서 일정 주기로 작업을 수행할 수 있게 합니다.

---

### 8. WiFi 초기화 및 서버 연결

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
      // WiFi 연결을 시도
    }
    else
      break;
  } while(1);

  while(WiFi.begin(AP_SSID, AP_PASS) != WL_CONNECTED) {
    // WiFi 연결 시도
  }
}
```

- `wifi_Setup()` 함수에서는 WiFi 모듈을 초기화하고 서버에 연결을 시도합니다. 
- `wifi_Init()`는 WiFi 연결을 시도하는 부분으로, 연결될 때까지 반복해서 시도합니다.

---

### 9. 서버 연결

```cpp
int server_Connect() {
  if (client.connect(SERVER_NAME, SERVER_PORT)) {
    client.print("[" LOGID ":" PASSWD "]");
  }
}
```

- `server_Connect()` 함수는 서버에 연결을 시도하며, 연결에 성공하면 로그인 정보를 서버에 전송합니다.

---

### 10. WiFi 상태 출력

```cpp
void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
```

- `printWifiStatus()`는 WiFi 연결 상태를 시리얼 모니터에 출력하는 함수입니다.