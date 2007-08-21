#include "tPLMutex.h"
#include <pthread.h>
#include <stdlib.h>

/** Create the mutex. */
int CreateMutex(tPLMutex* mutex)
{
	if(!mutex)
		return -1;
	else
	{
		pthread_mutex_t *pmutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		if(!pmutex)
		{
			// not enough memory.
			return -1;
		}
		pthread_mutex_init(pmutex,NULL);
		*mutex = pmutex;
		return 0; // success.
	}
}
/** Lock the mutex. */
int LockMutex(tPLMutex mutex)
{
	if(!mutex)
		return -1;
	if( pthread_mutex_lock( (pthread_mutex_t*)mutex) != 0 )
	{
		// locking failed.
		return -1;
	}
	return 0;
	
}
/** Unlock the mutex. */
int UnLockMutex(tPLMutex mutex)
{
	if(!mutex)
		return -1;
	if( pthread_mutex_unlock( (pthread_mutex_t*)mutex) != 0 )
	{
		// unlocking failed.
		return -1;
	}
	return 0;
	
}
/** Destroy the mutex. */
int DestroyMutex(tPLMutex* mutex)
{
	if( !mutex || !(*mutex) )
		return -1;
	if( pthread_mutex_destroy( (pthread_mutex_t*)*mutex ) != 0 )
	{
		// destroy failed.
		return -1;
	}
	free(*mutex);
	*mutex = 0;
	return 0;

}
