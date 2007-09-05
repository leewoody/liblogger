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

  \section SECTION_DOWNLOAD Downloading...
  liblogger is still in development phase and no releases have been made yet,
  but you can get the latest sources from the 
  <a href="http://sourceforge.net/svn/?group_id=202343"> subversion repository </a>.

  \section SECTION_LICENSE License
  liblogger is distributed under <a href="http://www.gnu.org/licenses/lgpl-3.0.txt"> GNU LGPL license </a>.

  \section SECTION_TOC Table of Contents
  \li @subpage PAGE_WHY_LOG
  \li @subpage PAGE_LOG_CONCEPTS
  <hr>
  \section Tutorial
  \li @subpage SECTION_BUILD
  \li @subpage SECTION_INCLUDING
  \li @subpage SECTION_INIT
  \li @subpage SECTION_CAL_LOG_FUNCS
  \li @subpage SECTION_MODULE_NAME
  \li @subpage SECTION_LOG_LEVEL
  \li @subpage SECTION_ASC_GRP 
  \li @subpage SECTION_DISABLE_FILENAME 
  \li @subpage SECTION_DEINIT 
  \li @subpage SECTION_DISABLE 
  \li @subpage SECTION_SOCK_LOG 
  \li @subpage SECTION_EXAMPLES 
  \li @subpage SECTION_ANALYZE_LOG 
  <hr>
  \li @subpage PAGE_FEEDBACK
  \li @subpage PAGE_LIMITATIONS
  \li @subpage PAGE_ABOUT
 */

/** 
  \page PAGE_WHY_LOG Why bother to use logging in the first place?
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
 
  \page SECTION_BUILD 1. Building the liblogger.
  \section SUBSEC_NIX 1.1. Building for linux/unix platforms:
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
  
  \section SUBSEC_WIN32 1.2. Building for Windows platform
  \li To build for Windows platform, the Visual Studio 2005 solution with console based test app
  is provided under folder src/build/liblogger_win32/
  <hr>
  Next : \ref SECTION_INCLUDING 
  

  \page SECTION_INCLUDING 2. Including the logger in your C / C++ Source files
  The Following is a simple example which illustrates the basic usage of liblogger,
  for more complex examples see section \ref SECTION_EXAMPLE "examples".
  \li Each source file should \b atleast include the header liblogger.h, example \ref src_min.cpp
	\code
	#include <liblogger/liblogger.h>
	\endcode

	After including the above header, the log functions can be called.
	For Example :
	\code
	#include <liblogger/liblogger.h>
	int main(int argc, char** argv)
	{
		LogDebug(" Debug message... ");
		LogInfo (" int val = %d ", 9);
		// ......
		LogFatal(" Fatal error has occured, ptr %#x ", 0XABCD );
		// .... other log functions. ........
		return 0;
	}
	\endcode

	\sa 
	For More examples , such as controlling the log level, associating a module name, see the 
	section \ref SECTION_EXAMPLES "examples"

	\li Previous : \ref SECTION_BUILD 
	\li Next : \ref SECTION_INIT 

  \page SECTION_INIT 3. Initializing the logger.
  	Before using the logger, you (may) initialize the logger using InitLogger(), 
	it is better to do it at the beginning of the program for ex: main() or DllMain(). 
	The example for this is can be found in the file main.cpp

	Initializing the logger is \b not mandatory, if any of the log functions are called without
	initializing, then the default log destination is to console (stdout).

  \section SUBSEC_INIT_FILE 3.1 Logging to File
  The Initialization can be done to log to a file
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

  \section SUBSEC_INIT_CONSOLE 3.2 Logging to console
  The Initialization can be done to log to console.
  \code
	// the init argument can be either stdout or stderr.
	InitLogger(LogToConsole, stdout);
  \endcode

  \section SUBSEC_INIT_SOCK 3.3 Logging to a socket
  The Initialization can be done to log to socket.
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

	\b Note:If you have already initialized the logger and want to change the log destination
	(for example, initially you were doing to a console, but during the course of execution, 
	 you decide to redirect the logs to a socket), then you can call InitLogger() again.

	<hr>
	\li Previous : \ref SECTION_INCLUDING
	\li Next : \ref SECTION_CAL_LOG_FUNCS
*/

