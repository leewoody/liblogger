#include "liblogger.h"
#include "file_logger.h"
#include "socket_logger.h"

#include <stdio.h>
#include <stdarg.h>

#ifndef _WIN32
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#else
#endif

#ifndef DISABLE_ALL_LOGS 


/** The log writer func ptr is initialized depending on the log destination. */
static LogWriter *pLogWriter = 0;


/** Macro to check if logger subsystem is initialize, 
 * if not, then it is initialized to log to file
 * */
#define CHECK_AND_INIT_LOGGER	if(!pLogWriter)	\
	{ 							\
		if(InitLogger(LogToFile,0)) 			\
			return -1; 				\
	}							\


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

#if LOG_LEVEL<= LOG_LEVEL_INFO

#ifdef VARIADIC_MACROS
int FuncLogInfo(const char* moduleName,const char* file,const char* funcName, const int lineNum, const char* fmt,...)
#else
int LogInfo(const char* fmt,...)
#endif
{
	CHECK_AND_INIT_LOGGER;
	
	{
		va_list ap; 
		int retVal = 0;
		va_start(ap,fmt);
		retVal = pLogWriter->log(pLogWriter,"[I]",
#ifdef VARIADIC_MACROS
				moduleName,file,funcName,lineNum,
#endif
				fmt,ap);
		va_end(ap);
		return retVal;
	}
}
#endif

#if LOG_LEVEL<= LOG_LEVEL_DEBUG
#ifdef VARIADIC_MACROS
int FuncLogDebug(const char* moduleName,const char* file,const char* funcName, const int lineNum,const char* fmt,...)
#else
int LogDebug(const char* fmt,...)
#endif
{
	CHECK_AND_INIT_LOGGER;
	{
		va_list ap; 
		int retVal = 0;
		va_start(ap,fmt);
		retVal = pLogWriter->log(pLogWriter,"[D]",
#ifdef VARIADIC_MACROS
				moduleName,file,funcName,lineNum,
#endif
				fmt,ap);
		va_end(ap);
		return retVal;
	}	
}
#endif

#if LOG_LEVEL<= LOG_LEVEL_CRITICAL
#ifdef VARIADIC_MACROS
int FuncLogCritical(const char* moduleName,const char* file,const char* funcName,const int lineNum,const char* fmt,...)
#else
int LogCritical(const char* fmt,...)
#endif
{
	CHECK_AND_INIT_LOGGER;
	
	{
		va_list ap; 
		int retVal = 0;
		va_start(ap,fmt);
		retVal = pLogWriter->log(pLogWriter,"[C]",
#ifdef VARIADIC_MACROS
				moduleName,file,funcName,lineNum,
#endif
				fmt,ap);
		va_end(ap);
		return retVal;
	}	
}
#endif

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
