#include <time.h>
#include "log.h"
#include "utils.h"

void SetLogLevel(LOG_LEVEL minLevel)
{
	CLog::GetInstance()->SetLogLevel(minLevel);
}

void Log(LOG_LEVEL level, const char *strFileName, int nLine,
	 const char *strFormat, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	CLog::GetInstance()->Log(level, strFileName, nLine, strFormat, arg_ptr);
	va_end(arg_ptr);
}

void Logs(LOG_LEVEL level, const char *strFormat, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	CLog::GetInstance()->Logs(level, strFormat, arg_ptr);
	va_end(arg_ptr);
}

CLog *CLog::m_pInstance = NULL;

CLog::CLog()
{
	m_LogLevel = LEVEL_DEBUG;

	m_LogFile = NULL;
	memset(m_strFilename, 0, sizeof(m_strFilename));

	char strMac[32] = {0};
	strcpy(strMac, "00-00-00-00-00-00");

	time_t timep;
	struct tm *tmp;
	time(&timep);
	tmp = localtime(&timep);
	snprintf(m_strFilename, sizeof(m_strFilename),"process-%s-%02d%02d%02d.log",
											strMac,
											tmp->tm_year+1900,
											tmp->tm_mon+1,
											tmp->tm_mday);
	memset(strMac, 0, sizeof(strMac));
	if (GetMacAddress(strMac, sizeof(strMac), "eth0"))
	{
		snprintf(m_strFilename, sizeof(m_strFilename),"process-%s-%02d%02d%02d.log",
										strMac,
										tmp->tm_year+1900,
										tmp->tm_mon+1,
										tmp->tm_mday);
	}
}

CLog::~CLog()
{

}

CLog *CLog::GetInstance()
{
	if (NULL == m_pInstance) {
		m_pInstance = new CLog();
	}

	return m_pInstance;

}

bool CLog::ReleaseInstance()
{
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = NULL;
	}

	return true;
}

void CLog::SetLogLevel(LOG_LEVEL minLevel)
{
	m_LogLevel = minLevel;
}

void CLog::Log(LOG_LEVEL level, const char *strFileName, int nLine,
	       const char *strFormat, va_list arg_ptr)
{
	if (NULL == strFormat) {
		return;
	}

	char strInfo[2048] = { 0 };
	vsprintf(strInfo, strFormat, arg_ptr);
	char strOutPut[2048] = { 0 };

	if (NULL == m_LogFile)
	{
		m_LogFile = fopen(m_strFilename, "a+");
	}

	time_t timep;
	struct tm *tmp;
	time(&timep);
	tmp = localtime(&timep);
	fprintf(m_LogFile, "[%02d:%02d:%02d][%s::%d] %s\n",
						tmp->tm_hour,
						tmp->tm_min,
						tmp->tm_sec,
						strFileName, nLine, strInfo);
	fclose(m_LogFile);
	m_LogFile = NULL;

	if (level < m_LogLevel) {
		return;
	}

	sprintf(strOutPut, "[%s::%d] %s", strFileName, nLine, strInfo);
	printf("%s\n", strOutPut);
}

void CLog::Logs(LOG_LEVEL level, const char *strFormat, va_list arg_ptr)
{
	if (NULL == strFormat) {
		return;
	}

	char strInfo[2048] = { 0 };
	vsprintf(strInfo, strFormat, arg_ptr);

	if (NULL == m_LogFile)
	{
		m_LogFile = fopen(m_strFilename, "a+");
	}

	fprintf(m_LogFile, "%s", strInfo);
	fclose(m_LogFile);
	m_LogFile = NULL;

	if (level < m_LogLevel) {
		return;
	}

	printf("%s", strInfo);
}
