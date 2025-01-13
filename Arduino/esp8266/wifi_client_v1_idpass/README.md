## **wifi_client_v1_idpass**

### 1. WiFi 및 서버 설정

```cpp
#define AP_SSID "embA"
#define AP_PASS "embA1234"
#define SERVER_NAME "10.10.14.48"
#define SERVER_PORT 5000
#define LOGID "KSH_ARD"
#define PASSWD "PASSWD"
```

이 부분은 WiFi 네트워크 및 서버와의 연결에 필요한 설정입니다. WiFi에 연결할 SSID와 비밀번호, 서버의 IP 주소와 포트를 설정하고, 서버에 인증 정보를 보내기 위한 ID와 비밀번호를 정의합니다.

---

### 2. WiFi 핀 설정

```cpp
#define WIFIRX 8  // ESP8266 RX
#define WIFITX 7  // ESP8266 TX
#define CMD_SIZE 50
```

WiFi 통신을 위한 핀 번호를 설정합니다. `WIFIRX`는 ESP8266 모듈의 RX 핀에, `WIFITX`는 TX 핀에 해당하며, `CMD_SIZE`는 송수신 버퍼의 크기입니다.

---

### 3. 라이브러리 및 객체 정의

```cpp
#include "WiFiEsp.h"
#include "SoftwareSerial.h"

SoftwareSerial wifiSerial(WIFIRX, WIFITX);  // WiFi 통신을 위한 소프트웨어 시리얼
WiFiEspClient client;  // WiFi 클라이언트 객체
```

필요한 라이브러리인 `WiFiEsp`와 `SoftwareSerial`을 포함시킵니다. `wifiSerial`은 ESP8266과의 통신을 위한 시리얼 객체이며, `client`는 서버와의 통신을 위한 WiFi 클라이언트 객체입니다.

---

### 4. setup() 함수

```cpp
void setup() {
  Serial.begin(115200);  // 시리얼 모니터를 위한 디버깅용
  wifi_Setup();  // WiFi 설정 및 연결
}
```

Arduino의 초기 설정을 처리하는 `setup()` 함수입니다. 시리얼 통신을 초기화하고, WiFi 설정 및 서버 연결을 위한 `wifi_Setup()` 함수를 호출합니다.

---

### 5. loop() 함수

```cpp
void loop() {
  // 서버로부터 데이터 수신
  while (client.available()) {
    int len = client.readBytesUntil('/', recvBuf, CMD_SIZE);
    Serial.write(recvBuf, len);
  }
}
```

`loop()` 함수는 반복적으로 실행되며, 서버로부터 수신한 데이터를 처리합니다. `client.available()`로 데이터가 있을 때마다 데이터를 읽어 시리얼 모니터에 출력합니다.

---

### 6. wifi_Setup() 함수

```cpp
void wifi_Setup() {
  wifiSerial.begin(38400);  // WiFi 모듈의 통신 속도 설정
  wifi_Init();  // WiFi 초기화
  server_Connect();  // 서버에 연결
}
```

WiFi 모듈을 설정하는 함수입니다. `wifiSerial.begin()`으로 통신 속도를 설정하고, `wifi_Init()`로 WiFi 초기화를 수행한 후 `server_Connect()`로 서버와 연결을 시도합니다.

---

### 7. wifi_Init() 함수

```cpp
void wifi_Init() {
  do {
    WiFi.init(&wifiSerial);
    if (WiFi.status() == WL_NO_SHIELD) {
      // WiFi가 정상적으로 연결되지 않으면 계속 시도
    } else
      break;
  } while (1);

  while (WiFi.begin(AP_SSID, AP_PASS) != WL_CONNECTED) {
    // WiFi에 연결할 때까지 반복
  }
}
```

WiFi 모듈이 정상적으로 초기화되었는지 확인하고, 연결되지 않았으면 계속 시도합니다. `WiFi.begin()`으로 WiFi 네트워크에 연결을 시도하고, 연결되면 반복을 종료합니다.

---

### 8. server_Connect() 함수

```cpp
int server_Connect() {
  if (client.connect(SERVER_NAME, SERVER_PORT)) {
    client.print("[" LOGID ":" PASSWD "]");  // 서버에 인증 정보 전송
  } else {
    // 서버 연결 실패 시 메시지 출력
  }
}
```

서버와의 연결을 시도하는 함수입니다. 지정된 IP와 포트로 서버에 연결을 시도하고, 연결 성공 시 인증 정보를 전송합니다. 연결에 실패하면 실패 메시지를 출력합니다.

---

### 9. printWifiStatus() 함수

```cpp
void printWifiStatus() {
  // WiFi 상태 출력
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

WiFi 연결 상태를 출력하는 함수입니다. 연결된 네트워크의 SSID, Arduino의 IP 주소, 그리고 수신 신호 강도(RSSI)를 시리얼 모니터에 출력합니다.