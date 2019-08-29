ifneq (${KERNELRELEASE},)
obj-m += globalfifo_async.o
else
KDIR := /home/psm/work/wslinux-kernel-v2/source/linux
all:
	make -C ${KDIR} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-
.PHONY:clean
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers modul*
endif
