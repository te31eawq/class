# 목차

### [함수 정의들](#함수-정의들-1)
### [프로젝트 개요](#프로젝트-개요-1)

---

## 함수 정의들

### 1. **`onCreate(Bundle savedInstanceState)`**
   - **설명**: `Activity`가 처음 생성될 때 호출되는 메서드입니다. 주로 UI 요소를 초기화하고, 화면에 표시할 콘텐츠를 설정하는 작업을 합니다.
   - **사용된 함수들**:
     - `super.onCreate(savedInstanceState)`: 부모 클래스(`AppCompatActivity`)의 `onCreate` 메서드를 호출하여 `Activity`의 기본적인 생성 과정을 진행합니다.
     - `setContentView(R.layout.activity_main)`: `activity_main` 레이아웃 파일을 화면에 표시합니다.
     - `ViewCompat.setOnApplyWindowInsetsListener()`: 시스템 바(상단/하단 바)의 여백을 처리하여 화면의 엣지 투 엣지(Edge-to-Edge) UI를 구현합니다.

### 2. **`findViewById(int id)`**
   - **설명**: 레이아웃 파일에서 지정한 UI 요소를 찾아 객체로 반환합니다.
   - **사용 예**:
     ```java
     EditText editTextIp = findViewById(R.id.editTextTextIp);
     ```

### 3. **`setOnClickListener(View.OnClickListener listener)`**
   - **설명**: 버튼 클릭과 같은 UI 요소의 이벤트를 처리하는 리스너를 설정하는 메서드입니다.
   - **사용 예**:
     ```java
     toggleButtonLamp.setOnClickListener(new View.OnClickListener() {
         @Override
         public void onClick(View v) {
             // 버튼 클릭 시 처리할 작업
         }
     });
     ```

### 4. **`Thread.sleep(long millis)`**
   - **설명**: 현재 스레드를 지정된 시간(밀리초)만큼 일시 정지시킵니다.
   - **사용 예**:
     ```java
     Thread.sleep(100);
     ```
     이 예제에서는 연결 성공 후 100ms 동안 대기합니다.

### 5. **`Log.d(String tag, String msg)`**
   - **설명**: 로그 메시지를 디버그 수준으로 출력하는 메서드입니다. Android Studio의 Logcat에서 로그를 볼 수 있습니다.
   - **사용 예**:
     ```java
     Log.d("MainHandler", data);
     ```

### 6. **`Message.obtainMessage()`**
   - **설명**: 새 메시지를 생성하거나, 재사용 가능한 메시지를 반환하는 메서드입니다. `Handler`를 통해 메시지를 전달할 때 사용됩니다.
   - **사용 예**:
     ```java
     Message message = MainActivity.mainHandler.obtainMessage();
     ```

### 7. **`message.setData(Bundle data)`**
   - **설명**: `Message` 객체에 데이터를 설정하는 메서드입니다. 데이터를 `Bundle` 객체에 넣어서 전달합니다.
   - **사용 예**:
     ```java
     bundle.putString("msg", data);
     message.setData(bundle);
     ```

### 8. **`MainActivity.mainHandler.sendMessage(Message msg)`**
   - **설명**: `Handler`를 사용하여 메시지를 메인 UI 스레드로 전달하는 메서드입니다. `Message`를 큐에 넣고, 이를 처리하여 UI 업데이트 등의 작업을 합니다.
   - **사용 예**:
     ```java
     MainActivity.mainHandler.sendMessage(message);
     ```

### 9. **`append(CharSequence text)`**
   - **설명**: `TextView`에 텍스트를 추가하는 메서드입니다. 기존 텍스트 뒤에 새로운 텍스트를 덧붙일 수 있습니다.
   - **사용 예**:
     ```java
     textviewRecv.append(strDate);
     ```

### 10. **`fullScroll(int direction)`**
   - **설명**: `ScrollView`에서 내용을 자동으로 스크롤하는 메서드입니다. `View.FOCUS_DOWN`을 사용하면 스크롤이 맨 아래로 이동합니다.
   - **사용 예**:
     ```java
     scrollViewRecv.fullScroll(View.FOCUS_DOWN);
     ```

### 11. **`setEnabled(boolean enabled)`**
   - **설명**: UI 요소가 활성화되어 있는지 비활성화 상태인지 설정하는 메서드입니다. `false`로 설정하면 버튼이나 토글이 클릭 불가능해집니다.
   - **사용 예**:
     ```java
     toggleButtonLamp.setEnabled(false);
     ```

