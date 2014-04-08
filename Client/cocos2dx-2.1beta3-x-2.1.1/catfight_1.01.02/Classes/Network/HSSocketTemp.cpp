#include "HSSocketTemp.h"
#include "HSSocket.h"
#include "HSTime.h"
#include "HSSocketPool.h"
#include<signal.h>
HSSocketTemp::HSSocketTemp()
{
    m_pSocket = INVALID_SOCKET;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
    m_currentRecvSize = 0;
    m_recvBufSize = 0;
    m_sendBufSize = 0;
    m_needRecvSize = 0;
    m_currentSendSize = 0;

    m_error = Error_Invalid;
    m_handlerError = Error_Invalid;
    //this->SetSendBufSize();
    this->SetRecvBufSize();
    //m_pRecvHeadBuf

    m_connectionCloseType = Close_Nomal;

    m_pRecvHeadBuf = new char[4];
    m_recvHeadBufSize = 4;
    m_currentRecvHeadSize = 0;

    m_psendData = NULL;
    isLoop = false;
    this->SetIsClose(true);
}

HSSocketTemp::~HSSocketTemp()
{
    Closed(Close_Nomal);

    CC_SAFE_DELETE(m_pRecvBuf);
    CC_SAFE_DELETE(m_pSendBuf);


    while (!m_recvDataQueue.empty())
    {
        HSSocketRecvData* pData = m_recvDataQueue.front();
        delete pData;
        m_recvDataQueue.pop();
    }
    while (!m_sendDataQueue.empty())
    {
        m_recvDataQueue.pop();
    }

    m_currentRecvSize = 0;
    m_recvBufSize = 0;
    m_sendBufSize = 0;
    m_needRecvSize = 0;
}

bool HSSocketTemp::Open()
{
	isLoop = true;
	this->SetIsClose(false);
	CCLog("HSSocketTemp constructor");

	if(m_type == HSSocket_Type_HTTP)
	{

		m_recvTimeout = 10;
		pthread_mutex_init(&m_mutex, NULL);
		pthread_cond_init(&m_cond, NULL);

		if(pthread_create(&m_thread, NULL, Run, this) != 0)
		{
		   HSMessageBox("发送线程创建错误");
		}
	}
	else if(m_type == HSSocket_Type_SOCKET)
	{
		m_recvTimeout = 1;
		pthread_mutex_init(&m_mutex, NULL);
		pthread_cond_init(&m_cond, NULL);

		if (pthread_create(&m_thread, NULL, Sender, this) != 0)
		{
		   HSMessageBox("发送线程创建错误");
		}
	}
    return true;
}



bool HSSocketTemp::Open(HSIPAddress& ip,int iServPort)
{
    try {

#ifdef WIN32
        //Set network synchronization
        WSADATA wsData;
        if (WSAStartup(MAKEWORD(2,0),&wsData) != 0)
        {
            CCLOG("Set network synchronization error");
        }
#endif

        this->m_pSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
        if (this->m_pSocket <= 0 || !this->SetSocketBuf())
        {
            CCLOG("Create socket failed");
            return false;
        }

        struct timeval overTime;
        overTime.tv_sec = 6;
        overTime.tv_usec = 0;

        if (-1 == setsockopt(this->GetSocket(), SOL_SOCKET, SO_SNDTIMEO, (char *)&overTime, sizeof(overTime)))
        {
            CCLOG("Set the [SO_SNDTIMEO] overtime failed");
            return false;
        }

        struct sockaddr_in add;
        memset(&add,0,sizeof(struct sockaddr_in));
        add.sin_family = AF_INET;//UNIX:(AF_INET or AF_UNIX)
        add.sin_port = htons(m_iServPort);
        add.sin_addr.s_addr = inet_addr(m_ipAddress.GetIP());

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
            fd_set wset;
            FD_ZERO(&wset);
            FD_SET(this->GetSocket(), &wset);
            int selectCode = -1;

            selectCode = select(this->GetSocket() + 1, &wset,&wset, NULL, &overTime);
            switch (selectCode)
            {
            	CCLog("connection selectCode %d",selectCode);
                case 0:
                	if(m_type==HSSocket_Type_SOCKET)
                	{
                		 m_error = Error_ConnectTimeout;
                	}
                	CCLog(CCString::createWithFormat("Connection timeout [code %d]",selectCode)->getCString());
                    return false;
                case 1:
                {
                	CCLog("Connect ok : %s:%d",m_ipAddress.GetIP(),m_iServPort);

                    this->ConnectionSucceedNotification(m_ipAddress.GetIP(),m_iServPort);
                }
                break;

                default:
                {
                    return false;
                }
            }
        }



    }catch(...){



        HSMessageBox(" Unexpected exception ");
        return false;
    }

    return true;
}

