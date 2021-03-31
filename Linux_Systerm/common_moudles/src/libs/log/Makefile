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
DEMO = Demolog
LIBSO = liblog.so
LIB = liblog.a
SOURCES = ./src/log.cpp
OBJS = $(SOURCES:%.cpp=%.o)
LD_FLAGS = -L ../../../bin/lib/ -llog -lutils

DEMO_SOURCE = ./demo.cpp
DEMO_OBJS = $(DEMO_SOURCE:%.cpp=%.o)
LDFLAGS = -L ./ -llog -L ../../../bin/lib/ -lutils
LD_RUN_PATH = -Wl,-rpath,./lib

CC = arm-linux-g++
AR = arm-linux-ar
CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -mstructure-size-boundary=8 -Werror
INCLUDE_DIR = -I ./inc -I ../utils/inc

all:$(LIB) $(DEMO)
	@if [ ! -d ../../../bin/lib ]; then \
	mkdir ../../../bin/lib; \
	fi

	arm-linux-strip $(DEMO)
	@chmod 755 $(DEMO)
	@mv $(DEMO) ../../../bin
	@mv $(LIB) ../../../bin/lib/
	@echo "$(DEMO) has been compiled successfully!!!"

#form the static library
$(LIB) : $(OBJS)
	$(AR) -cr $@ $(OBJS)

$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(DEMO_OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(DEMO):$(DEMO_OBJS)
	$(CC) -o $@ $(DEMO_OBJS) $(LDFLAGS)

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ../../../bin/lib/$(LIBSO)
	@rm -f ../../../bin/lib/$(LIB)
	@rm -f ../../../bin/$(DEMO)