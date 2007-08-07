#ifndef __LOGGER_OBJECT_H__
#define __LOGGER_OBJECT_H__
#include <stdarg.h>
#include <stdio.h>
#include  "liblogger.h"
/** Indicates the logger object. */

/* fwd declaration. */
struct LogWriter;
/** Indicates the log writer object. */
typedef int (*Log)(struct LogWriter* _this,const char* levelStr,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap);
typedef int (*LogFuncEntry)(struct LogWriter * _this,const char* funcName);
typedef int (*LogFuncExit)(struct LogWriter* _this,const char* funcName,int lineNum);
typedef int (*LoggerDeInit)(struct LogWriter* _this);

/** The log writer object */
typedef struct LogWriter
{
	Log 			log;
	LogFuncEntry 	logFuncEntry;
	LogFuncExit		logFuncExit;
	LoggerDeInit	loggerDeInit;
}LogWriter;


#endif // __LOGGER_OBJECT_H__
