#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
static int hello_init(void)
{
	printk("This is Test World\n");
	return 0;
}
static void hello_exit(void)
{
	printk("Goodbye, world\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("kcci");
MODULE_DESCRIPTION("kcci led key test module");
