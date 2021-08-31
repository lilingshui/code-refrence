/**************************************************************
* ntpclient.cpp
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.11
**************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "ntpclient.h"
#include "ntptime.h"
#include "ntpsocket.h"

int N_TIME_ZONE = 0;

CNtpClient::CNtpClient()
{
	m_dwTimeout = 5000; //Default timeout of 5 seconds
}

BOOL CNtpClient::GetServerTime(const char* pszHostName, NtpServerResponse& response, int nPort)
{
	//Create the socket, Allocated of the heap so we can control
	//the time when it's destructor is called. This means that
	//we can call SetLastError after its destructor
	CNtpSocket* pSocket = new CNtpSocket();
	if (!pSocket->Create())
	{
		printf("Failed to create client socket\n");
		return FALSE;
	}

	//Connect to the SNTP server
	if (!pSocket->Connect(pszHostName, nPort))
	{
		printf("Could not connect to the SNTP server %s on port %d\n", pszHostName, nPort);
		delete pSocket;
		pSocket = NULL;
		return FALSE;
	}
	else
	{
		//Initialise the NtpBasicInfo packet
		NtpBasicInfo nbi;
		int nSendSize = sizeof(NtpBasicInfo);
		memset(&nbi, 0, nSendSize);
		
		nbi.m_LiVnMode = 27; //Encoded representation which represents NTP Client Request & NTP version 3.0
		nbi.m_TransmitTimestamp = CNtpTime::GetCurrentTime();

		//Send off the NtpBasicInfo packet
		if (!pSocket->Send((const char*) &nbi, nSendSize))
		{
			printf("Failed in call to send NTP request to the SNTP server\n");
			delete pSocket;
			pSocket = NULL;
			return FALSE;
		}

		//Need to use select to determine readibilty of socket
		if (!pSocket->IsReadable(m_dwTimeout))
		{
			printf("Unable to wait for NTP reply from the SNTP server\n");
			//Tidy up prior to returning
			delete pSocket;
			pSocket = NULL;
			return FALSE;
		}
		response.m_DestinationTime = CNtpTime::GetCurrentTime();

		//read back the response into the NtpFullPacket struct
		NtpFullPacket nfp;
		int nReceiveSize = sizeof(NtpFullPacket);
		memset(&nfp, 0, nReceiveSize);
		if (!pSocket->Receive((char*) &nfp, nReceiveSize))
		{
			printf("Unable to read reply from the SNTP server\n");
			//Tidy up prior to returning
			delete pSocket;
			pSocket = NULL;
			return FALSE;
		}

		//Transfer all the useful info into the response structure
		response.m_nStratum = nfp.m_Basic.m_Stratum;
		response.m_nLeapIndicator = (nfp.m_Basic.m_LiVnMode & 0xC0) >> 6;
		response.m_OriginateTime = nfp.m_Basic.m_OriginateTimestamp;
		response.m_ReceiveTime = nfp.m_Basic.m_ReceiveTimestamp;
		response.m_TransmitTime = nfp.m_Basic.m_TransmitTimestamp;
		response.m_RoundTripDelay = (response.m_DestinationTime - response.m_OriginateTime) - (response.m_ReceiveTime - response.m_TransmitTime);
		response.m_LocalClockOffset = ((response.m_ReceiveTime - response.m_OriginateTime) + (response.m_TransmitTime - response.m_DestinationTime)) / 2;

		delete pSocket;
		pSocket = NULL;
		return TRUE;
	}
}

BOOL CNtpClient::SetClientTime(const CNtpTime& NewTime)
{
	struct tm _tm;  
	struct timeval tv;  
	time_t timep;
	SYSTEMTIME st = NewTime;

	_tm.tm_year = st.wYear - 1900;
	_tm.tm_mon = st.wMonth - 1;
	_tm.tm_wday = st.wDayOfWeek;
	_tm.tm_mday = st.wDay;
	_tm.tm_hour = st.wHour;
	_tm.tm_min = st.wMinute;
	_tm.tm_sec = st.wSecond;

	timep = mktime(&_tm);
	tv.tv_sec = timep;
	tv.tv_sec += 3600 * N_TIME_ZONE;//加上北京时间的时区 
	tv.tv_usec = st.wMilliseconds * 1000; 

	if(settimeofday (&tv, (struct timezone *) 0) < 0)  
	{  
		printf("Set system datatime error!/n");  
		return FALSE;  
	} 

	return TRUE;
}


