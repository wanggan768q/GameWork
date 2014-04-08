#include "HSSocketInterface.h"
#include "HSTime.h"

HSSocketInterface::HSSocketInterface()
{
    m_isRecvThreadAlive = false;
    m_pSocket = -1;
    m_isConnect = false;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
    m_currentRecvSize = 0;
    m_recvBufSize = 0;
    m_sendBufSize = 0;
    m_fSendDataInterval = 0.f;
    m_isIdle = true;
    m_needRecvSize = 0;
    m_isSendAction = false;
    m_currentSendSize = 0;
    
    m_error = Error_Invalid;
    this->SetSendBufSize();
    this->SetRecvBufSize();
    m_recvTimeout = 10;
}

HSSocketInterface::~HSSocketInterface()
{
    Closed();
    
    CC_SAFE_DELETE(m_pRecvBuf);
    CC_SAFE_DELETE(m_pSendBuf);
    
    HSAutoLock autoLock(m_lock);
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
    m_isSendAction = false;
}

bool HSSocketInterface::Open()
{
    if(0 == strcmp(m_ipAddress.GetIP(), ""))
    {
        HSMessageBox("Initialize the Socket, please");
        return false;
    }
    
    if (pthread_create(&m_connectID, NULL, ThreadConnect, this) != 0)
    {
        HSMessageBox("创建连接线程失败");
        return false;
    }
    
    return true;
}

bool HSSocketInterface::CreateRecvThread()
{
    if (pthread_create(&m_RecvID, NULL, ThreadRecvData, this) != 0)
    {
        HSMessageBox("创建接收线程失败");
        return false;
    }
    return true;
}

bool HSSocketInterface::Open(HSIPAddress& ip,int iServPort)
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
                case 0:
                    m_error = Error_ConnectTimeout;
                    this->Closed();
                    CCLOG(CCString::createWithFormat("Connection timeout [code %d]",selectCode)->getCString());
                    return false;
                case 1:
                {
                    CCLOG("Connect ok : %s:%d",m_ipAddress.GetIP(),m_iServPort);
                    SetConnected(true);
                    this->ConnectionSucceedNotification(m_ipAddress.GetIP(),m_iServPort);
                }
                    break;
                    
                default:
                {
                    return false;
                }
            }
        }
        
        this->SetConnected(true);
        this->SetIdle(false);
        
        
    }catch(...){
        
        this->SetConnected(false);
        this->SetIdle(true);
        
        HSMessageBox(" Unexpected exception ");
        return false;
    }
    
    return true;
}

bool HSSocketInterface::SetSocketBuf()
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

bool HSSocketInterface::Init(HSSocketType type,const char *ip, int iServPort)
{
    m_ipAddress.SetHostName(ip, false);
    m_iServPort = iServPort;
    m_type = type;
    return true;
}

HSSocketType HSSocketInterface::GetType()
{
    return m_type;
}

void HSSocketInterface::SetRecvBufSize(int size /*= 6*1024*/)
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

void HSSocketInterface::SetSendBufSize(int size /*= 512*/)
{
    m_sendBufSize = size;
    if (!m_pSendBuf) {
        m_pSendBuf = new char[size];
    }else{
        delete m_pSendBuf;
        m_pSendBuf = NULL;
        m_pSendBuf = new char[size];
    }
    memset(m_pSendBuf, 0, size);
}


int HSSocketInterface::GetSocket()
{
    return m_pSocket;
}

bool HSSocketInterface::IsIdle()
{
    return m_isIdle;
}

void HSSocketInterface::SetIdle(bool is)
{
    m_isIdle = is;
}

bool HSSocketInterface::IsConnected()
{
    return m_isConnect;
}

void HSSocketInterface::SetConnected(bool is)
{
    m_isConnect = is;
}

