#include "HSThread.h"

HSThread::HSThread()
{
    m_hThreadID = 0;
}

HSThread::~HSThread()
{
    
}

bool HSThread::Start()
{
#ifdef WIN32
    unsigned long long ret = _beginthreadex(NULL, 0, ThreadProc, (void *) this, 0, NULL);
    
    if (ret == -1 || ret == 1  || ret == 0)
    {
        HSMessageBox("create thread error!");
        return false;
    }
    m_hThreadID = ret;
#else
    pthread_t ptid = 0;
    int ret = pthread_create(&ptid, NULL, ThreadProc, (void*)this);
    if (ret != 0)
    {
        HSMessageBox("create thread error!");
        return false;
    }
    m_hThreadID = (unsigned long long)ptid;
    
#endif
    return true;
}

bool HSThread::Wait()
{
#ifdef WIN32
    if (WaitForSingleObject((HANDLE)m_hThreadID, INFINITE) != WAIT_OBJECT_0)
    {
        return false;
    }
#else
    if (pthread_join((pthread_t)m_hThreadID, NULL) != 0)
    {
        return false;
    }
#endif
    return true;
}

#ifdef WIN32
unsigned int WINAPI  ThreadProc(LPVOID lpParam)
{
	HSThread * p = (HSThread *) lpParam;
	p->Run();
	_endthreadex(0);
	return 0;
}
#else
void * ThreadProc(void * pParam)
{
	HSThread * p = (HSThread *) pParam;
	p->Run();
	return NULL;
}
#endif


