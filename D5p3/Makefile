obj-m := D5p3_div.o D5p3_add.o D5p3_sub.o D5p3_mul.o 

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o div_app div_app.c
	gcc -o add_app add_app.c
	gcc -o sub_app sub_app.c
	gcc -o mul_app mul_app.c
	

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm div_app
	rm add_app
	rm sub_app
	rm mul_app
	