### 12. **`String.indexOf(String str)`**
   - **설명**: 문자열에서 특정 문자열이 처음 나타나는 위치를 반환합니다. 문자열이 포함되어 있지 않으면 `-1`을 반환합니다.
   - **사용 예**:
     ```java
     if (data.indexOf("GASON") != -1)
     ```

### 13. **`new SimpleDateFormat(String pattern)`**
   - **설명**: 날짜를 지정된 형식으로 포맷할 수 있는 `SimpleDateFormat` 객체를 생성합니다.
   - **사용 예**:
     ```java
     SimpleDateFormat dateFormat = new SimpleDateFormat("yy-MM-dd HH:mm:ss");
     ```

### 14. **`new Date()`**
   - **설명**: 현재 날짜와 시간을 나타내는 `Date` 객체를 생성합니다.
   - **사용 예**:
     ```java
     Date date = new Date();
     ```

### 15. **`dateFormat.format(Date date)`**
   - **설명**: `SimpleDateFormat`을 사용하여 `Date` 객체를 지정된 형식의 문자열로 변환합니다.
   - **사용 예**:
     ```java
     String strDate = dateFormat.format(date);
     ```

### 16. **`findViewById(R.id.someView)`**
   - **설명**: XML 레이아웃 파일에서 정의된 UI 요소를 찾아 반환하는 메서드입니다. `R.id.someView`는 해당 UI 요소의 ID를 나타냅니다.

### 17. **`setContentView(R.layout.activity_main)`**
   - **설명**: 액티비티에 표시할 레이아웃을 설정하는 메서드입니다. XML 레이아웃 파일을 화면에 적용합니다.

이 코드에서 사용된 함수들은 Android 애플리케이션의 UI 구성, 이벤트 처리, 서버와의 네트워크 통신, 로그 출력 등 여러 작업을 효율적으로 처리하는 데 필요한 메서드들입니다. UI 구성 요소들의 동작을 제어하고, 서버와의 데이터를 송수신하는 기능을 제공합니다.

---

## 프로젝트 개요

이 애플리케이션은 원격 서버와 텔넷(Telnet) 프로토콜을 사용하여 연결하고 데이터를 주고받을 수 있는 Android 애플리케이션입니다. 서버와 연결 후 사용자는 버튼을 통해 장치(예: 램프, 플러그 등)를 제어할 수 있으며, 서버로부터 받은 응답은 실시간으로 UI에 표시됩니다.

## 주요 기능

1. **서버와 연결**: 사용자가 지정한 IP 주소와 포트를 통해 서버에 연결합니다.
2. **명령 전송 및 장치 제어**: 사용자 인터페이스에서 제공하는 버튼을 통해 서버로 명령을 전송하여 장치의 상태를 제어할 수 있습니다. 예: 램프 켜기/끄기, 플러그 켜기/끄기.
3. **서버 응답 표시**: 서버로부터 받은 메시지를 UI에 실시간으로 표시합니다.
4. **엣지 투 엣지 UI**: 시스템 바를 포함하여 화면을 최대로 활용하는 UI를 제공합니다.

## 앱 구조

앱은 크게 두 가지 주요 클래스로 나뉩니다:
1. **`MainActivity`**: UI 구성 및 사용자와 상호작용하는 메인 액티비티 클래스입니다.
2. **`ClientThread`**: 서버와의 연결을 관리하고, 데이터를 송수신하는 백그라운드 스레드 클래스입니다.

### `ClientThread` 클래스

`ClientThread` 클래스는 서버와의 네트워크 통신을 처리합니다. 서버에 연결하고 데이터를 전송하며, 서버로부터 응답을 받습니다.

#### 주요 변수
- `serverIp`: 서버의 IP 주소.
- `serverPort`: 서버의 포트 번호.
- `clientId` 및 `clientPw`: 클라이언트 인증 정보를 나타내는 ID와 비밀번호.
- `arduinoId`: 아두이노 장치의 고유 ID.

#### 주요 메서드