bool HSSocketTemp::SetSocketBuf()
{
	int isMTU = 1;	//Allow hair fragmented packets(MTU): 1. Allow ------- 0.is not allowed
	int rcvBufSize = 65536;
	int sendBufSize = 65536;
	if(-1 == setsockopt(this->GetSocket(), IPPROTO_TCP, TCP_NODELAY, (char *)&isMTU, sizeof(int))){
		CCLOG("Whether to allow sending MTU, setting error");
		return false;
	}
	if (-1 == setsockopt(this->GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&rcvBufSize, sizeof(int))){
		CCLOG("Set the receive buffer : %d",rcvBufSize);
		return false;
	}
	if (-1 == setsockopt(this->GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&sendBufSize, sizeof(int))){
		CCLOG("Set the send buffer : %d",sendBufSize);
		return false;
	}

	return true;
}

bool HSSocketTemp::Init(HSSocketType type,const char *ip, int iServPort)
{
    m_ipAddress.SetHostName(ip, false);
    m_iServPort = iServPort;
    m_type = type;
    return true;
}

HSSocketType HSSocketTemp::GetType()
{
    return m_type;
}

void HSSocketTemp::SetRecvBufSize(int size /*= 6*1024*/)
{
    m_recvBufSize = size;
    char* pTempBuf = NULL;

    if(m_currentRecvSize != 0 && m_pRecvBuf)
    {
        pTempBuf = new char[m_currentRecvSize];
        memset(pTempBuf, 0, m_currentRecvSize);
        memcpy(pTempBuf,m_pRecvBuf,m_currentRecvSize);
    }
    if (!m_pRecvBuf) {
        m_pRecvBuf = new char[size];
    }else{
        delete m_pRecvBuf;
        m_pRecvBuf = NULL;
        m_pRecvBuf = new char[size];
        memset(m_pRecvBuf, 0, size);
    }
    if(pTempBuf)
    {
        memcpy(m_pRecvBuf, pTempBuf, m_currentRecvSize);
    }
}

void HSSocketTemp::SetSendBufSize(int size /*= 512*/)
{
	m_sendBufSize = size;

    if (!m_pSendBuf)
    {
        m_pSendBuf = new char[size];
    }
    else
    {
        delete m_pSendBuf;
        m_pSendBuf = NULL;
        m_pSendBuf = new char[size];
    }
    memset(m_pSendBuf, 0, size);
}


int HSSocketTemp::GetSocket()
{
    return m_pSocket;
}

bool HSSocketTemp::Recv()
{
	bool isLoop = true;

	while(isLoop)
	{
		if(RecHead())
		{
			if(RecBody())
			{
				return true;
			}
			else
			{
				isLoop = false;
			}
		}
		else
		{

			isLoop = false;
		}
	}
	return false;
}

bool HSSocketTemp::RecHead()
{
	int m_currentRecvHeadSize =0;
	bool isLoop = true;
	if(checkRec())
	{
		while(isLoop)
		{
			int recvLen = recv(m_pSocket,m_pRecvHeadBuf + m_currentRecvHeadSize,m_recvHeadBufSize - m_currentRecvHeadSize,0);

			if (recvLen < 0 )
			{

				CCLog("套接字 : %d",m_pSocket);

				if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)//正常
				{
					continue;
				}

				m_error = Error_ConnectClose;
				return false;
			}
			else if(recvLen == 0)
			{
				//网络中断
				m_error = Error_ConnectClose;
				CCLog("head 服务器主动关闭连接(Recv): %s:%d:%d ",m_ipAddress.GetIP(),m_iServPort,m_currentRecvHeadSize);
				return false;
				//continue;
			}

			m_currentRecvHeadSize+=recvLen;

			if(m_currentRecvHeadSize == m_recvHeadBufSize)//收购了4个字节
			{
				 memcpy(&m_needRecvSize,m_pRecvHeadBuf,m_recvHeadBufSize);
				 memset(m_pRecvHeadBuf,0,m_recvHeadBufSize);
				 m_currentRecvHeadSize =0;
				 this->Swap_long(m_needRecvSize);
				 CCLog("head =%ld",m_needRecvSize);
				 return true;
			}
		}
	}
	else
	{
		return false;
	}

