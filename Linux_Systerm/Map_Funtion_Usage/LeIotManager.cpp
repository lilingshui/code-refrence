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
map<string, PGetCallback>	CLeIotManager::m_GetCallBack={{"test", NULL}};
map<string, PSetCallback>	CLeIotManager::m_SetCallBack={{"test", NULL}};
map<string, PServiceCallback>	CLeIotManager::m_ServiceCallBack={{"test", NULL}};

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

bool CLeIotManager::Init()
{
	bool    ret = false;
	char*  module_name = NULL;

	log_init(TAG_NAME, LOG_STDOUT, LOG_LEVEL_DEBUG, LOG_MOD_BRIEF);
	log_i(TAG_NAME, "ttu startup\r\n");

    /* 初始驱动 */
    module_name = leda_get_module_name();
    if (NULL == module_name)
    {
        log_e(TAG_NAME, "the driver no deploy or deploy failed\r\n");
        return ret;
    }

    if (LE_SUCCESS != (ret = leda_init(module_name, 5)))
    {
        log_e(TAG_NAME, "leda_init failed\r\n");
        return ret;
    }

    /* 解析配置 */
    if (LE_SUCCESS != (ret = Get_and_parse_deviceconfig(module_name)))
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

int CLeIotManager::Get_and_parse_deviceconfig(const char* module_name)
{
    int ret = LE_SUCCESS;
    int size = 0;
    char *device_config = NULL;
    char *productKey = NULL;
    char *deviceName = NULL;
    cJSON *root = NULL;
    cJSON *object = NULL;
    cJSON *item = NULL;
    cJSON *result = NULL;

    leda_device_callback_t      device_cb;
    device_handle_t             dev_handle      = -1;

    /* 获取驱动设备配置 */
    size = leda_get_config_size(module_name);
    if (size >0)
    {
        device_config = (char*)malloc(size);
        if (NULL == device_config)
        {
            log_e(TAG_NAME, "allocate memory failed\r\n");
            return LE_ERROR_INVAILD_PARAM;
        }

        if (LE_SUCCESS != (ret = leda_get_config(module_name, device_config, size)))
        {
            log_e(TAG_NAME, "get device config failed\r\n");
            return ret;
        }
    }

    /* 解析驱动设备配置 */
    root = cJSON_Parse(device_config);
    if (NULL == root)
    {
        log_e(TAG_NAME, "device config parser failed\r\n");
        return LE_ERROR_INVAILD_PARAM;
    }

    object = cJSON_GetObjectItem(root, "deviceList");
    cJSON_ArrayForEach(item, object)
    {
        if (cJSON_Object == item->type)
        {
            /* 按照配置格式解析内容 */
            result = cJSON_GetObjectItem(item, "productKey");
            productKey = result->valuestring;
            
            result = cJSON_GetObjectItem(item, "deviceName");
            deviceName = result->valuestring;

            /* TODO: 解析设备自定义配置信息custom，该字段内容来源在云端控制台的驱动配置项。由于该字段内容
               为字符串的json内容，所以在去除custom的value值后，需要再次进行json解析操作。
            */

            /* 注册并上线设备 */
            device_cb.get_properties_cb            = &(CLeIotManager::get_properties_callback_cb);
            device_cb.set_properties_cb            = &(CLeIotManager::set_properties_callback_cb);
            device_cb.call_service_cb              = &(CLeIotManager::call_service_callback_cb);
            device_cb.service_output_max_count     = 5;

            dev_handle = leda_register_and_online_by_device_name(productKey, deviceName, &device_cb, NULL);
            if (dev_handle < 0)
            {
                log_e(TAG_NAME, "product:%s device:%s register failed\r\n", productKey, deviceName);
                continue;
            }
            m_devHandleList[m_ndevHandleCount++] = dev_handle;
            log_i(TAG_NAME, "product:%s device:%s register success\r\n", productKey, deviceName);
        }
    }

    if (NULL != root)
    {
        cJSON_Delete(root);
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

