.SUFFIXES : .x .o .c .s

CC=arm-linux-gcc -O3 -static
TARGET = nuc970ImgMaker
LIBS=-lm
SRCS :=  main.c bch_encoder_verify.c ProcessOptionalIni.c info_elnec.c

all: 
	$(CC) $(WEC_LDFLAGS) $(SRCS) -o $(TARGET) $(LIBS)
	arm-linux-strip $(TARGET)

clean:
	rm -f *.o 
	rm -f *.x 
	rm -f *.flat
	rm -f *.map
	rm -f temp
	rm -f *.img
	rm -f $(TARGET)
	rm -f *.gdb
