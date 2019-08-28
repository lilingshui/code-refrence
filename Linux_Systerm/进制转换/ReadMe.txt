本工具的作用是将input.txt文件中的数字（10进制）
转换成16进制并按照8位的样式输出。
编译: gcc main.c -o main
运行: ./main

还有一种方式，直接在linux系统下执行脚本，如：
#!/bin/sh
printf "%08x\n" 6144    
printf "%08x\n" 20815872
printf "%08x\n" 1216512 
printf "%08x\n" 3649536 
printf "%08x\n" 1910784 
printf "%08x\n" 12320768
printf "%08x\n" 131072  
printf "%08x\n" 296960