#!/bin/sh

#添加这个库的编译的目的是，因为我们会在不同的平台切换，这个库需要经常的编译
#应用程序这边经常需要平台组提供这个库，所以在此进行记录，免得下次要的时候又
#去网上下载，编译的时候还要花一段时间，节约时间和精力

./configure CC=arm-linux-gnueabihf-gcc --prefix=`pwd`/output --host=arm-linux
make
make install
