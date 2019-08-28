/**************************************************************
* led.cpp
* Copyright (C) 2019 
* Author: lilingshui(lilingshui@126.com)
* Date: 2019.08.27
**************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>
#include "hal.h"
#include "led.h"

led_module_t HAL_MODULE_INFO_SYM =
{
        common:
        {
                szName:"led",
                nVer:0,
                szAuthor:"lilingshui",
                nFactory:0,
                szBuildDate:"2019-08-27",
                szDevices:{"led"},    
                pfOpen:open_led,
                pfClose:led_close_device,
        },
};

int32 open_led(const struct tag_HW_MODULE *module, const char* device_id, struct tag_HW_DEVICE **device)
{
	led_device_t* dev = (led_device_t*)malloc(sizeof(led_device_t));
	if(dev == NULL)
	{
		return -1;
	}
	memset(dev, 0, sizeof(*dev));
	dev->common.nVer = 0;
	dev->common.szDeviceID= "led";
	dev->common.pModule = (struct tag_HW_MODULE *)module;
	printf("===== open_led =====\n");

	/*
	dev->fd = open(device_id, O_RDWR);
	
	if(dev->fd == -1) 
	{
		free(dev);
		return -1;
	}
	*/

	dev->set_onoff = led_set_onoff;
	dev->close_led_device = led_close_device;
	dev->get_status = get_status;
	*device = (struct tag_HW_DEVICE*)dev;
	return 0;
}

int32 led_set_onoff(led_device_t* dev, int32 val)
{
	printf("===== In hal_led module led_set_onoff =====\n");
	//write(dev->fd, &val, sizeof(val));
	return 0;
}

int32 get_status(led_device_t* dev, int32* val) 
{
	if (NULL == val)
	{
		return -1;
	}

	printf("===== In hal_led module get_status =====\n");
	//read(dev->fd, val, sizeof(*val));
	return 0;
}

int32 led_close_device(struct tag_HW_DEVICE* device) 
{
	led_device_t*led_device = (led_device_t*)device;
	if(led_device) 
	{
		//close(led_device->fd);
		free(led_device);
		printf("===== In hal_led module free the memory =====\n");
	}

	printf("===== In hal_led module led_close_device =====\n");
	return 0;
}
