##################################################
#
#  Makefile
#
#  email: pengshuiming@wasion.com
#
#  Copyright(c) 2021 wasion
#  All rights reserved.
#
##################################################
PROGRAM = flash_param
CC= $(HOST)g++

SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)

DEFS = -D_REENTRANT -DTEST=\"SNTP\"
CPPFLAGS = -Wall -Werror -Os -DARM_LINUX -D_REENTRANT $(DEFS)
INCLUDE_DIR = -I ../libs/param/inc

LDFLAGS = -L ../bin/lib/ -lparam
LD_RUN_PATH = -Wl,-rpath,./lib

all: $(PROGRAM)

$(PROGRAM):$(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LD_RUN_PATH) 
	$(HOST)strip $(PROGRAM)
	@chmod 755 $(PROGRAM)
	@mv $(PROGRAM) ../bin
	@echo "$(PROGRAM) has been compiled successfully!!!"

$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	rm -f src/*.o src/*~ *.o
	rm -f ../bin/$(PROGRAM)
	