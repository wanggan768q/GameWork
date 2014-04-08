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
#include "socketcc.h"
#include  "HSSocketRecvData.h"
#include <queue>

typedef enum
{
    
    HSSocket_Type_HTTP,
    HSSocket_Type_SOCKET,
    
}HSSocketType;

class HSSocketInterface
{
public:
	HSSocketInterface(void);
	~HSSocketInterface(void);
protected:
    IPAddress m_ipAddress;
    int m_iServPort;
    TCPClientSocket* m_pSocket;
    bool m_isConnect;
    bool m_isIdle;
    bool m_isSendAction;
    
    char* m_pRecvBuf;
    char* m_pSendBuf;
    int m_recvBufSize;
    int m_sendBufSize;
    
    int m_currentSendSize;
    int m_currentRecvSize;
    unsigned long m_needRecvSize;
    
    queue<HSSocketRecvData*> m_recvDataQueue;
    queue<std::string> m_sendDataQueue;
    
    float m_fSendDataInterval;
    
    HSSocketType m_type;
    
    
private:
    static void* ThreadConnect(void* arg);
    static void* ThreadRecvData(void* arg);
public:
    virtual bool Handle(const void* pBuf,int size) = 0;
    
    virtual bool IsSend() = 0;
    
public:
    bool Open();
    
    bool Open(IPAddress& ip,int iServPort);
    
    bool Init(HSSocketType type,const char* ip,int iServPort);
    
    void Closed();
    
    HSSocketType GetType();
    
    IPAddress GetIPAddress();
    
    int GetServPort();
    
    void SetRecvBufSize(int size = 6*1024);
    
    void SetSendBufSize(int size = 512);
    
    TCPClientSocket* GetSocket();
    
    bool IsIdle();
    
    void SetIdle(bool is);
    
    bool IsConnected();
    
    void SetConnected(bool is);
    
    bool Recv();
    
    long Swap_long(unsigned long& v);
    
    float GetSendDataInterval();
    
    bool Send();
        
    void AddSendData(const std::string& sendData);
    
    void Updata(float dt);
	
};


#endif // __HSSocketInterface_H____

