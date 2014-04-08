#include "HSSocket.h"

HSSocket::HSSocket(const char* ip,int port,int type)
{
	this->m_socket = 0;
	this->m_curSendCount = 0;
	this->m_repeatSendCount = 0;
	this->m_iPort = port;
	this->m_strIp = ip;
	this->m_receiveBufferSize = 0;
	this->m_sendBufferSize = 0;
	this->m_receiveBuffer = NULL;
	this->m_sendBuffer = NULL;
	this->m_isConnectSucceed = false;
	this->m_socketType = type;
	this->m_thread = 0;
	this->m_hsSocketStart = HS_SOCKET_START_OVERTIME;
	this->Init();
}

HSSocket::~HSSocket(void)
{
	while(!this->m_SendDataQueue.empty())
	{
		this->m_SendDataQueue.pop();
	}
	while(!this->m_recvDataQueue.empty())
	{
		delete this->m_recvDataQueue.front().data;
		this->m_recvDataQueue.pop();
	}
	CC_SAFE_DELETE_ARRAY(this->m_receiveBuffer);
	this->ClosedSocket();
}

HSSocket* HSSocket::OpenSocket( const char* ip,const char* port,int type)
{
	int iPort = atoi(port);
	HSSocket* socket = new HSSocket(ip,iPort,type);
	return socket;
}

void HSSocket::Init()
{
	this->SetRepeatSendCount();
	this->SetReceiveBufferSize();
	this->SetSendBufferSize();
	this->StartThread();
}

void HSSocket::ClosedSocket()
{
	this->StopThread();
	if (this->GetSocket() > 0)
	{
#ifdef WIN32
		closesocket(this->GetSocket());
#else
		close(this->GetSocket());
#endif
	}
	this->m_socket = 0;
	this->SetIsConnectSucceed(false);
}

void HSSocket::SendData(string str)
{
	this->m_SendDataQueue.push(str);
	if (!this->IsConnectSucceed())
	{
		switch(this->GetSocketType())
		{
		case HS_SOCKET_TYPE_ONCE:
			this->StartThread();
			break;
		case HS_SOCKET_TYPE_KEEP:
			break;
		}
	}
}

void HSSocket::SetRepeatSendCount( int count /*= 3*/ )
{
	this->m_repeatSendCount = count;
}

void HSSocket::SetReceiveBufferSize( int size /*= 3*1024*/ )
{
	this->m_receiveBufferSize = size;
	if (this->m_receiveBuffer != NULL)
	{
		delete m_receiveBuffer;
		this->m_receiveBuffer = NULL;
		m_receiveBuffer = new char[size];
		memset((void*)this->m_receiveBuffer,0,size);
	}
}

void HSSocket::SetSendBufferSize(int size /*= 512*/)
{
	this->m_sendBufferSize = size;
	if (this->m_sendBuffer != NULL)
	{
		delete this->m_sendBuffer;
		this->m_sendBuffer = NULL;
		this->m_sendBuffer = new char[size];
		memset((void*)this->m_sendBuffer,0,size);
	}
}

void HSSocket::SetSocketType(int type)
{
	this->m_socketType = type;
}

bool HSSocket::Connect()
{
#ifdef WIN32
	//Set network synchronization
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2,0),&wsData) != 0)
	{
		CCLog("Set network synchronization error");
	}
#endif

	this->m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if (this->m_socket <= 0 || !this->SetSocketBuf())
	{
		CCLog("Create socket failed");
		return false;
	}

	struct timeval overTime;
	overTime.tv_sec = 6;
	overTime.tv_usec = 0;

	if (-1 == setsockopt(this->GetSocket(), SOL_SOCKET, SO_SNDTIMEO, (char *)&overTime, sizeof(overTime)))
	{
		CCLog("Set the [SO_SNDTIMEO] overtime failed");
		return false;
	}
	if (-1 == setsockopt(this->GetSocket(), SOL_SOCKET, SO_RCVTIMEO, (char *)&overTime, sizeof(overTime)))
	{
		CCLog("Set the [SO_RCVTIMEO]  overtime failed");
		return false;
	}

	struct sockaddr_in add;
	memset(&add,0,sizeof(struct sockaddr_in));
	add.sin_family = AF_INET;//UNIX:(AF_INET or AF_UNIX)
	add.sin_port = htons(this->GetSocketPort());
	add.sin_addr.s_addr = inet_addr(this->GetSocketIP());

