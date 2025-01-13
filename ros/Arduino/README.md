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