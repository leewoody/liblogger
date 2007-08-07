#include <liblogger_levels.h>
// For this file, we choose the logs with priority Info and higher, 
// Since Info is the least possible log level, all logs will appear.
#define LOG_LEVEL LOG_LEVEL_INFO
// The module name for this file.
#define LOG_MODULE_NAME	"LogInfoTest"
#include <liblogger.h>

int TestFuncInfo()
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
