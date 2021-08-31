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
PROGRAM = rs485_test
CC= arm-linux-g++

SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)

DEFS = -D_REENTRANT -DTEST=\"TEST_485\"
CPPFLAGS = -Wall -g -Os -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -mstructure-size-boundary=8 -Werror $(DEFS)

INCLUDE_DIR = -I ./inc -I ../../include -I ../../libs/log/inc -I ../../libs/serialcom/inc \
			-I ../../libs/proparse/inc -I ../../libs/utils/inc
LDFLAGS = -L ../../../bin/lib/ -lpthread -llog -lserialcom -lproparse -lutils

LD_RUN_PATH = -Wl,-rpath,./lib

all: $(PROGRAM)

$(PROGRAM):$(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	arm-linux-strip $(PROGRAM)
	@chmod 755 $(PROGRAM)
	@mv $(PROGRAM) ../../../bin
	@echo "$(PROGRAM) has been compiled successfully!!!"
	
$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ../../../bin/$(PROGRAM)