#include <liblogger/liblogger.h>
#include "file_logger_impl.h"
#include "socket_logger_impl.h"

#ifndef DISABLE_THREAD_SAFETY
	#include "tLLMutex.h"
	#define __LOCK_MUTEX 	if(sMutex) LockMutex(sMutex)
	#define __UNLOCK_MUTEX	if(sMutex) UnLockMutex(sMutex)
#else
	#define __LOCK_MUTEX 	/* NOP */
	#define __UNLOCK_MUTEX	/* NOP */
#endif // DISABLE_THREAD_SAFETY

#include <stdio.h>
#include <stdarg.h>

#ifndef DISABLE_ALL_LOGS 

/** The log writer func ptr is initialized depending on the log destination. */
static LogWriter *pLogWriter = 0;
#ifndef DISABLE_THREAD_SAFETY
static tLLMutex	sMutex = 0;
#endif


/** Macro to check if logger subsystem is initialize, 
 * if not, then it is initialized to log to file
 * */
#define CHECK_AND_INIT_LOGGER	if(!pLogWriter)	\
	{ 											\
		fprintf(stderr,"\n[liblogger]liblogger not initialized, logging will be done to console (stdout)\n");\
		if(InitLogger(LogToConsole,stdout)) 			\
			return -1; 							\
		if(!pLogWriter)							\
			return -1;							\
	}											\


/** Function to initialize the logger. */
int InitLogger(LogDest ldest,void* loggerInitParams)
{
	int retVal = 0;
	if(pLogWriter)
	{
		fprintf(stderr,"\n [liblogger]Deinitializing the current log writer\n");
		DeInitLogger();
	}
#ifndef DISABLE_THREAD_SAFETY
	if(!sMutex)
		CreateMutex(&sMutex);
#endif
	__LOCK_MUTEX;

	switch(ldest)
	{
		case LogToSocket:
			#ifndef DISABLE_SOCKET_LOGGER
			{
				if( -1 == InitSocketLogger(&pLogWriter,loggerInitParams) )
				{
					fprintf(stderr,"\n [liblogger] could not init socket logging, will be done to a file. \n");
					ldest = LogToFile;
					goto LOG_TO_FILE;
				}
			}
			#else
			{
				fprintf(stderr,"\n [liblogger] Socket logger not enabled during build, use DISABLE_SOCKET_LOGGER=0, logging will be done to file.\n");
				goto LOG_TO_FILE;
			}
			#endif
			break;

		case LogToConsole:
			{
				/* log to a console. */
				if( -1 == InitConsoleLogger(&pLogWriter,loggerInitParams) )
				{
					// control should never reach here, this should alwasy succeed.
					fprintf(stderr,"\n [liblogger] could not initialize console logger \n");
					retVal = -1;
					goto UNLOCK_RETURN;
				}
			}
		break;
LOG_TO_FILE:
		case LogToFile:
			{
				/* log to a file. */

				if( -1 == InitFileLogger(&pLogWriter,loggerInitParams) )
				{
					fprintf(stderr,"\n [liblogger] could not initialize file logger, check file path/name \n");
					retVal = -1;
					goto UNLOCK_RETURN;
				}
			}
			break;
	}
	retVal = 0;
UNLOCK_RETURN:
	__UNLOCK_MUTEX;
	return retVal; // success.
}

/** Deinitialize the logger, the file / socket is closed here. */
void DeInitLogger()
{
	__LOCK_MUTEX;
	pLogWriter->loggerDeInit(pLogWriter);
	pLogWriter = 0;
	__UNLOCK_MUTEX;

	// TODO : CHECK THIS CONDITON.
#ifndef DISABLE_THREAD_SAFETY
	//DestroyMutex(&sMutex);
	//sMutex = 0;
#endif
}

int vsLogStub(LogLevel logLevel,
#ifdef VARIADIC_MACROS
		const char* moduleName,const char* file,
		const char* funcName, const int lineNum,
#endif
	const char* fmt,va_list ap)
{
	int retVal = 0;
	CHECK_AND_INIT_LOGGER;

	__LOCK_MUTEX;

	retVal = pLogWriter->log(pLogWriter,logLevel,
#ifdef VARIADIC_MACROS
			moduleName,file,funcName,lineNum,
#endif
			fmt,ap);

	__UNLOCK_MUTEX;

	return retVal;
}

#ifdef VARIADIC_MACROS
int LogStub_vm(LogLevel logLevel,
		const char* moduleName,const char* file,
		const char* funcName, const int lineNum,
		const char* fmt,...)
{

	va_list ap; 
	int retVal = 0;
	va_start(ap,fmt);
	retVal = vsLogStub(logLevel,moduleName,file,funcName,lineNum,fmt,ap);
	va_end(ap);
	return retVal;
}

#else

int LogTrace(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(Trace,fmt,ap);
	va_end(ap);
	return retVal;
}

int LogDebug(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(Debug,fmt,ap);
	va_end(ap);
	return retVal;
}

int LogInfo(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(Info,fmt,ap);
	va_end(ap);
	return retVal;
}

int LogWarn(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(Warn,fmt,ap);
	va_end(ap);
	return retVal;
}

int LogError(const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(Error,fmt,ap);
	va_end(ap);
	return retVal;
}

int LogFatal (const char* fmt,...)
{
	int retVal = 0;
	va_list ap; 
	va_start(ap,fmt);
	retVal = vsLogStub(Fatal,fmt,ap);
	va_end(ap);
	return retVal;
}


#endif // VARIADIC_MACROS

int FuncLogEntry(const char* funcName)
{
	int retVal = 0;
	CHECK_AND_INIT_LOGGER;
	__LOCK_MUTEX;
	retVal = pLogWriter->logFuncEntry(pLogWriter,funcName);
	__UNLOCK_MUTEX;
	return retVal;
}

int FuncLogExit(const char* funcName,const int lineNumber)
{
	int retVal = 0;
	CHECK_AND_INIT_LOGGER;
	__LOCK_MUTEX;
	retVal = pLogWriter->logFuncExit(pLogWriter,funcName,lineNumber);
	__UNLOCK_MUTEX;
	return retVal;
}

#endif /* DISABLE_ALL_LOGS */
