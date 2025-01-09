# 목차
1. [turtlebot 설치 및 사용법](#ubunut에서-할-것)
2. [ros에 관해서](#ros)

### ubunut에서 할 것
$ sudo apt update

$ sudo apt upgrade

$ wget https://raw.githubusercontent.com/ROBOTIS-GIT/robotis_tools/master/install_ros_noetic.sh

$ chmod 755 ./install_ros_noetic.sh 

$ bash ./install_ros_noetic.sh

### SBC 설정

### SBC 설정(Raspberry Pi) - noetic-raspberry 3B+
이미지 다운로드 및 압축 해제 (ubuntu20.04 사용)
Direct Link : https://www.robotis.com/service/download.php?no=2008

### Raspberry Pi Imager를 통해 sd카드 write 

###  sd카드  ubuntu 마운트 후
ubuntu@ubuntu00:~$ df
/dev/sdb2                     8188896   6243460   1579240  80% /media/ubuntu/writable

ubuntu@ubuntu00:~$ cd /media/ubuntu/writable

ubuntu@ubuntu00:~/media/ubuntu/writable$ sudo vi /etc/netplan
```python
# This file is generated from information provided by the datasource.  Changes
# to it will not persist across an instance reboot.  To disable cloud-init's
# network configuration capabilities, write a file
# /etc/cloud/cloud.cfg.d/99-disable-network-config.cfg with the following:
# network: {config: disabled}

network:
    version: 2
    renderer: networkd
    ethernets:
        eth0:
            dhcp4: true
            optional: true
    wifis:
        wlan0:
            dhcp4: no
            dhcp6: no
            addresses: [10.10.14.108/24]
            gateway4: 10.10.14.254
            nameservers:
                addresses: [203.248.252.2, 8.8.8.8]
            access-points:
                embA:
                    password: embA1234
```

###  hostname 변경
ubuntu@ubuntu00:~$ sudo vi /media/ubuntu/writable/etc/hostname
```
botXX
```

## sd카드 및 ethernet 라즈베리파이 연결 후 부팅

## putty 할당한  ip 접속
id : ubuntu

passwd : turtlebot

## 넷툴 설치
$ sudo apt install net-tools

sudo apt install 패키지설치시 아래 오류 발생시
Waiting for cache lock: Could not get lock /var/lib/dpkg/lock-frontend

## lock 파일 제거
$ sudo rm /var/lib/apt/lists/lock 

$ sudo rm /var/cache/apt/archives/lock

$ sudo rm /var/lib/dpkg/lock*

## 패키지 업데이트

$ sudo dpkg --configure -a

$ sudo apt update

$ ifconfig			#할당된 ip 확인

## smaba 설치
$ sudo apt install samba -y

$ sudo vi /etc/samba/smb.conf
```python
[pi_smb]
        path = /srv/samba
        browseable = yes
        writable = yes
        valid users = ubuntu
        public = yes
```
$ sudo mkdir /srv/samba

$ sudo chmod 777 /srv/samba

$ sudo smbpasswd -a ubuntu      //password : turtlebot 사용

$ sudo service smbd restart


## 스왑메모리 확장
$ sudo apt-get install dphys-swapfile

$ sudo vi /sbin/dphys-swapfile
```
CONF_SWAPSIZE=2048
```
$ sudo /etc/init.d/dphys-swapfile restart

$ free

### 터틀봇 환경 변수 등록 및 실행

$ vi .bashrc

```python
export ROS_MASTER_URI=http://10.10.14.XX:11311		# XX :ubuntu host 주소
export ROS_HOSTNAME=10.10.14.108			#라즈베리파이 host wifi 주소
export TURTLEBOT3_MODEL=burger
```
$ source .bashrc

## 그다음
### ubuntu에서
$ sudo apt-get install ros-noetic-joy ros-noetic-teleop-twist-joy \
  ros-noetic-teleop-twist-keyboard ros-noetic-laser-proc \
  ros-noetic-rgbd-launch ros-noetic-rosserial-arduino \
  ros-noetic-rosserial-python ros-noetic-rosserial-client \
  ros-noetic-rosserial-msgs ros-noetic-amcl ros-noetic-map-server \
  ros-noetic-move-base ros-noetic-urdf ros-noetic-xacro \
  ros-noetic-compressed-image-transport ros-noetic-rqt* ros-noetic-rviz \
  ros-noetic-gmapping ros-noetic-navigation ros-noetic-interactive-markers

$ sudo apt install ros-noetic-dynamixel-sdk

$ sudo apt install ros-noetic-turtlebot3-msgs

$ sudo apt install ros-noetic-turtlebot3

$ vi .bashrc
```p
128 export ROS_MASTER_URI=http://10.10.14.28:11311 #자기꺼 주소
129 export ROS_HOSTNAME=10.10.14.28
```
$ source .bashrc

### 이후 turtlebot에서
```
$ sudo dpkg --add-architecture armhf  ## lock 파일 제거해야함 이상하면
$ sudo apt-get update  
$ sudo apt-get install libc6:armhf  

$ export OPENCR_PORT=/dev/ttyACM0 
$ export OPENCR_MODEL=burger_noetic  

$ rm -rf ./opencr_update.tar.bz2  

$ wget https://github.com/ROBOTIS-GIT/OpenCR-Binaries/raw/master/turtlebot3/ROS1/latest/opencr_update.tar.bz2   
$ tar -xvf opencr_update.tar.bz2 
$ cd ./opencr_update  
$ ./update.sh $OPENCR_PORT $OPENCR_MODEL.opencr 

---

### ubuntu에서
$ roscore

### turtlebot에서
$ roslaunch turtlebot3_bringup turtlebot3_robot.launch ## ./bringup.sh로 만들었음

### ubuntu에서
rqt로 이제 확인할 수 있음 ## roscore 실행한 상태로
```
---

### ubuntu에서
$ vi .bashrc
```p
130 export TURTLEBOT3_MODEL=burger
```

## 카메라
```
11. 터틀봇 usb webcam 사용

turtlebot3에서 설치 
$ sudo apt install ros-noetic-cv-camera
$ rosrun cv_camera cv_camera_node

ubuntu Master 
$ rqt_image_view #실행후 /cv_camera/image_raw 선택

slam 또는 navigation 실행 후 좌측 display 창에 
 Image  topic에  /cv_camera/image_raw  선택 , 
 Transport Hint에 raw 선택
```

### slam
ubuntu
```
$ roslaunch turtlebot3_slam turtlebot3_slam.launch
```

도중에 map 저장
```
$ rosrun map_server map_saver -f ~/map

```

### navigate
```
roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml
```

## ROS
### 운영체제 소개
- #### 범용 컴퓨터
    - Windows, Linux, MAC
- 스마트폰
    - Android, IOS, Windows Phone
- ROS = Robot Operating System

- ROS는 메타운영체제(Meta-Operation System)이다

