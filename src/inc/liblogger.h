
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



/** Use this macro to disable all logs */
#undef DISABLE_ALL_LOGS

/** Define this macro, to log to stdio, when logger is initialized with kLogToFile  option */
#undef LOG_TO_STDOUT

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

#if defined(__GNUC__) || (_MSC_VER >= 1400)
	/* 1. GCC supports variadic macros, 
	 * 2. this feature is available only in VS 2005 or higher versions.
	 * */
	#define VARIADIC_MACROS
#endif


// Logs needs to be disabled.
#ifdef DISABLE_ALL_LOGS

	#define LogInfo 		/* NOP */
	#define LogDebug 		/* NOP */
	#define LogCritical 	/* NOP */
	#define LogFuncEntry	/* NOP */
	#define LogFuncExit		/* NOP */
	#define InitLogger 		/* NOP */
	#define DeInitLogger()	/* NOP */

#else
	#include <loglevel_prefix.h>

	#ifdef VARIADIC_MACROS	
	int LogStub_vm(const char* logLevelStr,
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
	// Logs are enabled.	
	#if LOG_LEVEL<= LOG_LEVEL_INFO
		#ifdef VARIADIC_MACROS
			#define LogInfo(fmt, ...) LogStub_vm(LOG_LEVEL_INFO_PREFIX,LOG_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
		#else
			/** Emit a log with Info level. */
			int LogInfo(const char *fmt, ...);
		#endif
	#else
		#define LogInfo /*NOP*/
	#endif

	#if LOG_LEVEL<= LOG_LEVEL_DEBUG
		#ifdef VARIADIC_MACROS
			#define LogDebug(fmt, ...) LogStub_vm(LOG_LEVEL_DEBUG_PREFIX,LOG_MODULE_NAME, __FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
		#else
			/** Emit a log with Debug level. */
			int LogDebug(const char *fmt, ...);
		#endif

	#else
		#define LogDebug /* No OP */
	#endif
	
	#if LOG_LEVEL<= LOG_LEVEL_CRITICAL
		#ifdef VARIADIC_MACROS	
			#define LogCritical(fmt, ...) LogStub_vm(LOG_LEVEL_CRITICAL_PREFIX,LOG_MODULE_NAME, __FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
		#else
			/** Emit a log with Critical level. */
			int LogCritical(const char *fmt, ...);
		#endif
	#else
		#define LogCritical /* No OP */
	#endif

	#if LOG_LEVEL<= LOG_LEVEL_INFO
		/** Log Entry to a function. */
		int FuncLogEntry(const char* funcName);
		/** Log return from a function. */
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

