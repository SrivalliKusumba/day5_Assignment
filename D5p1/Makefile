obj-m :=D5p1.o

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o D5p1_app D5p1_app.c

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm D5p1_app
