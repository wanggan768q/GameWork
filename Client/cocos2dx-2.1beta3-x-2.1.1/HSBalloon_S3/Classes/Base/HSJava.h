/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/24   15:39
 *	File base:	HSJava.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSJava_H__
#define __HSJava_H__
#pragma once
#include "HSBase.h"
#include "HSJni.h"
#include "HSLock.h"


class HSJava : private cocos2d::CCObject
{
public:
	HSJava(void);
	~HSJava(void);
    
private:
    
    struct _CacheNode
    {
        _CacheNode(const char* pData,int size)
        {
            this->data = new char[size];
            memcpy(data, pData, size);
            this->size = size;
        }
        ~_CacheNode()
        {
            CC_SAFE_DELETE_ARRAY(data);
            size = 0;
        }
        char* data;
        int size;
    };
    
    std::vector<_CacheNode*> m_JsonCacheDataList;
    std::vector<_CacheNode*> m_GameCacheDataList;
    
    HSLock m_jsonCacheDataLock;
    HSLock m_gameCacheDataLock;
    
    void HandleJsonCacheData(const char* pData,int size);
    
    void HandleGameCacheData(const char* pData,int size);

public:

	static HSJava* ShaderJava();
    
    void Updata(float dt);
    
    bool init();
    
    void Init(const char* json);
    
    

	void CallBuy( int propID );


	void CallFinishInit(const char*);
	void CallFinishPay(const char*);
	void Callback(const char*);



	
	void Pay(int money);
	CCString*  JavaExec(const char* json);
    
#if HSIos
    CCString* Exec(const char* json);
#endif
    
    
	void KillProcess();
	int  CheckUser();
	void NotifyVersionCode(int newVersionCode);

	int  GetVersion();
	CCString* GetVersionName();
	int  GetChannel();
	CCString* GetPhoneModel();

	void ShowToast(const char* text,int dt = 0);

	void OpenURL(const char* text);
    
    void TestProto(const char* pdata,int size);

	/**
	 * 发送数据包，要求服务器转发
	 */
	void autoDistribute(const char* data,int size);

	/**
	 * 发送数据包，只转发其他人，自己不会儿收到
	 */
	void distributeDataToOthers(const char* data,int size);
	/**
	 * 发送数据包，要求服务器处理后再转发
	 */
	void handleDistribute(const char* data,int size);

	/**
	 * 服务器处理后转发数据包
	 */
	void distribute(const char* data,int size);

	/**
	 * 服务器收到要处理的数据
	 */
	void onHandleDistribute(const char* data,int pdataSize);
	/**
	 * 客户端收到服务器处理后转发来的数据
	 */
	void onHandleDistributeReceived(const char* data,int pdataSize);

	void disConnect(bool b);
    /**
     * 停止搜索分享圈
     */
    void StopSearchingShareCircle();

public:
	long long m_lastTime;
};

#endif // __HSJava_H____


