//
//  HSIPAddress.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-10-30.
//
//

#ifndef __HSBalloon_S3__HSIPAddress__
#define __HSBalloon_S3__HSIPAddress__
#include "HSBase.h"

class HSIPAddress
{
public:
    HSIPAddress();
    ~HSIPAddress();
    
private:
    std::string m_ip;
public:
    void SetHostName(const char* ip,bool bIPv6);
    
    const char* GetIP();
};

#endif /* defined(__HSBalloon_S3__HSIPAddress__) */
