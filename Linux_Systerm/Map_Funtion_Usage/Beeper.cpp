#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cJSON.h>
#include <string.h>
#include <fcntl.h>
#include "Beeper.h"
#include "ioctl.h"

bool CBeeper::m_swStatus = false;
CBeeper::CBeeper()
{
	m_swStatus = false;
}

CBeeper::~CBeeper()
{
}

bool CBeeper::GetSwitchStatus()
{
	return m_swStatus;
}

int CBeeper::get_properties_callback_cb(leda_device_data_t properties[], 
				   int properties_count, 
				   void *usr_data)
{
	int i = 0;
    for (i = 0; i < properties_count; i++)
    {
        log_i(TAG_NAME, "get_property %s: ", properties[i].key);

        if (!strcmp(properties[i].key, "temperature"))
        {
            /* 作为演示，填写获取属性数据为模拟数据 */
            properties[i].type = LEDA_TYPE_INT;
            sprintf(properties[i].value, "%d", 30);

            log_i(TAG_NAME, "%s\r\n",  properties[i].value);
        }
    }

    return LE_SUCCESS;				   
}
				   
int CBeeper::set_properties_callback_cb(const leda_device_data_t properties[], 
				   int properties_count, 
				   void *usr_data)
{
	int i = 0;
    for (i = 0; i < properties_count; i++)
    {
        /* 作为演示，仅打印出设置属性信息 */
        log_i(TAG_NAME, "set_property type:%d %s: %s\r\n", properties[i].type, properties[i].key, properties[i].value);
	
		if (!strcmp("Workingswitch", properties[i].key))
		{
			/*
			int fd = open(BEEP_DEV_NAME, O_RDWR);
			
			if(fd < 0) {
				log_e(TAG_NAME, "===== close the beeper ====\r\n");
				return LE_SUCCESS;
			}
			*/
			
			if (!strcmp("0", properties[i].value))
			{
				m_swStatus = false;
				//ioctl(fd, IOC_WFET_BEEP_ONOFF, 0);
				log_i(TAG_NAME, "===== close the beeper ====\r\n");
			}
			else if (!strcmp("1", properties[i].value))
			{
				m_swStatus = true;
				//ioctl(fd, IOC_WFET_BEEP_ONOFF, 1);
				log_i(TAG_NAME, "===== open the beeper ====\r\n");
			}
			
			//close(fd);
		}	
    }

    return LE_SUCCESS;				   
}
			   
int CBeeper::call_service_callback_cb(const char *service_name, 
						   const leda_device_data_t data[], 
						   int data_count, 
						   leda_device_data_t output_data[], 
						   void *usr_data)
{
	int i = 0;

    /* service_name为该驱动物模型自定义方法名称 */
    log_i(TAG_NAME, "service_name: %s\r\n", service_name);
    
    /* 获取service_name方法的参数名称和值信息 */
    for (i = 0; i < data_count; i++)
    {
        log_i(TAG_NAME, "input_data %s: %s\r\n", data[i].key, data[i].value);
    }

    /* 此处错位演示并没有执行真正的自定义方法 */

    return LE_SUCCESS;				   
}
