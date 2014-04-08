/********************************************************************
 *  Copyright(C) 2012 Ambition_HS ( All rights reserved. )
 *	Created:	2012/10/16   14:32
 *	File base:	HSSocket.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSocket_H__
#define __HSSocket_H__
#pragma once
#include "HSSocketTemp.h"
class HSFilter;




class HSSocket : public HSSocketTemp
{	
private:
	HSSocket(HSSocketType type,const char* ip,int iServPort);
public:
	~HSSocket();
    
private:
    std::string m_ip;
    int m_iServport;
    int m_tag;
    
    bool m_isStart;


public:
    
    static HSSocket* Create(HSSocketType type,const char* ip,int iServPort);
    
    void SetAddress(HSSocketType type,const char* ip,int iServPort);
    
    void SetTag(int tag);
    
    bool Start();
    /* 连接关闭 */
    virtual void ConnectionCloseNotification();
    /* 连接超时通知 */
    virtual void ConnectionTimeoutNotification();
    /* 连接成功通知 */
    virtual void ConnectionSucceedNotification(const char* ip,int iServPort);
    /* 发送数据异常通知 */
    virtual void SendDataErrorNotification();
    /* 接收数据异常通知 */
    virtual void RecvDataErrorNotification();
    /* 接收数据超时通知 */
    virtual void RecvDataTimeoutNotification();
    /* 处理接收数据 */
	virtual bool Handle(const void* pBuf,int size);
    /* 是否发送数据 */
    virtual bool IsSend();

};


#endif // __HSSocket_H____
