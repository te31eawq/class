#include <ros.h>
#include <std_msgs/String.h>
#include "bot3gpio.h"

ros::NodeHandle nh;
using bot3_kccistc_service::bot3gpio;
int i = 0;
void callback(const bot3gpio::Request & req, bot3gpio::Response & res){
  res.result = req.a + req.b;
}
ros::ServiceServer<bot3gpio::Request, bot3gpio::Response> gpio_server("bot3_gpio_srv",&callback);
void setup() {
  Serial.begin(115200);
  nh.initNode();
  nh.advertiseService(gpio_server);
}
void loop() {
  nh.spinOnce();
  delay(1000);
}