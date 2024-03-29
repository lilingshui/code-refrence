#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#define GLOBALMEM_SIZE	0x1000
#define GLOBALMEM_MAJOR 0

static int globalmem_major = GLOBALMEM_MAJOR;
static dev_t global_devno = 0;
struct globalmem_dev                                     
{                                                        
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
	wait_queue_head_t r_wait;
};

struct globalmem_dev *globalmem_devp;
int globalmem_open(struct inode *inode, struct file *filp)
{
	printk("===== globalmem_open =====\n");
	filp->private_data = globalmem_devp;
	return 0;
}

int globalmem_release(struct inode *inode, struct file *filp)
{
	printk("===== globalmem_release =====\n");
	return 0;
}

static long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("===== globalmem_ioctl cmd is %d =====\n", cmd);
	return 0;
}

static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t size,
							  loff_t *ppos)
{
	printk("===== globalmem_read =====\n");
	struct globalmem_dev *dev = filp->private_data;
	DECLARE_WAITQUEUE(wait, current);
	add_wait_queue(&dev->r_wait, &wait);
	__set_current_state(TASK_INTERRUPTIBLE);
	schedule();
	printk("===== read buffer =====\n");
	remove_wait_queue(&dev->r_wait, &wait);
	set_current_state(TASK_RUNNING);
	return 0;
}

static ssize_t globalmem_write(struct file *filp, const char __user *buf,
							   size_t size, loff_t *ppos)
{
	printk("===== globalmem_write =====\n");
	struct globalmem_dev *dev = filp->private_data;
	wake_up_interruptible(&dev->r_wait);
	return 0;
}

static const struct file_operations globalmem_fops =
{
	.owner = THIS_MODULE,
	.read = globalmem_read,
	.write = globalmem_write,
	.unlocked_ioctl = globalmem_ioctl,
	.open = globalmem_open,
	.release = globalmem_release,
};

static void globalmem_setup_cdev(struct globalmem_dev *dev, int index)
{
	int err;
	cdev_init(&dev->cdev, &globalmem_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, global_devno, 1);
	if (err)
		printk(KERN_NOTICE "Error %d adding LED%d", err, index);
}

int globalmem_init(void)
{
	int result;

	if (globalmem_major) {
		global_devno = MKDEV(globalmem_major, 0);
		result = register_chrdev_region(global_devno, 1, "globalmem");
	} else {
		result = alloc_chrdev_region(&global_devno, 0, 1, "globalmem");
		globalmem_major = MAJOR(global_devno);
	}  
	if (result < 0)
		return result;

	globalmem_devp = kmalloc(sizeof(struct globalmem_dev), GFP_KERNEL);
	if (!globalmem_devp) {
		result =  - ENOMEM;
		goto fail_malloc;
	}
	memset(globalmem_devp, 0, sizeof(struct globalmem_dev));

	globalmem_setup_cdev(globalmem_devp, 2);


	init_waitqueue_head(&globalmem_devp->r_wait);
	printk("===== globalmem_init =====\n");
	return 0;

fail_malloc: unregister_chrdev_region(global_devno, 1);
	return result;
}

void globalmem_exit(void)
{
	printk("===== globalmem_exit =====\n");
	cdev_del(&globalmem_devp->cdev);
	kfree(globalmem_devp);
	unregister_chrdev_region(MKDEV(globalmem_major, 0), 1);
}

module_init(globalmem_init);
module_exit(globalmem_exit);
MODULE_AUTHOR("Peng Shuiming");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("MODULE TEST");
MODULE_ALIAS("MODULE GLOBALMEM");
