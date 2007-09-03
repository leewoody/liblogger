/* - The documentation - used with doxygen. */
/**
  @mainpage liblogger : A logging framework for C / C++ 
  <div align="center"> <h3> http://liblogger.sourceforge.net/ - http://sourceforge.net/projects/liblogger </h3> </div>
  \section _FEATURES What is liblogger?
  \b liblogger is a logging framework for C / C++, with the following features :
  \li Transparent Logging to file / console / network.
  \li Supports different logging levels.
  \li Log level  and Module name can be configured on per file basis.
  \li Zero Performance overhead when the logging is disabled.


  \section SECTION_TOC Table of Contents
  \li @subpage PAGE_WHY_LOG
  \li @subpage PAGE_LOG_CONCEPTS
  \li @subpage PAGE_USING_LOGGER
  \li @subpage PAGE_FEEDBACK
  \li @subpage PAGE_LIMITATIONS
  \li @subpage PAGE_ABOUT

  \section SECTION_DOWNLOAD Downloading...
  liblogger is still in testing phase and currently works fine in linux/unix, no releases have been made yet, but you can get the latest sources from the <a href="http://sourceforge.net/svn/?group_id=202343"> subversion repository </a>
  porting of liblogger to windows is still under progress.

  \section SECTION_LICENSE License
  liblogger is distributed under <a href="http://www.gnu.org/licenses/lgpl-3.0.txt"> GNU LGPL license </a>.

 */

/** 
  \page SECTION_WHY Why bother to use logging in the first place?
  Well if you think why should logging be used , here are a few advantages:
  \li It saves you lot of time in debugging when the project grows bigger... 
  imagine tracing through thousands of functions Vs analyzing the log and pin-pointing the issue.
  \li Few of them argue, that the same can be achieved by adding printf()s... 
  but during release mode, you need to remove the printf()s... and if you dont remove them, 
  the performance overhead is still there.
  \li <a href="http://logging.apache.org/log4j/1.2/manual.html"> log4j </a> has a very apt excerpt from the
  book "The Practice of Programming" :
  \verbatim
  As personal choice, we tend not to use debuggers beyond getting a
  stack trace or the value of a variable or two. One reason is that it
  is easy to get lost in details of complicated data structures and
  control flow; we find stepping through a program less productive
  than thinking harder and adding output statements and self-checking
  code at critical places. Clicking over statements takes longer than
  scanning the output of judiciously-placed displays. It takes less
  time to decide where to put print statements than to single-step to
  the critical section of code, even assuming we know where that
  is. More important, debugging statements stay with the program;
  debugging sessions are transient.
  \endverbatim

*/

/**
  \page PAGE_LOG_CONCEPTS Few logging concepts.
  \section SECTION_LOG_LEVELS Log Levels
  The application can have several log levels depending on the severity/importance.
  The following log levels have been inspired by <a href="http://logging.apache.org/log4j/docs/"> log4j </a>
  The following log levels are supported (in increasing order of \b priority):
  \li Trace	(LOG_LEVEL_TRACE) - Messages with fine details.
  \li Debug 	(LOG_LEVEL_DEBUG) - Debug messages.
  \li Info 	(LOG_LEVEL_INFO) - Some informational messages
  \li Warn 	(LOG_LEVEL_WARN) - Warnings
  \li Error 	(LOG_LEVEL_ERROR) - Errors during execution of a program, but the application can still continue to run.
  \li Fatal	(LOG_LEVEL_FATAL) - Critical Errors which can lead the application to stop executing.
	
	The Application using liblogger can decide the logs above a certain level it wants to see. For example, if a source file contains all the above logs and the desired log level is set as Warn, then only the Warn, Error, Fatal logs will appear, all the below logs will be made null statements without any runtime overhead. The log level can be set on per-source file basis, for example in a project with several src files, one file can have max log level of Info and another file can have max log level as Fatal. (more details in the comming sections...)

  \section SECTION_LOGGING_FUNCTION Logging Functions.
  The following are the initalization functions:
  \li InitLogger() : Used to \ref SECTION_INIT "initialize" the log subsystem.
  \li DeInitLogger() : Used to Deinitialize the logger.

  Logging functions ( usage is similar to <a href="http://en.wikipedia.org/wiki/Printf"> printf() </a> ) :
  \li LogTrace() - Emit a log of level Trace.
  \li LogDebug() - Emit a log of level Debug.
  \li LogInfo() - Emit a log of level Info.
  \li LogWarn() - Emit a log of level Warn.
  \li LogError() - Emit a log of level Error.
  \li LogFatal() - Emit a log of level Fatal.

  The above functions are thread safe (unless thread safety is disabled during build).

  Log entry / exit from function (same priority as of Trace level log):
  \li LogFuncEntry() 	: Logs the entry to a function, add it at the begining of a function.
  \li LogFuncExit()	: Logs return from a function, the best place to use it is before a \b return from a function.

	\section SECTION_VM Variadic Macros
	The output of the the log depends on the variadic macro support of the compiler.
	To include the module name, the filename, the function name and the line number, the compiler must support variadic macros.

  \section SECTION_EXAMPLE Example of a log created.
	\li The \ref LogFuncEntry "function entry" and \ref LogFuncExit "function exit" logs have the same priority of log level Trace. 
	\li A sample function entry log will look like this:
	\code
	{ FunctionName
	\endcode

	\li A function exit log will look like this:
	\code
	FunctionName : <line-number> }
	\endcode
	
	\b NOTE: An open braces is inserted by the function log entry and a closing braces is added by function exit log, 
	this is to facilitate isolation of logs that appear between function calls and to identify nested function calls. Also
	this is very helpful when the log is being veiwed in editors (like vim) which support braces matching.

	\li The output of other log functions (LogDebug(), LogInfo(), ..... ) depend on the variadic macro support of the compiler.
	If the variadic macro support is available, then a sample log will look like:
	\verbatim
	<LogLevelID>:<ModuleName>:<FileName>:<FunctionName>:<LineNumber>:<UserLog...>
	\endverbatim
	If the variadic macro support is not available, the log will look like:
	\verbatim
	<LogLevelID>:<UserLog...>
	\endverbatim

	\b Example (compiler with variadic macro support):
	\include example.log
 */


