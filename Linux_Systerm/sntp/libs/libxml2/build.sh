#!/bin/sh
#
# build script for libxml2
#
# (C) Copyright 2016, Wasion Group
# YuWeifeng <yuweifeng@wasion.com>
#

UTIL_NAME=libxml2
UTIL_VER=2.9.4

UTIL_PATH=$PWD

ZIPCMD="gzip -d -c"

PACKNAME=${UTIL_NAME}-${UTIL_VER}.tar.gz
PACKPATH=${UTIL_PATH}/$PACKNAME

SRCPATH=${UTIL_PATH}/output/${UTIL_NAME}-${UTIL_VER}
USRPATH=${UTIL_PATH}/output/usr
BINPATH=${UTIL_PATH}/output/usr/bin
INCPATH=${UTIL_PATH}/output/usr/include
LIBPATH=${UTIL_PATH}/output/usr/lib
PATCHDIR=${UTIL_PATH}/patchs

OUTPUTDIR=$TOPDIR/output
TARGETDIR=$TOPDIR/bin/lib

SUPPORTDIR=$TOPDIR/support

mk_patch()
{
	echo "$APPNAME Patching"
	cat $PATCHDIR/*.patch | patch -p1 -d $SRCPATH -t -N \
		&& [ $? != 0 ] && { echo "Patch failed!"; exit 1; }

#	echo "$APPNAME Updating config.sub and config.guess"

#	echo "$APPNAME Patching libtool"

}

mk_config()
{
	echo "$APPNAME Configuring"

	rm -rf config.cache
	AR="arm-linux-ar" AS="arm-linux-as" LD="arm-linux-ld" NM="arm-linux-nm" CC="arm-linux-gcc" GCC="arm-linux-gcc" CPP="arm-linux-cpp" CXX="arm-linux-g++" FC="arm-linux-gfortran" F77="arm-linux-gfortran" RANLIB="arm-linux-ranlib" READELF="arm-linux-readelf" STRIP="arm-linux-strip" OBJCOPY="arm-linux-objcopy" OBJDUMP="arm-linux-objdump" AR_FOR_BUILD="/usr/bin/ar" AS_FOR_BUILD="/usr/bin/as" CC_FOR_BUILD="/usr/bin/gcc" GCC_FOR_BUILD="/usr/bin/gcc" CXX_FOR_BUILD="/usr/bin/g++" LD_FOR_BUILD="/usr/bin/ld" CPPFLAGS_FOR_BUILD="-I/usr/include" CFLAGS_FOR_BUILD="-O2 -I/usr/include" CXXFLAGS_FOR_BUILD="-O2 -I/usr/include" LDFLAGS_FOR_BUILD="-L/lib -L/usr/lib -Wl,-rpath,/usr/lib" FCFLAGS_FOR_BUILD="" DEFAULT_ASSEMBLER="arm-linux-as" DEFAULT_LINKER="arm-linux-ld" CPPFLAGS="-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64" CFLAGS="-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os " CXXFLAGS="-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os " LDFLAGS="" FCFLAGS=" -Os " FFLAGS=" -Os " PKG_CONFIG="pkg-config" STAGING_DIR="" INTLTOOL_PERL=/usr/bin/perl ac_cv_lbl_unaligned_fail=yes ac_cv_func_mmap_fixed_mapped=yes ac_cv_func_memcmp_working=yes ac_cv_have_decl_malloc=yes gl_cv_func_malloc_0_nonnull=yes ac_cv_func_malloc_0_nonnull=yes ac_cv_func_calloc_0_nonnull=yes ac_cv_func_realloc_0_nonnull=yes lt_cv_sys_lib_search_path_spec="" ac_cv_c_bigendian=no   CONFIG_SITE=/dev/null ./configure --target=arm-linux-gnueabi --host=arm-linux-gnueabi --build=x86_64-pc-linux-gnu --prefix=/usr --exec-prefix=/usr --sysconfdir=/etc --localstatedir=/var --program-prefix="" --disable-gtk-doc --disable-gtk-doc-html --disable-doc --disable-docs --disable-documentation --with-xmlto=no --with-fop=no --disable-dependency-tracking --enable-ipv6  --disable-static --enable-shared  --with-gnu-ld --without-python --without-debug --without-zlib --without-lzma --without-iconv

	echo "Done configuring"
}

md5sum_check()
{
	APP=$1
	APPNAME=`basename $1`
	md5sum --status -c $APP.md5
	if [ $? -ne 0 ]; then
		echo "ERROR: $APPNAME has wrong md5 hash:"
		echo "ERROR: expected: `more $APP.md5 | awk '{print $1}'`"
		echo "ERROR: got     : `md5sum $APP | awk '{print $1}'`"
		return 1
	fi

	echo "$APPNAME: OK (md5: `more $APP.md5 | awk '{print $1}'`)"

	return 0
}

mk_all()
{
	echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"

	if [ ! -d $SRCPATH ]; then
		md5sum_check $PACKNAME
		if [ $? -ne 0 ]; then
			return 1
		fi

		echo "$APPNAME Extracting"
		mkdir -p $SRCPATH
		$ZIPCMD $PACKPATH | tar --strip-components=1 -C $SRCPATH   -xf -
		if [ $? -ne 0 ]; then
			return 1
		fi

		cd $SRCPATH
		mk_patch
	fi

	[ -f $SRCPATH/Makefile ] || { cd $SRCPATH; mk_config; }

	echo "$APPNAME Building"
	/usr/bin/make -j5 -C $SRCPATH
	if [ $? -ne 0 ]; then
		return 1
	fi

	/usr/bin/make -j5 -C $SRCPATH DESTDIR=$OUTPUTDIR install

	echo "$APPNAME Installing to target"
	cp -f $OUTPUTDIR/usr/lib/${UTIL_NAME}.so* $TARGETDIR

	find "$TARGETDIR" -type f -name "${UTIL_NAME}".so* -print0 | xargs -0 arm-linux-strip --remove-section=.comment --remove-section=.note 2>/dev/null || true

	echo "Build: $PACKNAME succeeded"

	return 0
}

mk_clean()
{
	make -C $SRCPATH distclean
	/usr/bin/make -j5 -C $SRCPATH DESTDIR=$OUTPUTDIR uninstall

	rm -f $TARGETDIR/${UTIL_NAME}.so*
}

case "$1" in

	[aA][lL][lL] )
	mk_all
	;;

	[cC][lL][eE][aA][nN] )
	mk_clean
	;;
esac
