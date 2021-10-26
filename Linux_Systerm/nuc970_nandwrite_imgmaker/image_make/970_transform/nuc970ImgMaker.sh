#!/bin/sh
#

# 128 MB, 2048+64, page per block: 64, block size :128KB
# MTD NAND Partition layout
# Partition 0: 4 Block      offset: 0,          size: 0x80000
# Partition 1: (512KB)      offset: 0xa0000,    size: 0x80000
# Partition 2: (20MB)       offset: 0x160000,   size: 0x1400000
# Partition 3: (47MB)       offset: 0x1560000,  size: 0x2F00000
# Partition 4: (yaffs2)     offset: 0x4460000,  size: 0x3200000


#[Usage] ./nuc970ImgMaker
#   -v ....: version
#   -O ....: Output folder path
#   -p ....: page size
#   -o ....: OOB size
#   -s ....: page per block
#   -b ....: block number
#   -t ....: nuc970.ini path
#   -P "<ImgFilePath> [parameters]"

#   [parameters]
#       -t ....: Image type. Data:0, Env:1, uBoot:2
#       -o ....: Redundent area size.(option)\n"
#       -S ....: MTD partition entry size.
#       -O ....: MTD partition entry offset.
#       -j ....: Won't determine parity code if all 0xff in a page.
#       -b ....: BCH error bits(4, 8, 12, 15, 24).
#       -e ....: Execution address.

#[Example] ./nuc970ImgMaker -o ./nand_golden -p 2048 -o 64 -s 64 -b 1024
#               -P "./u-boot-spl.bin -t 2 -O 0 -S 0x80000 -j 0 " 
#               -P "./u-boot.bin -t 0 -O 0xa0000 -S 0x60000 -j 0 " 
#               -P "./nuc970image -t 0 -O 0x160000 -S 0x1400000 -j 0 " 
 
#: name                size            offset          mask_flags
# 0: bootstrap           0x00400000      0x00000000      0
# 1: u-boot              0x00400000      0x00400000      0
# 2: u-bootenv           0x00400000      0x00800000      0
# 3: dtb                 0x00400000      0x00c00000      0
# 4: kernel              0x01000000      0x01000000      0
# 5: rootfs              0x06000000      0x02000000      0
# 6: krnl-bak            0x08000000      0x08000000      0
# 7: usrbak              0x0c000000      0x10000000      0
# 8: home                0x0c000000      0x1c000000      0
# 9: data0               0xb6c00000      0x28000000      0
#10: data1               0x20000000      0xdec00000      0

if ./Src/nuc970ImgMaker -O ../970_transform/nand_golden -t ../970_transform/nuc970.ini -p 8192 -o 392 -s 128 -b 4156 \
                        -P "../970_transform/rootfs.img -t 0 -b 24 -O 0x2000000 -S 0x6000000 -g 0" \
                        -P "../970_transform/home.img -t 0 -b 24 -O 0x1c000000 -S 0xc000000 -g 1" \
                        -P "../970_transform/data0.img -t 0 -b 24 -O 0x28000000 -S 0xb6c00000 -g 1" \
                        -P "../970_transform/data1.img -t 0 -b 24 -O 0xdec00000 -S 0x20000000 -g 1"; then
    echo "========================================================================="
    echo "All golden images are created."
    echo "All parity code in spare area are produced by nuc970ImgMaker."
    echo "Now, Please put these files into memory by your NAND programmer."
    echo "========================================================================="
fi
