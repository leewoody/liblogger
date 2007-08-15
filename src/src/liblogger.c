#include "liblogger.h"
#include "file_logger.h"
#include "socket_logger.h"

#ifndef DISABLE_THREAD_SAFETY
#include "tLLMutex.h"
#endif

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
		if(InitLogger(LogToConsole)) 			\
			return -1; 							\
		if(!pLogWriter)							\
			return -1;							\
	}											\


/** Function to initialize the logger. */
int InitLogger(LogDest ldest,...)
{
	if(pLogWriter)
	{
		fprintf(stderr,"\n [liblogger]Deinitializing the current log writer\n");
		DeInitLogger();
	}
#ifndef DISABLE_THREAD_SAFETY
	CreateMutex(&sMutex);
#endif
	switch(ldest)
	{
		case LogToSocket:
			#ifndef DISABLE_SOCKET_LOGGER
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
				if( -1 == InitConsoleLogger(&pLogWriter,0) )
				{
					// control should never reach here, this should alwasy succeed.
					fprintf(stderr,"\n [liblogger] could not initialize console logger \n");
					return -1;
				}
			}
		break;
LOG_TO_FILE:
		case LogToFile:
			/* log to a file, the second arg is the filename. */
			{
				va_list args;
				char *filename;
				va_start(args,ldest);
				filename  = va_arg(args,char*);
				va_end(args);

				if( -1 == InitFileLogger(&pLogWriter,filename) )
				{
					fprintf(stderr,"\n [liblogger] could not initialize file logger, check file path/name \n");
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
#ifndef DISABLE_THREAD_SAFETY
	DestroyMutex(&sMutex);
	sMutex = 0;
#endif


}

int vsLogStub(LogLevel logLevel,
#ifdef VARIADIC_MACROS
		const char* moduleName,const char* file,
		const char* funcName, const int lineNum,
#endif
	const char* fmt,va_list ap)
{
	CHECK_AND_INIT_LOGGER;

#ifndef DISABLE_THREAD_SAFETY
	LockMutex(sMutex);
#endif
	return pLogWriter->log(pLogWriter,logLevel,
#ifdef VARIADIC_MACROS
			moduleName,file,funcName,lineNum,
#endif
			fmt,ap);
#ifndef DISABLE_THREAD_SAFETY
	UnLockMutex(sMutex);
#endif
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
	CHECK_AND_INIT_LOGGER;
	return pLogWriter->logFuncEntry(pLogWriter,funcName);
}

int FuncLogExit(const char* funcName,const int lineNumber)
{
	CHECK_AND_INIT_LOGGER;
	return pLogWriter->logFuncExit(pLogWriter,funcName,lineNumber);
}

#endif /* DISABLE_ALL_LOGS */
