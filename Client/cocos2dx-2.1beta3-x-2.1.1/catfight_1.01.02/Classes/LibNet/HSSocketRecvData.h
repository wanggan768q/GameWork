//
//  HSSocketRecvData.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-10-28.
//
//

#ifndef __HSBalloon_S3__HSSocketRecvData__
#define __HSBalloon_S3__HSSocketRecvData__

#include "HSBase.h"

class HSSocketRecvData
{
    
public:
    HSSocketRecvData();
    ~HSSocketRecvData();
    
public:
    static HSSocketRecvData* New(void* pBuf,int bufSize);
    
    bool init(void* pBuf,int bufSize);
    
    void Del();
    
    const void* GetBuf();
    
    int GetBufSize();
    
    
private:
    char* m_pBuf;
    int m_size;
};

#endif /* defined(__HSBalloon_S3__HSSocketRecvData__) */
