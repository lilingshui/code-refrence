/**************************************************************
* ntpclient.h
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.11
**************************************************************/

#ifndef __NTPCLIENT_H__
#define	__NTPCLIENT_H__

#include "params.h"
#include "ntptime.h"

//The actual SNTP class
class CNtpClient
{
public:
	//Constructors / Destructors
	CNtpClient();	
	//General functions
	BOOL  GetServerTime(const char* pszHostName, NtpServerResponse& response, int nPort = 123);
	DWORD GetTimeout() const { return m_dwTimeout; };
	void  SetTimeout(DWORD dwTimeout) { m_dwTimeout = dwTimeout; };
	BOOL  SetClientTime(const CNtpTime& NewTime);
	
protected:
	DWORD            	m_dwTimeout;
};

#endif /*__NTPCLIENT_H__*/

