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
DEMO = Demoproparse
LIB = libproparse.a
SOURCES = ./src/proparse.cpp
OBJS = $(SOURCES:%.cpp=%.o)

DEMO_SOURCE = ./demo.cpp
DEMO_OBJS = $(DEMO_SOURCE:%.cpp=%.o)
DEMO_LDFLAGS = -L ../../../bin/lib/ -L ./ -lproparse -llog -lutils  
LD_RUN_PATH = -Wl,-rpath,../../../bin/lib:./lib

CC = arm-linux-g++
AR = arm-linux-ar
CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -mstructure-size-boundary=8 -Werror
INCLUDE_DIR = -I ./inc -I ../log/inc
LDFLAGS = -L ../../../bin/lib/ -llog

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

$(DEMO):$(DEMO_OBJS)
	$(CC) -o $@ $(DEMO_OBJS) $(DEMO_LDFLAGS)

$(DEMO_OBJS): %.o : %.cpp
	$(CC)  $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	@rm -f src/*.o src/*~
	@rm -f *.o *.a
	@rm -f ../../../bin/lib/$(LIB)
	@rm -f ../../../bin/$(DEMO)
