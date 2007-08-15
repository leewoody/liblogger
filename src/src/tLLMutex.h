#ifndef __T_LLMUTEX_H__
#define __T_LLMUTEX_H__

/** The mutex handle. */
typedef void* tLLMutex;

/** Create the mutex. */
int CreateMutex(tLLMutex* mutex);
/** Lock the mutex. */
int LockMutex(tLLMutex mutex);
/** Release the mutex. */
int UnLockMutex(tLLMutex mutex);
/** Destroy the mutex. */
int DestroyMutex(tLLMutex* mutex);

#endif // __T_LLMUTEX_H__
