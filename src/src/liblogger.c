#include "liblogger.h"
#include "file_logger.h"
#include "socket_logger.h"

#include <stdio.h>
#include <stdarg.h>

#ifndef DISABLE_ALL_LOGS 

/** The log writer func ptr is initialized depending on the log destination. */
static LogWriter *pLogWriter = 0;


/** Macro to check if logger subsystem is initialize, 
 * if not, then it is initialized to log to file
 * */
#define CHECK_AND_INIT_LOGGER	if(!pLogWriter)	\
	{ 											\
		if(InitLogger(LogToFile,0)) 			\
			return -1; 							\
		if(!pLogWriter)							\
			return -1;							\
	}											\


/** Function to initialize the logger. */
int InitLogger(LogDest ldest,...)
{
	if(pLogWriter)
	{
		fprintf(stderr,"Deinitializing the current log writer");
		DeInitLogger();
	}
	switch(ldest)
	{
		case LogToSocket:
			{
				/* Then 2nd arg is the server and the 3rd ard is the port */
				va_list args;
				char *server;
				int port;
				va_start(args,ldest);
				server = va_arg(args,char*);
				port = va_arg (args, int);
				va_end(args);
				if( -1 == InitSocketLogger(&pLogWriter,server,port) )
				{
					fprintf(stderr,"could not init socket logging, will be done to a file.");
					goto LOG_TO_FILE;
				}
			}
			break;

LOG_TO_FILE:
		case LogToFile:
		case LogToConsole:
			/* log to a file */
			{
				va_list args;
				char *filename;
				va_start(args,ldest);
				filename  = va_arg(args,char*);
				va_end(args);

				if( -1 == InitFileLogger(&pLogWriter,filename,ldest) )
				{
					fprintf(stderr,"could not initialize file logger, check file path/name");
					return -1;
				}
			}
			break;
	}
	return 0; // success.
}

/** Deinitialize the logger, the file / socket is closed here. */
void DeInitLogger()
{
	pLogWriter->loggerDeInit(pLogWriter);
	pLogWriter = 0;

}

int vsLogStub(const char* logLevelStr,
#ifdef VARIADIC_MACROS
		const char* moduleName,const char* file,
		const char* funcName, const int lineNum,
#endif
	const char* fmt,va_list ap)
{
	CHECK_AND_INIT_LOGGER;

	return pLogWriter->log(pLogWriter,logLevelStr,
#ifdef VARIADIC_MACROS
			moduleName,file,funcName,lineNum,
#endif
			fmt,ap);
}

#ifdef VARIADIC_MACROS
int LogStub_vm(const char* logLevelStr,
		const char* moduleName,const char* file,
		const char* funcName, const int lineNum,
		const char* fmt,...)
{

	va_list ap; 
	int retVal = 0;
	va_start(ap,fmt);
	retVal = vsLogStub(logLevelStr,moduleName,file,funcName,lineNum,fmt,ap);
	va_end(ap);
	return retVal;
}

#else

int LogInfo(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(LOG_LEVEL_INFO_PREFIX,fmt,ap);
	va_end(ap);
	return retVal;
}

int LogDebug(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(LOG_LEVEL_DEBUG_PREFIX,fmt,ap);
	va_end(ap);
	return retVal;
}

int LogCritical(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(LOG_LEVEL_CRITICAL_PREFIX,fmt,ap);
	va_end(ap);
	return retVal;
}	

#endif // VARIADIC_MACROS

int FuncLogEntry(const char* funcName)
{
	CHECK_AND_INIT_LOGGER;
	return pLogWriter->logFuncEntry(pLogWriter,funcName);
}

int FuncLogExit(const char* funcName,const int lineNumber)
{
	CHECK_AND_INIT_LOGGER;
	return pLogWriter->logFuncExit(pLogWriter,funcName,lineNumber);
}

#endif /* DISABLE_ALL_LOGS */
