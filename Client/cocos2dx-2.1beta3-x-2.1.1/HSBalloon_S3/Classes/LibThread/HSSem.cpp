//
//  HSSem.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-7.
//
//

#include "HSSem.h"

HSSem::HSSem()
{
#ifdef WIN32
    m_hSem = NULL;
#else
    m_bCreate = false;
#endif
}

HSSem::~HSSem()
{
#ifdef WIN32
    if (m_hSem != NULL)
    {
        CloseHandle(m_hSem);
        m_hSem = NULL;
    }
#else
    if (m_bCreate)
    {
        m_bCreate = false;
        sem_destroy(&m_semid);
    }
#endif
}

bool HSSem::Create(int initcount)
{
    if (initcount < 0)
    {
        initcount = 0;
    }
#ifdef WIN32
    if (initcount > 64)
    {
        return false;
    }
    m_hSem = CreateSemaphore(NULL, initcount, 64, NULL);
    if (m_hSem == NULL)
    {
        return false;
    }
#else
    if (sem_init(&m_semid, 0, initcount) != 0)
    {
        return false;
    }
    m_bCreate = true;
#endif
    return true;
    
}


bool HSSem::Wait(int timeout/* = 0*/)
{
#ifdef WIN32
    if (timeout <= 0)
    {
        timeout = INFINITE;
    }
    if (WaitForSingleObject(m_hSem, timeout) != WAIT_OBJECT_0)
    {
        return false;
    }
#else
    if (timeout <= 0)
    {
        return (sem_wait(&m_semid) == 0);
    }
    else
    {
        timespec ts;
        ts.tv_sec += time(NULL) + timeout/1000;
        ts.tv_nsec += (timeout%1000)*1000000;
#if HSIos
        return (sem_wait(&m_semid) == 0);
#else
        return (sem_timedwait(&m_semid, &ts) == 0);
#endif
    }
#endif
    return true;
}

bool HSSem::Post()
{
#ifdef WIN32
    return ReleaseSemaphore(m_hSem, 1, NULL) ? true : false;
#else
    return (sem_post(&m_semid) == 0);
#endif
}