//	while(isLoop)
//	{
//		if(checkRec())
//		{
//				int recvLen = recv(m_pSocket,m_pRecvHeadBuf + m_currentRecvHeadSize,m_recvHeadBufSize - m_currentRecvHeadSize,0);
//
//				if (recvLen < 0 )
//				{
//
//					CCLog("套接字 : %d",m_pSocket);
//
////					if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)//正常
////					{
////
////					}
//
//					m_error = Error_ConnectClose;
//					isLoop = false;
//					return false;
//
//					//continue;
//				}
//				else if(recvLen == 0)
//				{
//					//网络中断
//					m_error = Error_ConnectClose;
//					CCLog("head 服务器主动关闭连接(Recv): %s:%d:%d ",m_ipAddress.GetIP(),m_iServPort,m_currentRecvHeadSize);
//					isLoop = false;
//					return false;
//					//continue;
//				}
//
//				m_currentRecvHeadSize+=recvLen;
//
//				if(m_currentRecvHeadSize == m_recvHeadBufSize)//收购了4个字节
//				{
//					 memcpy(&m_needRecvSize,m_pRecvHeadBuf,m_recvHeadBufSize);
//					 memset(m_pRecvHeadBuf,0,m_recvHeadBufSize);
//					 m_currentRecvHeadSize =0;
//					 this->Swap_long(m_needRecvSize);
//					 CCLog("head =%ld",m_needRecvSize);
//					 return true;
//				}
//		}
//		else
//		{
//			isLoop = false;
//		}
//	}
//	return false;
}

bool HSSocketTemp::RecBody()
{
	if(checkRec())
	{
		bool isLoop = true;
		while(isLoop)
		{
			int recvLen = recv(m_pSocket,m_pRecvBuf + m_currentRecvSize,m_needRecvSize - m_currentRecvSize,0);

			//SOCKET_ERROR;
			if(recvLen == -1)
			{
				CCLog("套接字 : %d",m_pSocket);
				if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)//正常
				{
					continue;
				}
				m_error = Error_ConnectClose;
				return false;
			}
			else if(recvLen == 0)
			{
				//网络中断
				m_error = Error_ConnectClose;
				CCLog("body 服务器主动关闭连接(Recv): %s:%d:%d:%d",m_ipAddress.GetIP(),m_iServPort,m_needRecvSize,m_currentRecvSize);
				return false;
			}

			m_currentRecvSize += recvLen;

			if(m_currentRecvSize == m_needRecvSize)
			{
				 HSSocketRecvData* pData = HSSocketRecvData::New(m_pRecvBuf, m_needRecvSize);
				 memset(m_pRecvBuf,0,m_needRecvSize);
				 m_currentRecvSize = 0;
				 m_needRecvSize = 0;
				 CCLog("rec lock");
				 lock.Lock();
				 m_recvDataQueue.push(pData);
				 lock.UnLock();
				 CCLog("rec unlock");
				 isLoop = false;
				 return true;
			}
		}
	}
	else
	{
		return false;
	}

