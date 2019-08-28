##################################################
#
#  Makefile
#
#  email: lilingshui@126.com
#
#  Copyright(c) 2019 lilingshui
#  All rights reserved.
#
##################################################
LIBSO = libhal.so
SOURCES = ./src/hal.cpp
OBJS = $(SOURCES:%.cpp=%.o)

LDFLAGS = -ldl

CPPFLAGS = -Wall -g -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format
INCLUDE_DIR = -I ./inc -I ../../include -I ../hal_led/inc
LD_RUN_PATH = -Wl,-rpath,./lib

all:$(LIBSO)
	$(STRIP) $(LIBSO)
	@chmod 755 $(LIBSO)
	@if [ ! -d ../../../bin/lib ]; then \
	mkdir ../../../bin/lib; \
	fi
	@mv $(LIBSO) ../../../bin/lib/
	@echo "$(LIBSO) has been compiled successfully!!!"

$(LIBSO):$(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): %.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)


clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ../../../bin/lib/$(LIBSO)

