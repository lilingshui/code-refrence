#ifndef __BEEPER_H__
#define __BEEPER_H__

#include <stdbool.h>
#include "log.h"
#include "le_error.h"
#include "leda.h"
#include "common.h"

class CBeeper
{
public:
	CBeeper();
	~CBeeper();

public:
	static int get_properties_callback_cb(leda_device_data_t properties[], 
                               int properties_count, 
                               void *usr_data);
							   
	static int set_properties_callback_cb( const leda_device_data_t properties[], 
                               int properties_count, 
                               void *usr_data);
							   
	static int call_service_callback_cb(const char *service_name, 
                               const leda_device_data_t data[], 
                               int data_count, 
                               leda_device_data_t output_data[], 
                               void *usr_data);
							   
							   
	bool GetSwitchStatus();				   

private:
	static bool m_swStatus ;
							   
							   
};

#endif //__BEEPER_H__
