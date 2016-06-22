#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	int nValue;
	FILE *fp;//定义一个文件指针
	fp = freopen("./a.txt","r",stdin); //打开文件,fp与stdin等价
	
	while (EOF != scanf("%d", &nValue))
	{
		printf("%08x\n",nValue);//按照八位输出，不足前面补零
	}
	
	//scanf("%d",in);//从文件里,读取字符串到in。//等价于 fscanf(fp,in);或fscanf(stdin,in);
	fclose(fp);
} 
