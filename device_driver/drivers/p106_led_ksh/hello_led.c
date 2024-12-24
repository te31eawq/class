#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#define OFF 0
#define ON 1
#define GPIOCNT 8
int gpioLed[8] = {518,519,520,521,522,523,524,525};

static int hello_init(void)
{
	int ret=0;
	char gpioName[10];
	printk("This is Test World\n");
	for(int i=0;i<GPIOCNT;i++)
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

	for(int i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],ON);
	}
	return 0;
}
static void hello_exit(void)
{
	printk("Goodbye, world\n");
	for(int i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],OFF);
	}
	for(int i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioLed[i]);
	}
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");
