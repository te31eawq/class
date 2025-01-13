이 코드는 **ROS (Robot Operating System)**와 **Arduino**를 사용하여, ROS에서 메시지를 보내고 Arduino에서 해당 메시지를 받아 LED를 토글하는 기능을 구현한 예제입니다. 주로 **`ros_serial`** 패키지를 사용하여 ROS와 Arduino 간의 통신을 처리합니다. 두 코드 파일은 **ROS 노드**와 **Arduino 코드**로 구성되어 있습니다.

### 1. **ROS 코드 (ros_serial_topic.cpp)**

이 코드는 ROS에서 LED를 제어하는 메시지를 발행(publish)하는 노드입니다.

#### 1.1. 코드 분석

```cpp
#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_serial_node");    // ROS 초기화, "ros_serial_node"라는 이름의 노드 생성
  ros::NodeHandle nh;                          // NodeHandle 객체 생성 (ROS와 통신하기 위한 인터페이스)
  ros::Publisher ledTogglePub = nh.advertise<std_msgs::Int16>("toggle_led", 10);  // "toggle_led"라는 토픽을 통해 Int16 메시지 전송
  ros::Rate loop_rate(1);                      // 루프 속도 설정 (1Hz, 1초에 한번 실행)
  int count = 0;                               // 카운트 변수

  while (ros::ok())  // ROS가 정상 동작하는 동안 반복
  {
    std_msgs::Int16 ledVal;                   // Int16 타입의 메시지 객체 생성
    std::stringstream ss;                      // 메시지 출력용 스트링스트림 객체
    ledVal.data = ++count % 2;                 // 0과 1을 번갈아 가며 토글하는 값 설정 (LED 상태: 0은 OFF, 1은 ON)
    ss << "ros_seiral_node : " << count;       // 디버그용 출력 메시지
    ROS_INFO("%d", ledVal.data);               // 로그로 현재 LED 상태 출력
    ledTogglePub.publish(ledVal);              // "toggle_led" 토픽에 메시지 발행
    ros::spinOnce();                           // 콜백 함수를 한 번 실행 (필수)
    loop_rate.sleep();                         // 루프 주기 (1초 대기)
  }
  return 0;
}
```

#### 1.2. 주요 동작

- **ROS 초기화**: `ros::init(argc, argv, "ros_serial_node");`로 ROS 노드를 초기화합니다.
- **ROS Publisher 설정**: `ros::Publisher ledTogglePub`는 "toggle_led"라는 이름의 토픽을 통해 `std_msgs::Int16` 메시지를 발행합니다. 이 메시지에는 LED의 상태 (0 또는 1)가 포함됩니다.
- **반복 동작**: `ros::Rate loop_rate(1)`로 루프 속도를 1Hz로 설정하고, `while (ros::ok())` 루프에서 계속해서 메시지를 발행합니다.
  - LED 상태는 `++count % 2`로 계산되어 0과 1을 번갈아 가며 변화합니다.
  - `ROS_INFO("%d", ledVal.data)`로 상태를 출력하고, `ledTogglePub.publish(ledVal)`로 메시지를 발행합니다.
  - `ros::spinOnce()`는 콜백 함수가 호출될 수 있도록 하고, `loop_rate.sleep()`로 루프를 1초 대기시킵니다.

### 2. **Arduino 코드**

Arduino 코드에서는 ROS에서 발행된 메시지를 받아 LED를 제어합니다. 이 코드에서는 `rosserial_arduino` 라이브러리를 사용하여 ROS와의 통신을 처리합니다.

#### 2.1. 코드 분석

```cpp
#include <ros.h>
#include <std_msgs/Int16.h>
ros::NodeHandle nh;

void messageCb(const std_msgs::Int16& toggle_msg) {
  int ledVal = toggle_msg.data;  // 수신된 메시지에서 LED 상태 가져오기
  if(ledVal)
    digitalWrite(LED_BUILTIN, HIGH);  // LED를 켬
  else
    digitalWrite(LED_BUILTIN, LOW);   // LED를 끔
  delay(1000);  // 1초 대기
}

ros::Subscriber<std_msgs::Int16> sub("toggle_led", &messageCb);  // "toggle_led" 토픽을 구독

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // 내장 LED 핀을 출력 모드로 설정
  nh.initNode();                 // ROS 노드 초기화
  nh.subscribe(sub);             // "toggle_led" 토픽을 구독
}

void loop() {
  nh.spinOnce();  // ROS 메시지 수신 및 콜백 함수 실행
  delay(1);       // 1ms 대기
}
```

#### 2.2. 주요 동작

- **ROS Node 초기화**: `nh.initNode();`로 Arduino 보드를 ROS 네트워크에 연결합니다.
- **Subscriber 설정**: `ros::Subscriber<std_msgs::Int16> sub("toggle_led", &messageCb);`는 "toggle_led"라는 이름의 토픽을 구독하며, 메시지를 받을 때마다 `messageCb` 함수를 호출합니다.
- **`messageCb` 콜백 함수**:
  - 이 함수는 ROS 메시지가 수신될 때 호출됩니다. 메시지의 `data` 값을 가져와 LED의 상태를 제어합니다.
  - `digitalWrite(LED_BUILTIN, HIGH);`로 LED를 켜고, `digitalWrite(LED_BUILTIN, LOW);`로 LED를 끕니다.
  - 1초 간격으로 토글되도록 `delay(1000)`을 사용하여 1초마다 LED 상태가 변경됩니다.
- **ROS 메시지 수신**: `nh.spinOnce();`는 한 번의 메시지 수신 및 콜백 함수 실행을 처리합니다.

### 3. **동작 흐름**

1. **ROS 노드 (`ros_serial_node`)**:
   - 이 노드는 1초에 한 번씩 "toggle_led"라는 토픽을 통해 메시지를 발행합니다.
   - 발행되는 메시지는 0과 1을 번갈아 가며 변경되며, 이 값은 Arduino에서 LED 상태를 제어하는 데 사용됩니다.
   
2. **Arduino**:
   - Arduino는 "toggle_led"라는 토픽을 구독하여, 수신된 메시지 (`std_msgs::Int16`)에 따라 내장 LED를 켜거나 끕니다.
   - LED는 1초 간격으로 ON/OFF 상태가 반복됩니다.

### 4. **통신 흐름**

- **ROS → Arduino**:
  - ROS 노드는 `"toggle_led"`라는 토픽을 통해 LED 상태를 나타내는 메시지를 발행합니다.
  - Arduino는 해당 토픽을 구독하고, 메시지를 받아서 LED 상태를 변경합니다.

### 5. **실행 요약**

- ROS에서 "toggle_led"라는 토픽을 통해 0과 1을 번갈아 발행하고, Arduino는 이를 수신하여 내장 LED를 제어합니다.
  - ROS: 0 → Arduino: LED OFF
  - ROS: 1 → Arduino: LED ON
- 이 과정은 1초 간격으로 반복되어, LED가 1초마다 켜지고 꺼지는 동작을 하게 됩니다.