#pragma region Non-blocking
#ifdef WIN32
	unsigned long ul = 1;
	ioctlsocket(this->GetSocket(), FIONBIO, (unsigned long*)&ul);
#else
	fcntl(this->GetSocket(), F_SETFL,fcntl(this->GetSocket(), F_GETFL)|O_NONBLOCK);
#endif
#pragma endregion Non-blocking

	int code = connect(this->GetSocket(),(struct sockaddr *)&add, sizeof(struct sockaddr));
	if (code == -1)
	{
		fd_set set;
		FD_ZERO(&set);
		FD_SET(this->GetSocket(), &set);
		int selectCode = -1;

		selectCode = select(this->GetSocket() + 1, &set,&set, NULL, &overTime);
		switch (selectCode)
		{
		case 0:
			//CCMessageBox("Link server failure","Server");
			CCLog("Link overtime");
			m_hsSocketStart = HS_SOCKET_START_OVERTIME;
			this->ClosedSocket();
			return false;
		case 1:
			CCLog("Connect ok : %s:%d",this->GetSocketIP(),this->GetSocketPort());
			this->SetIsConnectSucceed(true);
			m_hsSocketStart = HS_SOCKET_START_CONNECTED;
			break;
		case -1:
			CCLog("Connection please wait");
			m_hsSocketStart = HS_SOCKET_START_WAIT;
			break;
		}
	}
	return true;
}

int HSSocket::GetSocket()
{
	return this->m_socket;
}

bool HSSocket::SetSocketBuf()
{
	int isMTU = 1;	//Allow hair fragmented packets(MTU): 1. Allow ------- 0.is not allowed
	int rcvBufSize = 65536;
	int sendBufSize = 65536;
	if(-1 == setsockopt(this->GetSocket(), IPPROTO_TCP, TCP_NODELAY, (char *)&isMTU, sizeof(int))){
		CCLog("Whether to allow sending MTU, setting error");
		return false;
	}
	if (-1 == setsockopt(this->GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&rcvBufSize, sizeof(int))){
		CCLog("Set the receive buffer : %d",rcvBufSize);
		return false;
	}
	if (-1 == setsockopt(this->GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&sendBufSize, sizeof(int))){
		CCLog("Set the send buffer : %d",sendBufSize);
		return false;
	}
	
	return true;
}

#ifdef WIN32
	DWORD WINAPI HSSocket::SocketThreadUpdate(LPVOID lparam)
	{
		HSSocket *pThis = (HSSocket*)lparam;
		pThis->Connect();
		return 0;
	}
#else
	void* HSSocket::SocketThreadUpdate(void *lpParam)
	{
		HSSocket *pThis = (HSSocket*)lpParam;
		pThis->Connect();
		return NULL;
	}
#endif

void HSSocket::StopThread()
{
	if (this->m_thread != 0)
	{
#if WIN32
		WaitForSingleObject(this->m_thread, INFINITE);
		BOOL is = CloseHandle(this->m_thread);
#else
		pthread_join(this->m_thread, NULL);
#endif
	}	
	this->m_thread = 0;
}

void HSSocket::StartThread()
{
#if WIN32
	m_thread = CreateThread(NULL, 0, HSSocket::SocketThreadUpdate, (LPVOID)this, 0, NULL);
#else
	pthread_create(&m_thread, NULL, HSSocket::SocketThreadUpdate, (void *)this);
#endif
}

long HSSocket::Swap_long(unsigned long& v)
{
	v = (v << 24) |  
		((v << 8) & 0x00ff0000u) |  
		((v >> 8) & 0x0000ff00u) |  
		(v >> 24);
	return v;
}

