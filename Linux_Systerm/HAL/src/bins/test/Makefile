##################################################
#
#  Makefile
#
#  email: lilingshui@126.com
#
#  Copyright(c) 2019 wasion
#  All rights reserved.
#
##################################################
PROGRAM = test

SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)

DEFS = -D_REENTRANT -DTEST=\"TEST_485\"
CPPFLAGS = -Wall -g -Os -fPIC -D_REENTRANT -Wno-unknown-pragmas -Wno-format -Werror $(DEFS)

INCLUDE_DIR = -I ./inc -I ../../include -I ../../libs/hal_led/inc -I ../../libs/hal/inc
LDFLAGS = -L ../../../bin/lib/ -lpthread -lhal

LD_RUN_PATH = -Wl,-rpath,./lib

all: $(PROGRAM)

$(PROGRAM):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LD_RUN_PATH)
	$(STRIP) $(PROGRAM)
	@chmod 755 $(PROGRAM)
	@mv $(PROGRAM) ../../../bin
	@echo "$(PROGRAM) has been compiled successfully!!!"
	
$(OBJS): %.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ../../../bin/$(PROGRAM)
