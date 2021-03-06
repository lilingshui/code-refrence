#include<linux/init.h>
#include<linux/module.h>

static int __init hello_init(void)
{
	printk("======= Hello init ======\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk("======= Hello exit ======\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Peng Shuiming");
