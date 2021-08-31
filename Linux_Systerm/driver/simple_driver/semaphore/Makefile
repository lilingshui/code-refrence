ifneq (${KERNELRELEASE},)
obj-m += globalmem.o
else
KERN_VER = $(shell uname -r)
KERN_DIR = /lib/modules/$(KERN_VER)/build

all:
	make -C ${KERN_DIR} M=${PWD} modules 
	gcc -o test test.c
.PHONY:clean
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm test
endif
