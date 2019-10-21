#!/bin/sh

#添加这个PS命令的编译的目的是，我们自己做的根文件系统使用的是busybox
#busybox带的这个PS命令比较简单，得到的进程信息较少，在分析问题时信息不充分
#此代码是ps的源代码，编译之后可以直接将PS程序放入根文件系统中去使用，免得以后再满世界去找，节省时间和精力

CROSS_COMPILE=arm-linux-
ARCH=arm
TARGET_DIR=$(cd `dirname $0`; pwd)/output

build_procps() {

    echo "ac_cv_func_realloc_0_nonnull=yes" > arm-linux.cache
    echo "ac_cv_func_malloc_0_nonnull=yes" >> arm-linux.cache
    ./configure --host=$ARCH-linux --prefix=$TARGET_DIR \
        --enable-static \
        --disable-shared \
        --without-ncurses \
        --cache-file=arm-linux.cache \
        CC=$CROSS_COMPILE\gcc \
        STRIP=$CROSS_COMPILE\strip \
        RANLIB=$CROSS_COMPILE\ranlib \
        OBJDUMP=$CROSS_COMPILE\objdump \
        NM=$CROSS_COMPILE\nm \
        LD=$CROSS_COMPILE\ld \
        AR=$CROSS_COMPILE\ar \
        AS=$CROSS_COMPILE\as ;

    make ; make install || exit 1
    #make || exit 1
    cd -
}

build_procps

