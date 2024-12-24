#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <linux/moduleparam.h>

#include "ioctl_test.h"

#define DEBUG 1

#define OFF 0
#define ON 1
#define GPIOCNT 8

static int gpioLedInitFlag = 0;
static int gpioKeyInitFlag = 0;

static int gpioLedInit(void);
static void gpioLedSet(long val);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);

static int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
static int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};

static int timerVal = 10;		//timerVal=f=100HZ, T=1/100 = 10ms, 100*10ms = 1Sec
module_param(timerVal,int ,0);
static int ledVal = 0;
module_param(ledVal,int ,0);
struct timer_list timerLed;

void kerneltimer_func(struct timer_list *t);
void kerneltimer_registertimer(unsigned long timeover)
{
	timerLed.expires = get_jiffies_64() + timeover;	//10ms * 100 = 1Sec
	timer_setup(&timerLed,kerneltimer_func,0);
	add_timer(&timerLed);
}
void kerneltimer_func(struct timer_list *t)
{
#if DEBUG
	printk("ledVal : %#04x\n", (unsigned int)(ledVal));
#endif
	if(gpioKeyGet())
	{
		ledVal = gpioKeyGet();
	}
	gpioLedSet(ledVal);
	
	ledVal = ~ledVal & 0xff;
	mod_timer(t,get_jiffies_64() + timerVal);
}

int kerneltimer_init(void)
{
	int ret;
	ret = gpioLedInit();
	if(ret<0)
		return ret;
	ret = gpioKeyInit();
	if(ret<0)
		return ret;
#if DEBUG
	printk("timerVal : %d, sec : %d\n", timerVal,timerVal/HZ);
#endif
	kerneltimer_registertimer(timerVal);
	return 0;
}

void kerneltimer_exit(void)
{
	gpioLedFree();
	gpioKeyFree();
	if(timer_pending(&timerLed))
		del_timer(&timerLed);
}
module_init(kerneltimer_init);
module_exit(kerneltimer_exit);
MODULE_AUTHOR("KCCI-AIOT KSH");
MODULE_DESCRIPTION("led key test module");
MODULE_LICENSE("Dual BSD/GPL");

static int gpioLedInit(void)
{
	int i;
	int ret=0;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"led%d",i);
		ret = gpio_request(gpioLed[i], gpioName);
		if(ret < 0)
		{
			printk("Failed request gpio%d error\n",gpioLed[i]);
			return ret;
		}
		ret = gpio_direction_output(gpioLed[i],OFF);
		if(ret < 0)
		{
			printk("Failed directon_output gpio%d error\n",gpioLed[i]);
			return ret;
		}
	}
	gpioLedInitFlag = 1;
	return ret;
}
static void gpioLedSet(long val)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],(val & (0x01 << i)));
	}
}
static void gpioLedFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioLed[i]);
	}
	gpioLedInitFlag = 0;
}

int gpioKeyInit(void)
{
	int i;
	int ret=0;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"key%d",i);
		ret = gpio_request(gpioKey[i], gpioName);
		if(ret < 0) {
			printk("Failed Request gpio%d error\n", gpioKey[i]);
			return ret;
		}
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0) {
			printk("Failed direction_output gpio%d error\n", gpioKey[i]);
       	 	return ret;
		}
	}
	return ret;
}
int	gpioKeyGet(void)
{
	int i;
	int ret;
	int keyData=0;
	for(i=0;i<GPIOCNT;i++)
	{
		ret=gpio_get_value(gpioKey[i]);
		keyData = keyData | ( ret << i );
	}
	return keyData;
}
void gpioKeyFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioKey[i]);
	}
}
