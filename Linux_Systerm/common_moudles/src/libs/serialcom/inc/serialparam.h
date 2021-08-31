/**************************************************************
* serialparam.h
* Copyright (C) 2017 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2017.09.26
**************************************************************/

#ifndef _SERIAL_PARAM_H_
#define _SERIAL_PARAM_H_

#ifndef _T_BYTE
#define _T_BYTE
typedef unsigned char   BYTE;
#endif

/*func return value*/
#define SUCCESS 1
#define FAILURE -1

/*最大端口数目*/
#define  MAX_COMS 12
#define  COM1     0
#define  COM2     1
#define  COM3     2
#define  COM4     3
#define  COM5     4
#define  COM6     5
#define  COM7     6
#define  COM8     7
#define  COM9     8
#define  COM10    9
#define  COM11    10
#define  COM12    11

/* 校验方式定义 */
#define  PARITY_ODD   0 /*奇校验*/
#define  PARITY_EVEN  1 /*偶校验*/
#define  PARITY_NONE  2 /*无校验*/

/*阻塞方式定义*/
#define  COM_BLOCK    0
#define  COM_NBLOCK   1
/*RTS CTS，流控制定义*/
#define  COM_RTSCTS_ENABLE   0
#define  COM_RTSCTS_DISABLE  1

/*数据位定义*/
#define  COM_BYTESIZE5  5
#define  COM_BYTESIZE6  6
#define  COM_BYTESIZE7  7
#define  COM_BYTESIZE8  8

/*停止位定义*/
#define  COM_STOPBITS1  0
#define  COM_STOPBITS15 1
#define  COM_STOPBITS2  2

#define  SC_HANDLER		void*

/*定义485控制的读写、自动控制*/
#define  STATUS_AUTO   1
#define  STATUS_READ   2
#define  STATUS_WRITE  3

typedef struct {
	unsigned char flag;	//有效性
	int baudrate;		//速率
	unsigned char serial_num;	//端口号enum COM_NO { COM1=0, COM2=1, ... };
	unsigned char parity;	//校验
	unsigned char sync_mode;	//同步方式
	unsigned char rtscts;	//流控制
	unsigned char bytesize;	//数据位长度
	unsigned char stopbits;	//停止位长度
} __attribute__ ((packed)) S_COMM_PARA;

#endif /*_SERIAL_PARAM_H_*/
