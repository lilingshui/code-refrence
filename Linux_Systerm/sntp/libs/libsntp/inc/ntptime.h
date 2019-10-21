/**************************************************************
* ntptime.h
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.11
**************************************************************/

#ifndef __NTPTIME_H__
#define	__NTPTIME_H__

#include "params.h"

class CNtpTime
{
public:
	//Constructors / Destructors
	CNtpTime();
	CNtpTime(const CNtpTime& time);
	CNtpTime(NtpTimePacket& packet);
	CNtpTime(const SYSTEMTIME& st);
	
	//General functions
	CNtpTime& operator=(const CNtpTime& time);
	double operator-(const CNtpTime& time) const;
	CNtpTime operator+(const double& timespan) const;
	operator SYSTEMTIME() const;
	operator NtpTimePacket() const;
	operator unsigned long long() const { return m_Time; };
	DWORD Seconds() const;
	DWORD Fraction() const;
	
	//Static functions
	static CNtpTime GetCurrentTime();
	static DWORD MsToNtpFraction(WORD wMilliSeconds);
	static WORD NtpFractionToMs(DWORD dwFraction);
	static double NtpFractionToSecond(DWORD dwFraction);
	
protected:
	//Internal static functions and data
	static long GetJulianDay(WORD Year, WORD Month, WORD Day);
	static void GetGregorianDate(long JD, WORD& Year, WORD& Month, WORD& Day);
	static DWORD m_MsToNtp[1000];
	
	//The actual data
	unsigned long long m_Time;
};

struct NtpServerResponse
{
	int 	m_nLeapIndicator; 
	//0: no warning
	//1: last minute in day has 61 seconds
	//2: last minute has 59 seconds
	//3: clock not synchronized
	
	int 	m_nStratum; 
	//0: unspecified or unavailable
	//1: primary reference (e.g., radio clock)
	//2-15: secondary reference (via NTP or SNTP)
	//16-255: reserved
	
	CNtpTime	m_OriginateTime;    //Time when the request was sent from the client to the SNTP server
	CNtpTime	m_ReceiveTime;      //Time when the request was received by the server
	CNtpTime	m_TransmitTime;     //Time when the server sent the request back to the client
	CNtpTime	m_DestinationTime;  //Time when the reply was received by the client
	double		m_RoundTripDelay;   //Round trip time in seconds
	double		m_LocalClockOffset; //Local clock offset relative to the server
};

#endif /*__NTPTIME_H__*/

