//
//  HSLock.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-7.
//
//

#include "HSLock.h"


HSLock::HSLock()
{
#ifdef WIN32
    InitializeCriticalSection(&m_crit);
#else
    //m_crit = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m_crit, &attr);
    pthread_mutexattr_destroy(&attr);
#endif
}


HSLock::~HSLock()
{
#ifdef WIN32
    DeleteCriticalSection(&m_crit);
#else
    pthread_mutex_destroy(&m_crit);
#endif
}

void HSLock::Lock()
{
#ifdef WIN32
    EnterCriticalSection(&m_crit);
#else
    pthread_mutex_lock(&m_crit);
#endif
}

void HSLock::UnLock()
{
#ifdef WIN32
    LeaveCriticalSection(&m_crit);
#else
    pthread_mutex_unlock(&m_crit);
#endif
}





