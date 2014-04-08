//
//  HSIPAddress.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-10-30.
//
//

#include "HSIPAddress.h"


HSIPAddress::HSIPAddress()
{
    
}

HSIPAddress::~HSIPAddress()
{
    
}

void HSIPAddress::SetHostName(const char* ip,bool bIPv6)
{
    m_ip = ip;
}

const char* HSIPAddress::GetIP()
{
    return m_ip.c_str();
}