PROGRAMS = COMMON_MODULES

CC = arm-linux-g++
MAKEDATE = $(shell date +%G-%m-%d)
HADT_VERSION = COMMON_MODULES

TOPDIR=$(PWD)
export TOPDIR

all:$(PROGRAMS)
	@echo "All programs and library are in bin"
	@echo "Compile finished!"

COMMON_MODULES:
	mkdir -p ./bin
	@(cd src/libs/utils;	$(MAKE) )
	@(cd src/libs/log;	$(MAKE) )
	@(cd src/libs/serialcom;	$(MAKE) )
	@(cd src/libs/proparse;	$(MAKE) )
	@(cd src/bins;	$(MAKE) )

release:
	tar -zcvf ${HADT_VERSION}_$(MAKEDATE).tar.gz ./bin
	@echo "${HADT_VERSION}_$(MAKEDATE).tar.gz create!"
clean:
	(cd src/bins;	make clean )
	(cd src/libs/log;	make clean )
	(cd src/libs/utils;	make clean )
	(cd src/libs/serialcom;	make clean )
	(cd src/libs/proparse;	make clean )
	@rm -rf bin
	@rm -rf output/*
	@rm -f COMMON_MODULES*.tar.gz
