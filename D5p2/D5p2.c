#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int32_t a = 0;
int32_t b = 0;
int32_t value = 0;
char oper;

dev_t mydev;
int mychar_open(struct inode *inode,struct file *flip);
int mychar_release(struct inode *inode,struct file *flip);
ssize_t mychar_write(struct file *flip, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp);
static long mychar_ioctl(struct file * flip, unsigned int cmd, unsigned long arg);


struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mychar_open,
	.read = mychar_read,
	.write = mychar_write,
	.release = mychar_release,
	.unlocked_ioctl = mychar_ioctl,
};

struct cdev *my_cdev;

static int __init char_init(void)
{
	int r;
	int MAJOR,MINOR;
	r = alloc_chrdev_region(&mydev,0,1,"mychar");
	if(r<0)
	{
		printk("region requested is not available\n");
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

static void __exit char_exit(void)
{
	int MAJOR,MINOR;

	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t minor number %d\n");
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("Unregister\n");
}

int mychar_open(struct inode *inode, struct file *flip)
{
	printk("In open system call\n");
	return 0;
}

int mychar_release(struct inode *inode, struct file *flip)
{
	printk("In release system call\n");
	return 0;
}

ssize_t mychar_write(struct file *flip, const char __user *Ubuff, size_t count, loff_t *offp)
{
	char kbuff[100];
	unsigned long r;
	ssize_t ret;

	r = copy_from_user((char *)kbuff, (char *)Ubuff,count);
	if(r==0)
	{
		printk("User message %s\n",kbuff);
		ret=count;
		return ret;
	}
	else
	{	
		printk("Error\n");
		ret = -EFAULT;
		return ret;
	}

}

ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp)
{
	char kbuff[] = "Kernel to user";
	unsigned long r;
	ssize_t ret;

	r = copy_to_user((char *)Ubuff, (char *)kbuff, sizeof(kbuff));
	if(r==0)
	{
		printk("read data successfully\n");
		ret = count;
		return ret;
	}
	else
	{
		printk("Error\n");
		ret = -EFAULT;
		return ret;
	}
}

static long mychar_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	static int count = 0;

 switch(cmd)
 {
	 case WR_VALUE:
		 {
			 if(count == 0)
			 {
				 copy_from_user(&oper, (int32_t*)arg, sizeof(oper));
				 printk("oper = %d\n",oper);
				 break;
			 }
			 else if(count == 1)
			 {
				 copy_from_user(&a, (int32_t*)arg, sizeof(a));
				 printk("integer1 = %d\n",a);
				 break;
			 }
			 else if(count == 2)
			 {
				 copy_from_user(&b, (int32_t*)arg, sizeof(b));
				 printk("integer = %d\n",b);
				 break;
			 }
		 }

	 case RD_VALUE:
		 {
	 	if(oper == '+')
			value = a + b;
		else if(oper == '-')
			value = a-b;
		else if(oper == '*')
			value = a*b;
		else if(oper == '/')
			value = a/b;
		else
			break;
		copy_to_user((int32_t*) arg, &value,sizeof(value));
		break;
		 }
 }

 	count+=1;
 	if(count == 3)
        count = 0;

 return 0;

}

MODULE_LICENSE("GPL");
module_init(char_init);
module_exit(char_exit);



