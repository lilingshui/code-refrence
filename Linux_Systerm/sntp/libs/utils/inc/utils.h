/**************************************************************
* utils.h
* Copyright (C) 2016 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2016.12.16
**************************************************************/

#ifndef _UTILS_H_
#define _UTILS_H_

#include <sys/types.h>
#include <stdbool.h>
#define DEC 10
#define HEX 16

#define VERSION "v2.0"

#define PRT_OPEN_FAIL printf("result=fail:��֧�ָ��豸\n")
#define PRT_TEST_FAIL printf("result=fail:����ʧ��\n")
#define PRT_TEST_FAIL_NORESPOND printf("result=fail:����ʧ��,δ�ظ�����\n")
#define PRT_TEST_SUCCESS printf("result=success:���Ժϸ�\n")

#ifdef __cplusplus
extern "C" {
#endif

void split_str_value(const char *from, const char *key_word, char *value);
int get_shell_result(const char *command, char *string);
int get_shell_resultEx(const char *command, char *string);
unsigned short CalcCRC(unsigned char *InBuf,int InLen);
unsigned char GetCheckSum(unsigned char *buff, int buffLen);
int close_console_printk(void);
int open_console_printk(void);


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

int get_executable_path(char* processdir, char* processname, size_t len);

/**************************************************************
*��BCD��ת��Ϊ16����(һ���ֽ�)����32->0x20
*data : Ҫת����ֵ
*����ֵ: ת����Ľ��
***************************************************************/
u_int8_t Bcd2Hex(u_int8_t data);

/**************************************************************
*��BCD��ת��Ϊ10���ƣ���32 33 34 תΪ323334
*data : Ҫת����ֵ
*����ֵ: ת����Ľ��
***************************************************************/
int Bcd2Int(u_int8_t *data, u_int8_t len);

/*��str1�ַ����е�һ�γ��ֵ�str2�ַ����滻��str3*/
void replaceFirst(char *str1, const char *str2, const char *str3);

/*��str1���ֵ����е�str2���滻Ϊstr3*/
void replace(char *str1, const char *str2, const char *str3);

/*��ȡsrc�ַ�����,���±�Ϊstart��ʼ��end-1(endǰ��)���ַ���������dest��(�±��0��ʼ)*/
void substring(char *dest,char *src,int start,int end);

/*����src���±�Ϊindex���ַ�*/
char charAt(char *src,int index);

/*����str2��һ�γ�����str1�е�λ��(�±�����),�����ڷ���-1*/
int indexOf(char *str1,char *str2);

/*����str1�����һ�γ���str2��λ��(�±�),�����ڷ���-1*/
int lastIndexOf(char *str1,char *str2);

/*ɾ��str��ߵ�һ���ǿհ��ַ�ǰ��Ŀհ��ַ�(�ո���ͺ����Ʊ��)*/
void ltrim(char *str);

/*ɾ��str���һ���ǿհ��ַ���������пհ��ַ�(�ո���ͺ����Ʊ��)*/
void rtrim(char *str);

/*ɾ��str���˵Ŀհ��ַ�*/
void trim(char *str);

/************************
*���ַ���ת��Ϊָ���Ľ���
************************/
int StrToInt(char* sStr, char Radix);

/**************************************************
*�ж��ļ����Ƿ���ڣ��������򴴽�
***************************************************/
bool CreateFolder(const char* strFolderName);

/**************************************************
*��ȡMAC��ַ
***************************************************/
bool GetMacAddress(char* szBuff, int nlength, const char* strInterface);

/**************************************************
*��ȡIP��ַ
***************************************************/
bool GetIPAddress(char* IPAddr, int nlength, const char* strInterface);


/**************************************************
*��ȡMAC��ַ
***************************************************/
bool GetMacAddressEx(char* szBuff, int nlength, const char* strInterface);


#ifdef __cplusplus
}
#endif

#endif /*_UTILS_H_*/