//	while(isLoop)
//	{
//		if(checkRec())
//		{
//			int recvLen = recv(m_pSocket,m_pRecvBuf + m_currentRecvSize,m_needRecvSize - m_currentRecvSize,0);
//
//			//SOCKET_ERROR;
//			if(recvLen == -1)
//			{
//				CCLog("套接字 : %d",m_pSocket);
//
//				m_error = Error_ConnectClose;
//				isLoop = false;
//				return false;
//			}
//			else if(recvLen == 0)
//			{
//				//网络中断
//				m_error = Error_ConnectClose;
//				CCLog("body 服务器主动关闭连接(Recv): %s:%d:%d:%d",m_ipAddress.GetIP(),m_iServPort,m_needRecvSize,m_currentRecvSize);
//				isLoop = false;
//				return false;
//			}
//
//			m_currentRecvSize += recvLen;
//
//			if(m_currentRecvSize == m_needRecvSize)
//			{
//				 HSSocketRecvData* pData = HSSocketRecvData::New(m_pRecvBuf, m_needRecvSize);
//				 memset(m_pRecvBuf,0,m_needRecvSize);
//				 m_currentRecvSize = 0;
//				 m_needRecvSize = 0;
//				 CCLog("rec lock");
//				 lock.Lock();
//				 m_recvDataQueue.push(pData);
//				 lock.UnLock();
//				 CCLog("rec unlock");
//				 isLoop = false;
//				 return true;
//			}
//			CCLog("111111111111   %d:%d",m_currentRecvSize,m_needRecvSize);
//		}
//		else
//		{
//			isLoop = false;
//			CCLog("2222222222 %d:%d",m_currentRecvSize,m_needRecvSize);
//		}
//		CCLog("333333333333 %d:%d",m_currentRecvSize,m_needRecvSize);
//	}
//	CCLog("44444444444 %d:%d",m_currentRecvSize,m_needRecvSize);
//	return false;
}

