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
#define DEVICE_STATUS_BUSY	0x01	/* device is in use */
#define init_MUTEX(sem)     sema_init(sem, 1)

static int globalmem_major = GLOBALMEM_MAJOR;
static dev_t global_devno = 0;
struct globalmem_dev                                     
{                                                        
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
	struct semaphore sem;
	unsigned long	dev_status;
};

struct globalmem_dev *globalmem_devp;
int globalmem_open(struct inode *inode, struct file *filp)
{
	if (down_interruptible(&globalmem_devp->sem))
		return  -ERESTARTSYS;

	printk("===== globalmem_open =====\n");

	if (globalmem_devp->dev_status & DEVICE_STATUS_BUSY)
		goto out_busy;

	globalmem_devp->dev_status |= DEVICE_STATUS_BUSY;
	printk("===== globalmem_open success =====\n");
	up(&globalmem_devp->sem);
	return 0;

out_busy:
	up(&globalmem_devp->sem);
	printk("===== globalmem_open failed =====\n");
	return -EBUSY;	
}

int globalmem_release(struct inode *inode, struct file *filp)
{
	if (down_interruptible(&globalmem_devp->sem))
		return  -ERESTARTSYS;
	
	globalmem_devp->dev_status &= ~DEVICE_STATUS_BUSY;
	up(&globalmem_devp->sem);
	printk("===== globalmem_release success =====\n");
	return 0;
}

static long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	if (down_interruptible(&globalmem_devp->sem))
		return  -ERESTARTSYS;

	printk("===== globalmem_ioctl cmd is %d =====\n", cmd);
	up(&globalmem_devp->sem);
	return 0;
}

static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t size,
							  loff_t *ppos)
{
	if (down_interruptible(&globalmem_devp->sem))
		return  -ERESTARTSYS;

	printk("===== globalmem_read =====\n");

	up(&globalmem_devp->sem);
	return 0;
}

static ssize_t globalmem_write(struct file *filp, const char __user *buf,
							   size_t size, loff_t *ppos)
{
	if (down_interruptible(&globalmem_devp->sem))
		return  -ERESTARTSYS;

	printk("===== globalmem_write =====\n");

	up(&globalmem_devp->sem);
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
	init_MUTEX(&globalmem_devp->sem);
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