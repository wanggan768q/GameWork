//
//  HSSocketSendData.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-10-30.
//
//

#include "HSSocketSendData.h"

HSSocketSendData::HSSocketSendData()
{
    
}

HSSocketSendData::~HSSocketSendData()
{
    
}

HSSocketSendData* HSSocketSendData::New(const std::string& data,int id,const std::string& describe)
{
    
}

bool HSSocketSendData::init(const std::string& data,int id,const std::string& describe)
{
    m_data = data;
    m_id = id;
    m_describe = describe;
    return true;
}

const std::string& HSSocketSendData::GetData()
{
    return m_data;
}

const int& HSSocketSendData::GetID()
{
    return m_id;
}

const char* HSSocketSendData::GetDescribe()
{
    return m_describe.c_str();
}





