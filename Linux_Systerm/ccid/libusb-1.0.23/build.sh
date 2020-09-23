#!/bin/sh

TARGET_DIR=$(cd `dirname $0`; pwd)/../output
./configure --host=arm-linux --prefix=$TARGET_DIR --disable-udev CC=arm-linux-gcc CXX=arm-linux-g++
make
make install

