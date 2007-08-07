#include <liblogger_levels.h>
// For this file, we disable all the logs. - NO LOGS FROM THIS FILE WILL APPEAR.
#define LOG_LEVEL LOG_LEVEL_DISABLED
#include <liblogger.h>

int TestFuncNoLogs()
{
	// log the function entry log.
	LogFuncEntry();

	LogInfo("Info Level log %d" , 0);
	LogDebug("Debug level log" );
	LogCritical("Critical log" );

	// log the function exit log.
	LogFuncExit();
	
	return 0;
}
