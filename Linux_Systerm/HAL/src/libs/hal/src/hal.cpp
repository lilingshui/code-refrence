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

int32 hw_get_module(const char *id, const char *path, struct tag_HW_MODULE **module)
{
	int32 i;
	int32 status = -EINVAL;
	void *handle = NULL;
	struct tag_HW_MODULE *hmi = NULL;

       	const char *sym = HAL_MODULE_INFO_SYM_AS_STR;
	handle = dlopen(path, RTLD_NOW);
	if (handle == NULL) 
	{
		char const *err_str = dlerror();
		printf("===== err_str is %s =====\n", err_str);
		status = -EINVAL;
		goto done;
	}

	hmi = (struct tag_HW_MODULE *)dlsym(handle, sym);
	if (hmi == NULL)
	{
		status = -EINVAL;
		goto done;
	}

	for (i = 0; i < HW_MODULE_MAXDEVICES; i++)
	{
		if (strcmp(id, hmi->szDevices[i]) == 0)
		{
				  status = 0;
				  break;
		}
	}

	if (i >= HW_MODULE_MAXDEVICES)
	{
		status = -EINVAL;
		goto done;
	}

	status = 0;
done:
	if (status != 0)
	{
		hmi = NULL;
		if (handle != NULL)
		{
			dlclose(handle);
			handle = NULL;
		}
	} 
	else 
	{
		*module = hmi;
	}

	return status;
}

struct tag_HW_DEVICE* hw_get_device(const char* device_id)
{
	int32 err = -EINVAL;
	struct tag_HW_MODULE *module = NULL;

	char path[64] = {0};

	if (NULL != strstr(device_id, LED_HARDWARE_MODULE_ID))
	{
		sprintf(path, "%slibhal_%s.so", HAL_LIBRARY_PATH, LED_HARDWARE_MODULE_ID);
		printf("===== hw_get_device path is %s =====\n", path);
		err = hw_get_module(device_id, path, &module);
        	led_device_t* device = (led_device_t*)malloc(sizeof(led_device_t));
        	if(device == NULL)
        	{
                	return NULL;
        	}

        	err = module->pfOpen(module, device_id, (struct tag_HW_DEVICE**)(&device));
        	return ((0 != err) ? NULL : (struct tag_HW_DEVICE*)device);
	}
	else
	{
		return NULL;
	}
}