bool HSSocketInterface::Recv()
{
    int a = 0;
//    unsigned long long lastTime = 0;
    bool isLoop = true;
    while (isLoop)
    {
        if (!IsConnected())
        {
//            if(lastTime == 0)
//            {
//                lastTime = HSTime::GetLocalityTimeAccurate();
//            }else{
//                unsigned long long currentTime = HSTime::GetLocalityTimeAccurate();
//                //CCLOG("S :    %d",currentTime - lastTime);
//                if (currentTime - lastTime > 1000)
//                {
//                    CCLOG("*****接收断开超时******");
//                    return false;
//                }
//            }
//            continue;
            return  false;
        }
        try {
            
            struct timeval overTime;
            overTime.tv_sec = m_recvTimeout;
            overTime.tv_usec = 0;
            
            fd_set rset;
            FD_ZERO(&rset);
            FD_SET(this->GetSocket(), &rset);
            
            int code = select(this->GetSocket() + 1, &rset, NULL, NULL, &overTime);
            if (code == -1)
            {
                //m_error = Error_RecvTimeout;
                //isLoop = false;
                CCLOG("select: %d",++a);
                continue;
            }else if(code == 0){
                continue;
            }
            //signal(SIGPIPE, SIG_IGN);
            int recvLen = recv(m_pSocket,m_pRecvBuf + m_currentRecvSize,m_recvBufSize - m_currentRecvSize,0);
            if (recvLen == -1)
            {
                CCLOG("套接字 : %d",m_pSocket);
                
                m_error = Error_ConnectClose;
                isLoop = false;
                return false;
                
                continue;
            }
            else if(recvLen == 0)
            {
                //网络中断
                CCLOG("服务器主动关闭连接(Recv): %s:%d ",m_ipAddress.GetIP(),m_iServPort);
                isLoop = false;
                continue;
            }
            
            m_currentRecvSize += recvLen;
            
            //            if(m_currentRecvSize >= 4 && m_needRecvSize == 0)
            //            {
            //                memcpy(&m_needRecvSize,m_pRecvBuf,4);
            //                this->Swap_long(m_needRecvSize);
            //                if(m_needRecvSize > m_recvBufSize)
            //                {
            //                    this->SetRecvBufSize(m_needRecvSize + 4);
            //                }
            //            }
            //CCLOG("%d | %d",m_needRecvSize,m_currentRecvSize);
            //            if(m_needRecvSize == m_currentRecvSize - 4)
            //            {
            //                CCLOG("Recv Byte(%d) %% (%d)\n",m_needRecvSize,m_currentRecvSize);
            //                HSSocketRecvData* pData = HSSocketRecvData::New(m_pRecvBuf + 4, m_needRecvSize);
            //                m_recvDataQueue.push(pData);
            //
            //                memset(m_pRecvBuf, 0, m_recvBufSize);
            //
            //                m_currentRecvSize = 0;
            //                m_needRecvSize = 0;
            //
            //                if (m_type == HSSocket_Type_HTTP)
            //                {
            //                    isLoop = false;
            //                }
            //            }
            bool isFinsh = false;
            while (!isFinsh && m_currentRecvSize > 0)
            {
                if(m_needRecvSize <= m_currentRecvSize - 4)
                {
                    if(m_needRecvSize == 0)
                    {
                        memcpy(&m_needRecvSize,m_pRecvBuf,4);
                        this->Swap_long(m_needRecvSize);
                        if(m_needRecvSize > m_recvBufSize)
                        {
                            this->SetRecvBufSize(m_needRecvSize + 4);
                        }
                    }
                    
                    char tempData[m_needRecvSize];
                    memset(&tempData, 0, m_needRecvSize);
                    memcpy(&tempData, m_pRecvBuf + 4, m_needRecvSize);
                    
                    CCLOG("Recv Byte(%d) %% (%d)\n",m_needRecvSize,m_currentRecvSize);
                    
                    m_lock.Lock();
                    HSSocketRecvData* pData = HSSocketRecvData::New(&tempData, m_needRecvSize);
                    m_recvDataQueue.push(pData);
                    m_lock.UnLock();
                    
                    int surplusByteSize = m_currentRecvSize - m_needRecvSize - 4;
                    m_currentRecvSize = surplusByteSize;
                    if (surplusByteSize > 4)
                    {
                        char surplusData[surplusByteSize];
                        memset(&surplusData, 0, surplusByteSize);
                        memcpy(&surplusData, m_pRecvBuf + 4 + m_needRecvSize, surplusByteSize);
                        memset(m_pRecvBuf, 0, surplusByteSize);
                        memcpy(m_pRecvBuf, &surplusData, surplusByteSize);
                        m_needRecvSize = 0;
                        
                    }else{
                        isFinsh = true;
                    }
                    
                    if(m_currentRecvSize == 0)
                    {
                        m_currentRecvSize = 0;
                        m_needRecvSize = 0;
                        
                        if (m_type == HSSocket_Type_HTTP)
                        {
                            isLoop = false;
                        }
                    }
                }
            }
            
            
        } catch (...) {
            CCLOG("【接收线程终止】客户端的 recvData 方法抛出预料外的异常~\n");
            m_error = Error_RecvData;
            return false;
        }
    }
    return  true;
}

