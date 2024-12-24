virtualbox(VirtualBox-7.0.18-162988-Win.exe) 설치 후 실행 및 새로 만들기
 이름 :  ubuntu20.04
  폴더 : D:
 메모리 : 8192MB
 프로세서 : 4개
 가상하드디스크 : 170GB   설정 완료
 - 미리전체크기 할당 X

 virtualbox 설정
   저장소  ->  컨트롤러 : IDE  추가  -> 다운받은 ubuntu-20.04.6-desktop-amd64.iso 선택 (4.05GB)
   네트워크 어댑터1 -> 어댑터에 브리지 선택 
   USB 컨트롤러 활성화 -> USB3.0  선택
  메뉴 Export 선택 후
   디스플레이 -> 그래픽 컨트롤러  VBoxVGA,


 virtualbox -> ubuntu20.04 선택 후 시작

  설치 언어 : 한국어 , Ubuntu 설치, 키보드 레이아웃 Korean, 101/104 key 호환 -> 설치중 업데이트 다운로드 체크 해제 -> 다음 
   -> 디스크를 지우고 ubuntu 설치 체크 -> 지금 설치
  거주지 : Seoul
  이름(계정) : ubuntu         
  컴퓨터 이름 : ubuntuXX  XX 00 ~ 30
  사용자 이름 : ubuntu
  암 호 : ubuntu

 설치 완료 후 지금 다시 시작 
  
  
 설치후 설정-> 디스플레이 그래픽 컨트롤럴  VMSVGA 변경 후 시작

  login 계정 : ubuntu 
  암호 : ubuntu
  
  팝업 메시지 :   업그레이드 하지 않음(ubuntu22.04)
  불완전한 언어 지원 -> 이동작을 실행 -> 언어지원 설치 -> 한국어 제일 위쪽 배치 -> 시스템 적용

  고정 IP 할당
  프로그램 표시 -> 설정 -> 네트워크 -> 유선 -> 설정  아이콘 -> IPv4 탭 -> 수동
  주소 : 10.10.141.XX 할당         XX  : 윈도우 IP + 30  (31~ 60) 나는 28번(리눅스) 8번대
  네트마스크 : 255.255.255.0  
  게이트웨이 : 10.10.141.254
  네임서버 : 203.248.252.2    
  입력 후 적용 및 유선  off  후 on
  $sudo apt update
  $sudo apt install net-tools
  $ifconfig                       //할당된 IP 확인



  원격접속 ssh 서버 설치 
  $sudo apt install openssh-server -y 

  윈도우 원격터미널 putty 실행 및 접속
  호스트 이름 : 10.10.14.XX      : ubuntu 고정 ip
  SSH 프로토콜 
  저장된 세션 : ubuntuxx    이름으로 저장 및 열기

디스플레이 화면 자동 해상도 조정
virtual box  메뉴-> 장치 -> 게스트확장 CD 삽입
 $sudo apt-get install dkms build-essential linux-headers-generic linux-headers-virtual virtualbox-guest-utils
 $cd /media/ubuntu/VBox_GAs_7.1.14/
 $sudo ./VBoxLinuxAdditions.run


  삼바(윈도우즈와 리눅스 파일공유 서버) , NFS(  리눅스와 리눅스 ) - 첨부파일 참고

  ---
  ---

-. Ubuntu 20.04 Host 커널 빌드 (HDD 약27GB 필요)
  https://www.kernel.org  현재버젼 Kernel: 5.15.0, 설치버전 5.19.9 
$ mkdir ~/kernel_ubuntu ; cd kernel_ubuntu

$ wget https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.19.9.tar.xz

$ tar xvf linux-5.19.9.tar.xz

$ cd linux-5.19.9

$ cp /boot/config-5.15.0-105-generic .config

$ sudo apt install build-essential libncurses5-dev libssh-dev bison flex libelf-dev dwarves zstd

$ make menuconfig			   

-*- Cryptographic API  --->          // 이동 후 제일 아래(인증 문자열 제거)

 Certificates for signature checking  --->   //선택, 아래 문자열 제거
 
 (debian/canonical-certs.pem) Additional X.509 keys for default system key 
 
 (debian/canonical-revoked-certs.pem) X.509 도 없애기 
 
 ()  Additional X.509 keys for default system keyring

 (debian/canonical-revoked-certs.pem) X.509 certificates to be preloaded into the system blacklist key 
 ()    X.509 certificates to be preloaded into the system blacklist key
 
   수정 후 Exit 선택 후 저장/종료
   
$ make bzImage –j4 ; make modules -j4       //kernel : 20분, modules :58분

$ sudo make modules_install 

$ cd /lib/modules/5.19.9

$ sudo find . -name *.ko -exec strip --strip-unneeded {} \;

참고 : initramfs 생성 명령 $ sudo update-initramfs –c –k 5.19.9

    $ cd  ~/kernel_ubuntu/linux-5.19.9		   //커널홈 디렉토리  
    
$ sudo make install

$ sudo reboot                        //재부팅시 ESC키 grub 부트로드 메뉴 

$ uname  -a                         //커널 버전 및 빌드 시간 확인 업그레이드완료 

     Linux pi00 6.1.77-v7l+ #2 SMP Mon Apr 29 13:20:56 KST 2024 armv7l GNU/Linux
     
