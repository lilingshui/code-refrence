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
LIBSO = libutils.so

SOURCES = ./src/utils.cpp
OBJS = $(SOURCES:%.cpp=%.o)

DEMO_SOURCE = ./demo.cpp
DEMO_OBJS = $(DEMO_SOURCE:%.cpp=%.o)
DEMO_LDFLAGS = -L ./ -lutils
LD_RUN_PATH = -Wl,-rpath,./lib

CC = arm-linux-g++
CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -mstructure-size-boundary=8 -Werror
INCLUDE_DIR = -I ./inc -I ../log/inc -I ../../include

ifeq ($(BUILD_DEMO), Y)
all:$(LIBSO) $(DEMO)
	arm-linux-strip $(LIBSO)
	@chmod 755 $(LIBSO)
	@if [ ! -d $(TOPDIR)/bin/lib ]; then \
	mkdir $(TOPDIR)/bin/lib; \
	fi
	@mv $(LIBSO) $(TOPDIR)/bin/lib/
	@echo "$(LIBSO) has been compiled successfully!!!"

	arm-linux-strip $(DEMO)
	@chmod 755 $(DEMO)
	@mv $(DEMO) $(TOPDIR)/bin
	@echo "$(DEMO) has been compiled successfully!!!"

$(LIBSO):$(OBJS)
	$(CC) -shared -o $@ $(OBJS)

$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(DEMO_OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(DEMO):$(DEMO_OBJS)
	$(CC) -o $@ $(DEMO_OBJS) $(DEMO_LDFLAGS) $(LD_RUN_PATH)

else
all:$(LIBSO)
	arm-linux-strip $(LIBSO)
	@chmod 755 $(LIBSO)
	@if [ ! -d $(TOPDIR)/bin/lib ]; then \
	mkdir $(TOPDIR)/bin/lib; \
	fi
	@mv $(LIBSO) $(TOPDIR)/bin/lib/
	@echo "$(LIBSO) has been compiled successfully!!!"

$(LIBSO):$(OBJS)
	$(CC) -shared -o $@ $(OBJS)

$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

endif

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f $(TOPDIR)/bin/lib/$(LIBSO)
	@rm -f $(TOPDIR)/bin/$(DEMO)
