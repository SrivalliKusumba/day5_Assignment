#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)


int main()
{
	int fd;
	int num;
	int32_t x,y,value,oper,c;

	fd = open("/dev/mychar",O_RDWR,0777);
	if(fd<0)
	{
		printf("Error opening file\n");
		exit(1);
	}

	printf("choice\n");
	printf("1. Add\t 2.Subtract\t 3.Multilication\t 4.Division\n");

	scanf("%d",&num);	



	if(num > 4 && num <1)
	{
		printf("Enter correct choice ");
		return 0;
	}

	ioctl(fd, WR_VALUE, (int32_t*) &num);

	printf("enter first value\n");
	scanf("%d",&x);

	printf("Enter second value\n");
	scanf("%d",&y);

	ioctl(fd, WR_VALUE, (int32_t*) &x);
	ioctl(fd, WR_VALUE, (int32_t*) &y);

	//Read value from driver
	
	ioctl(fd, RD_VALUE, (int32_t*)&value);

	printf("value is %d\n",value);

	close(fd);
}


