#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       

#include <linux/gpio.h>
#include <linux/moduleparam.h>
#include "ioctl_test.h"

#define DEBUG 1

#define   LEDKEY_DEV_NAME            "ledkey"
#define   LEDKEY_DEV_MAJOR            230      

#define OFF 0
#define ON 1
#define GPIOCNT 8

static int gpioLedInit(void);
static void gpioLedSet(long val);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);

static int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
static int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};

static int onevalue = 1;
static char * twostring = NULL;
static int openFlag = 0;

module_param(onevalue, int ,0);
module_param(twostring,charp,0);

static int ledkey_open (struct inode *inode, struct file *filp)
{

#if DEBUG
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
#endif

	if(openFlag)
		return -EBUSY;
	else
		openFlag = 1;

	if(!try_module_get(THIS_MODULE))
		return -ENODEV;

//    return -ENOMEM;
    return 0;
}

static loff_t ledkey_llseek (struct file *filp, loff_t off, int whence )
{
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
    return 0x23;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
    printk( "call read -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
	kbuf=gpioKeyGet();
#if 1
	put_user(kbuf,buf);
#else
	int ret=copy_to_user(buf,&kbuf,sizeof(kbuf));
	if(ret < 0)
        return ret;
#endif
    return sizeof(kbuf);

}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
//    printk( "call write -> buf : %08X, count : %08X \n", (unsigned int)buf, count );

#if 1
	get_user(kbuf,buf);
#else
	int ret;
	ret=copy_from_user(&kbuf,buf,sizeof(kbuf));
#endif
	gpioLedSet(kbuf);
	return sizeof(kbuf);
}

//int ledkey_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

//    printk( "call ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
	int err=0;
	int size=0;
	ioctl_test_info ctrl_info={0,{0}};

	if(_IOC_TYPE(cmd) != IOCTLTEST_MAGIC) return -EINVAL;
	if(_IOC_NR(cmd) >= IOCTLTEST_MAXNR) return -EINVAL;

	size = _IOC_SIZE(cmd);
	if(size)   //_IOR,_IOW,_IOWR
	{
		if((_IOC_DIR(cmd) & _IOC_READ) || (_IOC_DIR(cmd) & _IOC_WRITE) )
		{
			err = access_ok((void*)arg,size);
			if(!err) return err;
		}
	}
	switch(cmd)
	{
		case IOCTLTEST_KEYINIT:
			err=gpioKeyInit();
			break;
		case IOCTLTEST_LEDINIT:
			err=gpioLedInit();
			break;
		case IOCTLTEST_KEYLEDINIT:
			err=gpioKeyInit();
			if(err<0)
				break;
			err=gpioLedInit();
			if(err<0)
				break;
			break;
		case IOCTLTEST_KEYLEDFREE:
			gpioKeyFree();
			gpioLedFree();
			break;
		case IOCTLTEST_READ:
			ctrl_info.buff[0] = gpioKeyGet();
			if(ctrl_info.buff[0] != 0)
				ctrl_info.size = 1;
			err = copy_to_user( (void *)arg,(void *)&ctrl_info,size);
			if(err != 0)
				return -EFAULT;
			break;
		case IOCTLTEST_LEDON:
			gpioLedSet(0xff);
			break;
		case IOCTLTEST_LEDOFF:
			gpioLedSet(0x00);
			break;
		case IOCTLTEST_GETSTATE:
			err=gpioKeyGet();
			break;
		case IOCTLTEST_WRITE:
			err = copy_from_user((void*)&ctrl_info,(void*)arg,size);
			gpioLedSet(ctrl_info.buff[0]);
			printk("ctrl_info.buff : %x\n",ctrl_info.buff[0]);
			break;

		case IOCTLTEST_WRITE_READ:
			err = copy_from_user((void*)&ctrl_info,(void*)arg,size);
			gpioLedSet(ctrl_info.buff[0]);
			ctrl_info.buff[0] = gpioKeyGet();
			if(ctrl_info.buff[0] != 0)
				ctrl_info.size = 1;
			err = copy_to_user( (void *)arg,(void *)&ctrl_info,size);
			if(err != 0)
				return -EFAULT;
			break;

	}
    return err;
}

static int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
	if (gpioLedInitFlag)
        gpioLedFree();
    if(gpioKeyInitFlag)
        gpioKeyFree();
	module_put(THIS_MODULE);
	openFlag = 0;
    return 0;
}

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
}
static int gpioKeyInit(void)
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
static int	gpioKeyGet(void)
{
	int i;
	int ret;
	int keyData=0;
	for(i=0;i<GPIOCNT;i++)
	{
//		ret=gpio_get_value(gpioKey[i]) << i;
//		keyData |= ret;
		ret=gpio_get_value(gpioKey[i]);
		keyData = keyData | ( ret << i );
	}
	return keyData;
}
static void gpioKeyFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioKey[i]);
	}
}

struct file_operations ledkey_fops =
{
//    .owner    = THIS_MODULE,
    .open     = ledkey_open,     
    .read     = ledkey_read,     
    .write    = ledkey_write,    
	.unlocked_ioctl = ledkey_ioctl,
    .llseek   = ledkey_llseek,   
    .release  = ledkey_release,  
};

static int ledkey_init(void)
{
    int result;

    printk( "call ledkey_init \n" );    

#if 0
	result = gpioLedInit();
	if(result < 0)
		return result;

	result = gpioKeyInit();
	if(result < 0)
		return result;
#endif

    result = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if (result < 0) return result;

    return 0;
}

static void ledkey_exit(void)
{
    printk( "call ledkey_exit \n" );    
    unregister_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME );
#if 0
	gpioLedFree();
	gpioKeyFree();
#endif
}

module_init(ledkey_init);
module_exit(ledkey_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("kcci");
MODULE_DESCRIPTION("led key test module");