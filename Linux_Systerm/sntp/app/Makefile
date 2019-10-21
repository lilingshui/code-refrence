##################################################
#
#  Makefile
#
#  email: pengshuiming@wasion.com
#
#  Copyright(c) 2018 wasion
#  All rights reserved.
#
##################################################
PROGRAM = sntp
CC= arm-linux-g++

SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)

DEFS = -D_REENTRANT -DTEST=\"SNTP\"
CPPFLAGS = -Wall -Werror -Os -DARM_LINUX -D_REENTRANT -mstructure-size-boundary=8 $(DEFS)
INCLUDE_DIR = -I ./inc -I $(TOPDIR)/output/usr/include -I ../libs/utils/inc -I ../libs/xmlutil -I ../libs/libsntp/inc

LDFLAGS = -L ../bin/lib/ -lutils -lxmlutil -lsntp -lxml2 -lpthread
LD_RUN_PATH = -Wl,-rpath,./lib

all: $(PROGRAM)

$(PROGRAM):$(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LD_RUN_PATH) 
	arm-linux-strip $(PROGRAM)
	@chmod 755 $(PROGRAM)
	@mv $(PROGRAM) ../bin
	@echo "$(PROGRAM) has been compiled successfully!!!"

$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	rm -f src/*.o src/*~ *.o
	rm -f ../bin/$(PROGRAM)
	