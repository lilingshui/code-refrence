#!/bin/sh

TARGET_DIR=$(cd `dirname $0`; pwd)/../output
./configure CC=arm-linux-gcc --host=arm-linux --prefix=$TARGET_DIR --enable-libusb LIBUSB_LIBS="-L$TARGET_DIR/lib -lusb-1.0" LIBUSB_CFLAGS="-I $TARGET_DIR/include/libusb-1.0" PCSC_LIBS="-L$TARGET_DIR/lib -lpcsclite" PCSC_CFLAGS="-I $TARGET_DIR/include/PCSC" --enable-usbdropdir=$TARGET_DIR/lib/pcsc/driver

make
make install

