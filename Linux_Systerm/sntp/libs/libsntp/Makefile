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

LIBSO = libsntp.so
SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)

CC = arm-linux-g++
CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -mstructure-size-boundary=8 -Werror
INCLUDE_DIR = -I ./inc -I ../log/inc -I ../../include

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

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f $(TOPDIR)/bin/lib/$(LIBSO)
