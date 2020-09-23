#!/bin/sh

TARGET_DIR=$(cd `dirname $0`; pwd)/../output
./configure CC=arm-linux-gcc --host=arm-linux --prefix=$TARGET_DIR PCSC_LIBS="-L$TARGET_DIR/lib -lpcsclite" PCSC_CFLAGS="-I $TARGET_DIR/include/PCSC"

make
make install
