//
//  HSSDK.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#ifndef __HSSDK_H__
#define __HSSDK_H__


class HSSDK
{
private:
    HSSDK();
public:
    ~HSSDK();
    
public:
    static HSSDK* S_HSSDK;
public:
    static HSSDK* SharedSDK();
    
    void OnLogin();
    
};

#endif /* defined(__HSSDK_H__) */
