#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/miscdevice.h>
#include<linux/fs.h>
#include<linux/export.h>

static int misc_open(struct inode *node, struct file *fp)
{
	printk("this dev is open\r\n");
	return 0;
}

static int misc_close(struct inode *node, struct file *fp)
{
	printk("this dev in clode\r\n");
	return 0;
}

ssize_t misc_read(struct file *fp, char __user *buf, size_t size, loff_t *loff)
{
	printk("this dev is read\r\n");
	return 0;
}

ssize_t misc_write(struct file *fp, const char __user *buf, size_t size, loff_t *loff)
{
	printk("this dev is write\r\n");
	return 0;
} 

static const struct file_operations fops = {
	.owner=THIS_MODULE,
	.open=misc_open,
	.read=misc_read,
	.write=misc_write,
	.release=misc_close,
};

struct miscdevice mymisc={
	.minor=MISC_DYNAMIC_MINOR,
	.name="mymisc",
	.fops=&fops,
};

static int __init misc_init(void)
{
	if(misc_register(&mymisc))
	{
		printk("this module is insmod fail\r\n");
		return -1;
	}

	printk("this modules is success\r\n");
	return 0;
}

static void __exit misc_exit(void)
{
	printk("this module is exit\r\n");
}

module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peng Shuiming");


