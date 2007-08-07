#ifndef __FILE_LOGGER_H__
#define __FILE_LOGGER_H__

#include "liblogger.h"
#include "logger_object.h"

int InitFileLogger(LogWriter** logWriter,char* filename);
int InitConsoleLogger(LogWriter** logWriter,void* dest);

#endif // __FILE_LOGGER_H__
