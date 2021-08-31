/**************************************************************
* serialcomexport.h
* Copyright (C) 2016 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2016.12.16
**************************************************************/

#ifndef _SERIAL_COM_EXPORT_H_
#define _SERIAL_COM_EXPORT_H_

#include "serialparam.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*�����������ٴ���*/
	SC_HANDLER SC_SerialCreate(S_COMM_PARA scParam);
	bool SC_SerialDestroy(SC_HANDLER sc_handler);

	/*�򿪻��߹رմ��� */
	bool SC_SerialOpen(SC_HANDLER sc_handler);
	bool SC_SerialClose(SC_HANDLER sc_handler);

	/*���ڶ�д*/
    int SC_SerialRead(SC_HANDLER sc_handler, unsigned char *rbuff, int len);
	int SC_SerialReadEx(SC_HANDLER sc_handler, unsigned char *rbuff, int len, int nMillisecond);
    int SC_SerialWrite(SC_HANDLER sc_handler, const unsigned char *wbuff, int len);
    void SC_Flush(SC_HANDLER sc_handler);

	/*���ô��ڲ���*/
    bool SC_ChangeBaudrate(SC_HANDLER sc_handler, int speed);
    bool SC_ChangePort(SC_HANDLER sc_handler, unsigned char com);

#ifdef __cplusplus
}
#endif

#endif /*_SERIAL_COM_EXPORT_H_*/