long HSSocketInterface::Swap_long(unsigned long& v)
{
    v = (v << 24) |
    ((v << 8) & 0x00ff0000u) |
    ((v >> 8) & 0x0000ff00u) |
    (v >> 24);
    return v;
}


bool HSSocketInterface::Send()
{
    if (m_sendDataQueue.empty() || !IsConnected())
    {
        return false;
    }
    
    if (m_type == HSSocket_Type_HTTP)
    {
        if (m_isSendAction)
        {
            return false;
        }
    }
    
    HSSocketSendData pHSSocketSendData = m_sendDataQueue.front();
    const std::string sendData = pHSSocketSendData.GetData();
    
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
    while (isSend)
    {
        try {
            //signal(SIGPIPE, SIG_IGN);
            
            m_currentSendSize = send(m_pSocket,m_pSendBuf + m_currentSendSize, (int)sendData.length() + 4 -m_currentSendSize,0);
            
            if( m_currentSendSize == (int)sendData.length() + 4)
            {
                CCLog("Send Byte: (%d) %% (%d) - (%s) (%d)\n",
                      m_currentSendSize,(int)sendData.length() + 4,
                      pHSSocketSendData.GetDescribe(),pHSSocketSendData.GetID());
                
                m_sendDataQueue.pop();
                isSend = false;
                m_isSendAction = true;
                
                memset(m_pSendBuf, 0, m_sendBufSize);
                m_currentSendSize = 0;
                
            }else if(m_currentSendSize == 0){
                this->Closed();
                CCLOG("服务器主动关闭连接(Send): %s:%d ",m_ipAddress.GetIP(),m_iServPort);
            }else if(m_currentSendSize == -1){
                m_error = Error_ConnectClose;
                isSend = false;
                CCLOG("非法套接字 (Send): %s:%d ",m_ipAddress.GetIP(),m_iServPort);
            }
            
        }catch( ... ){
            CCLOG("【接收线程终止】客户端的 Send 方法抛出预料外的异常");
            isSend = false;
            m_error = Error_SendData;
        }
    }
    return true;
}


void HSSocketInterface::AddSendData(const HSSocketSendData& sendData)
{
    m_sendDataQueue.push(sendData);
    CCLOG("HS Will Send Data Count-> Port(%d) : %d",m_iServPort,m_sendDataQueue.size());
}

HSIPAddress HSSocketInterface::GetIPAddress()
{
    return m_ipAddress;
}

int HSSocketInterface::GetServPort()
{
    return m_iServPort;
}

void* HSSocketInterface::ThreadRecvData(void* arg)
{
    HSSocketInterface* pSocketInterface = (HSSocketInterface*)arg;
    CCLOG("接收线程启动: %s:%d",pSocketInterface->GetIPAddress().GetIP(),pSocketInterface->GetServPort());
    pSocketInterface->Recv();
    CCLOG("接收线程关闭: %s:%d",pSocketInterface->GetIPAddress().GetIP(),pSocketInterface->GetServPort());
    return 0;
}

void* HSSocketInterface::ThreadConnect(void* arg)
{
    HSSocketInterface* pSocketInterface = (HSSocketInterface*)arg;
    HSIPAddress ip = pSocketInterface->GetIPAddress();
    CCLog("连接线程启动: %s:%d",pSocketInterface->GetIPAddress().GetIP(),pSocketInterface->GetServPort());
    pSocketInterface->Open(ip,pSocketInterface->GetServPort());
    CCLog("连接线程终止: %s:%d",pSocketInterface->GetIPAddress().GetIP(),pSocketInterface->GetServPort());
    return 0;
}

float HSSocketInterface::GetSendDataInterval()
{
    return m_fSendDataInterval;
}

