//
//  HSSDK.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#include "HSSDK.h"
#import "HSWBEngine.h"

HSSDK* HSSDK::S_HSSDK = NULL;

HSSDK::HSSDK()
{
    
}

HSSDK::~HSSDK()
{
    
}

HSSDK* HSSDK::SharedSDK()
{
    if (!S_HSSDK)
    {
        S_HSSDK = new HSSDK();
    }
    return S_HSSDK;
}

void HSSDK::OnLogin()
{
    [[HSWBEngine SharedWBEngine] Login];
}