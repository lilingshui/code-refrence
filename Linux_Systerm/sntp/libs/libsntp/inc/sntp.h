/**************************************************************
* sntp.h
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.20
**************************************************************/

#ifndef _SNTP_H_
#define _SNTP_H_


#ifdef __cplusplus
extern "C" {
#endif
bool SNTP_Synchronize(const char* serverAddress, int nPort, int nTimeZone);
#ifdef __cplusplus
}
#endif

#endif /*_SNTP_H_*/
