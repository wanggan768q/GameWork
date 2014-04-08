#include "HSThread.h"


HSThread::HSThread(void)
{
}


HSThread::~HSThread(void)
{
}

HSThread* HSThread::create( Start_thread startThread,void* arg )
{
	HSThread* pThread = new HSThread;
	if (pThread && pThread->init(startThread,arg))
	{
		return pThread;
	}
	CC_SAFE_DELETE(pThread);
	return NULL;
}

bool HSThread::init( Start_thread startThread,void* arg )
{
	m_startThread = startThread;
	m_pArg = arg;
	return true;
}

bool HSThread::Start()
{
	int errCode = 0;  
	do{  
		pthread_attr_t tAttr;  
		errCode = pthread_attr_init(&tAttr);  
		CC_BREAK_IF(errCode!=0);
		errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);  
		if (errCode!=0) {  
			pthread_attr_destroy(&tAttr);  
			break;  
		}         
		errCode = pthread_create(&m_pid,&tAttr,m_startThread,m_pArg);  
	}while (0);

	return errCode == 0 ? true : false;
}

void HSThread::Stop()
{
#ifdef WIN32
	pthread_cancel(m_pid);
	pthread_detach(m_pid);
#else
	pthread_kill(m_pid,0);
#endif
}

void* HSThread::GetParameter()
{
	return m_pArg;
}

void HSThread::Wait()
{
	pthread_join(this->m_pid, NULL);
}
