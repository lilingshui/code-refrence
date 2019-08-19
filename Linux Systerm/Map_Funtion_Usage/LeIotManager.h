#ifndef __LEIOTMANAGER_H__
#define __LEIOTMANAGER_H__

#include <map>  
#include <string>  
#include <iostream>  
using namespace std;

#include "log.h"
#include "le_error.h"
#include "leda.h"
#include "common.h"

#define MAX_DEVICE_NUM      32

class CLeIotManager
{
private:
	CLeIotManager();
	~CLeIotManager();

public:
	static CLeIotManager* GetInstance();
	static void ReleaseInstance();

	bool Init();
	void Exit();
	int ReportProperties(const leda_device_data_t properties[], int properties_count);
	int ReportEvent(const char *event_name, const leda_device_data_t data[], int data_count);

	void RegisterSetCallback(string strKey, PSetCallback pFunc);
	void RegisterGetCallback(string strKey, PGetCallback pFunc);
	void RegisterServiceCallback(string strKey, PServiceCallback pFunc);
	
protected:
	int Get_and_parse_deviceconfig(const char* module_name);
	static int get_properties_callback_cb(device_handle_t dev_handle, 
                               leda_device_data_t properties[], 
                               int properties_count, 
                               void *usr_data);
							   
	static int set_properties_callback_cb(device_handle_t dev_handle, 
                               const leda_device_data_t properties[], 
                               int properties_count, 
                               void *usr_data);
							   
	static int call_service_callback_cb(device_handle_t dev_handle, 
                               const char *service_name, 
                               const leda_device_data_t data[], 
                               int data_count, 
                               leda_device_data_t output_data[], 
                               void *usr_data);

private:
	static CLeIotManager* 			m_pInstance;
	static map<string, PGetCallback> 		m_GetCallBack;
	static map<string, PSetCallback> 		m_SetCallBack;
	static map<string, PServiceCallback> 		m_ServiceCallBack;
	device_handle_t 				m_devHandleList[MAX_DEVICE_NUM];
	int 					m_ndevHandleCount;	
};

#endif //__LEIOTMANAGER_H__
