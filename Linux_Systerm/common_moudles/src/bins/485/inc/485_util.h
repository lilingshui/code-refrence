/**************************************************************
* 485_util.h
* Copyright (C) 2016 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2016.12.26
**************************************************************/

#ifndef __485_UTILS_H__
#define	__485_UTILS_H__

#define TEST485		0x00
bool TestSingle485Channel(unsigned char channel_1, int nbaudrate, int nStopBit, int nDataBit, int nCheckBit);
bool TestTwo485Channel(unsigned char channel_1,
					   unsigned char channel_2,
					   int nbaudrate,
					   bool bloop);

bool TestChannelByFile(unsigned char channel_1, /* The channel to test */
					   char* filename, /* The file contain the frame */
					   int nbaudrate,  /* baudrate of the channel */
					   int nStopBit,   /* stop bit of the channel */
					   int nDataBit,   /* data bit of the channel */
					   int nCheckBit);  /* check bit of the channel */

#endif /*__485_UTILS_H__*/
