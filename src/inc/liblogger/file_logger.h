#ifndef __FILE_LOGGER_H__
#define __FILE_LOGGER_H__

#include <stdio.h>

/** File open mode.
 * \todo currently not supported, will be added in future.
 * */
typedef enum tFileOpenMode
{
	__unused,
} tFileOpenMode;

/** File Logger Initialization parameters. */
typedef struct tFileLoggerInitParams
{
	/** The filename of the log. */
	char* 			fileName;
	/** The file open mode. */
	tFileOpenMode 	fileOpenMode;
}tFileLoggerInitParams;

#endif // __FILE_LOGGER_H__