bool HSSocketTemp::checkRec()
{
	bool isLoop = true;
	while(isLoop)
	{
		struct timeval overTime;
		overTime.tv_sec = m_recvTimeout;
		overTime.tv_usec = 0;
        
		fd_set rset;
		FD_ZERO(&rset);
        
        if (this->GetSocket()<=0)
        {
            CCLog("socket <=0 ");
            m_error = Error_ConnectClose;
            isLoop = false;
            continue;
        }
		FD_SET(this->GetSocket(), &rset);

		int code = select(this->GetSocket() + 1, &rset, NULL, NULL, &overTime);
		if (code == -1)//出错
		{
			CCLog("select -1 %d",errno);
			if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)//正常
			{
				continue;
			}
			m_error = Error_ConnectClose;
			isLoop = false;
		}
		else if(code == 0)//超时
		{
			CCLog("select 0 超时 %d,port(%d)",errno,this->GetServPort());
			m_error = Error_SelectTimeOut;
			isLoop = false;
			continue;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool HSSocketTemp::IsNeedOpen()
{

	if(!this->m_isClose && this->m_pSocket==INVALID_SOCKET)
	{
		return true;
	}
	return false;
}

const bool& HSSocketTemp::isClose()
{
	return this->m_isClose;
}

void HSSocketTemp::SetIsClose(bool isClose)
{
	if(isClose)
	{
		CCLog("set socket closed state port(%d)",this->GetServPort());
	}
	else
	{
		CCLog("set socket open state port(%d)",this->GetServPort());
	}
	this->m_isClose = isClose;
}



long HSSocketTemp::Swap_long(unsigned long& v)
{
    v = (v << 24) |
    ((v << 8) & 0x00ff0000u) |
    ((v >> 8) & 0x0000ff00u) |
    (v >> 24);
    return v;
}


bool HSSocketTemp::Send(HSSocketSendData& hsSocketSendData)
{

    const std::string sendData = hsSocketSendData.GetData();

    unsigned long lenth = sendData.length();

    this->Swap_long(lenth);

    if ((int)sendData.length() + 4 > m_sendBufSize)
    {
        SetSendBufSize((int)sendData.length() + 4);
    }

    if(!m_pSendBuf)
    {
        SetSendBufSize();
    }
    memset(m_pSendBuf,0,m_sendBufSize);
    memcpy(m_pSendBuf,(char*)&lenth,4);
    memcpy(m_pSendBuf + 4,sendData.c_str(),sendData.length());

    bool isSend = true;
    //每次重新发送 m_currentSendSize 清0
    m_currentSendSize =0;
    while (isSend)
    {
        try
        {

            m_currentSendSize = send(m_pSocket,m_pSendBuf + m_currentSendSize, (int)sendData.length() + 4 -m_currentSendSize,0);

            if(m_currentSendSize == (int)sendData.length() + 4)
            {
                CCLog("Send Byte: (%d) %% (%d) - (%s) (%d)\n",
                      m_currentSendSize,(int)sendData.length() + 4,
                      hsSocketSendData.GetDescribe(),hsSocketSendData.GetID());

                PopSendData();
                isSend = false;
                memset(m_pSendBuf, 0, m_sendBufSize);
                m_currentSendSize = 0;
                return true;

            }
            else if(m_currentSendSize == 0)
            {
            	m_error = Error_ConnectClose;
                isSend = false;
                CCLOG("服务器主动关闭连接(Send): %s:%d ",m_ipAddress.GetIP(),m_iServPort);
                return false;
            }
            else if(m_currentSendSize == -1)
            {
                m_error = Error_ConnectClose;
                isSend = false;
                CCLOG("非法套接字 (Send): %s:%d ",m_ipAddress.GetIP(),m_iServPort);
                return false;
            }

        }
        catch( ... )
        {
            CCLOG("【接收线程终止】客户端的 Send 方法抛出预料外的异常");
            isSend = false;
            m_error = Error_ConnectClose;
            return false;
        }
    }
    return true;
}


void HSSocketTemp::AddSendData(const HSSocketSendData& sendData)
{
	if(this->isClose())
	{
		CCLog("this socket is close so discard sendData Port(%d):%d",m_iServPort,m_sendDataQueue.size());
		return;
	}
	CCLog("HS Will Send Data Count lock-> Port(%d) : %d",m_iServPort,m_sendDataQueue.size());

	pthread_mutex_lock(&m_mutex);

	pthread_cond_signal(&m_cond);

	m_sendDataQueue.push(sendData);

	pthread_mutex_unlock(&m_mutex);

	//HSSocketSendData s = sendData;

	//const int& id = sendData.GetID();

	CCLog("HS Will Send Data Count unlock-> Port(%d) : %d",m_iServPort,m_sendDataQueue.size());
}

/**
 * 这个函数私有，只有网络线程可以访问，其他线程无权访问
 */
 HSSocketSendData* HSSocketTemp::GetSendData()
{
	CCLog("getSendData lock");
	pthread_mutex_lock(&m_mutex);
	bool loop = true;

	while(loop)
	{
		if(!m_sendDataQueue.empty())
		{
			loop = false;
		}
		else
		{
			CCLog("getSendData entry wait");
			if(m_type== HSSocket_Type_SOCKET&&!this->isClose())
			{
				struct timeval now;
				struct timespec outtime;
				gettimeofday(&now, NULL);
				outtime.tv_sec = now.tv_sec + 1;
				outtime.tv_nsec = now.tv_usec * 1000;
				pthread_cond_timedwait(&m_cond,&m_mutex,&outtime);
				loop = false;
			}
			else
			{
				pthread_cond_wait(&m_cond, &m_mutex);
			}

			CCLog("getSendData exit wait");
		}
	}

	HSSocketSendData* data = NULL;

	if(!m_sendDataQueue.empty())
	{
		data = &(m_sendDataQueue.front());
	}
	pthread_mutex_unlock(&m_mutex);
	CCLog("getSendData unlock");
	return data;
}

void HSSocketTemp::PopSendData()
 {
	 CCLog("send over lock");

	 pthread_mutex_lock(&m_mutex);
	 if(!m_sendDataQueue.empty())
	 {
		 m_sendDataQueue.pop();
	 }
	 pthread_mutex_unlock(&m_mutex);
	 CCLog("send over unlock ");
 }


HSIPAddress HSSocketTemp::GetIPAddress()
{
    return m_ipAddress;
}

int HSSocketTemp::GetServPort()
{
    return m_iServPort;
}

void* HSSocketTemp::Run(void* arg)
{
	//signal(SIGPIPE, SIG_IGN);
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction( SIGPIPE, &sa, 0 );

	HSSocketTemp* pSocketInterface = (HSSocketTemp*)arg;

	int errorCount = 0;

	while(pSocketInterface->isLoop)
	{
		//检查是否有数据

		if(pSocketInterface->m_psendData == NULL)
		{
			pSocketInterface->m_psendData  = pSocketInterface->GetSendData();
		}


		if(!pSocketInterface->m_psendData)
		{
			CCLog("run m_psendData = null %d",pSocketInterface->GetServPort());
			continue;
		}

		//建立连接
		HSIPAddress ip = pSocketInterface->GetIPAddress();

		if(!pSocketInterface->Open(ip,pSocketInterface->GetServPort()))
		{
			//建立失败
			CCLog("run open connection fail = null %d",pSocketInterface->GetServPort());
			pSocketInterface->m_error = Error_ConnectTimeout;
			//continue;
		}
		else
		{
			//建立成功
			//发送
			if(pSocketInterface->Send(*pSocketInterface->m_psendData))
			{
				pSocketInterface->m_psendData = NULL;
				//发送成功开始接受
				if(pSocketInterface->Recv())
				{
					//接受成功清除发送数据指针

					HSSocketPool::ShareSocketPool()->ClearPingShortCounter();
				}
				else
				{
					pSocketInterface->m_error = Error_RecvData;
					memset(pSocketInterface->m_pRecvBuf,0,pSocketInterface->m_recvBufSize);
					pSocketInterface->m_currentRecvSize = 0;
					pSocketInterface->m_needRecvSize = 0;

					memset(pSocketInterface->m_pRecvHeadBuf,0,pSocketInterface->m_recvHeadBufSize);
					pSocketInterface->m_currentRecvHeadSize = 0;
				}
			}
			else
			{
				pSocketInterface->m_error = Error_SendData;
			}
		}


		//错误处理
		if(pSocketInterface->m_error ==Error_ConnectTimeout || pSocketInterface->m_error ==Error_RecvData||pSocketInterface->m_error==Error_SendData)
		{
			errorCount+=1;

			close(pSocketInterface->m_pSocket);//关闭连接

			if(errorCount>5)//连续错误
			{
				//pSocketInterface->m_psendData = NULL;
				memset(pSocketInterface->m_pSendBuf, 0, pSocketInterface->m_sendBufSize);
				pSocketInterface->PopSendData();
				pSocketInterface->m_psendData = NULL;
				CCLog("短连接连续5次错误 %d",pSocketInterface->GetServPort());
				//m_isError = true;
				//数据发送失败,抛给主线程处理
				pSocketInterface->m_handlerError =Error_ConnectClose;
				errorCount = 0;
			}
			CCLog("连接错误 进入等待 %d",pSocketInterface->GetServPort());
			pthread_mutex_lock(&(pSocketInterface->m_mutex));
			struct timeval now;
			struct timespec outtime;
			gettimeofday(&now, NULL);
			outtime.tv_sec = now.tv_sec + 1;
			outtime.tv_nsec = now.tv_usec * 1000;
			pthread_cond_timedwait(&(pSocketInterface->m_cond),&(pSocketInterface->m_mutex),&outtime);
			pthread_mutex_unlock(&(pSocketInterface->m_mutex));
			CCLog("连接错误 开启等待%d",pSocketInterface->GetServPort());
		}
		else if(pSocketInterface->m_error == Error_Invalid)//正常发送
		{
			errorCount =0;
		}
		pSocketInterface->m_error =Error_Invalid;
	}
	return 0;
}


void* HSSocketTemp::Sender(void* arg)
{

//	struct sigaction sa;
//	sa.sa_handler = SIG_IGN;
//	sigaction( SIGPIPE, &sa, 0 );
    signal(SIGPIPE, SIG_IGN);

	HSSocketTemp* pSocketInterface = (HSSocketTemp*)arg;

	int errorCount =0;
	while(pSocketInterface->isLoop)
	{
		if(pSocketInterface->m_error == Error_ConnectTimeout|| pSocketInterface->m_error ==Error_RecvData||pSocketInterface->m_error==Error_SendData)
		{
			errorCount+=1;

			close(pSocketInterface->m_pSocket);//关闭连接

//			if(errorCount>3)//连续错误
//			{

				close(pSocketInterface->m_pSocket);
				pSocketInterface->SetIsClose(true);
				pSocketInterface->m_pSocket = INVALID_SOCKET;
				pSocketInterface->PopSendData();
				pSocketInterface->m_psendData = NULL;
				memset(pSocketInterface->m_pSendBuf, 0, pSocketInterface->m_sendBufSize);
				pSocketInterface->m_handlerError =Error_ConnectClose;
				CCLog("长连接出错 %d,m_error(%d)",pSocketInterface->GetServPort(),pSocketInterface->m_error);
				//数据发送失败,抛给主线程处理
//			}
		}
		else if(pSocketInterface->m_error == Error_Invalid||pSocketInterface->m_error==Error_SelectTimeOut)
		{
			errorCount =0;
		}
		pSocketInterface->m_error =Error_Invalid;

		//检查发送队列
		CCLog("Sender port=%d",pSocketInterface->GetServPort());

		if(pSocketInterface->m_psendData == NULL)
		{
			pSocketInterface->m_psendData  =pSocketInterface->GetSendData();
			CCLog("HSSocketTemp Sender  getSendData ip=%s,port=%d",pSocketInterface->GetIPAddress().GetIP(),pSocketInterface->GetServPort());
		}

		//如果连接已经关闭
		if(pSocketInterface->m_psendData&&pSocketInterface->isClose())
		{
			pSocketInterface->m_psendData = NULL;
			pSocketInterface->PopSendData();
			continue;
		}

		//检查网络如果网断了，并且没有关闭，则重连

		if(pSocketInterface->IsNeedOpen()&&pSocketInterface->m_psendData)
		{
			HSIPAddress ip = pSocketInterface->GetIPAddress();

			if(!pSocketInterface->Open(ip,pSocketInterface->GetServPort()))
			{
				pSocketInterface->m_error = Error_ConnectTimeout;
				continue;
			}
		}

		if(pSocketInterface->m_psendData)
		{
			//发送
			if(pSocketInterface->Send(*pSocketInterface->m_psendData))
			{
				pSocketInterface->m_psendData = NULL;
			}
			else
			{
				pSocketInterface->m_error = Error_RecvData;
			}
		}
		else
		{
			CCLog("Sender m_psendData = null %d",pSocketInterface->GetServPort());
		}



		//接受
		if(pSocketInterface->Recv())
		{
			//接受成功清除发送数据指针
			CCLog("HSSocketTemp Run  receive ok ip=%s,port=%d",pSocketInterface->GetIPAddress().GetIP(),pSocketInterface->GetServPort());
			pSocketInterface->m_psendData = NULL;
			HSSocketPool::ShareSocketPool()->ClearPingShortCounter();
		}
		else
		{
			if(pSocketInterface->m_error!=Error_SelectTimeOut)
			{
				memset(pSocketInterface->m_pRecvBuf,0,pSocketInterface->m_recvBufSize);
				pSocketInterface->m_currentRecvSize = 0;
				pSocketInterface->m_needRecvSize = 0;

				memset(pSocketInterface->m_pRecvHeadBuf,0,pSocketInterface->m_recvHeadBufSize);
				pSocketInterface->m_currentRecvHeadSize = 0;
				pSocketInterface->m_error = Error_RecvData;
			}
		}
	}
	return 0;
}

void HSSocketTemp::HandleError()
{
		switch (m_handlerError)
		{
			case Error_ConnectTimeout:

				m_handlerError = Error_Invalid;
				//this->Closed1();
				ConnectionTimeoutNotification();
				HSMessageBox("Connection timeout");
				break;

			case Error_SendData:

				m_handlerError = Error_Invalid;
				//this->Closed1();
				SendDataErrorNotification();

				break;

			case Error_RecvData:

				m_handlerError = Error_Invalid;
				//this->Closed1();
				RecvDataErrorNotification();

				break;

			case Error_RecvTimeout:

				m_handlerError = Error_Invalid;
				//this->Closed1();
				RecvDataTimeoutNotification();

				break;

			case Error_ConnectClose:
				CCLog("handle error_Connection");
				m_handlerError = Error_Invalid;

				ConnectionCloseNotification();
				break;
			default:
				break;
		}
}

void HSSocketTemp::Updata(float dt)
{
	HandleError();

	lock.Lock();
	while(m_recvDataQueue.size() > 0)
    {
//    	CCLog("update lock");
        HSSocketRecvData* pData = m_recvDataQueue.front();
        if (this->Handle(pData->GetBuf(), pData->GetBufSize()))
        {
            CC_SAFE_DELETE(pData);
            m_recvDataQueue.pop();
        }
        CCLog("undate unlock");
    }
    lock.UnLock();
}



void HSSocketTemp::Closed(HSConnectionCloseType closeType)
{
	 m_connectionCloseType = closeType;

	 if(m_type == HSSocket_Type_SOCKET)
	 {

		 close(m_pSocket);

		 this->SetIsClose(true);

		 m_pSocket = INVALID_SOCKET;

		 this->m_psendData = NULL;

	 }
}














