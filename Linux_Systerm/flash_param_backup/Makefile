PROGRAMS = WS_FLASH_PARAM
MAKEDATE = $(shell date +%G-%m-%d)
HADT_VERSION = flash_param_backup-v1.0

TOPDIR=$(PWD)
export TOPDIR

HOST = 
export HOST

all:$(PROGRAMS)
	@echo "All programs and library are in bin"
	@echo "Compile finished!"

WS_FLASH_PARAM:
	mkdir -p ./bin/lib;
	@(cd ./libs/param;	$(MAKE))
	@(cd ./app;		$(MAKE))
clean:
	@(cd ./libs/param;	make clean)
	@(cd ./app;		make clean)
	@rm -rf ./bin
	@rm -rf ./output