void HSSocket::Send()
{
	if (!this->IsConnectSucceed())
	{
		return;
	}

	while(!this->m_SendDataQueue.empty())
	{
		string sendData = this->m_SendDataQueue.front();

		unsigned long lenth = sendData.length();
		this->Swap_long(lenth);
		
		if ((int)sendData.length() + (int)HS_SOCKET_PACKAGE_SIZE > this->GetSendBufferSize())
		{
			this->SetSendBufferSize(sendData.length() + HS_SOCKET_PACKAGE_SIZE);
		}
		if(this->m_sendBuffer == NULL)
		{
			this->m_sendBuffer = new char[this->GetSendBufferSize()];
		}
		memset(this->m_sendBuffer,0,this->GetSendBufferSize());
		memcpy(this->m_sendBuffer,(char*)&lenth,HS_SOCKET_PACKAGE_SIZE);
		memcpy(this->m_sendBuffer + HS_SOCKET_PACKAGE_SIZE,sendData.c_str(),sendData.length());	

		int code = 0;
		int sendSize = 0;

		while(sendSize < (int)sendData.length() + (int)HS_SOCKET_PACKAGE_SIZE && this->m_curSendCount < this->GetRepeatSendCount())
		{
			code = send(this->GetSocket(),this->m_sendBuffer,sendData.length() + HS_SOCKET_PACKAGE_SIZE,0);
			if (-1 == code)
			{
				CCLog("Again send data count:(%d)%%(%d)......",++this->m_curSendCount,this->GetRepeatSendCount());
			}else if(code > 0){
				CCLog("Send Byte: (%d) %% (%d)",code,sendData.length() + HS_SOCKET_PACKAGE_SIZE);
				sendSize += code;
			}
		}
		this->m_SendDataQueue.pop();
	}
	
}

void HSSocket::Receive()
{
	if (!this->IsConnectSucceed())
	{
		return;
	}

	struct timeval overTime;
	overTime.tv_sec = 0;
	overTime.tv_usec = 0;
	
	fd_set fds;
	FD_ZERO(&fds); 
	FD_SET(this->GetSocket(), &fds);  
	int code = select(this->GetSocket() + 1, &fds, NULL, NULL, &overTime); 
	if (code < 0)
	{
		//CCLog("Receive data error code is %d",code);
		return;
	}
	if (this->m_receiveBuffer == NULL)
	{
		this->m_receiveBuffer = new char[this->GetReceiveBufferSize()];
	}

	memset((void*)m_receiveBuffer,0,this->GetReceiveBufferSize());

	bool isRecv = true;
	int recvCode = 0;
	unsigned long needRecvSize = 0;
	int curRecvSize = 0;


	while(isRecv)
	{
		recvCode = recv(this->GetSocket(),m_receiveBuffer,this->GetReceiveBufferSize(),0);
		if (recvCode == -1)
		{
			//CCLog("recvCode :%d",recvCode);
			return;
		}
		if (needRecvSize == 0)
		{
			unsigned long lenth = 0;
			memcpy(&lenth,m_receiveBuffer,HS_SOCKET_PACKAGE_SIZE);
			needRecvSize = this->Swap_long(lenth);
			CCLog("Need recv data size : %ld",needRecvSize);
			if (needRecvSize > (unsigned long)this->GetReceiveBufferSize())
			{
				char* tempBuffer = new char[recvCode];
				memset(tempBuffer,0,recvCode);
				memcpy(tempBuffer,m_receiveBuffer,recvCode);
				this->SetReceiveBufferSize(needRecvSize);
				if (NULL != m_receiveBuffer)
				{
					memcpy(m_receiveBuffer,tempBuffer,recvCode);
				}
				delete tempBuffer;
				tempBuffer = NULL;
			}
		}
		curRecvSize += recvCode;
		if(needRecvSize == curRecvSize - sizeof(int))
		{
			isRecv = false;
		}else{
			isRecv = true;
		}
	}
	HSFilter::ShareFilter()->CreaterMessage(m_receiveBuffer + HS_SOCKET_PACKAGE_SIZE,needRecvSize);
	
	switch (this->GetSocketType())
	{
	case HS_SOCKET_TYPE_ONCE:
		this->ClosedSocket();
		break;
	case  HS_SOCKET_TYPE_KEEP:
		break;
	}
}

void HSSocket::Updata()
{
	this->Send();
	this->Receive();
}



