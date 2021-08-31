/**************************************************************
* 485_util.cpp
* Copyright (C) 2016 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2016.12.26
**************************************************************/

#include <string.h>
#include <stdio.h>
#include "productID.h"
#include "logexport.h"
#include "utils.h"
#include "serialcomexport.h"
#include "proparseexport.h"
#include "485_util.h"

bool TestSingle485Channel(unsigned char channel_1, int nbaudrate, int nStopBit, int nDataBit, int nCheckBit)
{
	SC_HANDLER scH_485_1 = NULL;
	S_COMM_PARA scParam_1 = {0};
	scParam_1.serial_num = channel_1;
	scParam_1.baudrate = nbaudrate;
	scParam_1.parity = nCheckBit;
	scParam_1.sync_mode = COM_BLOCK;
	scParam_1.rtscts = COM_RTSCTS_DISABLE;
	scParam_1.bytesize = nDataBit;
	scParam_1.stopbits = nStopBit;
	scH_485_1 = SC_SerialCreate(scParam_1);

	if (NULL == scH_485_1)
	{
		LogE("Create Serial Failed!");
		return false;
	}

	unsigned char recvData[256] = {0};
	int rlen = 0;
	char strResult[500] = {0};

	if (!SC_SerialOpen(scH_485_1))
	{
		LogE("Open Serial Failed!");
		SC_SerialClose(scH_485_1);
		SC_SerialDestroy(scH_485_1);
		return false;
	}

	while(1)
	{
		rlen = SC_SerialRead(scH_485_1, recvData, sizeof(recvData));

		if (FAILURE != rlen)
		{
		    if (rlen < 400)
		    {
		        for (int i = 0; i < rlen; i++)
		        {
		            sprintf(strResult, "%s %02x", strResult, recvData[i]);
		        }
		    }

                printf("Receive and Send <==> [%s ]\n", strResult);
		   fflush(stdout);
                memset(strResult, 0, sizeof(strResult));                
                SC_SerialWrite(scH_485_1, recvData, rlen);
		}

		rlen = 0;
		memset(recvData, 0, sizeof(recvData));
		usleep(200000);
	}

	SC_SerialClose(scH_485_1);
	SC_SerialDestroy(scH_485_1);
	return false;
}

bool TestTwo485Channel(unsigned char channel_1,
					   unsigned char channel_2,
					   int nbaudrate,
					   bool bloop)
{
	SC_HANDLER scH_485_1 = NULL;
	SC_HANDLER scH_485_2 = NULL;

	S_COMM_PARA scParam_1 = {0};
	S_COMM_PARA scParam_2 = {0};

	scParam_1.serial_num = channel_1;
	scParam_1.baudrate = nbaudrate;
	scParam_1.parity = PARITY_EVEN;
	scParam_1.sync_mode = COM_BLOCK;
	scParam_1.rtscts = COM_RTSCTS_DISABLE;
	scParam_1.bytesize = COM_BYTESIZE8;
	scParam_1.stopbits = COM_STOPBITS1;
	scH_485_1 = SC_SerialCreate(scParam_1);

	scParam_2.serial_num = channel_2;
	scParam_2.baudrate = nbaudrate;
	scParam_2.parity = PARITY_EVEN;
	scParam_2.sync_mode = COM_BLOCK;
	scParam_2.rtscts = COM_RTSCTS_DISABLE;
	scParam_2.bytesize = COM_BYTESIZE8;
	scParam_2.stopbits = COM_STOPBITS1;
	scH_485_2 = SC_SerialCreate(scParam_2);

    //CSerialCom RS485_1, RS485_2;
    FrameStruct* tmpStruct=NULL;
    FrameStruct* head=NULL;
    BYTE tmpBuff[500]={0};
    int len=0;
	bool bResult = true;

	/* The data contain in the frame */
	BYTE buffData[200] = {0};

	/* initial the data of the data */
	for (int i = 0; i < (int)(sizeof(buffData)/sizeof(BYTE)); i++)
	{
		buffData[i] = i;
	}

    /*485测试流程：
     *以波特率9600实现1、2互测(1发2收, 2发1收), FuncCode=TEST485
     */

    //open ports
    if (!SC_SerialOpen(scH_485_1)|| !SC_SerialOpen(scH_485_2))
    {
        LogE("TestRS485: open RS485_1/2 port failed!");
        return false;
    }

	do
	{
		len = PP_FormSndFrame(tmpBuff, buffData, sizeof(buffData)/sizeof(BYTE), TEST485);

		if (SC_SerialWrite(scH_485_1, tmpBuff, len) != FAILURE)//RS485_1发
		{
			memset(tmpBuff, 0, sizeof(BYTE)*500);

			if ((len = SC_SerialRead(scH_485_2, tmpBuff, sizeof(tmpBuff)/sizeof(BYTE))) != FAILURE)//RS485_2收
			{
				if ((PP_SeperateRevData(tmpBuff, len, &tmpStruct) != SUCCESS)
						|| (PP_ParseSingleFrame(tmpStruct) != TEST485))
				{
					LogE("TestRS485: data RS485_2 received from RS485_1 is bad!");
					bResult = false;
				}
				else
				{
					memset(tmpBuff, 0, sizeof(BYTE)*500);
					len = PP_FormSndFrame(tmpBuff, buffData, sizeof(buffData)/sizeof(BYTE), TEST485);

					if (SC_SerialWrite(scH_485_2, tmpBuff, len) != FAILURE)//RS485_2发
					{
						memset(tmpBuff, 0, sizeof(BYTE)*500);

						if ((len=SC_SerialRead(scH_485_1, tmpBuff, sizeof(tmpBuff)/sizeof(BYTE))) != FAILURE)//RS485_1收
						{
							if ((PP_SeperateRevData(tmpBuff, len, &tmpStruct) != SUCCESS)
									|| (PP_ParseSingleFrame(tmpStruct) != TEST485))
							{
								LogE("TestRS485: data RS485_1 received from RS485_2 is bad!");
								bResult = false;
							}
						}
						else
						{
							LogE("TestRS485: RS485_1 couldn't receive data from RS485_2!");
							bResult = false;
						}
					}
					else
					{
						LogE("TestRS485: RS485_2 fails sending data!");
						bResult = false;
					}
				}
			}
			else
			{
				LogE("TestRS485: RS485_2 couldn't receive data from RS485_1!");
				bResult = false;
			}
		}
		else
		{
			LogE("TestRS485: RS485_1 fails sending data!");
			bResult = false;
		}

		/*clear tmpStruct*/
		while (NULL != tmpStruct)
		{
			head=tmpStruct->next;
			delete []tmpStruct;
			tmpStruct=head;
		}

		if (!bResult)
		{
			break;
		}
	}
	while(bloop);

	SC_SerialClose(scH_485_1);
	SC_SerialDestroy(scH_485_1);
	SC_SerialClose(scH_485_2);
	SC_SerialDestroy(scH_485_2);
	return bResult;
}

