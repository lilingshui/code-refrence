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
DEMO = DemoUtils
LIB = libutils.a
SOURCES = ./src/utils.cpp
OBJS = $(SOURCES:%.cpp=%.o)

DEMO_SOURCE = ./demo.cpp
DEMO_OBJS = $(DEMO_SOURCE:%.cpp=%.o)
DEMO_LDFLAGS = -L ./ -lutils
LD_RUN_PATH = -Wl,-rpath,./lib

CC = arm-linux-g++
AR = arm-linux-ar
CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -mstructure-size-boundary=8 -Werror 
INCLUDE_DIR = -I ./inc -I ../log/inc -I ../../include

all:$(LIB) $(DEMO)
	#arm-linux-strip $(LIB)
	@chmod 755 $(LIB)
	@if [ ! -d ../../../bin/lib ]; then \
	mkdir ../../../bin/lib; \
	fi
	@mv $(LIB) ../../../bin/lib/
	@echo "$(LIB) has been compiled successfully!!!"

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
	@rm -f ../../../bin/lib/$(LIB)
	@rm -f ../../../bin/$(DEMO)
