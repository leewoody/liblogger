#ifndef __T_PLMUTEX_H__
#define __T_PLMUTEX_H__

#if defined(WIN32) || (_WIN32)
/* Windows */
#include <windows.h>
/** The mutex handle. */
typedef HANDLE tPLMutex;
#elif defined(__unix) || defined(__linux)
#include <pthread.h>
/* A Unix system */
/** The mutex handle. */
typedef pthread_mutex_t* tPLMutex;
#else
/* Unsupported platform. */
#endif

/** Create the mutex. */
int PLCreateMutex(tPLMutex* mutex);
/** Lock the mutex. */
int PLLockMutex(tPLMutex mutex);
/** Release the mutex. */
int PLUnLockMutex(tPLMutex mutex);
/** Destroy the mutex. */
int PLDestroyMutex(tPLMutex* mutex);

#endif // __T_PLMUTEX_H__
