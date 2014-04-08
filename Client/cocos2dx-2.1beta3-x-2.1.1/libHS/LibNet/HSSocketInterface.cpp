#include "HSSocketInterface.h"


HSSocketInterface::HSSocketInterface()
{ 
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
}

HSSocketInterface::~HSSocketInterface()
{
    Closed();
    
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
    m_isSendAction = false;
}

bool HSSocketInterface::Open()
{
    if(0 == strcmp(m_ipAddress.GetHostName(), ""))
    {
        HSMessageBox("Initialize the Socket, please");
        return false;
    }
    pthread_t t;
    
    if (pthread_create(&t, NULL, ThreadConnect, this) != 0)
    {
        HSMessageBox("创建连接线程失败");
        return false;
    }
    
    pthread_t t1;
    
    if (pthread_create(&t1, NULL, ThreadRecvData, this) != 0)
    {
        HSMessageBox("创建接收线程失败");
        return false;
    }
    
    return true;
}

bool HSSocketInterface::Open(IPAddress& ip,int iServPort)
{
    try {
        m_pSocket = new TCPClientSocket(ip,iServPort);
        
        int rcvBufSize = 65536;
        int sendBufSize = 65536;
        int isMTU = 1;
        
        m_pSocket->SetSockOpt(IPPROTO_TCP, 0x0001, (char*)&isMTU, sizeof(int));
        m_pSocket->SetSockOpt(SOL_SOCKET, SO_RCVBUF, (char *)&rcvBufSize, sizeof(int));
        m_pSocket->SetSockOpt(SOL_SOCKET, SO_SNDBUF, (char *)&sendBufSize, sizeof(int));
        
        this->SetSendBufSize();
        this->SetRecvBufSize();
        this->SetConnected(true);
        this->SetIdle(false);
        
        CCLog("HS Connect : %s:%d",(const char*)m_ipAddress,m_iServPort);
        
    } catch (SocketException& e) {
        
        this->SetConnected(false);
        this->SetIdle(true);
        
        HSMessageBox((const char*)e);
        return false;
    } catch(...){
        
        this->SetConnected(false);
        this->SetIdle(true);

        HSMessageBox(" Unexpected exception ");
        return false;
    }
    
    return true;
}

bool HSSocketInterface::Init(HSSocketType type,const char *ip, int iServPort)
{
    m_ipAddress.SetHostName(ip, false);
    m_iServPort = iServPort;
    m_type = type;
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


TCPClientSocket* HSSocketInterface::GetSocket()
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
    bool isLoop = true;
    while (isLoop)
    {
        if (!IsConnected())
        {
            continue;
        }
        try {
            int recvLen = m_pSocket->RecvData(m_pRecvBuf + m_currentRecvSize,sizeof(m_pRecvBuf));
            
            m_currentRecvSize += recvLen;
            
            if(m_currentRecvSize >= 4 && m_needRecvSize == 0)
            {
                memcpy(&m_needRecvSize,m_pRecvBuf,4);
                this->Swap_long(m_needRecvSize);
                if(m_needRecvSize > m_recvBufSize)
                {
                    this->SetRecvBufSize(m_needRecvSize);
                }
            }
            CCLOG("%d | %d",m_needRecvSize,m_currentRecvSize);
            if(m_needRecvSize == m_currentRecvSize - 4)
            {
                HSSocketRecvData* pData = HSSocketRecvData::New(m_pRecvBuf + 4, m_needRecvSize);
                m_recvDataQueue.push(pData);
                
                memset(m_pRecvBuf, 0, m_recvBufSize);
                
                m_currentRecvSize = 0;
                m_needRecvSize = 0;
                
                if (m_type == HSSocket_Type_HTTP)
                {
                    isLoop = false;
                }
                
            }
            
        } catch (SocketException &e) {
            CCLog("【接收线程终止】客户端的 recvData 方法抛出预料内的异常：%s\n", (const char*)e);
            this->Closed();
            
        } catch (...) {
            CCLog("【接收线程终止】客户端的 recvData 方法抛出预料外的异常~\n");
            this->Closed();
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
    
    
    std::string sendData = m_sendDataQueue.front();
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
            m_currentSendSize = m_pSocket->SendData(m_pSendBuf + m_currentSendSize, (int)sendData.length() + 4 -m_currentSendSize);
            
            if( m_currentSendSize == (int)sendData.length() + 4)
            {
                CCLog("Send Byte: (%d) %% (%d)",m_currentSendSize,(int)sendData.length() + 4);
                m_sendDataQueue.pop();
                isSend = false;
                m_isSendAction = true;
                
                memset(m_pSendBuf, 0, m_sendBufSize);
                m_currentSendSize = 0;

            }
            
        } catch (SocketException &e) {
            HSMessageBox((const char*)e);
            isSend = false;
        }catch( ... ){
            CCLog("【接收线程终止】客户端的 Send 方法抛出预料外的异常");
            isSend = false;
        }
    }
    return true;
}


void HSSocketInterface::AddSendData(const std::string& sendData)
{
    m_sendDataQueue.push(sendData);
    CCLog("%d",m_sendDataQueue.size());
}

IPAddress HSSocketInterface::GetIPAddress()
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
    pSocketInterface->Recv();
    return 0;
}

void* HSSocketInterface::ThreadConnect(void* arg)
{
    HSSocketInterface* pSocketInterface = (HSSocketInterface*)arg;
    IPAddress ip = pSocketInterface->GetIPAddress();
    pSocketInterface->Open(ip,pSocketInterface->GetServPort());
    return 0;
}

float HSSocketInterface::GetSendDataInterval()
{
    return m_fSendDataInterval;
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
    
    //Recv();
    
    if(m_recvDataQueue.size() > 0)
    {
        HSSocketRecvData* pData = m_recvDataQueue.front();
        if (this->Handle(pData->GetBuf(), pData->GetBufSize()))
        {
            CC_SAFE_DELETE(pData);
            m_recvDataQueue.pop();
        }
    }
}

void HSSocketInterface::Closed()
{
    CC_SAFE_DELETE(m_pSocket);
    
    SetConnected(false);
    SetIdle(true);
    
    
    
    memset(m_pSendBuf, 0, m_sendBufSize);
    memset(m_pRecvBuf, 0, m_recvBufSize);
    
    m_currentRecvSize = 0;
    m_currentSendSize = 0;
    m_needRecvSize = 0;
    
    m_isSendAction = false;
    CCLog("HS Closed : %s:%d",(const char*)m_ipAddress,m_iServPort);
}














