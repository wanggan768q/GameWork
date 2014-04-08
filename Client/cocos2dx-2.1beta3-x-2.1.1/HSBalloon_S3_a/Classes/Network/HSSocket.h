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
#include "HSSocketInterface.h"
class HSFilter;




class HSSocket : public HSSocketInterface
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
    
	virtual bool Handle(const void* pBuf,int size);
    
    virtual bool IsSend();

};


#endif // __HSSocket_H____