/**
	\page SECTION_CAL_LOG_FUNCS 4. Calling the Log Functions
	Once the logger is initialized (which is not mandatory), you can call the log functions : 
	LogTrace(), LogDebug(), LogInfo(), LogWarn(), LogError(), LogFatal(), and the usage is similar to 
	printf.

	\sa \ref SECTION_EXAMPLE "Examples".
	<hr>
	\li Previous : \ref SECTION_INIT
	\li Next : \ref SECTION_MODULE_NAME
*/

/**
  \page SECTION_MODULE_NAME 5. Attaching a Module Name to the logs.
  If you wish to attach a module name with the logs that appear from a (group of) file(s),
  the macro \c LOG_MODULE_NAME should be defined. 
  \b Note: The order of definition of macro LOG_MODULE_NAME is very important, 
  it should be defined before including the header liblogger.h , the following code snippet illustrates 
  this :

	\code
	#include <liblogger/liblogger_levels.h>
	// The module name for logs done from this file.
	#define LOG_MODULE_NAME	"LoggerTest"
	#include <liblogger/liblogger.h>
	\endcode

	<hr>
	\li Previous : \ref SECTION_CAL_LOG_FUNCS
	\li Next : \ref SECTION_LOG_LEVEL
*/

/**
  \page SECTION_LOG_LEVEL 6. Controlling Log Level
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

	In the above example, all logs with priorit lesser than LOG_LEVEL (in this case LOG_LEVEL_TRACE), 
	will not appear.

	<hr>
	\li Previous : \ref SECTION_MODULE_NAME
	\li Next : \ref SECTION_ASC_GRP
*/

/**
	\page SECTION_ASC_GRP 7. Associating a module name / log level with a group of source files.
	Often in a project, a group of files belong to a specific module or a particular log level
	is needed to be associated with a group of files, this can be easily done by including the log details 
	in a header commonly included by these source files.
	For Example :
	Declare a http_module_log.h with the following contents :
	\code
	#include <liblogger_levels.h>
	// For this file, we choose logs of priority info and above.
	#define LOG_LEVEL LOG_LEVEL_INFO
	// The module name for logs done from this file.
	#define LOG_MODULE_NAME	"HTTP Module"
	#include <liblogger.h>
	\endcode

	Then include this header amoung the source files which need to have the same module name 
	and log level.


	<hr>
	\li Previous : \ref SECTION_LOG_LEVEL
	\li Next : \ref SECTION_DISABLE_FILENAME

	\page SECTION_DISABLE_FILENAME 8. Selectively Disabling Filenames from appearing in log.
	Depending on the compilation path of the sources, the filenames might be very long and 
	not desirable to appear in the log. To prevent filenames from appearing in the log, 
	\#define DISABLE_FILENAMES before including
	the header liblogger.h, the following example illustrates this :
	\code
	#include <liblogger/liblogger_levels.h>
	// For this file, we choose the logs with priority Info and higher, 
	// so logs with lesser priority i.e 
	// LogTrace(), LogDebug(), will NOT appear, THEY WILL BE NULL STATEMENTS WITH NO OVERHEAD
	#define LOG_LEVEL LOG_LEVEL_INFO
	// We Choose not to include the filenames in the log generated from this source file.
	#define DISABLE_FILENAMES
	// The module name for this file.
	#define LOG_MODULE_NAME	"ModuleInfoTest"
	#include <liblogger/liblogger.h>
	\endcode
	<hr>
	\li Previous : \ref SECTION_ASC_GRP
	\li Next : \ref SECTION_DEINIT


	\page SECTION_DEINIT 9. DeInitializing the logger.
	At the end of program's execution, the logger can be deinitialized by calling the function DeInitLogger(),
	and the logger will close the file/socket objects if any (depending on the initalization settings.)
	and release all resources in use.
	<hr>
	\li Previous : \ref SECTION_DISABLE_FILENAME
	\li Next : \ref SECTION_DISABLE

	\page SECTION_DISABLE 10. Disabling the logger.
	Lets say you want to disable all the log function calls, (for example during the release mode), this can be done either 
	\li by \#define ing the DISABLE_ALL_LOGS in file liblogger_config.h
	\li or by adding the flag ( in gcc : -DDISABLE_ALL_LOGS ) during the compilation stage.
	
	\warning When the logger is disabled, all the log statements will become \b NULL statements,
	so \b NEVER \b NEVER write logs which includes a computation or a function call :
	\code
	// The following code is NOT CORRECT
	// The following statement will be null when the logger is disabled and the function 
	// foo is never called, when logger is disabled.
	LogDebug(" foo() returned %d " , foo());
	\endcode
	<hr>
	\li Previous : \ref SECTION_DEINIT
	\li Next : \ref SECTION_SOCK_LOG

	\page SECTION_SOCK_LOG 11. Log Server 
	The log server can be used to capture the logs emitted, when initialized in LogToSocket mode.
	To use logging to a socket:
	\li Start the log server at the destination machine. The log server (log_server.py) requires python. (by default the log server will bind to port 50007)
	\li Specify the server details with the call to InitLogger(), see section \ref SUBSEC_INIT_SOCK for an example.
	\li Make sure that the port on which the log server runs is not blocked by a firewall.
	\li The log server can accept any number of connections, for each connection it creates a file with name of format 
	\verbatim
 <day>-<month>-<year>-<HH>-<MM>-<SS>.log 
	\endverbatim and write the logs to this file , as well displays it on the screen.
	<hr>
	\li Previous : \ref SECTION_DISABLE
	\li Next : \ref SECTION_EXAMPLES

	\page SECTION_EXAMPLES 12. Examples
	The best way to understand is to look into the examples under folder <a href="files.html"> testapp </a>
	<hr>
	\li Previous : \ref SECTION_SOCK_LOG
	\li Next : \ref SECTION_ANALYZE_LOG
 */

