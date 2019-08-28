/**************************************************************
* hal_common.h
* Copyright (C) 2019
* Author: lilingshui(lilingshui@126.com)
* Date: 2019.08.28
**************************************************************/

#ifndef __HAL_COMMON_H__
#define	__HAL_COMMON_H__

#define HW_MODULE_MAXDEVICES (64)
#define HAL_LIBRARY_PATH   "/home/psm/work/code-refrence/Linux_Systerm/HAL/bin/lib/"
#define HAL_MODULE_INFO_SYM_AS_STR  "HMI"
#define HAL_MODULE_INFO_SYM  HMI

typedef int int32;
typedef unsigned int uint32;
 
typedef struct tag_HW_MODULE 
{ 
	const char *szName;
	uint32 nVer;
	const char *szAuthor;
	uint32 nFactory;
	const char *szBuildDate;
	const char *szDevices[HW_MODULE_MAXDEVICES];
	int32 (*pfOpen)(const struct tag_HW_MODULE *pModule, const char*szDeviceID, struct tag_HW_DEVICE**ppDevice); 
	int32 (*pfClose)(struct tag_HW_DEVICE *pDevice); 
}HW_MODULE;

typedef struct tag_HW_DEVICE  
{ 
	struct tag_HW_MODULE	*pModule;
	int32 			nVer;
	const char		*szDeviceID;
}HW_DEVICE;

#endif /*__HAL_COMMON_H__*/
