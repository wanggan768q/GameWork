//
//  HSSem.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-7.
//
//

#ifndef __HSBalloon_S3__HSSem__
#define __HSBalloon_S3__HSSem__

#include "HSThread.h"

class HSSem
{
public:
	HSSem();
	virtual ~HSSem();
public:
	bool Create(int initcount);
	bool Wait(int timeout = 0);
	bool Post();
    
private:
#ifdef WIN32
	HANDLE m_hSem;
#else
	sem_t m_semid;
	bool  m_bCreate;
#endif
};



#endif /* defined(__HSBalloon_S3__HSSem__) */
