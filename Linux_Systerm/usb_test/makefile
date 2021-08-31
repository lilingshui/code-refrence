#Simple makefile for libusb application
# this is a proper pound sign! jolly good!

CC=arm-linux-gcc

GCCFLAGS = -Wall -I ./include -L ./lib -lusb-1.0
USB_Linux_HSET : USB_Linux_HSET.c
	$(CC) $(GCCFLAGS) -o $@ $?	
clean :
	-rm *.o $(objects) USB_Linux_HSET
