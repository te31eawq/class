#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#include <linux/moduleparam.h>
#include <asm/uaccess.h>

#include <linux/slab.h>
#include <linux/time.h>
#include <linux/timer.h>


#include "ioctl_test.h"

#define   LEDKEY_DEV_NAME            "pregrade"
#define   LEDKEY_DEV_MAJOR            230      

#define DEBUG 1

#define OFF 0
#define ON 1
#define GPIOCNT 8

static int gpioLedInitFlag = 0;

static int gpioLedInit(void);
static void gpioLedSet(long val);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);

void kerneltimer_func(struct timer_list *t);
void kerneltimer_registertimer(unsigned long timeover);

static int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
static int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};


static int timerVal = 50;		//timerVal=f=100HZ, T=1/100 = 10ms, 100*10ms = 1Sec
module_param(timerVal,int ,0);
static int ledVal = 0;
module_param(ledVal,int ,0);
struct timer_list timerLed;


int minor0_open (struct inode *inode, struct file *filp)
{
    printk( "call minor0_open\n" );
    return 0;
}

ssize_t minor0_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;    
	int ret;
	//  get_user(status,buf);
    ret=copy_from_user(&status,buf,count);
    gpioLedSet(status);
	ledVal = status;

    return count;
}

static long minor0_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
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
		case IOCTLTEST_WRITE:
			err = copy_from_user((void*)&ctrl_info,(void*)arg,size);
			gpioLedSet(ctrl_info.buff[0]);
			ledVal = ctrl_info.buff[0];
			printk("ctrl_info.buff : %x\n",ctrl_info.buff[0]);
			break;
		case IOCTLTEST_READ:
			ctrl_info.buff[0] = gpioKeyGet();
			if(ctrl_info.buff[0] != 0)
				ctrl_info.size = 1;
			err = copy_to_user((void *)arg,(void *)&ctrl_info,size);
			if(err != 0)
				return -EFAULT;
			break;
		case IOCTLTEST_GETSTATE:
			err=gpioKeyGet();
			break;
		case IOCTLTEST_TIMERON:
			kerneltimer_registertimer(timerVal);
			break;
		case IOCTLTEST_TIMEROFF:
			if(timer_pending(&timerLed))
				del_timer(&timerLed);
			break;
	}
    return err;
}

int minor0_release (struct inode *inode, struct file *filp)
{
    printk( "call minor0_release\n" );    
    return 0;
}

int minor1_open (struct inode *inode, struct file *filp)
{
    printk( "call minor1_open\n" );
	kerneltimer_registertimer(timerVal);
    return 0;
}

ssize_t minor1_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;
	int ret;
    status = gpioKeyGet();
//  put_user(status,buf);
    ret=copy_to_user(buf,&status,count);

    return count;
}

static long minor1_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
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
		case IOCTLTEST_WRITE:
			err = copy_from_user((void*)&ctrl_info,(void*)arg,size);
			gpioLedSet(ctrl_info.buff[0]);
			ledVal = ctrl_info.buff[0];
			printk("ctrl_info.buff : %x\n",ctrl_info.buff[0]);
			break;
		case IOCTLTEST_READ:
			ctrl_info.buff[0] = gpioKeyGet();
			if(ctrl_info.buff[0] != 0)
				ctrl_info.size = 1;
			err = copy_to_user((void *)arg,(void *)&ctrl_info,size);
			if(err != 0)
				return -EFAULT;
			break;
		case IOCTLTEST_GETSTATE:
			err=gpioKeyGet();
			break;
		case IOCTLTEST_TIMERON:
			kerneltimer_registertimer(timerVal);
			break;
		case IOCTLTEST_TIMEROFF:
			if(timer_pending(&timerLed))
				del_timer(&timerLed);
			break;
	}
    return err;
}

int minor1_release (struct inode *inode, struct file *filp)
{
    printk( "call minor1_release\n" );
	if(timer_pending(&timerLed))
		del_timer(&timerLed);
    return 0;
}

struct file_operations minor0_fops =
{
    .owner    = THIS_MODULE,
    .write    = minor0_write,
	.unlocked_ioctl = minor0_ioctl,
    .open     = minor0_open,
    .release  = minor0_release,
};

struct file_operations minor1_fops =
{
    .owner    = THIS_MODULE,
    .read     = minor1_read,
	.unlocked_ioctl = minor1_ioctl,
    .open     = minor1_open,
    .release  = minor1_release,
};

int minor_open (struct inode *inode, struct file *filp)
{
    printk( "call minor_open\n" );
    switch (MINOR(inode->i_rdev)) 
    {
    	case 0: filp->f_op = &minor0_fops; break;
    	case 1: filp->f_op = &minor1_fops; break;
    	default : return -ENXIO;
    }
    
    if (filp->f_op && filp->f_op->open)
        return filp->f_op->open(inode,filp);
        
    return 0;
}
struct file_operations minor_fops =
{
    .owner    = THIS_MODULE,
    .open     = minor_open,     
};

static int ledkey_open (struct inode *inode, struct file *filp)
{

    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
		
	if(!try_module_get(THIS_MODULE))
		return -ENODEV;

    return 0;
	//return -ENOMEM;
}

static loff_t ledkey_llseek (struct file *filp, loff_t off, int whence )
{
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
    return 0x23;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
	int ret;
    printk( "call read -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
//	*buf = gpioKeyGet();

	kbuf=gpioKeyGet();
	ret = copy_to_user(buf,&kbuf,1);					// copy_to_user((void *)To, From, 1);
//	return count;
	return ret;
}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
	int ret;
    printk( "call write -> buf : %08X, count : %08X \n", (unsigned int)buf, count);

//	get_user(kbuf, buf);
	ret = copy_from_user(&kbuf,buf,1);			// copy_from_user((void *)To, From, 1);
	ledVal = kbuf;
//	return count;
	return ret;
}

//int ledkey_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

//    printk( "call ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
	int err=0;
	int size=0;

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
		case IOCTLTEST_TIMERON:
			kerneltimer_registertimer(timerVal);
			break;
		case IOCTLTEST_TIMEROFF:
			if(timer_pending(&timerLed))
				del_timer(&timerLed);
			break;
	}
    return err;
}

static int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
	module_put(THIS_MODULE);
	if(timer_pending(&timerLed))
		del_timer(&timerLed);
    return 0;
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
	printk("timerled start \n");
	ret = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &minor_fops);
#if DEBUG
	printk("timerVal : %d, sec : %d\n", timerVal,timerVal/HZ);
#endif
	
	return 0;
}

void kerneltimer_exit(void)
{
	unregister_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME );
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
