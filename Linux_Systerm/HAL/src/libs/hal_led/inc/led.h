/**************************************************************
* led.h
* Copyright (C) 2019
* Author: lilingshui(lilingshui@126.com)
* Date: 2019.08.27
**************************************************************/
#ifndef __LED_H__
#define	__LED_H__

#include "hal_common.h"
#define    LED_HARDWARE_MODULE_ID "led"

typedef struct led_module_t 
{
	struct tag_HW_MODULE common;
}led_module_t;

typedef struct led_device_t 
{
	struct tag_HW_DEVICE common;
	int32 fd;
	int32 (*set_onoff)(led_device_t* dev, int32 val);
	int32 (*get_status)(led_device_t* dev, int32* val);
	int32 (*close_led_device)(struct tag_HW_DEVICE* device);
}led_device_t;

int32 open_led(const struct tag_HW_MODULE* module, const char* device_id, struct tag_HW_DEVICE** device);
int32 led_close_device(struct tag_HW_DEVICE* device);

int32 led_set_onoff(led_device_t* dev, int32 val);
int32 get_status(led_device_t* dev, int32* val); 

#endif /*__LED_H__*/
