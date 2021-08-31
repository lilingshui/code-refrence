/**************************************************************
* ntpsocket.h
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.11
**************************************************************/

#ifndef __NTPSOCKET_H__
#define	__NTPSOCKET_H__
#include "params.h"

class CNtpSocket
{
public:
	//Constructors / Destructors 
	CNtpSocket();
	~CNtpSocket();
	
	//General functions
	BOOL Create();
	BOOL Connect(const char* pszHostAddress, int nPort);
	BOOL Send(const char* pszBuf, int nBuf);
	int Receive(char* pszBuf, int nBuf);
	void Close();
	BOOL IsReadable(DWORD dwTimeout);
	
protected:
	BOOL Connect(const struct sockaddr* lpSockAddr, int nSockAddrLen);
	SOCKET m_hSocket;
};

#endif /*__NTPSOCKET_H__*/

