// If you dont want to bother about log levels and module names,
// then the minimum thing that needs to be done is to include the header below
// and start logging. - NOTE ALL LOGS WILL APPEAR IN THIS CASE
#include <liblogger.h>

int TestFuncMin()
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
