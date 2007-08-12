#ifndef __EXP_LOGGER_CONFIG_H__
#define __EXP_LOGGER_CONFIG_H__

/** \defgroup GRP_LOG_LEVELS Log Levels
 * The following macros indicate the log levels
 * @{
 * */
/** The Trace log level */
#define LOG_LEVEL_TRACE	1
/** The Debug log level */
#define LOG_LEVEL_DEBUG 2
/** The Info log level */
#define LOG_LEVEL_INFO	3
/** The Warning log level */
#define LOG_LEVEL_WARN	4
/** The Error log level */
#define LOG_LEVEL_ERROR	5
/** The Fatal log level */
#define LOG_LEVEL_FATAL	6

/** define this macro to disable logs (in the current file), to disable globally define DISABLE_ALL_LOGS   */
#define LOG_LEVEL_DISABLED 12

/** Indicates the log level */
typedef enum LogLevel
{
	Trace, /**< The trace log level */
	Debug, /**< The debug log level */
	Info, /**< The info log level */
	Warn, /**< The warn log level */
	Error, /**< The error log level */
	Fatal /**< The fatal log level */
}LogLevel;

/** @} */

#endif // __EXP_LOGGER_CONFIG_H__

