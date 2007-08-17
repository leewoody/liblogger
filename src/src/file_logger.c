#include "file_logger_impl.h"
#include <stdio.h>
#include <memory.h>

/** Default log file name, if InitLogger() is not done and a 
  logger function is directly called. */
#define FILE_NAME_LOG "NoNameLogFile.txt"
#define MAX_PATH 255

/* win32 support */
#ifdef _WIN32
	#define  vsnprintf(buf,buf_size,fmt,ap) _vsnprintf(buf,buf_size,fmt,ap);
#endif

/** Helper function to write the logs to file */
static int sWriteToFile(LogWriter *_this,
		const LogLevel logLevel ,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap);

/** File Logger object function to log function entry */
static int sFileFuncLogEntry(LogWriter *_this,const char* funcName);

/** File Logger object function to log function exit */
static int sFileFuncLogExit(LogWriter * _this,
		const char* funcName,const int lineNumber);

/** File Logger object function deinitialization function */
static int sFileLoggerDeInit(LogWriter* _this);

/* helper function to get the log prefix , the log prefix is added to help in greping*/
static const char* sGetLogPrefix(const LogLevel logLevel);

/** The File logger object. */
typedef struct FileLogWriter
{
	/** Base logger object. */
	LogWriter	 base;
	/** The log file pointer. */
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

int InitConsoleLogger(LogWriter** logWriter,void* dest)
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
	if ( (dest != stdout) && (dest != stderr) )
	{
		fprintf(stderr,"Incorrect init params for console logger, stdout will be used.\n");
		dest = stdout;
	}
	sFileLogWriter.fp = stdout;
	*logWriter = (LogWriter*)&sFileLogWriter;
	return 0; // success!
}

int InitFileLogger(LogWriter** logWriter,tFileLoggerInitParams* initParams)
{
	if(!logWriter || !initParams)
	{
		fprintf(stderr,"Invalid args to function InitFileLogger\n");
		return -1;
	}
	*logWriter = 0;
	if(!initParams->fileName)
	{
		fprintf(stderr,"filename is null, error \n");
		return -1;
	}

	/* deinitialize the file logger if already initialized. */
	if (sFileLogWriter.fp)
		sFileLoggerDeInit((LogWriter*)&sFileLogWriter);

	sFileLogWriter.fp = fopen(initParams->fileName,"w");
	if( !sFileLogWriter.fp )
	{
		fprintf(stderr,"could not open log file %s",initParams->fileName);
		return -1;
	}

	*logWriter = (LogWriter*)&sFileLogWriter;
	return 0; // success!
}

/** Helper function to write the logs to file */
static int sWriteToFile(LogWriter *_this,
		const LogLevel logLevel,
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
		fprintf(flw->fp,sGetLogPrefix(logLevel));
#ifdef VARIADIC_MACROS
		fprintf(flw->fp,"%s:%s:%s:%d:",moduleName,file,funcName,lineNum);
#endif
		vfprintf(flw->fp,fmt,ap); 
		fprintf(flw->fp,"\n");
		fflush(flw->fp);
		return 0;
	}
}

/** File Logger object function to log function entry */
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

/** File Logger object function to log function exit */
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


/** File Logger object function deinitialization function */
int sFileLoggerDeInit(LogWriter* _this)
{
	FileLogWriter *flw = (FileLogWriter*) _this;
	if(flw && flw->fp)
	{
		if( (flw->fp != stdout) && (flw->fp != stderr) )
			fclose(flw->fp);
	}
	flw->fp = 0;
	return 0;
}

/* helper function to get the log prefix */
static const char* sGetLogPrefix(const LogLevel logLevel)
{
	switch (logLevel)
	{
		case Trace:	return "[T]";
		case Debug: return "[D]";
		case Info:	return "[I]";
		case Warn:	return "[W]";
		case Error:	return "[E]";
		case Fatal:	return "[F]";
		default:	return "";
	}
}
