/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/10/22   16:43
 *	File base:	HSSocketInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSocketInterface_H__
#define __HSSocketInterface_H__
#pragma once
#include "HSBase.h"
#include "HSSocketRecvData.h"
#include "HSSocketSendData.h"
#include "HSIPAddress.h"
#include "HSLock.h"
#include <queue>

#include <pthread.h>
#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#pragma comment( lib, "ws2_32.lib" )
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <memory.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#ifndef TCP_NODELAY
#define TCP_NODELAY	0x0001
#endif

#endif


typedef enum
{
    HSSocket_Type_HTTP,
    HSSocket_Type_SOCKET,
    
}HSSocketType;

typedef enum
{
    Error_Invalid,
    Error_ConnectTimeout,
    Error_SendData,
    Error_RecvData,
    Error_RecvDataTimeout,
    Error_RecvTimeout,
    Error_ConnectClose,
    
}HSSocketError;

class HSSocketInterface
{
public:
	HSSocketInterface(void);
	virtual ~HSSocketInterface(void);
protected:
    HSIPAddress m_ipAddress;
    int m_iServPort;
    int m_pSocket;
    
    bool m_isConnect;
    bool m_isIdle;
    bool m_isSendAction;
    bool m_isRecvThreadAlive;
    
    char* m_pRecvBuf;
    char* m_pSendBuf;
    int m_recvBufSize;
    int m_sendBufSize;
    
    int m_currentSendSize;
    int m_currentRecvSize;
    unsigned long m_needRecvSize;
    
    queue<HSSocketRecvData*> m_recvDataQueue;
    queue<HSSocketSendData> m_sendDataQueue;
    
    float m_fSendDataInterval;
    
    HSSocketType m_type;
    
    pthread_t m_connectID;
    pthread_t m_RecvID;
    
    float m_recvTimeout;    //单位(秒)
    
    HSSocketError m_error;
    HSLock m_lock;
    
private:
    static void* ThreadConnect(void* arg);
    static void* ThreadRecvData(void* arg);
public:
    /* 连接关闭 */
    virtual void ConnectionCloseNotification() = 0;
    /* 连接超时通知 */
    virtual void ConnectionTimeoutNotification() = 0;
    /* 连接成功通知 */
    virtual void ConnectionSucceedNotification(const char* ip,int iServPort) = 0;
    /* 发送数据异常通知 */
    virtual void SendDataErrorNotification() = 0;
    /* 接收数据异常通知 */
    virtual void RecvDataErrorNotification() = 0;
    /* 接收数据超时通知 */
    virtual void RecvDataTimeoutNotification() = 0;
    /* 处理接收数据 */
    virtual bool Handle(const void* pBuf,int size) = 0;
    /* 是否发送数据 */
    virtual bool IsSend() = 0;
    
public:
    bool Open();
    
    bool Open(HSIPAddress& ip,int iServPort);
    
    bool Init(HSSocketType type,const char* ip,int iServPort);
    
    bool CreateRecvThread();
    
    void Closed();
    
    HSSocketType GetType();
    
    HSIPAddress GetIPAddress();
    
    int GetServPort();
    
    void SetRecvBufSize(int size = 6*1024);
    
    void SetSendBufSize(int size = 512);
    
    bool SetSocketBuf();
    
    int GetSocket();
    
    bool IsIdle();
    
    void SetIdle(bool is);
    
    bool IsConnected();
    
    void SetConnected(bool is);
    
    bool Recv();

    long Swap_long(unsigned long& v);
    
    float GetSendDataInterval();
    
    bool Send();
        
    void AddSendData(const HSSocketSendData& sendData);
    
    void HandleError();
        
    void Updata(float dt);
	
};


#endif // __HSSocketInterface_H____

