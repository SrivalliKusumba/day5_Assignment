#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>

#define Write_Add _IOW('a','a',int32_t*)
#define Read_Add _IOR('a','b',int32_t*)

int32_t a = 0;
int32_t b = 0;
int32_t value = 0;
int32_t oper = 0;


dev_t mydev;
int AddDev_open(struct inode *inode,struct file *flip);
int AddDev_release(struct inode *inode,struct file *flip);
static long AddDev_ioctl(struct file *flip, unsigned int cmd, unsigned long arg);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = AddDev_open,
	.release = AddDev_release,
	.unlocked_ioctl = AddDev_ioctl,
};

struct cdev *my_cdev;

static int add_init(void)
{
	int r;
	int MAJOR,MINOR;
	r = alloc_chrdev_region(&mydev,0,1,"AddDev");
	if(r<0)
	{
		printk("region requested in not available\n");
		return -1;
	}

	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Minor number %d\n",MAJOR,MINOR);
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	r = cdev_add(my_cdev,mydev,1);
	if(r<0)
	{
		printk("Device not created\n");
		return -1;
	}
	return 0;
}

static void __exit add_exit(void)
{
	int MAJOR,MINOR;

	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Minor number %d\n",MAJOR,MINOR);
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("Unregister\n");
}

int AddDev_open(struct inode *inode,struct file *flip)
{
	printk("In AddDev open system call\n");
	return 0;
}

int AddDev_release(struct inode *inode,struct file *flip)
{
	printk("In AddDev release system call\n");
	return 0;
}

static long AddDev_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	static int count = 0;

	switch(cmd)
	{
		case Write_Add:
			       if(count == 1)
				{
					copy_from_user(&a, (int32_t*)arg, sizeof(a));
					printk("a = %d\n",a);
					break;
				}
				else if(count == 2)
				{
					copy_from_user(&b, (int32_t*)arg, sizeof(b));
					printk("b = %d\n",b);
			                break;
				}

			

		case Read_Add:
			{
				value = a+b;
		                copy_to_user((int32_t*)arg,&value,sizeof(value));
	               		break;
			}
	}
	count+=1;
if(count ==3)
count = 0;

	return 0;
}


MODULE_LICENSE("GPL");
module_init(add_init);
module_exit(add_exit);
				
