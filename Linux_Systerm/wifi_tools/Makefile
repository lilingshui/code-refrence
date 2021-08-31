# Auto Build for wifi application.
#
# Author: Peng Shuiming
# Date:¡¡2018.05.18
#
PROGRAMS = wifi_application
TOPDIR=$(PWD)

all:$(PROGRAMS)
	@echo "Compile finished!"

wifi_application:
	mkdir -p ./output
	@(cd $(TOPDIR);	./build.sh)
	#@(cd src/libs/libxml2;	./build.sh all)
clean:
	(cd ./libnl-3.2.25; make clean)
	(cd ./openssl-1.0.2; make dclean; make clean)
	(cd ./hostapd-2.4/hostapd; make clean)
	(cd ./wpa_supplicant-2.6/wpa_supplicant; make clean)
	(cd ./wireless_tools.30.rtl; make clean)
	(cd ./net-tools-1.60; make dist; make clean)
	(cd ./zlib-1.2.11; make distclean)
	(cd ./openssh-8.0p1; make clean)
	@rm -rf output/*
