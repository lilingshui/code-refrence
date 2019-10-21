/**************************************************************
* ntpsocket.cpp
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.11
**************************************************************/
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "ntpsocket.h"

CNtpSocket::CNtpSocket()
{
	m_hSocket = -INVALID_SOCKET; //default to an invalid scoket descriptor
}

CNtpSocket::~CNtpSocket()
{
	Close();
}

BOOL CNtpSocket::Create()
{
	//NTP Uses UDP instead of the usual TCP
	m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);
	return (m_hSocket != INVALID_SOCKET);
}

BOOL CNtpSocket::Connect(const char* pszHostAddress, int nPort)
{
	//Determine if the address is in dotted notation
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short)nPort);
	sockAddr.sin_addr.s_addr = inet_addr(pszHostAddress);	

	//If the address is not dotted notation, then do a DNS 
	//lookup of it.
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		struct hostent* lphost;	
		lphost = gethostbyname(pszHostAddress);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((in_addr*)lphost->h_addr)->s_addr;
		else
			return FALSE;
	}

	//Call the protected version which takes an address 
	//in the form of a standard C style struct.
	return Connect((struct sockaddr*)&sockAddr, sizeof(sockAddr));
}

BOOL CNtpSocket::Connect(const struct sockaddr* lpSockAddr, int nSockAddrLen)
{
	int nConnect = connect(m_hSocket, lpSockAddr, nSockAddrLen);
	return (nConnect == 0);
}

BOOL CNtpSocket::Send(const char* pszBuf, int nBuf)
{
	//must have been created first
	return (send(m_hSocket, pszBuf, nBuf, 0) != SOCKET_ERROR);
}

int CNtpSocket::Receive(char* pszBuf, int nBuf)
{
	//must have been created first
	return recv(m_hSocket, (void*)pszBuf, nBuf, 0); 
}

void CNtpSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		close(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
}

BOOL CNtpSocket::IsReadable(DWORD dwTimeout)
{
	BOOL bReadable = FALSE;
	timeval timeout;
	timeout.tv_sec = dwTimeout / 1000;
	timeout.tv_usec = dwTimeout % 1000;

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(m_hSocket, &fds);
	int nStatus = select(m_hSocket + 1, &fds, NULL, NULL, &timeout);

	if (SOCKET_ERROR == nStatus || 0 == nStatus)
	{
		bReadable = FALSE;
	}
	else
	{
		bReadable = TRUE;
	}

	return bReadable;
}

