#include <linux/kernel.h>
#include <linux/gpio.h>

#define OFF 0
#define ON 1
#define GPIOCNT 8
int gpioLedInit(void);
void gpioLedSet(long val);
void gpioLedFree(void);

int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
long sys_mysyscall(long val)
{
	int ret=0;
	ret=gpioLedInit();
	if(ret<0)
		return ret;
	gpioLedSet(val);
	gpioLedFree();
	return (long)ret;
}

int gpioLedInit(void)
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
	return ret;
}
void gpioLedSet(long val)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],(val & (0x01 << i)));
	}
}
void gpioLedFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioLed[i]);
	}
}
