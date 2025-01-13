### Arduino
File -> Preference -> Additional Board Manager Url 부분에
```
https://raw.githubusercontent.com/ROBOTIS-GIT/OpenCR/master/arduino/opencr_release/package_opencr_index.json
```

### Libraries는 OpenCR 다운로드

![text](./images/OpenCR_install.png)

### Ubuntu에서 Arduino 실행

https://www.arduino.cc/en/software 에서 Appimage 다운로드 후 ubuntu에서 실행

### USB Port Settings

```
$ wget https://raw.githubusercontent.com/ROBOTIS-GIT/OpenCR/master/99-opencr-cdc.rules
$ sudo cp ./99-opencr-cdc.rules /etc/udev/rules.d/
$ sudo udevadm control --reload-rules
$ sudo udevadm trigger
```

### RosSerial
```
1.ros_serial_arduni.ino 작성 및 빌드 / 업로드
----------------------------------
#include <ros.h>
#include <std_msgs/Int16.h>
ros::NodeHandle  nh;
void messageCb( const std_msgs::Int16& toggle_msg){
  int ledVal = toggle_msg.data;
  if(ledVal)
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  else                                // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second  
}
ros::Subscriber<std_msgs::Int16> sub("toggle_led", &messageCb );
void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
 // nh.getHardware()->setBaud(57600);
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
---------------------------------------------
2.ubuntu linux에서
리눅스 ros serial 패키지 설지
$ sudo apt-get install ros-noetic-rosserial ros-noetic-rosserial-server ros-noetic-rosserial-arduino

3. roscore 실행

4. ubuntu 로스시리얼 서버를 실행

ubuntu에 usb 시리얼 장치 추가 후
$ rosrun rosserial_python serial_node.py __name:=arduino _port:=/dev/ttyACM0 _baud:=57600

5. ubuntu에서 publisher 작성 및 빌드
패키지 이름 ros_seiral_topic, 
노드 명 ros_serial_node
토픽 명 toggle_led

$cm 

6. ros 노드 실행
$ rosrun ros_serial_topic ros_serial_uno
```
### [예제](../../Arduino/examples/ros_serial_arduino/)
---
