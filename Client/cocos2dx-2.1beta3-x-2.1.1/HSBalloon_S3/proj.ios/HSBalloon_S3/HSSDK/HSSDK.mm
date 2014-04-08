//
//  HSSDK.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#include "HSSDK.h"
#import "HSWBEngine.h"
#import "HSSDK_Request.h"
#include "HSJava.h"
#import "HSSDK_Pay.h"

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

void HSSDK::Login(int wbType)
{
    switch (wbType) {
        case HS_SDK_TXWB:
        {
            [[HSWBEngine SharedWBEngine] Login];
        }
            break;
            
        default:
            break;
    }
}

void HSSDK::PostText(const char* text,int wbType)
{
    NSString* pStr = [NSString stringWithCString:text encoding:NSUTF8StringEncoding];
    switch (wbType)
    {
        case HS_SDK_TXWB:
        {
            [[HSWBEngine SharedWBEngine] PostText:pStr];
        }
            break;
            
        default:
            break;
    }
}

void HSSDK::SetGameUUID(const char* gameUUID)
{
    this->m_gameUUID = gameUUID;
    HSSDK_Request* pSdkReq = [HSSDK_Request SharedSDKRequest];
    
    NSString* pStr = [NSString stringWithCString:m_gameUUID.c_str() encoding:NSUTF8StringEncoding];
    NSLog(@"%@",pStr);
    [pSdkReq setM_gameUUID:pStr];
}

void HSSDK::SetWBType(const char* type)
{
    this->m_type = type;
    HSSDK_Request* pSdkReq = [HSSDK_Request SharedSDKRequest];
    NSString* pStr = [NSString stringWithCString:m_type.c_str() encoding:NSUTF8StringEncoding];
    [pSdkReq setM_type:pStr];
}

void HSSDK::SetAPPID(int appid)
{
    this->m_appID = appid;
    HSSDK_Request* pSdkReq = [HSSDK_Request SharedSDKRequest];
    [pSdkReq setM_appid:appid];
}

void HSSDK::LoginResponse(const char* pJson)
{
    HSJava::ShaderJava()->Callback(pJson);
}

bool HSSDK::Buy(int itemID)
{
    [[HSSDK_Pay SharedPay] Pay:itemID];
    return true;
}





