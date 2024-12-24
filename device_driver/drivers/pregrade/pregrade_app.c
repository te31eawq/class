#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "ioctl_test.h"

#define WRITE_DEVICE_FILENAME  "/dev/pregrade_led"  //major:230, minor:0
#define READ_DEVICE_FILENAME   "/dev/pregrade_key"   //major:230, minor:1

void print_led(unsigned long val);
int main(int argc,char * argv[])
{
	ioctl_test_info info={0,{0}};
	int state = 0;
	int oldState =0;
	int  read_dev;
    int  write_dev;
    int ret;
	if(argc < 2)
	{
		printf("USAGE : %s [ledval] \n",argv[0]);
		return 1;
	}
//	buff = atoi(argv[1]);
	state = (char)strtoul(argv[1],0,16);
	info.buff[0] = state;
    read_dev  = open( READ_DEVICE_FILENAME,  O_RDWR|O_NDELAY );
    if( read_dev < 0 ) 
    {  
		perror("open()");
        printf( READ_DEVICE_FILENAME " open error\n" );
        exit(1);
    }
    write_dev = open( WRITE_DEVICE_FILENAME, O_RDWR|O_NDELAY );
    if( write_dev < 0 ) 
    {  
		perror("open()");
        printf( WRITE_DEVICE_FILENAME " open error\n" );
        close( read_dev );
        exit(1);
    }
	ioctl(write_dev,IOCTLTEST_WRITE, &info);
	print_led(state);
	// ioctl(dev, IOCTLTEST_TIMERON);
	state = 0;
	do {
		state = ioctl(read_dev,IOCTLTEST_GETSTATE);
//		buff = 1 << buff-1;
		if((state != 0) && (oldState != state))
		{
			printf("key : %#04x\n",state);
			info.buff[0] = state;
    		ioctl(write_dev,IOCTLTEST_WRITE,&info);
			print_led(state);
			oldState = state;
			if(state == 0x80) //key:8
				break;
		}
	} while(1);

	// ioctl(dev, IOCTLTEST_TIMEROFF);
    close(read_dev);
    close(write_dev);
    return 0;
}
void print_led(unsigned long led)
{
	int i;
	puts("1:2:3:4:5:6:7:8");
	for(i=0;i<=7;i++)
	{
		if(led & (0x01 << i))
			putchar('O');
		else
			putchar('X');
		if(i < 7 )
			putchar(':');
		else
			putchar('\n');
	}
	return;
}
