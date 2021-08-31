/**************************************************************
* utils.cpp
* Copyright (C) 2016 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2017.01.11
**************************************************************/

#include "utils.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <dirent.h>
#include "fcntl.h"
#include "logexport.h"
/**************************************************************
*��ȡ��ִ�г����·�������֣�������·���ĳ���
*processdir : ���ڱ����ִ�г����·��
*processname : ���ڱ����ִ�г��������
*len : processdir�ĳ���
*����ֵ: ��ִ�г����·���ĳ���
***************************************************************/
/**************************************************************
int main()
{
	char path[PATH_MAX];
	char processname[1024];
	get_executable_path(path, processname, sizeof(path));
	printf("directory:%s\nprocessname:%s\n",path,processname);
}
***************************************************************/

int get_executable_path(char* processdir, char* processname, size_t len)
{
	char* path_end;
	if(readlink("/proc/self/exe", processdir,len) <=0) {
	    return -1;
    }

	path_end = strrchr(processdir, '/');
	if(path_end == NULL) {
	    return -1;
    }

	++path_end;
	strcpy(processname, path_end);
	*path_end = '\0';
	return (int)(path_end - processdir);
}

/**************************************************************
*��BCD��ת��Ϊ16����(һ���ֽ�)����32->0x20
*data : Ҫת����ֵ
*����ֵ: ת����Ľ��
***************************************************************/
u_int8_t Bcd2Hex(u_int8_t data)
{
    return ((data >> 4) * 10) + (data & 0x0F);
}

/**************************************************************
*��BCD��ת��Ϊ10���ƣ���32 33 34 תΪ323334
*data : Ҫת����ֵ
*����ֵ: ת����Ľ��
***************************************************************/
int Bcd2Int(u_int8_t *data, u_int8_t len)
{
    int m_data = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        m_data = m_data * 100 + Bcd2Hex(data[i]);
    }
    return m_data;
}

/*��str1�ַ����е�һ�γ��ֵ�str2�ַ����滻��str3*/
void replaceFirst(char *str1, const char *str2, const char *str3)
{
    char str4[strlen(str1)+1];
    char *p;
    strcpy(str4,str1);
    if((p=strstr(str1,str2))!=NULL)/*pָ��str2��str1�е�һ�γ��ֵ�λ��*/
    {
        while(str1!=p&&str1!=NULL)/*��str1ָ���ƶ���p��λ��*/
        {
            str1++;
        }
        str1[0]='\0';/*��str1ָ��ָ���ֵ���/0,�Դ����ض�str1,����str2���Ժ�����ݣ�ֻ����str2��ǰ������*/
        strcat(str1,str3);/*��str1��ƴ����str3,�����str1*/
        strcat(str1,strstr(str4,str2)+strlen(str2));/*strstr(str4,str2)��ָ��str2���Ժ������(����str2),strstr(str4,str2)+strlen(str2)���ǽ�ָ����ǰ�ƶ�strlen(str2)λ������str2*/
    }
}

/*��str1���ֵ����е�str2���滻Ϊstr3*/
void replace(char *str1, const char *str2, const char *str3)
{
    while(strstr(str1, str2)!=NULL)
    {
        replaceFirst(str1, str2, str3);
    }
}

/*��ȡsrc�ַ�����,���±�Ϊstart��ʼ��end-1(endǰ��)���ַ���������dest��(�±��0��ʼ)*/
void substring(char *dest,char *src,int start,int end)
{
    int i=start;
    if(start > (int)strlen(src))return;
    if(end>(int)strlen(src))
        end=(int)strlen(src);
    while(i<end)
    {
        dest[i-start]=src[i];
        i++;
    }
    dest[i-start]='\0';
    return;
}

/*����src���±�Ϊindex���ַ�*/
char charAt(char *src,int index)
{
    char *p=src;
    int i=0;
    if(index<0||index>(int)strlen(src))
        return 0;
    while(i<index)i++;
    return p[i];
}

/*����str2��һ�γ�����str1�е�λ��(�±�����),�����ڷ���-1*/
int indexOf(char *str1,char *str2)
{
    char *p=str1;
    int i=0;
    p=strstr(str1,str2);
    if(p==NULL)
        return -1;
    else{
        while(str1!=p)
        {
            str1++;
            i++;
        }
    }
    return i;
}

/*����str1�����һ�γ���str2��λ��(�±�),�����ڷ���-1*/
int lastIndexOf(char *str1,char *str2)
{
    char *p=str1;
    int i=0,len=strlen(str2);
    p=strstr(str1,str2);
    if(p==NULL)return -1;
    while(p!=NULL)
    {
        for(;str1!=p;str1++)i++;
        p=p+len;
        p=strstr(p,str2);
    }
    return i;
}

