##################################################
#
#  Makefile
#
#  email: pengshuiming@wasion.com
#
#  Copyright(c) 2016 wasion
#  All rights reserved.
#
##################################################
DEMO = Demoserial
LIB = libserialcom.a
CC = arm-linux-g++
AR = arm-linux-ar
SOURCES = ./src/serial.cpp
OBJS = $(SOURCES:%.cpp=%.o)

DEMO_SOURCE = ./demo.cpp
DEMO_OBJS = $(DEMO_SOURCE:%.cpp=%.o)
LDFLAGS = -L ../../../bin/lib/ -llog
DEMO_LDFLAGS = -L ../../../bin/lib/ -L ./ -llog -lserialcom -lutils 

CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -mstructure-size-boundary=8 -Werror
INCLUDE_DIR = -I ./inc -I ../log/inc
LD_RUN_PATH = -Wl,-rpath,./lib

all:$(LIB) $(DEMO)
	@if [ ! -d ../../../bin/lib ]; then \
	mkdir ../../../bin/lib; \
	fi
	
	@mv $(LIB) ../../../bin/lib/
	arm-linux-strip $(DEMO)
	@chmod 755 $(DEMO)
	@mv $(DEMO) ../../../bin
	@echo "$(DEMO) has been compiled successfully!!!"

#form the static library
$(LIB) : $(OBJS)
	$(AR) -cr $@ $(OBJS)

$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(DEMO_OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(DEMO):$(DEMO_OBJS)
	$(CC) -o $@ $(DEMO_OBJS) $(DEMO_LDFLAGS)

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f *.o *.a
	@rm -f ../../../bin/lib/$(LIB)
	@rm -f ../../../bin/$(DEMO)
