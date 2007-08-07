#include <liblogger_levels.h>
// For this file, we choose the logs with priority Debug and higher, 
// so logs with lesser priority i.e LogInfo(), will not appear.
#define LOG_LEVEL LOG_LEVEL_DEBUG
// The module name for this file.
#define LOG_MODULE_NAME	"LogDebugTest"
#include <liblogger.h>

int TestFuncDebug()
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
