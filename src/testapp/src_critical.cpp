#include <liblogger_levels.h>
// For this file, we choose the critical logs, 
// so logs with lesser priority i.e LogDebug(), LogInfo() will not appear.
#define LOG_LEVEL LOG_LEVEL_CRITICAL
// The module name for this file.
#define LOG_MODULE_NAME	"LogCriticalTest"
#include <liblogger.h>

int TestFuncCritical()
{
	// log the function entry log.
	LogFuncEntry();

	LogInfo("Info Level log %d" , 0);
	LogDebug("Debug level log" );
	LogCritical("Critical log" );

	if(1)
	{
		// log the function exit .
		LogFuncExit();
		return 0;
	}
	else
	{
		// log the function exit .
		LogFuncExit();
		return -1;
	}
	
}
