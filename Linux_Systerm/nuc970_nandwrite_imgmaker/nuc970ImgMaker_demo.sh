#!/bin/bash

# 128 MB, 2048+64, page per block: 64, block size :128KB
# MTD NAND Partition layout
# Partition 0: 4 Block		offset: 0, 			size: 0x80000
# Partition 1: (512KB)		offset: 0xa0000,	size: 0x80000
# Partition 2: (20MB)		offset: 0x160000,	size: 0x1400000
# Partition 3: (47MB)		offset: 0x1560000,	size: 0x2F00000
# Partition 4: (yaffs2)		offset: 0x4460000,	size: 0x3200000


#[Usage] ./nuc970ImgMaker
#	-v ....: version
#	-O ....: Output folder path
#	-p ....: page size
#	-o ....: OOB size
#	-s ....: page per block
#	-b ....: block number
#	-t ....: nuc970.ini path
#	-P "<ImgFilePath> [parameters]"

#	[parameters]
#		-t ....: Image type. Data:0, Env:1, uBoot:2
#		-o ....: Redundent area size.(option)\n"
#		-S ....: MTD partition entry size.
#		-O ....: MTD partition entry offset.
#		-j ....: Won't determine parity code if all 0xff in a page.
#		-b ....: BCH error bits(4, 8, 12, 15, 24).
#		-e ....: Execution address.

#[Example] ./nuc970ImgMaker -o ./nand_golden -p 2048 -o 64 -s 64 -b 1024
#				-P "./u-boot-spl.bin -t 2 -O 0 -S 0x80000 -j 0 " 
#				-P "./u-boot.bin -t 0 -O 0xa0000 -S 0x60000 -j 0 " 
#				-P "./nuc970image -t 0 -O 0x160000 -S 0x1400000 -j 0 " 


if ./Src/nuc970ImgMaker -O ../nuc970_nandwrite_imgmaker/nand_golden -t ../nuc970_nandwrite_imgmaker/nuc970.ini -p 2048 -o 64 -s 64 -b 1024 \
                        -P "../nuc970_nandwrite_imgmaker/u-boot-spl.bin -t 2 -b 4 -O 0 -S 0x80000" \
                        -P "../nuc970_nandwrite_imgmaker/u-boot.bin -t 0 -b 8 -O 0xa0000 -S 0x60000" \
                        -P "../nuc970_nandwrite_imgmaker/nuc970image -t 0 -b 8 -O 0x160000 -S 0x1400000"; then
	echo "========================================================================="
	echo "All golden images are created."
	echo "All parity code in spare area are produced by nuc970ImgMaker."
	echo "Now, Please put these files into memory by your NAND programmer."
	echo "========================================================================="
fi
