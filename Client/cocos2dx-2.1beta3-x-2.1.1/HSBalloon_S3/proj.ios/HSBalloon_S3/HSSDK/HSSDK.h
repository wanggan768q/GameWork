//
//  HSSDK.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#ifndef __HSSDK_H__
#define __HSSDK_H__
#include <string>
using namespace std;

#define HS_SDK_TXWB 0x01
#define HS_SDK_XLWB 0x02

class HSSDK
{
private:
    HSSDK();
public:
    ~HSSDK();
    
private:
    int m_appID;
    std::string m_gameUUID;
    std::string m_type; //微博类型
    
    
public:
    static HSSDK* S_HSSDK;
public:
    static HSSDK* SharedSDK();
    
    /** 登陆 */
    void Login(int wbType);
    /** 登陆响应 */
    void LoginResponse(const char* pJson);
    /** 发微博 */
    void PostText(const char* text,int wbType);
    /** 设置游戏ID*/
    void SetGameUUID(const char* gameUUID);
    /** 设置微博类型*/
    void SetWBType(const char* type);
    /** 设置产品ID*/
    void SetAPPID(int appid);
    /** 购买物品*/
    bool Buy(int itemID);
    
    
    
};

#endif /* defined(__HSSDK_H__) */
