PROGRAM = upgrademsg
CC= arm-linux-g++

SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:%.cpp=%.o)

CPPFLAGS = -Wall -O2 -DARM_LINUX -D_REENTRANT  -mstructure-size-boundary=8
INCLUDE_DIR = -I ./inc
LDFLAGS = -lpthread

all: $(PROGRAM)
	@arm-linux-strip $(PROGRAM)
	@chmod 755 $(PROGRAM)
	@mkdir -p bin
	@mv $(PROGRAM) ./bin

$(PROGRAM):$(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	@echo "$(PROGRAM) has been compiled successfully!!!"
	
$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	@rm -f src/*.o src/*~ *.o
	@rm -f ./bin/$(PROGRAM)	
