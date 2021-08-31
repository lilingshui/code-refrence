#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cJSON.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "LeIotManager.h"
#include "ioctl.h"

CLeIotManager* CLeIotManager::m_pInstance  = NULL;
map<string, PGetCallback>	CLeIotManager::m_GetCallBack = CLeIotManager::CreateGetMap();
map<string, PSetCallback>	CLeIotManager::m_SetCallBack = CLeIotManager::CreateSetMap();
map<string, PServiceCallback>	CLeIotManager::m_ServiceCallBack = CLeIotManager::CreateServiceMap();

CLeIotManager::CLeIotManager()
{
}

CLeIotManager::~CLeIotManager()
{
	m_GetCallBack.clear();
	m_SetCallBack.clear();
	m_ServiceCallBack.clear();
}

CLeIotManager* CLeIotManager::GetInstance()
{
	if (NULL == m_pInstance) {
		m_pInstance = new CLeIotManager();
	}
	
	return m_pInstance;
}

void CLeIotManager::ReleaseInstance()
{
	if (NULL != m_pInstance) {
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

GetMap CLeIotManager::CreateGetMap()
{
	GetMap tmp_map;
	tmp_map.insert(pair<string, PGetCallback>("INVALID", NULL)); 
	return tmp_map;
}

SetMap CLeIotManager::CreateSetMap()
{
	SetMap tmp_map;
	tmp_map.insert(pair<string, PSetCallback>("INVALID", NULL)); 
	return tmp_map;
}

ServiceMap CLeIotManager::CreateServiceMap()
{
	ServiceMap tmp_map;
	tmp_map.insert(pair<string, PServiceCallback>("INVALID", NULL)); 
	return tmp_map;
}

bool CLeIotManager::Init()
{
	bool    ret = false;
	log_init(TAG_NAME, LOG_STDOUT, LOG_LEVEL_DEBUG, LOG_MOD_BRIEF);
	log_i(TAG_NAME, "ttu startup\r\n");

    if (LE_SUCCESS != (ret = leda_init(5)))
    {
        log_e(TAG_NAME, "leda_init failed\r\n");
        return ret;
    }
	
	/* 解析配置 */
    if (LE_SUCCESS != (ret = Get_and_parse_deviceconfig()))
    {
        log_e(TAG_NAME, "parse device config failed\r\n");
        return ret;
    }
	
	return true;
}

void CLeIotManager::Exit()
{
	leda_exit();
}

int CLeIotManager::Get_and_parse_deviceconfig()
{
	int                         ret             = LE_SUCCESS;
    int                         size            = 0;
    char                        *device_config  = NULL;

    char                        *productKey     = NULL;
    char                        *deviceName     = NULL;

    cJSON                       *devices           = NULL;
    cJSON                       *item           = NULL;
    cJSON                       *result         = NULL;

    leda_device_callback_t      device_cb;
    device_handle_t             dev_handle      = -1;

    /* 获取驱动设备配置 */
    size = leda_get_device_info_size();
    if (size >0)
    {
        device_config = (char*)malloc(size);
        if (NULL == device_config)
        {
            log_e(TAG_NAME, "allocate memory failed\n");
            return LE_ERROR_INVAILD_PARAM;
        }

        if (LE_SUCCESS != (ret = leda_get_device_info(device_config, size)))
        {
            log_e(TAG_NAME, "get device config failed\n");
            return ret;
        }
    }

    /* 解析驱动设备配置 */
    devices = cJSON_Parse(device_config);
    if (NULL == devices)
    {
        log_e(TAG_NAME, "device config parser failed\n");
        return LE_ERROR_INVAILD_PARAM;
    }

    cJSON_ArrayForEach(item, devices)
    {
        if (cJSON_Object == item->type)
        {
            /* 解析配置内容 */
            result      = cJSON_GetObjectItem(item, "productKey");
            productKey  = result->valuestring;
            
            result      = cJSON_GetObjectItem(item, "deviceName");
            deviceName  = result->valuestring;

            result      = cJSON_GetObjectItem(item, "custom");
            if (NULL != result)
            {
                log_i(TAG_NAME, "custom content: %s\n", cJSON_PrintUnformatted(result));
            }

            /* 注册并上线设备 */
            device_cb.get_properties_cb            = &(CLeIotManager::get_properties_callback_cb);
            device_cb.set_properties_cb            = &(CLeIotManager::set_properties_callback_cb);
            device_cb.call_service_cb              = &(CLeIotManager::call_service_callback_cb);
            device_cb.service_output_max_count     = 5;

            dev_handle = leda_register_and_online_by_device_name(productKey, deviceName, &device_cb, NULL);
            if (dev_handle < 0)
            {
                log_e(TAG_NAME, "product:%s device:%s register failed\n", productKey, deviceName);
                continue;
            }

            m_devHandleList[m_ndevHandleCount++] = dev_handle;
            log_i(TAG_NAME, "product:%s device:%s register success\n", productKey, deviceName);
        }
    }

    if (NULL != devices)
    {
        cJSON_Delete(devices);
    }

    free(device_config);
    return LE_SUCCESS;
}

int CLeIotManager::get_properties_callback_cb(device_handle_t dev_handle, 
						   leda_device_data_t properties[], 
						   int properties_count, 
						   void *usr_data)
{
	int i = 0;
	for (i = 0; i < properties_count; i++)
	{
		log_i(TAG_NAME, "set_property type:%d %s: %s\r\n", properties[i].type, properties[i].key, properties[i].value);

		map<string, PGetCallback>::iterator it_find; 
		it_find = m_GetCallBack.find(properties[i].key); 
		if (it_find != m_GetCallBack.end()){
			PGetCallback pFunc = it_find->second;
			(*pFunc)(properties, properties_count, usr_data);
		} 
	}

	return LE_SUCCESS;	
}
						   
int CLeIotManager::set_properties_callback_cb(device_handle_t dev_handle, 
						   const leda_device_data_t properties[], 
						   int properties_count, 
						   void *usr_data)
{
	int i = 0;
	for (i = 0; i < properties_count; i++)
	{
		log_i(TAG_NAME, "set_property type:%d %s: %s\r\n", properties[i].type, properties[i].key, properties[i].value);
		   
		map<string, PSetCallback>::iterator it_find; 
		it_find = m_SetCallBack.find(properties[i].key); 
		if (it_find != m_SetCallBack.end()){
			PSetCallback pFunc = it_find->second;
			(*pFunc)(properties, properties_count, usr_data);
		} 
	}

	return LE_SUCCESS;						   
}
						   
int CLeIotManager::call_service_callback_cb(device_handle_t dev_handle, 
						   const char *service_name, 
						   const leda_device_data_t data[], 
						   int data_count, 
						   leda_device_data_t output_data[], 
						   void *usr_data)
{
	log_i(TAG_NAME, "service_name is %s\r\n", service_name);
	   
	map<string, PServiceCallback>::iterator it_find; 
	it_find = m_ServiceCallBack.find(service_name); 
	if (it_find != m_ServiceCallBack.end()){
		PServiceCallback pFunc = it_find->second;
		(*pFunc)(service_name, data, data_count, output_data, usr_data);
	} 

	return LE_SUCCESS;	
}

int CLeIotManager::ReportProperties(const leda_device_data_t properties[], int properties_count)
{
	leda_report_properties(m_devHandleList[0], properties, properties_count);
	return 0;
}

int CLeIotManager::ReportEvent(const char *event_name, const leda_device_data_t data[], int data_count)
{
	leda_report_event(m_devHandleList[0], "event_name", data, data_count);
	return 0;
}

void CLeIotManager::RegisterSetCallback(string strKey, PSetCallback pFunc)
{
    m_SetCallBack.insert(pair<string, PSetCallback>(strKey, pFunc)); 
}

void CLeIotManager::RegisterGetCallback(string strKey, PGetCallback pFunc)
{
	m_GetCallBack.insert(pair<string, PGetCallback>(strKey, pFunc));
}

void CLeIotManager::RegisterServiceCallback(string strKey, PServiceCallback pFunc)
{
	m_ServiceCallBack.insert(pair<string, PServiceCallback>(strKey, pFunc));
}

