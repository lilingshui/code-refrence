#!/bin/bash
# Auto Build for wifi application.
#
# Author: Peng Shuiming
# Date:　2018.05.18
#

TOP=`pwd`
DEST=${TOP}/output

#build libnl
cd ${TOP}/libnl-3.2.25
./configure CC=arm-linux-gcc --prefix=${DEST}/libnl --host=arm-linux
make
make install

#build openssl
cd ${TOP}/openssl-1.0.2
./config no-sse2 no-asm shared -fPIC --prefix=${DEST}/openssl
sed -i "s@CC= gcc@CC=arm-linux-gcc@g" Makefile
sed -i "s/-m64//g" Makefile
make
make install

#build hostapd
cd ${TOP}/hostapd-2.4/hostapd
make
cp hostapd ${DEST}/

#build udhcpd
cd ${TOP}/udhcp-0.9.8
make
cp udhcpc ${DEST}/
cp udhcpd ${DEST}/

#build wpa_supplicant-2.6
cd ${TOP}/wpa_supplicant-2.6/wpa_supplicant
make
cp wpa_cli ${DEST}/
cp wpa_passphrase ${DEST}/
cp wpa_supplicant ${DEST}/

#build wireless_tools.30.rtl
cd ${TOP}/wireless_tools.30.rtl
make
mv ifrename ${DEST}/
mv iwconfig ${DEST}/
mv iwevent ${DEST}/
mv iwgetid ${DEST}/
mv iwlist ${DEST}/
mv iwpriv ${DEST}/
mv iwspy ${DEST}/

cd ${TOP}/zlib-1.2.11
./configure --prefix=${DEST}/zlib
make
make install

cd ${TOP}/net-tools-1.60
make
make install

cd ${TOP}/openssh-8.0p1
./configure --prefix=${DEST}/openssh --host=arm-linux --with-libs --with-zlib=${TOP}/zlib-1.2.11 --with-ssl-dir=${TOP}/openssl-1.0.2 --disable-etc-default-login CC=arm-linux-gcc AR=arm-linux-ar
make
 
