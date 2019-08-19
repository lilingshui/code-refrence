PROGRAMS = OPENSSL_TEST

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
	@openssl req -newkey rsa:2048 -nodes -keyout serverKey.pem -x509 -days 365 -out serverCert.cer -subj "/C=CN/ST=GD/L=GZ/O=abc/OU=defg/CN=hijk/emailAddress=132456.com"
	@mv serverKey.pem serverCert.cer ./bin
	@echo "All programs and library are in bin"
	@echo "Compile finished!"

$(PROGRAMS):
	mkdir -p ./bin
	@(cd src;	$(MAKE) )

clean:
	(cd src;	make clean)
	@rm -rf bin
	@rm -rf output/*
