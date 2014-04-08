//
//  HSSocketRecvData.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-10-28.
//
//

#include "HSSocketRecvData.h"

HSSocketRecvData::HSSocketRecvData()
{
    m_pBuf = NULL;
    m_size = 0;
}

HSSocketRecvData::~HSSocketRecvData()
{
    Del();
}

HSSocketRecvData* HSSocketRecvData::New(void* pBuf,int bufSize)
{
    HSSocketRecvData* pData = new HSSocketRecvData();
    if(pData && pData->init(pBuf, bufSize))
    {
        return pData;
    }
    CC_SAFE_DELETE(pData);
    return NULL;
}

bool HSSocketRecvData::init(void* pBuf, int bufSize)
{
    if (!m_pBuf) {
        m_pBuf = new char[bufSize];
    }
    memset(m_pBuf, 0, bufSize);
    
    memcpy(m_pBuf, pBuf, bufSize);
    
    m_size = bufSize;

    return true;
}

void HSSocketRecvData::Del()
{
    CC_SAFE_DELETE(m_pBuf);
    m_size = 0;
}

const void* HSSocketRecvData::GetBuf()
{
    return m_pBuf;
}

int HSSocketRecvData::GetBufSize()
{
    return m_size;
}







