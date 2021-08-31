#Simple makefile for libusb application
# this is a proper pound sign! jolly good!

CC=arm-linux-gcc

GCCFLAGS = -Wall
mdio : mdio.c
	$(CC) $(GCCFLAGS) -o $@ $?	
clean :
	-rm *.o $(objects) mdio
