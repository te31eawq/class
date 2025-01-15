#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_serial_node");
  ros::NodeHandle nh;
  ros::Publisher ledTogglePub = nh.advertise<std_msgs::Int16>("toggle_led", 10);
  ros::Rate loop_rate(1);
  int count = 0x00;

  while (ros::ok())
  {
    std_msgs::Int16 ledVal;
    std::stringstream ss;
    // ledVal.data = ++count%2;
    ledVal.data = count++;
    if(count > 0x0f)
      count = 0x00;
    ss << "ros_seiral_node : " << count;
    ROS_INFO("%#04x", ledVal.data);
    ledTogglePub.publish(ledVal);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
