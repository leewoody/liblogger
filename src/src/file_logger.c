#include "file_logger.h"
#include <stdio.h>
#include <logger_object.h>
#include <memory.h>

/** Default log file name, if InitLogger() is not done and a 
  logger function is directly called. */
#define FILE_NAME_LOG "NoNameLogFile.txt"
#define MAX_PATH 255

#ifdef _WIN32
	#define  vsnprintf(buf,buf_size,fmt,ap) _vsnprintf(buf,buf_size,fmt,ap);
	#define inline __inline
#endif

/** Helper function to write the logs to file */
static inline int sWriteToFile(LogWriter *_this,
		const char* levelStr,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap);

static int sFileFuncLogEntry(LogWriter *_this,const char* funcName);

static int sFileFuncLogExit(LogWriter * _this,
		const char* funcName,const int lineNumber);

int sFileLoggerDeInit(LogWriter* _this);

typedef struct FileLogWriter
{
	LogWriter	 base;
	FILE		*fp;
}FileLogWriter;

static FileLogWriter sFileLogWriter = 
{
	.base.log = sWriteToFile,
	.base.logFuncEntry 	= sFileFuncLogEntry,
	.base.logFuncExit	= sFileFuncLogExit,
	.base.loggerDeInit	= sFileLoggerDeInit,
	.fp					= 0
};

/** Helper function to prepend the current date and time to the log filename. */
static void PrependDateTimeToLogFileName(char* outBuf,int bufMaxSize, char* filename)
{
#ifdef WIN32
	SYSTEMTIME sysTime;
	memset(&sysTime,0,sizeof(SYSTEMTIME));
	GetLocalTime(&sysTime);
	_snprintf(outBuf,bufMaxSize-1,"%d-%d-%d-%d-%d-%d-%s",sysTime.wYear,sysTime.wMonth,sysTime.wDay,
			sysTime.wHour,sysTime.wMinute,sysTime.wSecond,filename);
#else
	// TODO 
	strncpy(outBuf,filename,bufMaxSize-1);
#endif
	outBuf[bufMaxSize-1] = 0;
}

int InitFileLogger(LogWriter** logWriter,char* filename,LogDest dest)
{
	if(!logWriter)
	{
		fprintf(stderr,"Invalid args to function InitFileLogger\n");
		return -1;
	}
	*logWriter = 0;

	if (sFileLogWriter.fp)
	{
		sFileLoggerDeInit((LogWriter*)&sFileLogWriter);
	}
	if(LogToConsole == dest)
	{
		sFileLogWriter.fp = stdout;
	}
	else // LogToFile
	{
		char  tempBuf[MAX_PATH];
		if(filename)
		{
			PrependDateTimeToLogFileName(tempBuf,MAX_PATH,filename);
		}
		else
		{
			PrependDateTimeToLogFileName(tempBuf,MAX_PATH,FILE_NAME_LOG);
		}
		sFileLogWriter.fp = fopen(tempBuf,"w");
		if( !sFileLogWriter.fp )
		{
			fprintf(stderr,"could not open log file %s",tempBuf);
			return -1;
		}
	}
	*logWriter = (LogWriter*)&sFileLogWriter;
	return 0; // success!
}

/** Helper function to write the logs to file */
static inline int sWriteToFile(LogWriter *_this,
		const char* levelStr,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap)
{
	FileLogWriter *flw = (FileLogWriter*) _this;
	if(!_this || !flw->fp)
	{
		fprintf(stderr,"Invalid args to sWriteToFile.");
		return -1;
	}
	else
	{
		fprintf(flw->fp,levelStr);
#ifdef VARIADIC_MACROS
		fprintf(flw->fp,"%s:%s:%s:%d:",moduleName,file,funcName,lineNum);
#endif
		vfprintf(flw->fp,fmt,ap); 
		fprintf(flw->fp,"\n");
		fflush(flw->fp);
		return 0;
	}
}

static int sFileFuncLogEntry(LogWriter *_this,const char* funcName)
{
	FileLogWriter *flw = (FileLogWriter*) _this;
	if(!_this || !flw->fp)
	{
		fprintf(stderr,"Invalid args to File Log Writer (Func Entry)\n");
		return -1;
	}
	else
	{
		int bytes_written = 0;
		bytes_written = fprintf(flw->fp,"{ %s \n", funcName);
		fflush(flw->fp);
		return bytes_written;
	}
		
}

static int sFileFuncLogExit(LogWriter * _this,
		const char* funcName,const int lineNumber)
{
	FileLogWriter *flw = (FileLogWriter*) _this;
	if(!_this || !flw->fp)
	{
		fprintf(stderr,"Invalid args to File Log Writer (Func Exit)\n");
		return -1;
	}
	else
	{
		int bytes_written = 0;
		bytes_written = fprintf(flw->fp,"%s : %d }\n", funcName,lineNumber);
		fflush(flw->fp);
		return bytes_written;
	}
}


int sFileLoggerDeInit(LogWriter* _this)
{
	FileLogWriter *flw = (FileLogWriter*) _this;
	if(flw && flw->fp)
	{
		fclose(flw->fp);
	}
	flw->fp = 0;
	return 0;
}
