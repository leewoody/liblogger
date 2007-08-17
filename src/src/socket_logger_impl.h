#ifndef __SOCKET_LOGGER_IMPL_H__
#define __SOCKET_LOGGER_IMPL_H__

#include <liblogger/liblogger.h>
#include <liblogger/logger_object.h>
#include <liblogger/socket_logger.h>

/** Factory Function to create the Socket Logger. 
 * \param [out] logWriter 	The log writer handle.
 * \param [in]	initParams	The Socket log writer initialization parameters.
 * \returns 0 on success , -1 on failure.
 * */
int InitSocketLogger(LogWriter** logWriter,tSockLoggerInitParams *initparams);

#endif // __SOCKET_LOGGER_IMPL_H__
