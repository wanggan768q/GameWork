/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/10/22   16:43
 *	File base:	HSSocketTemp.h
 *	Author:		Ambition
 *
 *	Purpose:
*********************************************************************/
#ifndef __HSSocketTemp_H__
#define __HSSocketTemp_H__
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
    Error_OpenConnectionFail,
    Error_SelectTimeOut,

}HSSocketError;

typedef enum
{
	Close_Nomal,
	Close_Active,
	Close_Passive,
}HSConnectionCloseType;


class HSSocketTemp
{
public:
	HSSocketTemp(void);
	virtual ~HSSocketTemp(void);
protected:
    HSIPAddress m_ipAddress;
    int m_iServPort;
    int m_pSocket;

    char* m_pRecvBuf;
    char* m_pSendBuf;
    int m_recvBufSize;
    int m_sendBufSize;

    int m_currentSendSize;
    int m_currentRecvSize;
    unsigned long m_needRecvSize;

    char* m_pRecvHeadBuf;
    int m_recvHeadBufSize;
    int m_currentRecvHeadSize;

    queue<HSSocketRecvData*> m_recvDataQueue;
    queue<HSSocketSendData> m_sendDataQueue;

    HSSocketType m_type;

    float m_recvTimeout;    //单位(秒)

    HSSocketError m_error;
    HSSocketError m_handlerError;

    HSConnectionCloseType m_connectionCloseType;

    HSLock lock;
    pthread_t m_thread;
    pthread_cond_t m_cond;
    pthread_mutex_t m_mutex;
    HSSocketSendData* m_psendData;

    bool m_isClose;
    bool isLoop;
private:
    static void* Run(void* arg);
    static void* Sender(void* arg);

    //static void* ThreadRece
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

    void Closed(HSConnectionCloseType);

    HSSocketType GetType();

    HSIPAddress GetIPAddress();

    int GetServPort();

    void SetRecvBufSize(int size = 6*1024);

    void SetSendBufSize(int size = 512);

    bool SetSocketBuf();

    int GetSocket();

    bool Recv();

    bool RecHead();

    bool RecBody();

    bool checkRec();

    bool IsNeedOpen();

    const bool& isClose();

    void SetIsClose(bool);

    long Swap_long(unsigned long& v);

    bool Send(HSSocketSendData& hsSocketSendData);

    void AddSendData(const HSSocketSendData& sendData);

    HSSocketSendData* GetSendData();

    void PopSendData();

    void HandleError();

    void Updata(float dt);

};


#endif // __HSSocketInterface_H____

