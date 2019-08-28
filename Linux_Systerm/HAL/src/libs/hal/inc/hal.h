/**************************************************************
* hal.h
* Copyright (C) 2019
* Author: lilingshui(lilingshui@126.com)
* Date: 2016.12.26
**************************************************************/

#ifndef __HAL_H__
#define	__HAL_H__

#include "led.h"

#ifdef __cplusplus
extern "C" {
#endif

struct tag_HW_DEVICE* hw_get_device(const char* device_id);

#ifdef __cplusplus
}
#endif

#endif /*__HAL_H__*/