bool TestChannelByFile(unsigned char channel_1, /* The channel to test */
					   char* filename, /* The file contain the frame */
					   int nbaudrate,  /* baudrate of the channel */
					   int nStopBit,   /* stop bit of the channel */
					   int nDataBit,   /* data bit of the channel */
					   int nCheckBit)  /* check bit of the channel */
{
	if (NULL == filename) {
		LogE("filename is NULL");
		return false;
	}

	SC_HANDLER scH_485_1 = NULL;
	S_COMM_PARA scParam_1 = {0};

	scParam_1.serial_num = channel_1;
	scParam_1.baudrate = nbaudrate;
	scParam_1.parity = nCheckBit;
	scParam_1.sync_mode = COM_BLOCK;
	scParam_1.rtscts = COM_RTSCTS_DISABLE;
	scParam_1.bytesize = nDataBit;
	scParam_1.stopbits = nStopBit;
	scH_485_1 = SC_SerialCreate(scParam_1);
	LogD("===== serial_num is %d =====", scParam_1.serial_num);
	LogD("===== baudrate is %d =====", scParam_1.baudrate);
	LogD("===== parity is %d =====", scParam_1.parity);
	LogD("===== bytesize is %d =====", scParam_1.bytesize);
	LogD("===== stopbits is %d =====", scParam_1.stopbits);

    BYTE tmpBuff[500]={0};
    int len = 0;
	bool bResult = true;
	FILE * fp;
    char * line = NULL;
    size_t linelen = 0;
	ssize_t read;

    //open ports
    if (!SC_SerialOpen(scH_485_1))
    {
        LogE("TestRS485: open RS485_1/2 port failed!");
        return false;
    }

	fp = fopen(filename, "r");
	if (fp == NULL) {
		LogsE("open file error\n");
		return false;
	}

	while ((read = getline(&line, &linelen, fp)) != -1) {
		len = 0;
		char* pstrLine = line;
		unsigned int nValue = 0;

		while (1) {
			int ret = sscanf(pstrLine, "%02X", &nValue);

			if (EOF == ret || 0 >= ret) {
				break;
			}

			tmpBuff[len] = nValue;
			//LogsD("%02X\n", tmpBuff[len]);
			len++;
			pstrLine += 3;
		}

		if (len > 0) {
			LogsD("Send Data => ");
			for(int j = 0; j < len; j++) {
				LogsD("%02X ", tmpBuff[j]);
			}
			LogsD("\n");

			/* Send the read data */
			if (SC_SerialWrite(scH_485_1, tmpBuff, len) != FAILURE)
			{
				memset(tmpBuff, 0, sizeof(BYTE)*500);
				len = 0;

				/* Receive the data */
				if ((len = SC_SerialRead(scH_485_1, tmpBuff, sizeof(tmpBuff))) != FAILURE)
				{
					LogsD("Receive Data <== ");
					for(int j = 0; j < len; j++) {
						LogsD("%02X ", tmpBuff[j]);
					}
					LogsD("\n");
				}
				else
				{
					LogE("Couldn't receive data from the channel");
				}
			}
		}

		memset(tmpBuff, 0, sizeof(BYTE)*500);
		len = 0;
     }

	 return bResult;
}
