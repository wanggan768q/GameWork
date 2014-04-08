/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/10/16   14:32
 *	File base:	HSSocket.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSocket_H__
#define __HSSocket_H__
#pragma once

#ifdef WIN32
	//#include <Windows.h>
	#pragma comment (lib, "WS2_32.lib")
#else
	#include <memory.h>
	#include <pthread.h>
	#include <sys/socket.h>
	#include <netinet/in.h>  // sockaddr_in结构体调用
	#include <arpa/inet.h>   // 数据顺序转换调用
	#include <unistd.h>      // close(); 调用
	#include <netdb.h>       // gethostbyname();调用
	#include <errno.h>       // 错误返回标志
	#include <fcntl.h>
	#include <time.h>
#endif
#include <queue> 
#include <string>
#include <vector>
#include "HSFilter.h"
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

#ifdef WIN32
	typedef HANDLE HSThread;
#else
	typedef pthread_t HSThread;
#endif

class HSFilter;

#define HS_SOCKET_PACKAGE_SIZE (sizeof(int))

#ifndef TCP_NODELAY
#define TCP_NODELAY	0x0001
#endif

#define HS_SOCKET_TYPE_ONCE 0
#define HS_SOCKET_TYPE_KEEP 1

typedef enum
{
	HS_SOCKET_START_OVERTIME = 0x01,
	HS_SOCKET_START_CONNECTED,
	HS_SOCKET_START_WAIT,

}HSSocketStart;

class HSSocket
{	
private:
	HSSocket(const char* ip,int port,int type);
public:
	~HSSocket(void);

public:
	typedef struct{
		char* data;
		int size;
	}HSRecvData;

private:
	int m_socket;
	int m_repeatSendCount;
	int m_curSendCount;
	int m_receiveBufferSize;
	int m_sendBufferSize;
	HSThread m_thread;

	string m_strIp;
	int m_iPort;

	queue<string> m_SendDataQueue;	

	queue<HSRecvData> m_recvDataQueue;
	char* m_receiveBuffer;
	char* m_sendBuffer;

	bool m_isConnectSucceed;

	int m_socketType;

	HSSocketStart m_hsSocketStart;
	
public:

	static HSSocket* OpenSocket(const char* ip,const char* port,int type);

	void ClosedSocket();

	void SendData(string str);

	void SetRepeatSendCount(int count = 3);
	
	void SetReceiveBufferSize(int size = 3*1024);

	void SetSendBufferSize(int size = 512);

	void Updata();

	inline int GetRepeatSendCount(){return this->m_repeatSendCount;}

	inline const char* GetSocketIP(){return this->m_strIp.c_str();}

	inline int GetSocketPort(){return this->m_iPort;}

	inline int GetReceiveBufferSize(){return this->m_receiveBufferSize;}

	inline int GetSendBufferSize(){return this->m_sendBufferSize;}

	inline bool IsConnectSucceed(){return this->m_isConnectSucceed;}

	inline int GetSocketType(){return this->m_socketType;}

	inline HSSocketStart GetSocketStart(){return this->m_hsSocketStart;}
protected:
	void Init();

	bool Connect();

	int GetSocket();

	bool SetSocketBuf();

	void SetSocketType(int type);

	void StartThread();

	void StopThread();	

	inline void SetIsConnectSucceed(bool is){this->m_isConnectSucceed = is;}

#ifdef WIN32
	static DWORD WINAPI SocketThreadUpdate(LPVOID lparam);
#else
	static void* SocketThreadUpdate(void *lpParam);
#endif

	long Swap_long(unsigned long& v);

	void Send();

	void Receive();

};


#endif // __HSSocket_H____
