/**************************************************************
* main.cpp
* Copyright (C) 2018 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2018.04.11
**************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sntp.h"
#include "xmlutil.h"
#include "utils.h"

#ifndef PATH_MAX
#define PATH_MAX 256
#endif

int main(int argc, char* argv[])
{
	char applicationPath[PATH_MAX] = {0};
	char processname[1024];
	char config_file[PATH_MAX] = {0};	

	if (-1 == get_executable_path(applicationPath, processname, sizeof(applicationPath)))
	{
		perror("can not get executable path");
		return -1;
	}

	snprintf(config_file, sizeof(config_file),"%sconf/setting.xml", applicationPath);

	char serverAddress[256] = { 0 };
	char strTimeZone[32] = { 0 };
	
	open_xml_file(config_file);
	get_xml_node_attr_value((char *)"//wasion/server", (char *) "address", serverAddress);
	get_xml_node_attr_value((char *)"//wasion/timezone", (char *) "value", strTimeZone);
	close_xml_file();
	
	int nport = 123;
	int nTimeZone = atoi(strTimeZone);
	if (SNTP_Synchronize(serverAddress, nport, nTimeZone))
	{
		printf("Successs to sync system time correct\n");
	}
	else
	{
		printf("Failed to sync system time correct\n");
	}

	return 0;
}

