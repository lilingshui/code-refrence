#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

int main() {
	int fp=0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	fp = open ("/dev/fb0",O_RDWR);

	if (fp < 0){
		printf("Error : Can not open framebuffer device/n");
		exit(1);
	}

	if (ioctl(fp,FBIOGET_FSCREENINFO,&finfo)){
		printf("Error reading fixed information/n");
		exit(2);
	}

	if (ioctl(fp,FBIOGET_VSCREENINFO,&vinfo)){
		printf("Error reading variable information/n");
		exit(3);
	}

	printf("The mem is :%d/n",finfo.smem_len);
	printf("The line_length is :%d/n",finfo.line_length);
	printf("The xres is :%d/n",vinfo.xres);
	printf("The yres is :%d/n",vinfo.yres);
	printf("bits_per_pixel is :%d/n",vinfo.bits_per_pixel);
	close(fp);
}

struct fb_var_screeninfo 和 struct fb_fix_screeninfo 两个数据结构是在/usr/include/linux/fb.h中定义的，里面有些有趣的值：（都是无符号32位的整数）
 
在fb_fix_screeninfo中有
__u32 smem_len 			是这个/dev/fb0的大小，也就是内存大小。
__u32 line_length 		是屏幕上一行的点在内存中占有的空间，不是一行上的点数。
在fb_var_screeninfo 中有
__u32 xres, x方向的分辨率
__u32 yres, y方向的分辨率
__u32 bits_per_pixel 是每一点占有的内存空间。


把上面的程序编译以后运行，在我的机器上的结果如下
The mem is :6291456 
The line_length is :4096 T
he xres is :1024
The yres is :768
bits_per_pixel is :32
//这样子在调试的时候相当的重要和完善了呀！！！！！
内存长度恰好是6M，每行占有4M的空间，分辨率是1024x768，色彩深度是32位。细心的你可能已经发现有些不对。
屏幕上的点有1024x768＝786432个，每个点占有32比特。屏幕一共的占有内存数为32x786432＝25165824 就是3145728字节，
恰好是3M但是上面的程序告诉我们有6M的存储空间。这是因为在现代的图形系统中大多有缓冲技术，显存中存有两页屏幕数据，
这是方便快速的改变屏幕内容实现动画之类比较高的要求。关于这种缓冲技术有点复杂，我们目前先不讨论。
对于我们来说只有这3M内存来存放这一个屏幕的颜色数据。好了，现在你应该对FrameBuffer有一个大概的了解了吧。
那么接下来你一定会想在屏幕上画一些东西，让我们先从画一个点开始吧。先说说我的想法：在类Unix系统中，一切东西都是文件。
我们对屏幕的读写就可以转换成对/dev/fb0的读写。那么就把/dev/fb0用open打开，再用lseek定位要读写的位置，最后调用read或者write来操作。
通过这么一大段的操作我们才完成了对一个点的读或者写。这种方法开销太大了。还有一种方法，我们把/dev/fb0映射到程序进程的内存空间中来，
然后得到一个指向这段存储空间的指针，这样就可以方便的读写了。但是我们要知道能映射多少和该映射多少，这能很方便的从上面一个程序得出的参数来决定。
//内存当中的映射的关键的部分描述和介绍

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

int main() {
	int fp=0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long screensize=0;
	char *fbp = 0;
	int x = 0, y = 0;
	long location = 0;
	fp = open ("/dev/fb0",O_RDWR);

	if (fp < 0){
		printf("Error : Can not open framebuffer device/n");
		exit(1);
	}

	if (ioctl(fp,FBIOGET_FSCREENINFO,&finfo)){
		printf("Error reading fixed information/n");
		exit(2);
	}

	if (ioctl(fp,FBIOGET_VSCREENINFO,&vinfo)){
		printf("Error reading variable information/n");
		exit(3);
	}

	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	/*这就是把fp所指的文件中从开始到screensize大小的内容给映射出来，得到一个指向这块空间的指针*/
	fbp =(char *) mmap (0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp,0);
	if ((int) fbp == -1)
	{
		printf ("Error: failed to map framebuffer device to memory./n");
		exit (4);
	}
	/*这是你想画的点的位置坐标,(0，0)点在屏幕左上角*/
	x = 100;
	y = 100;
	location = x * (vinfo.bits_per_pixel / 8) + y  *  finfo.line_length;

	*(fbp + location) = 100;  /* 蓝色的色深 */  /*直接赋值来改变屏幕上某点的颜色*/
	*(fbp + location + 1) = 15; /* 绿色的色深*/   
	*(fbp + location + 2) = 200; /* 红色的色深*/   
	*(fbp + location + 3) = 0;  /* 是否透明*/  
	munmap (fbp, screensize); /*解除映射*/
	close (fp);    /*关闭文件*/
	return 0;
}