PROGRAMS = WS_SNTP

CC = arm-linux-g++
MAKEDATE = $(shell date +%G-%m-%d)
HADT_VERSION = HardAssistedDetectionTool-v2.0

BUILD_DEMO = N
export BUILD_DEMO

TOPDIR=$(PWD)
export TOPDIR

all:$(PROGRAMS)
	@echo "All programs and library are in bin"
	@echo "Compile finished!"

WS_SNTP:
	mkdir -p ./bin/lib;
	@(cp -rf ./conf ./bin/;)
	@(cd ./libs/utils;	$(MAKE))
	@(cd ./libs/libsntp;	$(MAKE))
	@(cd ./libs/libxml2;	./build.sh all)
	@(cd ./libs/xmlutil;	CROSS_COMPILE=arm-linux- prefix=$(TOPDIR)/output/usr DESTDIR=$(TOPDIR)/bin/lib make all)
	@(cd ./app;		$(MAKE))
clean:
	@(cd ./libs/utils;	make clean)
	@(cd ./libs/libsntp;	make clean)
	@(cd ./libs/libxml2;	./build.sh clean)
	@(cd ./libs/xmlutil;	CROSS_COMPILE=arm-linux- prefix=$(TOPDIR)/output/usr DESTDIR=$(TOPDIR)/bin make distclean)
	@(cd ./app;		make clean)
	@rm -rf ./bin
	@rm -rf ./output