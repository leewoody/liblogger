#ifndef __LIBLOGGER_CONFIG_H__
#define __LIBLOGGER_CONFIG_H__

/** define this macro to disable all logs */
//#define DISABLE_ALL_LOGS

/** Define this macro to prevent checking the variadic macro support of your compiler.
 * By defining this macro, you can also stop the filenames, function name, and the line no
 * from appearing in the logs.
 * */
//#define DISABLE_VARIADIC_CHECK

/** Define this macro to forcefully enable the varadic macro support. This can lead to compile time
 * errors if the compiler doesnot support variadic macros.*/
//#define ASSUME_VARIADIC_SUPPORT

/** Define this macro to prevent filenames from appearing in the logs. This is useful if the filenames are very long
 * and their presence is not desired in the logs.
 * */
//#define DISABLE_FILENAMES

#endif // __LIBLOGGER_CONFIG_H__
