##################################################
#
#  Makefile
#
#  email: pengshuiming@wasion.com
#
#  Copyright(c) 2017 wasion
#  All rights reserved.
#
##################################################
PROGRAM = helloworld.cgi
CC= arm-linux-gcc

SOURCES = $(wildcard *.c)
OBJS = $(SOURCES:%.c=%.o)

CFLAGS = -Wall -Werror -Os -DARM_LINUX -D_REENTRANT $(INCLUDE) -mstructure-size-boundary=8

all: $(PROGRAM)
	arm-linux-strip $(PROGRAM)
	@chmod 755 $(PROGRAM)
	@mv $(PROGRAM) ../../output
	@echo "$(PROGRAM) has been compiled successfully!!!"

$(PROGRAM):$(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ../../../output/$(PROGRAM)