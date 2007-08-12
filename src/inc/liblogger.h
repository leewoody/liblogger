
#ifndef __EXP_LOGGER_H__
#define __EXP_LOGGER_H__

#include <liblogger_levels.h>

/** WIN32 Hack. */
#if defined(WIN32) || defined(_WIN32)
#define __func__ __FUNCTION__
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <liblogger_config.h>

/**Indicates the  Log Level for the source file */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

#ifndef LOG_MODULE_NAME
#define LOG_MODULE_NAME ""
#endif



/** enum which indicates the log destination, used with \ref InitLogger */
typedef enum LogDest
{
	/** Indicates that logging should be done to file. */
	LogToFile,
	/** Log to Console. (stdout) */
	LogToConsole,
	/** Indicates that logging should be done to socket. Please note that log server should be 
	 *  running. */
	LogToSocket
}LogDest;

/* few compilers dont support variadic macros,so initially undef it, 
 * and depending on the compiler define it.
 */
#undef VARIADIC_MACROS

#if !defined(DISABLE_VARIADIC_CHECK) && (defined(__GNUC__) || (_MSC_VER >= 1400))
	/* 1. GCC supports variadic macros, 
	 * 2. this feature is available only in VS 2005 or higher versions.
	 * */
	#define VARIADIC_MACROS
#endif

/* Forcefully enable the variadic macro support, results in compiler errors if not supported. */
#ifdef ASSUME_VARIADIC_SUPPORT
	#define VARIADIC_MACROS
#endif	


#ifdef DISABLE_ALL_LOGS
// Logs needs to be disabled, warn the user.
#warning Logger disabled.

	#define LogInfo 		/* NOP */
	#define LogDebug 		/* NOP */
	#define LogCritical 	/* NOP */
	#define LogFuncEntry()	/* NOP */
	#define LogFuncExit()	/* NOP */
	#define InitLogger 		/* NOP */
	#define DeInitLogger()	/* NOP */

#else
	// The logs are enabled.

	#ifdef VARIADIC_MACROS	
	int LogStub_vm(LogLevel logLevel,
		const char* moduleName,const char* file,
		const char* funcName, const int lineNum,
		const char* fmt,...);
	#endif
	/** Function used to initialize the logger.
	 If the logger is not initialized and a log function is called, then a default log file 
         will be used, also if log to socket is used and if the connection to the server cannot be
         established, then a log filename with that ip address will be created and logging will be done.
        */
	int InitLogger(LogDest ldest,...);
	/** Function used to deinitialize the logger. */
	void DeInitLogger();


	/* -- Log Level Trace -- */
	#if LOG_LEVEL<= LOG_LEVEL_TRACE
		#ifdef VARIADIC_MACROS
			#if defined(DISABLE_FILENAMES)
				/* the filename should be disabled. */
				#define LogTrace(fmt, ...) LogStub_vm(Trace,LOG_MODULE_NAME,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#else 
				#define LogTrace(fmt, ...) LogStub_vm(Trace,LOG_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#endif // DISABLE_FILENAMES
		#else
			/** Emit a log with Trace level. */
			int LogTrace(const char *fmt, ...);
		#endif // VARIADIC_MACROS
	#else
		#define LogTrace	/*NOP*/
	#endif

	/* -- Log Level Debug -- */
	#if LOG_LEVEL<= LOG_LEVEL_DEBUG
		#ifdef VARIADIC_MACROS
			#if defined(DISABLE_FILENAMES)
				/* the filename should be disabled. */
				#define LogDebug(fmt, ...) LogStub_vm(Debug,LOG_MODULE_NAME,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#else 
				#define LogDebug(fmt, ...) LogStub_vm(Debug,LOG_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#endif // DISABLE_FILENAMES
		#else
			/** Emit a log with Debug level. */
			int LogDebug(const char *fmt, ...);
		#endif // VARIADIC_MACROS
	#else
		#define LogDebug	/*NOP*/
	#endif

	/* -- Log Level Info -- */
	#if LOG_LEVEL<= LOG_LEVEL_INFO
		#ifdef VARIADIC_MACROS
			#if defined(DISABLE_FILENAMES)
				/* the filename should be disabled. */
				#define LogInfo(fmt, ...) LogStub_vm(Info,LOG_MODULE_NAME,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#else 
				#define LogInfo(fmt, ...) LogStub_vm(Info,LOG_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#endif // DISABLE_FILENAMES
		#else
			/** Emit a log with Info level. */
			int LogInfo(const char *fmt, ...);
		#endif // VARIADIC_MACROS
	#else
		#define LogInfo /*NOP*/
	#endif

	/* -- Log Level Warn -- */
	#if LOG_LEVEL<= LOG_LEVEL_WARN
		#ifdef VARIADIC_MACROS
			#if defined(DISABLE_FILENAMES)
				/* the filename should be disabled. */
				#define LogWarn(fmt, ...) LogStub_vm(Warn,LOG_MODULE_NAME,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#else 
				#define LogWarn(fmt, ...) LogStub_vm(Warn,LOG_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#endif // DISABLE_FILENAMES
		#else
			/** Emit a log with Warn level. */
			int LogWarn(const char *fmt, ...);
		#endif // VARIADIC_MACROS
	#else
		#define LogWarn	/*NOP*/
	#endif

	/* -- Log Level Error-- */
	#if LOG_LEVEL<= LOG_LEVEL_ERROR
		#ifdef VARIADIC_MACROS
			#if defined(DISABLE_FILENAMES)
				/* the filename should be disabled. */
				#define LogError(fmt, ...) LogStub_vm(Error,LOG_MODULE_NAME,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#else 
				#define LogError(fmt, ...) LogStub_vm(Error,LOG_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#endif // DISABLE_FILENAMES
		#else
			/** Emit a log with Error level. */
			int LogError(const char *fmt, ...);
		#endif // VARIADIC_MACROS
	#else
		#define LogError	/*NOP*/
	#endif

	/* -- Log Level Fatal -- */
	#if LOG_LEVEL<= LOG_LEVEL_FATAL
		#ifdef VARIADIC_MACROS
			#if defined(DISABLE_FILENAMES)
				/* the filename should be disabled. */
				#define LogFatal(fmt, ...) LogStub_vm(Fatal,LOG_MODULE_NAME,"",__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#else 
				#define LogFatal(fmt, ...) LogStub_vm(Fatal,LOG_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
			#endif // DISABLE_FILENAMES
		#else
			/** Emit a log with Fatal level. */
			int LogFatal(const char *fmt, ...);
		#endif // VARIADIC_MACROS
	#else
		#define LogFatal	/*NOP*/
	#endif

	#if LOG_LEVEL<= LOG_LEVEL_TRACE
		/* Log Entry to a function. */
		int FuncLogEntry(const char* funcName);
		/* Log return from a function. */
		int FuncLogExit(const char* funcName,const int lineNumber);
		
		#define LogFuncEntry()	FuncLogEntry(__func__)
		#define LogFuncExit()	FuncLogExit(__func__,__LINE__)
		
	#else
		#define LogFuncEntry()	/* NOP */
		#define LogFuncExit()	/* NOP */
	#endif

#endif // DISABLE_ALL_LOGS


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EXP_LOGGER_H__ */

