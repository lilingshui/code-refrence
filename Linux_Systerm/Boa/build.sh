#!/bin/sh

TOP_DIR=`pwd`

#编译BOA
cd $TOP_DIR/boa-0.94.13/src
make
arm-linux-strip boa

#部署输出文件
cp $TOP_DIR/boa-0.94.13/src/boa $TOP_DIR/output
cp $TOP_DIR/boa-0.94.13/boa.conf $TOP_DIR/output
cp $TOP_DIR/boa-0.94.13/mime.types $TOP_DIR/output
cp -rf $TOP_DIR/www $TOP_DIR/output

#编译CGI程序
cd $TOP_DIR/cgi
make

cd $TOP_DIR
echo "===== build success ====="