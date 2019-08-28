##################################################
#
#  Makefile
#
#  email: pengshuiming@wasion.com
#
#  Copyright(c) 2019 wasion
#  All rights reserved.
#
##################################################

LDFLAGS = -pthread
SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)
CPPFLAGS = -Wall -std=c++0x

$(warning "the value of OBJS is$(OBJS)")

all: client server
	$(STRIP) client
	$(STRIP) server
	@chmod 755 client
	@chmod 755 server
	@mv client ../bin
	@mv server ../bin
	@echo "client server has been compiled successfully!!!"

client: ./src/client.o
	$(warning "===== the value of OBJS 1 =====")
	$(CXX) -o $@ ./src/client.o $(LDFLAGS)

server: ./src/server.o
	$(warning "===== the value of OBJS 2 =====")
	$(CXX) -o $@ ./src/server.o $(LDFLAGS)

$(OBJS): %.o : %.cpp
	$(warning "===== the value of OBJS 3 =====")
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ../../bin/$(PROGRAM)

