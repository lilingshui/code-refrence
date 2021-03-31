CC = arm-linux-gcc
GCCFLAGS = -Wall -Werror \
					 -I ../include \
					 -I ./../libs/result/inc  \
					 -I ./../libs/utils/inc  \
					 -L ../../bin/ \
					 -L ../../bin/lib/ \
					 -lutils -llog \
					 -Wl,-rpath,./lib

APPLICATION = application
all:$(APPLICATION)

application:
	(cd 485;	$(MAKE))

clean:
	(cd 485;	make clean)
