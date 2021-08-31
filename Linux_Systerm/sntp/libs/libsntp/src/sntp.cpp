/**************************************************************
* sntp.cpp
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.20
**************************************************************/

#include <stdio.h>
#include "sntp.h"
#include "ntpclient.h"

extern int N_TIME_ZONE;

bool SNTP_Synchronize(const char* serverAddress, int nPort, int nTimeZone)
{
	N_TIME_ZONE = nTimeZone;
	CNtpClient sntp;
	NtpServerResponse response;

	if (sntp.GetServerTime(serverAddress, response, nPort))
	{		
		CNtpTime newTime(CNtpTime::GetCurrentTime() + response.m_LocalClockOffset);
		if (sntp.SetClientTime(newTime))
		{	
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
	return false;
}
