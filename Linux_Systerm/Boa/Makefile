# Auto Build for boa application.
#
# Author: Peng Shuiming
# Date: 2018.05.18
#

PROGRAMS = boa
TOPDIR=$(PWD)

all:$(PROGRAMS)
	@echo "===== Compile finished! ====="
boa:
	mkdir -p ./output
	#清除上次的输出结果
	rm output/* -rf
	@(cd $(TOPDIR); ./build.sh)

clean:
	(cd ./boa-0.94.13/src;     make clean)
	(cd ./cgi;    make clean)
	@rm -rf output/*