/*ɾ��str��ߵ�һ���ǿհ��ַ�ǰ��Ŀհ��ַ�(�ո���ͺ����Ʊ��)*/
void ltrim(char *str)
{
    int i=0,j,len=strlen(str);
    while(str[i]!='\0')
    {
        if(str[i]!=32&&str[i]!=9)break;/*32:�ո�,9:�����Ʊ��*/
        i++;
    }
    if(i!=0)
    for(j=0;j<=len-i;j++)
    {
        str[j]=str[j+i];/*��������ַ�˳��ǰ��,����ɾ���Ŀհ�λ��*/
    }
}

/*ɾ��str���һ���ǿհ��ַ���������пհ��ַ�(�ո���ͺ����Ʊ��)*/
void rtrim(char *str)
{
    char *p=str;
    int i=strlen(str)-1;
    while(i>=0)
    {
        if(p[i]!=32&&p[i]!=9)break;
        i--;
    }
    str[++i]='\0';
}

/*ɾ��str���˵Ŀհ��ַ�*/
void trim(char *str)
{
    ltrim(str);
    rtrim(str);
}

/************************
*���ַ���ת��Ϊָ���Ľ���
************************/
int StrToInt(char* sStr, char Radix)
{
    int Decimal = 0;
    int i,StrLen;
    char TmpChar;

    StrLen = strlen(sStr);
    if(StrLen > 10)
    {
        return 0xffffffff;
    }

    for(i = 0; i < StrLen; i++)
    {
        TmpChar = *(sStr + i);
        if(TmpChar>='A' && TmpChar<'G')
        {
          TmpChar -= 0x37;
        }
        else if(TmpChar>='a' && TmpChar<'g')
        {
          TmpChar -= 0x57;
        }
        else if(TmpChar>='0' && TmpChar<='9')
        {
          TmpChar -= 0x30;
        }
		else if(TmpChar == 'x')/*���ڶ�0x��ͷ���ַ�������ת��*/
		{
			TmpChar = 0;
		}
        else
        {
          return 0xffffffff;
        }

        Decimal = Decimal*Radix + TmpChar;
    }

    return Decimal;
}

/**************************************************
*�ж��ļ����Ƿ���ڣ��������򴴽�
***************************************************/
bool CreateFolder(const char* strFolderName)
{
    if (access(strFolderName, 0) == -1)
    {
        int flag = mkdir(strFolderName, 0777);

        if (flag == 0)
        {
            printf("make successfully\n");
			return true;
        }
		else
        {
            printf("make errorly\n");
			return false;
        }
    }

    return true;
}


/**
 * @function void split_str_value(const char *from, const char *key_word ,char *value)
 * @details	�����ַ������ض��ӱ�����ֵ
 * @param[in]   from:��Ҫ�������ַ�����key_word�������ؼ���
 * @param[out]  value���ؼ��ֶ�Ӧ��ֵ��
 * @retval ��
 * @example
    split_str_value("color=white,backlight=off","color=",color);
	��ʾ��ȡ��color=��Ϊ�ؼ��ֵ�ֵ���������к�colorֵΪwhite.

 * @par �޸���־
 *      ���Ŀ���2016-11-24����
 */

void split_str_value(char *from, char *key_word , char *value)
{
	char *p;
	char temp[400];

	p = strstr(from, key_word);
	strcpy(temp, key_word);
	/*
		sscanf��ʽ������%[^,]��ʾ�������Ž���ֹͣ��
	*/
	strcat(temp, "%[^,]");
	if (p)
		sscanf(p, temp, value);
	LogD("%s\"%s\"\n", key_word, value);
}

/**
 * @function int get_shell_result(const char *command, char *string)
 * @details	��ȡshell�����ִ�н��
 * @param[in]   command:ִ�е�����
 * @param[out]  string��ִ�н����
 * @retval 0:�ɹ���-1ʧ�ܣ�
 * @example
   char test_string[1000] = {0};
	 get_shell_result("cat /proc/cpuinfo", test_string);
	 printf("%s",test_string);

 * @par �޸���־
 *      ���Ŀ���2016-12-22����
 */
int get_shell_result(const char *command, char *string)
{
	FILE *fp;
	char buffer[200] = {0};
	strcpy(string, "");
	LogD("command:\"%s\"",command);
	fp = popen(command, "r");
	if (NULL == fp) {
		LogD("popen error\n");
			return -1;
	}
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
		strcat(string, buffer);
	pclose(fp);
	replace(string, "\r", "");
	replace(string, "\n", "");
	if (strlen(string) <= 0) {
		LogD("no result");
		return -1;
	}
	LogD("result:\"%s\"",string);
	return 0;
}

