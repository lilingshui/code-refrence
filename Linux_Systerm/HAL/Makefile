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

PROGRAMS = HAL_MODULES
export CROSS_COMPILE=
export CC=${CROSS_COMPILE}gcc
export CXX=${CROSS_COMPILE}g++
export LD=${CROSS_COMPILE}ld
export AR=${CROSS_COMPILE}ar
export RANLIB=${CROSS_COMPILE}ranlib
export STRIP=${CROSS_COMPILE}strip

TOPDIR=$(PWD)
export TOPDIR

all:$(PROGRAMS)
	@echo "All programs and library are in bin"
	@echo "Compile finished!"

HAL_MODULES:
	mkdir -p ./bin
	@(cd src/libs/hal;	$(MAKE))
	@(cd src/libs/hal_led;	$(MAKE))
	@(cd src/bins;		$(MAKE))

clean:
	(cd src/libs/hal;	make clean)
	(cd src/libs/hal_led;	make clean)
	(cd src/bins/;		make clean)
	@rm -rf bin
	@rm -rf output/*

