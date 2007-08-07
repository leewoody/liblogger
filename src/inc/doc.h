/* - The documentation - used with doxygen. */
/**
  @mainpage liblogger Manual
  <div align="center"> <h2> http://liblogger.sourceforge.net/ </h2> </div>
  \section _FEATURES What is liblogger?
  \b liblogger is a logging framework for C / C++, with the following features :
  \li Transparent Logging to file / console / network.
  \li Supports different logging levels.
  \li Log level  and Module name can be configured on per file basis.
  \li Zero Performance overhead when the logging is disabled.

  Once you read the \ref PAGE_LOG_CONCEPTS, you can read \ref PAGE_USING_LOGGER for more details.
  <h2> Table of Contents </h2>
  \li @subpage PAGE_LOG_CONCEPTS
  \li @subpage PAGE_USING_LOGGER
  \li @subpage PAGE_HELP_IMPROVE
 */

/** 
  \page PAGE_LOG_CONCEPTS liblogger concepts.
  \section SECTION_LOG_LEVELS Log Levels
  The following log levels are supported (in increasing order of \b priority):
  \li Info (LOG_LEVEL_INFO)
  \li Debug (LOG_LEVEL_DEBUG)
  \li Critical (LOG_LEVEL_CRITICAL)

  Each file using the logger has to define the logs of a particular level that should be used.

  \section SECTION_LOGGING_FUNCTION Logging Functions.
  The following are the initalization functions:
  \li InitLogger() : Used to \ref SECTION_INIT "initialize" the log subsystem.
  \li DeInitLogger() : Used to Deinitialize the logger.

  Logging functions ( usage is similar to <a href="http://en.wikipedia.org/wiki/Printf"> printf() </a> ) :
  \li LogInfo() - Emit a log of level Info.
  \li LogDebug() - Emit a log of level Debug.
  \li LogCritical() - Emit a log of level Critical.

  Log entry / exit from function:
  \li LogFuncEntry() 	: Logs the entry to a function, add it at the begining of a function.
  \li LogFuncExit()	: Logs return from a function, the best place to use it is before a \b return from a function.
 */

/** 
  \page PAGE_USING_LOGGER Using the liblogger
  \section SECTION_BUILD Building the liblogger.
  Initially you need to build the liblogger. The build system uses <a href="http://scons.org"> scons </a>
  which can be freely obtained for any platform.
  To build just run the command \b scons, which will create the static library and shared library under 
  the folder \b src

  \section SECTION_INIT Initializing the logger.
  \li	Before using the logger, you need to initialize the logger using InitLogger(), it is better to do it at the beginning of the program
  for ex: main() or DllMain(). The example for this is can be found in the file main.cpp
  \li The Initialization can be done either to log to a file
  \code
	// The second arg is the filename. 
	InitLogger(LogToFile,"log.log");
  \endcode
  \li The Initialization can be done either to log to console.
  \code
	InitLogger(LogToConsole);
  \endcode

  \li The Initialization can be done either to log to socket.
  \code
	// The second arg is the server and the third arg is the port.
	InitLogger(LogToSocket,"127.0.0.1",50007);
  \endcode

	\li If you have already initialized the logger and want to change the log destination (for example, initially you were doing to a console, but during the course of execution, you decide to redirect the logs to a socket), then you can call InitLogger() again.

  \section SECTION_INCLUDING Including the logger in your C / C++ Source files
  \li Each source file should atleast include the header liblogger.h, example \ref src_min.cpp
	\code
	#include <liblogger.h>
	\endcode
  \li If you wish to attach a module name with the logs of a particular file, then the following needs to be done.
	\code
	#include <liblogger_levels.h>
	// The module name for logs done from this file.
	#define LOG_MODULE_NAME	"LogCriticalTest"
	#include <liblogger.h>
	\endcode

  \li If you wish to attach a module name, and control the level of logs that will appear from a particular file,
	then the following needs to be done.
	\code
	#include <liblogger_levels.h>
	// For this file, we choose logs of priority debug and above.
	#define LOG_LEVEL LOG_LEVEL_DEBUG
	// The module name for logs done from this file.
	#define LOG_MODULE_NAME	"LogDebugTest"
	#include <liblogger.h>
	\endcode

	\li The best way to understand is to look into the examples under folder <a href="files.html"> testapp </a>

	
	\section SECTION_DEINIT DeInitializing the logger.
	\li The logger can be deinitialized by calling the function DeInitLogger(), and the logger will close the file/socket objects if any
	and release all resources in use.


 */
