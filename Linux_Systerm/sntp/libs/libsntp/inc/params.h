/**************************************************************
* params.h
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.11
**************************************************************/

#ifndef __PARAMS_H__
#define	__PARAMS_H__

#include <iostream>  
#include <string>  

#define SOCKET_ERROR	(-1)
#define INVALID_SOCKET  (-1)
#define FALSE   		0
#define TRUE    		1

typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef unsigned char	BYTE;
typedef int 		BOOL;
typedef void *		HANDLE;
typedef int		SOCKET;

const double NTP_FRACTIONAL_TO_MS = (((double)1000.0)/0xFFFFFFFF);
const double NTP_TO_SECOND = (((double)1.0)/0xFFFFFFFF);
const long JAN_1ST_1900 = 2415021;

struct NtpTimePacket
{
	DWORD m_dwInteger;
	DWORD m_dwFractional;
};

struct NtpAuthenticationInfo
{
	unsigned long m_KeyID;
	BYTE m_MessageDigest[16];
};

struct NtpBasicInfo
{
	BYTE m_LiVnMode;
	BYTE m_Stratum;
	char m_Poll;
	char m_Precision;
	long m_RootDelay;
	long m_RootDispersion;
	char m_ReferenceID[4];
	NtpTimePacket m_ReferenceTimestamp;
	NtpTimePacket m_OriginateTimestamp;
	NtpTimePacket m_ReceiveTimestamp;
	NtpTimePacket m_TransmitTimestamp;
};

struct NtpFullPacket
{
	NtpBasicInfo          m_Basic;
	NtpAuthenticationInfo m_Auth;
};

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

#endif /*__PARAMS_H__*/