/**
  \page SECTION_ANALYZE_LOG 13. Analyzing the logs
  Depending on the priority of the log, the line starts with a string that indicates the type of
  log.
  For Example, Info logs start with [I], Warn logs start with [W], Fatal logs start with [F], and so on.
  This can be used to filter out the desired logs, 
  for example, to filter out all the fatal logs from the log file log.log, 
  use (under windows, <a href="http://www.cygwin.com/"> cygwin </a> or <a href="http://gnuwin32.sourceforge.net/packages/grep.htm"> GNU Win32 grep </a> can be used.):
  \verbatim
	#grep "\[F\]" log.log
  \endverbatim


  The function entry and function exit logs have a open brace \b { and a close brace \b }.
  This is very helpful when the log is viewed in a editor which supports parantheses matching (ex: vim, kate)
  <hr>
  \li Previous : \ref SECTION_EXAMPLES

 */

/**
	\page PAGE_FEEDBACK Providing feedback.... / Doubts??
	Your support is required to improve this project.
	\section SEC_BUGS Bugs?
	Pls file the bug reports <a href="http://sourceforge.net/tracker/?group_id=202343&atid=981202">here</a>.
	\section SEC_IDEAS Any new idea?
	If you have new ideas pls share them 
	<a href="http://sourceforge.net/tracker/?group_id=202343&atid=981205"> here </a>.
	\section SEC_DBTS Doubts?
	If you have any doubts  you can ask them at the 
	\li <a href="http://sourceforge.net/mail/?group_id=202343">  Mailing list </a>
	\li <a href="http://sourceforge.net/forum/forum.php?forum_id=721800"> Discussion forum </a> 
	\li You can also mail the developer at : \image html nvemail.png
 */

/**
 * \page PAGE_LIMITATIONS Limitations
 * Currently liblogger has the following limitations :
 * \li Configuration using config file is not implemented yet. (The feature will added in future releases.)
 * \li Log View tool, which highlights the logs is not implemented yet.
 * */

/**
	\page PAGE_ABOUT About liblogger
	\li Special thanks to http://sourceforge.net 
	\li 2007 - &copy; Vineeth Neelakant, 
	email: <img align="left" src="nvemail.png" alt="nvineeth _a_t_  gmail _ com" > 
	\n
*/