- **`run()`**: 이 메서드는 스레드가 실행될 때 호출됩니다. 
    - 서버에 연결 요청을 보낸 후, 연결이 성공하면 클라이언트 ID와 비밀번호를 서버로 전송합니다.
    - 서버로부터 받은 데이터를 읽고, 이를 `MainActivity`로 전달하여 UI에 반영합니다.
    - 연결이 끊어지면 `socket.close()`를 호출하여 리소스를 정리합니다.

- **`stopClient()`**: 클라이언트의 연결을 종료하는 메서드입니다. 소켓을 닫고 서버와의 연결을 끊습니다.

- **`sendData(String data)`**: 서버로 데이터를 전송하는 메서드입니다. 
    - 데이터를 UTF-8 인코딩으로 변환하여 서버에 전송합니다. 이 과정은 별도의 스레드에서 실행됩니다.

- **`sendMainActivity(String text)`**: 서버로부터 받은 메시지를 `MainActivity`로 전달하여 UI를 업데이트합니다.

- **`displayText(String text)`**: 로그 메시지를 출력하는 메서드로, 서버와의 연결 상태나 오류 등을 로그로 기록합니다.

### `MainActivity` 클래스

`MainActivity` 클래스는 사용자 인터페이스(UI)와 관련된 부분을 담당합니다. 사용자는 이 화면에서 서버와 연결하거나 장치를 제어하는 명령을 보낼 수 있습니다.

#### 주요 UI 요소

1. **서버 연결 버튼 (ToggleButton)**: 서버에 연결하거나 연결을 끊을 수 있는 버튼입니다. 연결 시 `ClientThread`가 실행되며, 서버에 연결합니다.
2. **장치 제어 버튼 (ToggleButton)**: 램프와 플러그의 상태를 제어하는 버튼입니다. 사용자가 버튼을 클릭하면 서버로 제어 명령을 전송하고, 상태가 변경됩니다.
3. **데이터 전송 버튼 (Button)**: 사용자가 입력한 데이터를 서버로 전송하는 버튼입니다.
4. **서버 응답 표시 영역 (TextView, ScrollView)**: 서버로부터 받은 메시지를 타임스탬프와 함께 표시하는 영역입니다. 새로운 메시지가 오면 자동으로 스크롤되어 최신 메시지를 확인할 수 있습니다.

### `MainHandler` 클래스

`MainHandler`는 서버로부터 받은 메시지를 `MainActivity`로 전달하여 UI를 업데이트하는 역할을 합니다. 메시지에 포함된 데이터를 분석하여, 장치의 상태를 적절히 업데이트합니다. 예를 들어, 서버가 `GASON` 메시지를 보냈으면 램프 상태를 "켜짐"으로 업데이트하고, `LAMPOFF` 메시지를 받으면 "꺼짐"으로 변경합니다.

## 사용 방법

1. **IP 주소와 포트 입력**: `MainActivity` 화면에서 서버의 IP 주소와 포트를 입력합니다.
2. **서버 연결**: "연결" 버튼을 클릭하여 서버에 연결합니다. 연결이 성공하면 텍스트가 UI에 표시됩니다.
3. **명령 전송**: "데이터 전송" 버튼을 클릭하여 입력한 데이터를 서버로 전송합니다.
4. **장치 제어**: "램프 제어" 및 "플러그 제어" 버튼을 클릭하여 서버로 장치 제어 명령을 전송합니다.

## 코드 흐름

1. 사용자가 "연결" 버튼을 클릭하면 `ClientThread`가 시작되어 서버에 연결합니다.
2. 서버에 연결된 후, 사용자는 "데이터 전송" 버튼을 클릭하여 서버로 데이터를 보냅니다.
3. 서버에서 응답이 오면, `ClientThread`가 이를 읽고, `MainActivity`의 `MainHandler`로 메시지를 전달하여 UI에 응답을 표시합니다.
4. 사용자는 "램프 제어" 및 "플러그 제어" 버튼을 통해 장치의 상태를 제어합니다. 이 명령은 `ClientThread`를 통해 서버로 전송됩니다.

## 기술 스택

- **Android**: Java를 사용하여 Android 애플리케이션을 개발합니다.
- **Telnet 프로토콜**: 서버와의 데이터 통신은 텔넷 프로토콜을 사용하여 이루어집니다.

## 주의 사항

- 서버와의 연결을 위해 유효한 IP 주소와 포트를 입력해야 합니다.
- 서버에서 올바른 응답을 받지 못하면 명령어가 제대로 작동하지 않을 수 있습니다.
