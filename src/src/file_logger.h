#ifndef __FILE_LOGGER_H__
#define __FILE_LOGGER_H__

#include "liblogger.h"
#include "logger_object.h"

int InitFileLogger(LogWriter** logWriter,char* filename,LogDest dest);

#endif // __FILE_LOGGER_H__
