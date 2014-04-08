//
//  HSLock.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-7.
//
//

#ifndef __HSBalloon_S3__HSLock__
#define __HSBalloon_S3__HSLock__

#include "HSThread.h"


class HSLock
{
public:
	HSLock();
	virtual ~HSLock();
    
public:
	void Lock();
	void UnLock();
    
    
private:
    
#ifdef WIN32
	CRITICAL_SECTION m_crit;
#else
	pthread_mutex_t  m_crit;
#endif
    
};

class HSAutoLock
{
public:
	explicit HSAutoLock(HSLock & lk):m_lock(lk)
    {
        m_lock.Lock();
    }
    
	~HSAutoLock()
    {
        m_lock.UnLock();
    }
private:
    
	HSLock& m_lock;
};



#endif /* defined(__HSBalloon_S3__HSLock__) */
