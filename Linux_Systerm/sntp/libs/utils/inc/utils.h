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

#define PRT_OPEN_FAIL printf("result=fail:不支持该设备\n")
#define PRT_TEST_FAIL printf("result=fail:测试失败\n")
#define PRT_TEST_FAIL_NORESPOND printf("result=fail:测试失败,未回复报文\n")
#define PRT_TEST_SUCCESS printf("result=success:测试合格\n")

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
*获取可执行程序的路径和名字，并返回路径的长度
*processdir : 用于保存可执行程序的路径
*processname : 用于保存可执行程序的名字
*len : processdir的长度
*返回值: 可执行程序的路径的长度
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
*将BCD码转换为16进制(一个字节)，如32->0x20
*data : 要转换的值
*返回值: 转换后的结果
***************************************************************/
u_int8_t Bcd2Hex(u_int8_t data);

/**************************************************************
*将BCD码转换为10进制，如32 33 34 转为323334
*data : 要转换的值
*返回值: 转换后的结果
***************************************************************/
int Bcd2Int(u_int8_t *data, u_int8_t len);

/*将str1字符串中第一次出现的str2字符串替换成str3*/
void replaceFirst(char *str1, const char *str2, const char *str3);

/*将str1出现的所有的str2都替换为str3*/
void replace(char *str1, const char *str2, const char *str3);

/*截取src字符串中,从下标为start开始到end-1(end前面)的字符串保存在dest中(下标从0开始)*/
void substring(char *dest,char *src,int start,int end);

/*返回src中下标为index的字符*/
char charAt(char *src,int index);

/*返回str2第一次出现在str1中的位置(下表索引),不存在返回-1*/
int indexOf(char *str1,char *str2);

/*返回str1中最后一次出现str2的位置(下标),不存在返回-1*/
int lastIndexOf(char *str1,char *str2);

/*删除str左边第一个非空白字符前面的空白字符(空格符和横向制表符)*/
void ltrim(char *str);

/*删除str最后一个非空白字符后面的所有空白字符(空格符和横向制表符)*/
void rtrim(char *str);

/*删除str两端的空白字符*/
void trim(char *str);

/************************
*将字符串转化为指定的进制
************************/
int StrToInt(char* sStr, char Radix);

/**************************************************
*判断文件夹是否存在，不存在则创建
***************************************************/
bool CreateFolder(const char* strFolderName);

/**************************************************
*获取MAC地址
***************************************************/
bool GetMacAddress(char* szBuff, int nlength, const char* strInterface);

/**************************************************
*获取IP地址
***************************************************/
bool GetIPAddress(char* IPAddr, int nlength, const char* strInterface);


/**************************************************
*获取MAC地址
***************************************************/
bool GetMacAddressEx(char* szBuff, int nlength, const char* strInterface);


#ifdef __cplusplus
}
#endif

#endif /*_UTILS_H_*/
