#ifndef __FILE_LOGGER_IMPL_H__
#define __FILE_LOGGER_IMPL_H__

#include <liblogger/liblogger.h>
#include <liblogger/logger_object.h>
#include <liblogger/file_logger.h>

/** Factory Function to create the File Logger. 
 * \param [out] logWriter 	The log writer handle.
 * \param [in]	initParams	The log writer initialization parameters.
 * \returns 0 on success , -1 on failure.
 * */
int InitFileLogger(LogWriter** logWriter,tFileLoggerInitParams* initParams );

/** Factory Function to create the Console Logger. 
 * A console logger is a special case of file logging (where the file is stdout or stderr)
 * \param [out] logWriter 	The log writer handle.
 * \param [in]	initParams	The log writer initialization parameters.
 * \returns 0 on success , -1 on failure.
 * */
int InitConsoleLogger(LogWriter** logWriter,void* initParams);

#endif // __FILE_LOGGER_IMPL_H__
