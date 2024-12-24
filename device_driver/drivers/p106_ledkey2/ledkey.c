#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#define OFF 0
#define ON 1
#define GPIOCNT 8

int gpioLedInit(void);
void gpioLedSet(long val);
void gpioLedFree(void);
int gpioKeyInit(void);
int gpioKeyGet(void);
void gpioKeyFree(void);

int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};

static int hello_init(void)
{
	int ret = 0;
	printk("This is Test World\n");
	ret = gpioLedInit();
	if(ret <0)
		return ret;
	gpioLedSet(0xff);

	ret =gpioKeyInit();
	if(ret <0)
		return ret;
	ret=gpioKeyGet();
	if(ret != 0)
		printk("key : %#04x\n", ret);
	return 0;
}
static void hello_exit(void)
{
	int ret = 0; 
	printk("Goodbye, world\n");
	gpioLedSet(0x00);
	gpioLedFree();

	ret=gpioKeyGet();
	if(ret !=0)
		printk("key : %#04x\n", ret);
	gpioKeyFree();
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
			printk("Failed direction_output gpio%d error\n",gpioLed[i]);
			return ret;
		}
	}
	return ret;
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
		if(ret < 0)
		{
			printk("Failed request key gpio%d error\n",gpioKey[i]);
			return ret;
		}
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0)
		{
			printk("Failed direction_output key gpio%d error\n",gpioKey[i]);
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

int gpioKeyGet(void)
{
	int i;
	long val = 0x00;
	for (i = 0; i < GPIOCNT; i++)
	{
		val = val | (gpio_get_value(gpioKey[i]) << i);
	}
	return val;
}
void gpioLedFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioLed[i]);
	}
}

void gpioKeyFree(void)
{
	int i;
	for (i = 0; i < GPIOCNT; i++)
	{
		gpio_free(gpioKey[i]);
	}
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("kcci");
MODULE_DESCRIPTION("kcci led key test module");
