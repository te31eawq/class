cmake_minimum_required(VERSION 2.8.3)
project(ros_serial_topic)
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)
catkin_package(CATKIN_DEPENDS roscpp std_msgs)
include_directories(${catkin_INCLUDE_DIRS})
add_executable(ros_serial_uno src/ros_serial_uno.cpp)
target_link_libraries(ros_serial_uno ${catkin_LIBRARIES})
