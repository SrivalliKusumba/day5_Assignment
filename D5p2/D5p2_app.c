#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

struct test 
{
	int a;
	int b;
	char c;
};

int main()
{
	struct test p;
	int fd;
	int x,y,num;
	int32_t value,oper;

	fd = open("/dev/mychar",O_RDWR,0777);
	if(fd<0)
	{
		printf("Error opening file\n");
		exit(1);
	}

	printf("choice\n");
	printf("'+' for addition\t '-' for subtraction\t '*' for multiplication\t '/' for division\n");

	scanf("%c",&p.c);


	ioctl(fd, WR_VALUE, (int32_t*) &p.c);

        printf("enter first value");
	scanf("%d",&p.a);
	printf("\n enter second value");
	scanf("%d",&p.b);


	ioctl(fd, WR_VALUE, (int32_t*) &p.a);
	ioctl(fd, WR_VALUE, (int32_t*) &p.b);

	//Read value from driver
	
	ioctl(fd, RD_VALUE, (int32_t*)&value);

	printf("value is %d\n",value);

	close(fd);
}


