#ifndef __T_PLMUTEX_H__
#define __T_PLMUTEX_H__

/** The mutex handle. */
typedef void* tPLMutex;

/** Create the mutex. */
int CreateMutex(tPLMutex* mutex);
/** Lock the mutex. */
int LockMutex(tPLMutex mutex);
/** Release the mutex. */
int UnLockMutex(tPLMutex mutex);
/** Destroy the mutex. */
int DestroyMutex(tPLMutex* mutex);

#endif // __T_PLMUTEX_H__
