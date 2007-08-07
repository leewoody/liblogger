#include <liblogger_levels.h>
// For this file, we disable all the logs.
#define LOG_LEVEL LOG_LEVEL_DISABLED
#include <liblogger.h>

int TestFuncNoLogs()
{
	// log the function entry log.
	LogFuncEntry();

	LogInfo("Info Level Log %d" , 0);
	LogDebug("Debug level Log" );
	LogCritical("Critical Log" );

	// log the function exit log.
	LogFuncExit();
	
	return 0;
}
