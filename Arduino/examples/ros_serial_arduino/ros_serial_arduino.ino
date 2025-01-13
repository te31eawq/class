#include <ros.h>
#include <std_msgs/Int16.h>
ros::NodeHandle nh;

void messageCb(const std_msgs::Int16& toggle_msg){
  int ledVal = toggle_msg.data;
  if(ledVal)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
ros::Subscriber<std_msgs::Int16> sub("toggle_led", &messageCb);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(1);
}
