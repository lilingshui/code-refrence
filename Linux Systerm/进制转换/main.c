#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	int nValue;
	FILE *fp;//����һ���ļ�ָ��
	fp = freopen("./a.txt","r",stdin); //���ļ�,fp��stdin�ȼ�
	
	while (EOF != scanf("%d", &nValue))
	{
		printf("%08x\n",nValue);//���հ�λ���������ǰ�油��
	}
	
	//scanf("%d",in);//���ļ���,��ȡ�ַ�����in��//�ȼ��� fscanf(fp,in);��fscanf(stdin,in);
	fclose(fp);
} 