int get_shell_resultEx(const char *command, char *string)
{
	FILE *fp;
	char buffer[200] = {0};
	strcpy(string, "");

	fp = popen(command, "r");
	if (NULL == fp) {
			return -1;
	}
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
		strcat(string, buffer);
	pclose(fp);
	replace(string, "\r", "");
	replace(string, "\n", "");
	if (strlen(string) <= 0) {
		return -1;
	}
	printf("%s", string);
	return 0;
}

//*****************��������*******************//
unsigned short CalcCRC(unsigned char *InBuf,int InLen)
{
    static unsigned char auchCRCHi[] =
    {
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
    };

    static char auchCRCLo[] =
    {
        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
        0x43, 0x83, 0x41, 0x81, 0x80, 0x40
    };
	unsigned char uchCRCHi =0xff;   //CRC���ֽڳ�ʼ��
    unsigned char uchCRCLo =0xff;  //CRC���ֽڳ�ʼ��
    unsigned char uIndex ; /*CRCѭ������*/
    while (InLen--) /*������Ϣ������*/
    {
        uIndex = uchCRCHi ^ *InBuf++; /*����CRC*/
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex];
    }
    return (uchCRCHi  | uchCRCLo << 8);

}

unsigned char GetCheckSum(unsigned char *buff, int buffLen)
{
	int init = 0x00;
	int i = 0;
	for (i = 0; i< buffLen; i ++)
	{
		init += *(buff+i);
	}
	return (init & 0xFF);
}

int close_console_printk(void)
{
	int fd = 0;
	fd = open("/proc/sys/kernel/printk",O_RDWR);

    if(fd < 0) {
    perror("/proc/sys/kernel/printk open fail\n");
    return -1;
    }
    write(fd,"0",1);
    close(fd);
    return 0;
}

int open_console_printk(void)
{
	int fd = 0;
	fd = open("/proc/sys/kernel/printk",O_RDWR);

    if(fd < 0) {
    perror("/proc/sys/kernel/printk open fail\n");
    return -1;
    }
    write(fd,"7",1);
    close(fd);
    return 0;
}
/**************************************************
*��ȡMAC��ַ
***************************************************/

bool GetMacAddress(char* szBuff, int nlength, const char* strInterface)
{
	struct ifreq ifreq;
	int sock;

	if(NULL == strInterface || strlen(strInterface) <= 0)
	{
		//printf("strInterface is invalid");
		return false;
	}

	if((sock = socket(AF_INET, SOCK_STREAM,0))<0)
	{
		//printf("create socket failed");
		return false;
	}

	strcpy(ifreq.ifr_name, strInterface);
	if(ioctl(sock,SIOCGIFHWADDR,&ifreq)<0)
	{
		//printf("==== SIOCGIFHWADDR error ====");
		return false;
	}

	snprintf(szBuff, nlength,"%02x-%02x-%02x-%02x-%02x-%02x",
					(unsigned char)ifreq.ifr_hwaddr.sa_data[0],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[1],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[2],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[3],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[4],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[5]);
	return true;
}

bool GetMacAddressEx(char* szBuff, int nlength, const char* strInterface)
{
	struct ifreq ifreq;
	int sock;

	if(NULL == strInterface || strlen(strInterface) <= 0)
	{
		//printf("strInterface is invalid");
		return false;
	}

	if((sock = socket(AF_INET, SOCK_STREAM,0))<0)
	{
		//printf("create socket failed");
		return false;
	}

	strcpy(ifreq.ifr_name, strInterface);
	if(ioctl(sock,SIOCGIFHWADDR,&ifreq) < 0)
	{
		//printf("==== SIOCGIFHWADDR error ====");
		return false;
	}

	snprintf(szBuff, nlength,"%02x:%02x:%02x:%02x:%02x:%02x",
					(unsigned char)ifreq.ifr_hwaddr.sa_data[0],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[1],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[2],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[3],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[4],
					(unsigned char)ifreq.ifr_hwaddr.sa_data[5]);
	return true;
}

/**************************************************
*��ȡIP��ַ
***************************************************/
bool GetIPAddress(char* IPAddr, int nlength, const char* strInterface)
{
    int sock;
    struct sockaddr_in sin;
    struct ifreq ifr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        return false;
    }

    strncpy(ifr.ifr_name, strInterface, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0)//get interface address
    {
        return false;
    }

    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    snprintf(IPAddr, nlength, "%s", inet_ntoa(sin.sin_addr));
    return true;
}

