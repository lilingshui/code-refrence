export CROSS_COMPILE=
export CC=${CROSS_COMPILE}gcc
export CXX=${CROSS_COMPILE}g++
export LD=${CROSS_COMPILE}ld
export AR=${CROSS_COMPILE}ar
export RANLIB=${CROSS_COMPILE}ranlib
export STRIP=${CROSS_COMPILE}strip

LDFLAGS = -lmosquitto

SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:%.cpp=%.o)


all: mqtt_pub mqtt_sub


mqtt_pub: mqtt_pub.o
	$(CXX) -o $@ mqtt_pub.o $(LDFLAGS)


mqtt_sub: mqtt_sub.o
	$(CXX) -o $@ mqtt_sub.o $(LDFLAGS)


$(OBJS): %.o : %.cpp
	$(CXX) -c $< -o $@

clean:
	@rm -f *.o *~ mqtt_pub mqtt_sub

