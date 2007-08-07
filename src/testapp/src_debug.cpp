#include <liblogger_levels.h>
// For this file, we choose the debug log level.
#define LOG_LEVEL LOG_LEVEL_DEBUG
// The module name for this file.
#define LOG_MODULE_NAME	"LogDebugTest"
#include <liblogger.h>

int TestFuncDebug()
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
