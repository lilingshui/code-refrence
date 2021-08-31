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

/*���˿���Ŀ*/
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

/* У�鷽ʽ���� */
#define  PARITY_ODD   0 /*��У��*/
#define  PARITY_EVEN  1 /*żУ��*/
#define  PARITY_NONE  2 /*��У��*/

/*������ʽ����*/
#define  COM_BLOCK    0
#define  COM_NBLOCK   1
/*RTS CTS�������ƶ���*/
#define  COM_RTSCTS_ENABLE   0
#define  COM_RTSCTS_DISABLE  1

/*����λ����*/
#define  COM_BYTESIZE5  5
#define  COM_BYTESIZE6  6
#define  COM_BYTESIZE7  7
#define  COM_BYTESIZE8  8

/*ֹͣλ����*/
#define  COM_STOPBITS1  0
#define  COM_STOPBITS15 1
#define  COM_STOPBITS2  2

#define  SC_HANDLER		void*

/*����485���ƵĶ�д���Զ�����*/
#define  STATUS_AUTO   1
#define  STATUS_READ   2
#define  STATUS_WRITE  3

typedef struct {
	unsigned char flag;	//��Ч��
	int baudrate;		//����
	unsigned char serial_num;	//�˿ں�enum COM_NO { COM1=0, COM2=1, ... };
	unsigned char parity;	//У��
	unsigned char sync_mode;	//ͬ����ʽ
	unsigned char rtscts;	//������
	unsigned char bytesize;	//����λ����
	unsigned char stopbits;	//ֹͣλ����
} __attribute__ ((packed)) S_COMM_PARA;

#endif /*_SERIAL_PARAM_H_*/
