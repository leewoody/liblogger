#ifndef __T_PLMUTEX_H__
#define __T_PLMUTEX_H__

/** The mutex handle. */
typedef void* tPLMutex;

/** Create the mutex. */
int PLCreateMutex(tPLMutex* mutex);
/** Lock the mutex. */
int PLLockMutex(tPLMutex mutex);
/** Release the mutex. */
int PLUnLockMutex(tPLMutex mutex);
/** Destroy the mutex. */
int PLDestroyMutex(tPLMutex* mutex);

#endif // __T_PLMUTEX_H__
