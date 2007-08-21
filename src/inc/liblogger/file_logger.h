#ifndef __FILE_LOGGER_H__
#define __FILE_LOGGER_H__

#include <stdio.h>

/** File open mode.
 * */
typedef enum tFileOpenMode
{
	/** Indicates that the log file should be opened in append mode. */
	AppendMode,
	/** Rollback Mode : The log file will be opened in append mode and will
	 * roll back when the size indicated 
	 * by \ref tFileLoggerInitParams::rollbackSize is reached.
	 * */
	RollbackMode
} tFileOpenMode;

/** File Logger Initialization parameters. */
typedef struct tFileLoggerInitParams
{
	/** The filename of the log. */
	char* 			fileName;
	/** The file open mode. */
	tFileOpenMode 	fileOpenMode;
	/** The rollback size to use, when \ref tFileLoggerInitParams::fileOpenMode "fileOpenMode"
	 * is equal \ref tFileOpenMode::RollbackMode "RollbackMode"
	 * */
	unsigned long	rollbackSize;
}tFileLoggerInitParams;

#endif // __FILE_LOGGER_H__
