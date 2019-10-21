#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cJSON.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "ioctl.h"
#include "LeIotManager.h"
#include "Beeper.h"

static CLeIotManager* g_pLeInstance = NULL;

int main(int argc,char *argv[])
{
	CBeeper beeper;
	char   szSwitchStatus[32] = {0};

	g_pLeInstance = CLeIotManager::GetInstance();
	g_pLeInstance->Init();
	g_pLeInstance->RegisterSetCallback("Workingswitch", &(CBeeper::set_properties_callback_cb));
	g_pLeInstance->RegisterGetCallback("Workingswitch", &(CBeeper::get_properties_callback_cb));
	g_pLeInstance->RegisterServiceCallback("WorkingService", &(CBeeper::call_service_callback_cb));
	
	/* 对已上线设备每隔5秒钟上报一次开关状态 */
	while (1)
	{
		if (beeper.GetSwitchStatus())
		{
			strcpy(szSwitchStatus, "1");
		}
		else
		{
			strcpy(szSwitchStatus, "0");   
		}

		/* report device properties */
		leda_device_data_t dev_proper_data;
		dev_proper_data.type = LEDA_TYPE_BOOL;
		strcpy(dev_proper_data.key, "Workingswitch");
		strcpy(dev_proper_data.value, szSwitchStatus); 
		g_pLeInstance->ReportProperties(&dev_proper_data, 1);
		sleep(5);
	}

	g_pLeInstance->Exit();
	CLeIotManager::ReleaseInstance();
	return LE_SUCCESS;
}

