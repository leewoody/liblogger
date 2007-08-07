#ifndef __SOCKET_LOGGER_H__
#define __SOCKET_LOGGER_H__

#include "liblogger.h"
#include "logger_object.h"

int InitSocketLogger(LogWriter** logWriter,char* server,int port);

#endif // __SOCKET_LOGGER_H__
