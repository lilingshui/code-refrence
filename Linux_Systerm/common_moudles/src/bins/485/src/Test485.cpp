/**************************************************************
* Test485.cpp
* Copyright (C) 2016 CHANGSHA WILLFAR INFORMATION Ltd.
* Author: Shuiming Peng(pengshuiming@wasion.com)
* Date: 2016.12.26
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include "logexport.h"
#include "485_util.h"
#include "serialparam.h"
#include "utils.h"

#define PROGRAM_NAME "rs485_test"

void usage(int status)
{
	if(0 == status)
	{
		fprintf(stdout,
			"#################### rs485_test %s     #############################\n"
			"#################### usage: %s [OPTIONS] #####################\n"
			"###### Single channel: rs485_test -S -p 3 -b 4800 -s 1 -d 8 -c 2 #####\n"
			"####### Multi channel: rs485_test -M -p 3 -q 4 -b 4800 ###############\n"
			"  -h, --help           Display this help output\n"
			"  -p, --port1          Channel ttyS[p] to test\n"
			"  -q, --port2          Channel ttyS[q] to test\n"
			"  -b, --baudrate       Baudrate speed default is 4800\n"
			"  -s, --stopbit        Stopbit 0: COM_STOPBITS1 1: COM_STOPBITS15 2: COM_STOPBITS2\n"
			"                       default is COM_STOPBITS1\n"
			"  -d, --databit        Databit default is 8\n"
			"  -c, --checkbit       Checkbit 0:PARITY_ODD 1:PARITY_EVEN 2:PARITY_NONE default is PARITY_ODD\n"
			"  -v, --version        Version of the tool\n"
			"  -S, --simple         Simple channel\n"
			"  -M, --multi          Multi channels\n"
			"  -f, --file           File contain the frame to send just used in Singel channel mode\n"
			"  -l, --loop			Loop Test\n"
			"  -D, --Debug			Debug Mode\n",
			VERSION,
			PROGRAM_NAME);
	}
	else if(1 == status)
	{
		fprintf(stderr,
			"#################### rs485_test %s     #############################\n"
			"#################### usage: %s [OPTIONS] #####################\n"
			"###### Single channel: rs485_test -S -p 3 -b 4800 -s 1 -d 8 -c 2 #####\n"
			"####### Multi channel: rs485_test -M -p 3 -q 4 -b 4800 ###############\n"
			"  -h, --help           Display this help output\n"
			"  -p, --port1          Channel ttyS[p] to test\n"
			"  -q, --port2          Channel ttyS[q] to test\n"
			"  -b, --baudrate       Baudrate speed default is 4800\n"
			"  -s, --stopbit        Stopbit 0: COM_STOPBITS1 1: COM_STOPBITS15 2: COM_STOPBITS2\n"
			"                       default is COM_STOPBITS1\n"
			"  -d, --databit        Databit default is 8\n"
			"  -c, --checkbit       Checkbit 0:PARITY_ODD 1:PARITY_EVEN 2:PARITY_NONE default is PARITY_EVEN\n"
			"  -v, --version        Version of the tool\n"
			"  -S, --simple         Simple channel\n"
			"  -M, --multi          Multi channels\n"
			"  -f, --file           File contain the frame to send just used in Singel channel mode\n"
			"  -l, --loop			Loop Test\n"
			"  -D, --Debug          Debug Mode\n",
			VERSION,
			PROGRAM_NAME);

	}
	else if (2 == status)
	{
		fprintf(stdout, "%s \n", VERSION);
	}

	exit(0);
}

static const char short_options[] = "hp:q:b:s:d:c:f:lvSMD";
static const struct option long_options[] = {
	{ "help", no_argument, 0, 'h' },
	{ "port1", required_argument, 0, 'p' },
	{ "port2", required_argument, 0, 'q' },
	{ "baudrate", required_argument, 0, 'b' },
	{ "stopbit", required_argument, 0, 's' },
	{ "databit", required_argument, 0, 'd' },
	{ "checkbit", required_argument, 0, 'c' },
	{ "version", no_argument, 0, 'v' },
	{ "simple", no_argument, 0, 'S' },
	{ "multi", no_argument, 0, 'M' },
	{ "file", required_argument, 0, 'f' },
	{ "loop", no_argument, 0, 'l' },
	{ "debug", no_argument, 0, 'D' },
	{0, 0, 0, 0},
};

int main(int argc, char *argv[])
{
	int nChannel_1 = 0;
	int nChannel_2 = 0;
	int nbaudrate = 4800;
	int nstopbit = 0;
	int ndatabit = 8;
	int ncheckbit = PARITY_EVEN;
	bool bSingleChannel = false;
	bool bMultichannel = false;
	bool bDebugMode = false;
	int noption = 0;
	int option_index = 0;
	bool bloop = false;
	bool bresult = false;
	char strfile[256] = {0};

	while((noption = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch (noption)
		{
			case 'h':
				usage(0);
				break;
			case '?':
				usage(1);
				break;
			case 'v':
				usage(2);
				break;
			case 'p':
				nChannel_1 = atol(optarg);
				break;
			case 'q':
				nChannel_2 = atol(optarg);
				break;
			case 'b':
				nbaudrate = strtol(optarg, NULL, 0);
				break;
			case 's':
				nstopbit = atol(optarg);
				break;
			case 'd':
				ndatabit = atol(optarg);
				break;
			case 'c':
				ncheckbit = atol(optarg);
				break;
			case 'S':
				bSingleChannel = true;
				break;
			case 'M':
				bMultichannel = true;
				break;
			case 'f':
				strncpy(strfile, optarg, (sizeof(strfile) - 1));
				strfile[sizeof(strfile) - 1] = '\0';
				break;
			case 'l':
				bloop = true;
				break;
			case 'D':
				bDebugMode = true;
				break;
		}
	}

	/* if strfile has been assigned but not test in single channel then exit */
	if (strlen(strfile) > 0 && !bSingleChannel)
	{
		usage(1);
	}

	if (bDebugMode)
	{
		SetLogLevel(LEVEL_DEBUG);
	}
	else if (bloop)
	{
		SetLogLevel(LEVEL_ERROR);
	}
	else
	{
		SetLogLevel(LEVEL_FATAL);
	}

	if(bSingleChannel)
	{
		LogD("=== Channel_1 is ttyS%d ===", nChannel_1);
		LogD("=== nstopbit is %d ===", nstopbit);
		LogD("=== ndatabit is %d ===", ndatabit);
		LogD("=== ncheckbit is %d ===", ncheckbit);
	}
	else
	{
		LogD("=== Channel_1 is ttyS%d ===", nChannel_1);
		LogD("=== Channel_2 is ttyS%d ===", nChannel_2);
	}

	LogD("=== nbaudrate is %d ===", nbaudrate);
	LogD("=== bDebugMode is %d ===", bDebugMode);

	if (bSingleChannel)
	{
		if (strlen(strfile) > 0)
		{
			LogD("=== file name is %s ===", strfile);
			bresult = TestChannelByFile(nChannel_1, strfile, nbaudrate, nstopbit, ndatabit, ncheckbit);
		}
		else
		{
			bresult = TestSingle485Channel(nChannel_1, nbaudrate, nstopbit, ndatabit, ncheckbit);
		}
	}
	else if (bMultichannel)
	{
		bresult = TestTwo485Channel(nChannel_1, nChannel_2, nbaudrate, bloop);
		if (bresult)
		{
			printf("正常");
		}
		else
		{
			printf("异常");
		}
	}
	else
	{
		LogF("输入参数错误");
	}

	return 0;
}
