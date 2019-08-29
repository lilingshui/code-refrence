ifneq (${KERNELRELEASE},)
obj-m := hello.o
$(warning "====== the value of LOCAL_PATH is 1 KERNELRELEASE is ${KERNELRELEASE} ======")
else
$(warning "====== the value of LOCAL_PATH is 2 KERNELRELEASE is ${KERNELRELEASE} ======")
KDIR := /home/psm/work/wslinux-kernel-v2/source/linux
all:
	make -C ${KDIR} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-
.PHONY:clean
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers modul*
endif
