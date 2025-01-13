```
-.ssh server 설치
~$sudo apt update
~$sudo apt install openssh-server
윈도우즈에서 putty 설치 

-.삼바 서버 설정
~$ sudo apt install samba -y		//패키지 설치
~$ sudo mkdir /srv/samba		//공유 디렉토리 setup
~$ sudo chmod 777 /srv/samba	//디렉토리 접근권한 모두허용
~$ sudo vi /etc/samba/smb.conf	//삼바 환경 설정
 맨 끝에 아래 라인 추가 
===============================
[samba]
   comment = shared folder
   path = /srv/samba
   browseable = yes
   writable = yes
   valid users = ubuntu
   public = yes
================================
~$ sudo smbpasswd -a ubuntu	//접속 계정과 암호 설정 
~$ sudo service smbd restart 	//삼바데몬 재시작

윈도우즈 탐색기 실행창에서
\\192.168.0.x     			//x:리눅스 서버 IP


=================================
NFS 서버 설치 - ubuntu 
~$sudo apt-get install nfs-common nfs-kernel-server rpcbind
~$sudo mkdir /srv/nfs
~$sudo chmod 777 /srv/nfs
~$sudo vi /etc/exports
-----------------------
/srv/nfs    10.10.14.0/24(rw,sync)
-----------------------
~$sudo service nfs-kernel-server restart
~$sudo exportfs
/srv/nfs        192.168.0.0/24(rw,sync)

NFS 마운트 (파일 읽고 쓰기) - raspberryPi
~$sudo mkdir /mnt/ubuntu_nfs
~$sudo mount -t nfs 10.10.14.28:/srv/nfs /mnt/ubuntu_nfs   //XX:리눅스 IP

~$df
-------------
10.10.14.XX:/srv/nfs   78310400 5295104  69014016   8% /mnt/ubuntu_nfs
-------------
~$cd /mnt/ubuntu_nfs  ==> 192.168.10.50서버의 /srv/nfs에 접속됨

NFS 마운트 해제
~$sudo umount /mnt/lect_nfs

ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
라즈베리파이
cd /mnt/ 안에 sudo vi mount.sh안에

#!/bin/bash
SERVIP=10.10.14.28                     #xx : 자기꺼 ubuntu IP
if ! df | grep ubuntu_nfs > /dev/null ; then
        ping -c 1 $SERVIP > /dev/null
        if [ $? -eq 0 ] ; then
                sudo mount -t nfs $SERVIP:/srv/nfs /mnt/ubuntu_nfs
                df | grep ubuntu_nfs
        fi
fi

============
ubuntu cd /mnt/ 안에 vi mount.sh에

#!/bin/bash
SERVIP=10.10.14.40                      #xx : ubuntu host ip
if ! df | grep lect_nfs > /dev/null ; then
        ping -c 1 $SERVIP > /dev/null
        if [ $? -eq 0 ] ; then
                sudo mount -t nfs $SERVIP:/srv/lect_nfs /mnt/lect_nfs
                df | grep lect_nfs
        fi
fi
============

라즈베리와 ubuntu home에서 vi .profile에 맨 마지막에
if [ -f "/mnt/mount.sh" ] ; then
        . /mnt/mount.sh
fi
============

위에꺼 다 하고
vi /etc/sudoers.d/01_ubuntu_nopasswd
요거 친다음
ubuntu ALL=(ALL) NOPASSWD: ALL
이거 저장
```