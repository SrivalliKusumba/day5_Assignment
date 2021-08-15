#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define Write_Div _IOW('a','a',int32_t*)
#define Read_Div _IOR('a','b',int32_t*)


int main()
{
	int fd;
	int32_t x,y,value;

	fd = open("/dev/DivDev",O_RDWR,0777);
	if(fd<0)
	{
		printf("Error opening file\n");
		exit(1);
	}

	printf("enter first value\n");
	scanf("%d",&x);
	printf("enter second value\n");
	scanf("%d",&y);

	ioctl(fd, Write_Div, (int32_t*)&x);
	ioctl(fd, Write_Div, (int32_t*)&y);

	ioctl(fd, Read_Div, (int32_t*)&value);

	
	printf("Addition result is %d\n",value);

	close(fd);

	return 0;
}


