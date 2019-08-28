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

LDFLAGS = -lssl -lcrypto
SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)
CPPFLAGS = -Wall

$(warning "the value of OBJS is$(OBJS)")

all: sslclient sslserver
	$(STRIP) sslclient
	$(STRIP) sslserver
	@chmod 755 sslclient
	@chmod 755 sslserver
	@mv sslclient ../bin
	@mv sslserver ../bin
	@echo "sslclient sslserver has been compiled successfully!!!"

sslclient: ./src/sslclient.o
	$(warning "===== the value of OBJS 1 =====")
	$(CXX) -o $@ ./src/sslclient.o $(LDFLAGS)

sslserver: ./src/sslserver.o
	$(warning "===== the value of OBJS 2 =====")
	$(CXX) -o $@ ./src/sslserver.o $(LDFLAGS)

$(OBJS): %.o : %.cpp
	$(warning "===== the value of OBJS 3 =====")
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ../../bin/$(PROGRAM)