void HSSocketInterface::HandleError()
{
    switch (m_error)
    {
        case Error_ConnectTimeout:
            
            m_error = Error_Invalid;
            this->Closed();
            ConnectionTimeoutNotification();
            HSMessageBox("Connection timeout");
            
            break;
            
        case Error_SendData:
            
            m_error = Error_Invalid;
            this->Closed();
            SendDataErrorNotification();
            
            break;
            
        case Error_RecvData:
            
            m_error = Error_Invalid;
            this->Closed();
            RecvDataErrorNotification();
            
            break;
            
        case Error_RecvTimeout:
            
            m_error = Error_Invalid;
            this->Closed();
            RecvDataTimeoutNotification();
            
            break;
            
        case Error_ConnectClose:
            
            m_error = Error_Invalid;
            this->Closed();
            ConnectionCloseNotification();
            
            break;
            
            
            
        default:
            break;
    }
}

void HSSocketInterface::Updata(float dt)
{
    if(IsSend())
    {
        bool isSendOK = Send();
        if (isSendOK) {
            m_fSendDataInterval = 0.f;
        }else{
            m_fSendDataInterval += dt;
        }
    }else{
        m_fSendDataInterval += dt;
    }
    
    m_lock.Lock();
    while(m_recvDataQueue.size() > 0)
    {
        HSSocketRecvData* pData = m_recvDataQueue.front();
        if (this->Handle(pData->GetBuf(), pData->GetBufSize()))
        {
            CC_SAFE_DELETE(pData);
            m_recvDataQueue.pop();
        }
    }
    m_lock.UnLock();
    
    if (IsConnected())
    {
        if (!m_isRecvThreadAlive)
        {
            m_isRecvThreadAlive = this->CreateRecvThread();
        }
    }
    
    HandleError();
}

void HSSocketInterface::Closed()
{
    if (m_type == HSSocket_Type_HTTP)
    {
        close(m_pSocket);
        m_pSocket = INVALID_SOCKET;
        SetConnected(false);
        SetIdle(true);
    }
    
    
    if (m_type == HSSocket_Type_SOCKET)
    {
        HSAutoLock autoLock(m_lock);
        while (!m_sendDataQueue.empty())
        {
            m_sendDataQueue.pop();
        }
    }
    
    if (m_type == HSSocket_Type_SOCKET)
    {
        close(m_pSocket);
        m_pSocket = INVALID_SOCKET;
        
        SetConnected(false);
        SetIdle(true);
    }
    
    bool isClose = false;
    CCLOG("============================");
    int results = 0;
//    results = pthread_kill(m_RecvID, 0);
//    if (results == ESRCH)
//    {
//        isClose = true;
//        CCLOG("接收线程 正确 关闭 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
//    }else if(results == EINVAL){
//        CCLog("接收线程 信号无效 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
//    }else{
//        CCLOG("接收线程 还活着 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
//    }
//    results = pthread_kill(m_connectID, 0);
//    if (results == ESRCH)
//    {
//        isClose = true;
//        CCLOG("连接线程 正确 关闭 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
//    }else if(results == EINVAL){
//        CCLOG("连接线程 信号无效 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
//    }else{
//        CCLOG("连接线程 还活着 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
//    }
    results = pthread_join(m_RecvID, NULL);
    if (results == 0)
    {
        isClose = true;
        CCLOG("接收线程 正确 关闭 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
    }else{
        CCLOG("接收线程 关闭失败: %s:%d",m_ipAddress.GetIP(),m_iServPort);
    }
    results = pthread_join(m_connectID, NULL);
    if (results == 0)
    {
        isClose = true;
        CCLOG("连接线程 正确 关闭 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
    }else{
        CCLOG("连接线程 关闭失败 : %s:%d",m_ipAddress.GetIP(),m_iServPort);
    }

    CCLOG("HS Closed : %s:%d",m_ipAddress.GetIP(),m_iServPort);
    
    
    CCLOG("============================");
    
//    if (m_type == HSSocket_Type_SOCKET && isClose)
//    {
//        close(m_pSocket);
//        m_pSocket = INVALID_SOCKET;
//        
//        SetConnected(false);
//        SetIdle(true);
//    }
    m_isRecvThreadAlive = false;
    memset(m_pSendBuf, 0, m_sendBufSize);
    memset(m_pRecvBuf, 0, m_recvBufSize);
    
    m_currentRecvSize = 0;
    m_currentSendSize = 0;
    m_needRecvSize = 0;
    
    m_isSendAction = false;
    
}














