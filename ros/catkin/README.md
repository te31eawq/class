1. 시작
    ```
    cd ~/catkin_ws/src

    catkin_create_pkg oroca_ros_tutorials std_msgs roscpp
    ```

2. vi package.xml
    ```xml
    <?xml version="1.0"?>
    <package>
    <name>oroca_ros_tutorials</name>
    <version>0.1.0</version>
    <description>The oroca_ros_tutorials package</description>

    <maintainer email="passionvirus@gmail.com">Yoonseok Pyo</maintainer>
    <url type="website">http://oroca.org</url>
    <url type="repository">https://github.com/oroca/oroca_ros_tutorials.git</url>
    <author email="passionvirus@gmail.com">Yoonseok Pyo</author>

    <license>MIT</license>

    <buildtool_depend>catkin</buildtool_depend>

    <build_depend>roscpp</build_depend>
    <build_depend>std_msgs</build_depend>
    <build_depend>message_generation</build_depend>

    <run_depend>roscpp</run_depend>
    <run_depend>std_msgs</run_depend>
    <run_depend>message_runtime</run_depend>

    <export>
    </export>
    </package>
    ```
3. 빌드 설정 파일
    ```txt
    vi CMakeLists.txt 

    ---

    cmake_minimum_required(VERSION 2.8.3)
    project(oroca_ros_tutorials)

    ## Find catkin and any catkin packages
    find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)

    ## Declare ROS messages and services
    add_message_files(FILES msgTutorial.msg)

    ## Generate added messages and services
    generate_messages(DEPENDENCIES std_msgs)

    ## Declare a catkin package
    catkin_package(
    #INCLUDE_DIRS include
    LIBRARIES oroca_ros_tutorials
    CATKIN_DEPENDS roscpp std_msgs
    DEPENDS system_lib
    )

    ## Build node
    include_directories(include ${catkin_INCLUDE_DIRS})

    add_executable(ros_tutorial_msg_publisher src/ros_tutorial_msg_publisher.cpp)
    target_link_libraries(ros_tutorial_msg_publisher ${catkin_LIBRARIES})
    add_dependencies(ros_tutorial_msg_publisher oroca_ros_tutorials_generate_messages_cpp)

    add_executable(ros_tutorial_msg_subscriber src/ros_tutorial_msg_subscriber.cpp)
    target_link_libraries(ros_tutorial_msg_subscriber ${catkin_LIBRARIES})
    add_dependencies(ros_tutorial_msg_subscriber oroca_ros_tutorials_generate_messages_cpp)
    ```

4. receiver, publisher
    ```
    receiver

    rosrun oroca_ros_tutorials ros_tutorial_msg_subscriber

    publisher

    rosrun oroca_ros_tutorials ros_tutorial_msg_publisher
    ```

5. rostopic
    ```
    rostopic info 보고싶은 정보

    

    ```

