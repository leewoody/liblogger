/**
 * \file Implementation of the Mutex Abstraction API for Win32 platform.
 * */
#include "tPLMutex.h"
#include <windows.h>

/** Create the mutex. */
int PLCreateMutex(tPLMutex* mutex)
{
	if(!mutex)
		return -1;
	else
	{
		HANDLE _mutex = CreateMutex( 
				NULL,              // default security attributes
				FALSE,             // initially not owned
				NULL);             // unnamed mutex
		if ( !_mutex)
		{
			fprintf(stderr,"Mutex creation failed.");
			return -1;
		}
		*mutex = _mutex;
		return 0; // success.
	}
}
/** Lock the mutex. */
int PLLockMutex(tPLMutex mutex)
{
	if(!mutex)
		return -1;
	if( WaitForSingleObject(mutex) != WAIT_OBJECT_0 )
	{
		// locking failed.
		return -1;
	}
	return 0;
	
}
/** Unlock the mutex. */
int PLUnLockMutex(tPLMutex mutex)
{
	if(!mutex)
		return -1;
	if( ReleaseMutex (mutex) == 0  )
	{
		//If the function succeeds, the return value is nonzero.
		// unlocking failed.
		return -1;
	}
	return 0;
}

/** Destroy the mutex. */
int PLDestroyMutex(tPLMutex* mutex)
{
	if( !mutex || !(*mutex) )
		return -1;
	if( CloseHandle( (HANDLE)*mutex ) != 0 )
	{
		// destroy failed.
		return -1;
	}
	*mutex = 0;
	return 0;

}
