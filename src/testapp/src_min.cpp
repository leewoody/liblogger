// If you dont want to bother about log levels and module names,
// then the minimum thing that needs to be done is to include the header below
// and start logging.
#include <liblogger.h>

int TestFuncMin()
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
