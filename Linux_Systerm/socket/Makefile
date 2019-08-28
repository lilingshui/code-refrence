PROGRAMS = CHAT_TEST

export CROSS_COMPILE=
export CC=${CROSS_COMPILE}gcc
export CXX=${CROSS_COMPILE}g++
export LD=${CROSS_COMPILE}ld
export AR=${CROSS_COMPILE}ar
export RANLIB=${CROSS_COMPILE}ranlib
export STRIP=${CROSS_COMPILE}strip

MAKEDATE = $(shell date +%G-%m-%d)

TOPDIR=$(PWD)
export TOPDIR

all:$(PROGRAMS)
	@echo "All programs and library are in bin"
	@echo "Compile finished!"

$(PROGRAMS):
	mkdir -p ./bin
	@(cd src;       $(MAKE) )

clean:
	(cd src;        make clean)
	@rm -rf bin
	@rm -rf output/*

