#ifndef _LOG_EXPORT_H_
#define _LOG_EXPORT_H_

typedef enum {
	LEVEL_DEBUG = 0,
	LEVEL_WARNING = 1,
	LEVEL_ERROR = 2,
	LEVEL_FATAL = 3,
}LOG_LEVEL;

#ifdef __cplusplus
extern "C" {
#endif

void SetLogLevel(LOG_LEVEL minLevel);
void Log(LOG_LEVEL level, const char *strFileName, int nLine,
		 const char *strFormat, ...);

/*simple log do not print the file name and the line number*/
void Logs(LOG_LEVEL level, const char *strFormat, ...);

#define LogD(strFormat, ...) \
    Log(LEVEL_DEBUG, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LogW(strFormat, ...) \
    Log(LEVEL_WARNING, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LogE(strFormat, ...) \
    Log(LEVEL_ERROR, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)

#define LogF(strFormat, ...) \
    Log(LEVEL_FATAL, __FILE__, __LINE__, strFormat, ## __VA_ARGS__)


#define LogsD(strFormat, ...) \
    Logs(LEVEL_DEBUG, strFormat, ## __VA_ARGS__)

#define LogsW(strFormat, ...) \
    Logs(LEVEL_WARNING, strFormat, ## __VA_ARGS__)

#define LogsE(strFormat, ...) \
    Logs(LEVEL_ERROR, strFormat, ## __VA_ARGS__)

#define LogsF(strFormat, ...) \
    Logs(LEVEL_FATAL, strFormat, ## __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /*_LOG_EXPORT_H_*/