/** 
  \page PAGE_USING_LOGGER Using the liblogger
  \section SECTION_BUILD Building the liblogger.
  \subsection SUBSEC_NIX Building for linux/unix platforms:
  \li The build system uses <a href="http://scons.org"> scons </a>
  which can be freely obtained for any platform.
  \li To build just run the command \b scons, from the folder \b build, which will create the static library, shared library and a test app which uses the shared library. \n
	If you interested to check network logging, then before running the test app, also start the log server, using command "python log_server.py" (in linux/unix) or simply clicking on the log_server.py on windows. If the log server is not running and connection fails, then the netowk logs will be redirected to a file with same name as of log server IP address.
  To run the test app under linux/unix : 
  \verbatim
  $export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
  $./logger_test
  \endverbatim

  \n

  The supported build options can be viewed using "scons -h" command:
  \li RELEASE - used to enable O3 optimizations and exclude debugging symbols. example: scons RELEASE=1
  \li DISABLE_THREAD_SAFETY - used to disable thread safety checks, use if you have a single thread of execution.
  \li DISABLE_SOCKET_LOGGER - used to disable network logger, use it if you are not using socket logging.
  \li CROSS_COMPILE - used for cross compilation.

  Examples :
  \li For cross compiling to arm without a socket logger : scons CROSS_COMPILE=arm-linux- DISABLE_SOCKET_LOGGER=1
  \li For compiling with O3 optimizations : scons RELEASE=1
  \li To enable the option just use \b OptionName=1
  
  \subsection SUBSEC_WIN32 Building for Windows platform
  \li To build for Windows platform, the Visual Studio 2005 solution with console based test app
  is provided under folder src/build/liblogger_win32/
  

  \section SECTION_INIT Initializing the logger.
  \li	Before using the logger, you need to initialize the logger using InitLogger(), it is better to do it at the beginning of the program
  for ex: main() or DllMain(). The example for this is can be found in the file main.cpp
  \li The Initialization can be done to log to a file
  \code
	tFileLoggerInitParams fileInitParams;
	// very important, memset to prevent breaks when new members are
	// added to fileInitParams.
	memset(&fileInitParams,0,sizeof(tFileLoggerInitParams));
	fileInitParams.fileName = "log.log";
	InitLogger(LogToFile,&fileInitParams);
  \endcode
  By default the file will be opened in write mode and all previous data will be removed.
  To open a file in append mode, use the following : example (append_test.cpp)
  \code
	tFileLoggerInitParams fileInitParams;
	// very important, memset to prevent breaks when new members are
	// added to fileInitParams.
	memset(&fileInitParams,0,sizeof(tFileLoggerInitParams));
	fileInitParams.fileOpenMode = AppendMode;
	fileInitParams.fileName = "log.log";
	InitLogger(LogToFile,&fileInitParams);
  \endcode

  \li The Initialization can be done to log to console.
  \code
	// the init argument can be either stdout or stderr.
	InitLogger(LogToConsole, stdout);
  \endcode

  \li The Initialization can be done to log to socket.
  \code
	tSockLoggerInitParams sockInitParams;
	// very important, memset to prevent breaks when new members are
	// added to sockInitParams.
	memset(&sockInitParams,0,sizeof(tSockLoggerInitParams));
	sockInitParams.server 	= "127.0.0.1";
	sockInitParams.port		= 50007;
	InitLogger(LogToSocket,&sockInitParams);
  \endcode
	See section \ref SECTION_SOCK_LOG for more details.

	\li Calling the initialization function is not compulsory, if InitLogger() is not called, then 
	the logs will be directed to \c stdout.
	\li If you have already initialized the logger and want to change the log destination (for example, initially you were doing to a console, but during the course of execution, you decide to redirect the logs to a socket), then you can call InitLogger() again.

  \section SECTION_INCLUDING Including the logger in your C / C++ Source files
  \li Each source file should atleast include the header liblogger.h, example \ref src_min.cpp
	\code
	#include <liblogger/liblogger.h>
	\endcode
  \subsection SUB_SECTION_MODULE_NAME Attaching a Module Name
  If you wish to attach a module name with the logs that appear from a (group of) file(s),
  the macro \c LOG_MODULE_NAME should be defined. 
  \b Note: The order of definition of macro LOG_MODULE_NAME is very important, 
  it should be defined before including the header liblogger.h.
	\code
	#include <liblogger/liblogger_levels.h>
	// The module name for logs done from this file.
	#define LOG_MODULE_NAME	"LoggerTest"
	#include <liblogger/liblogger.h>
	\endcode

  \subsection SUB_SECTION_LOG_LEVEL Controlling Log Levels
  To control the level of logs that will appear from a (group of) file(s),
  the macro LOG_LEVEL should be define as shown below:
  \b Note: The order of definition of macros LOG_LEVEL and  LOG_MODULE_NAME is very important, 
  it should be defined before including the header liblogger.h.
	\code
	#include <liblogger_levels.h>
	// For this file, we choose logs of priority debug and above.
	#define LOG_LEVEL LOG_LEVEL_DEBUG
	// The module name for logs done from this file.
	#define LOG_MODULE_NAME	"LogDebugTest"
	#include <liblogger.h>
	\endcode

	\subsection SUB_SECTION_ASC_GRP Associating a module name / log level with a group of source files.
	Often in a project, a group of files belong to a specific module or a particular log level
	is needed to be associated with a group of files, this can be easily done by including the above
	example in a header, and including this header in the desired source files.

	\subsection SUB_SECTION_EXAMPLES Examples
	The best way to understand is to look into the examples under folder <a href="files.html"> testapp </a>

	\section SECTION_DEINIT DeInitializing the logger.
	\li The logger can be deinitialized by calling the function DeInitLogger(),
	and the logger will close the file/socket objects if any (depending on the destination.)
	and release all resources in use.

	\section SECTION_DISABLE Disabling the logger.
	Lets say you want to disable all the log function calls, (for example during the release mode), this can be done either 
	\li by \#define ing the DISABLE_ALL_LOGS in file liblogger_config.h
	\li or by adding the flag ( in gcc : -DDISABLE_ALL_LOGS ) during the compilation stage.
	
	\warning When the logger is disabled, all the log statements will become \b NULL statements,
	so \b never \b never write logs which includes a computation or a function call :
	\code
	// The following code is NOT CORRECT
	// The following statement will be null when the logger is disabled and the function 
	// foo is never called, when logger is disabled.
	LogDebug(" foo() returned %d " , foo());
	\endcode

	\section SECTION_SOCK_LOG Logging to a Socket.
	To use logging to a socket:
	\li Start the log server at the destination machine. The log server (log_server.py) requires python. (by default the log server will bind to port 50007)
	\li Specify the server details with the call to InitLogger(), see section \ref SECTION_INIT for an example.
	\li Make sure that the port on which the log server runs is not blocked by a firewall.
	\li The log server can accept any number of connections, for each connection it creates a file with name of format 
	\verbatim
 <day>-<month>-<year>-<HH>-<MM>-<SS>.log 
	\endverbatim and write the logs to the file , as well displays it on the screen.

 */

/** 
	\page PAGE_FEEDBACK Providing feedback / Doubts...
	Your support is required to improve this project.
	\li Pls file the bug reports <a href="http://sourceforge.net/tracker/?group_id=202343&atid=981202">here</a>.
	\li If you have new ideas pls share them <a href="http://sourceforge.net/tracker/?group_id=202343&atid=981205"> here </a>.
	\li If you have any doubts you can ask them at the 
	<a href="http://sourceforge.net/forum/forum.php?forum_id=721800"> discussion forum </a> or  at the <a href="http://sourceforge.net/mail/?group_id=202343">  mailing list </a>
	\li You can also mail the developer at : \image html nvemail.png
	
*/

/**
	\page PAGE_ABOUT About liblogger
	\li Special thanks to http://sourceforge.net 
	\li 2007 - &copy; Vineeth Neelakant, 
	email: <img align="left" src="nvemail.png" alt="nvineeth _a_t_  gmail _ com" > 
	\n
*/
