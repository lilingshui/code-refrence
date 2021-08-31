#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include "logexport.h"

class CLog {
public:
	~CLog();
	static CLog *GetInstance(void);
	static bool ReleaseInstance(void);
	void SetLogLevel(LOG_LEVEL minLevel);
	void Log(LOG_LEVEL level, const char *strFileName, int nLine,
		 const char *strFormat, va_list arg_ptr);

	/*
	* Simple log do not print the file name and log number
	*/
	void Logs(LOG_LEVEL level, const char *strFormat, va_list arg_ptr);

private:
	 CLog();

private:
	FILE*           m_LogFile;
	LOG_LEVEL 		m_LogLevel;
	static CLog*	m_pInstance;
	char            m_strFilename[256];
};

#endif /*_LOG_H_*/
