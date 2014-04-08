#include "HSSocket.h"
#include "HSTool.h"

HSSocket::HSSocket(HSSocketType type,const char* ip,int iServPort)
{
    SetAddress(type,ip, iServPort);
}

HSSocket::~HSSocket()
{

}

HSSocket* HSSocket::Create(HSSocketType type,const char* ip,int iServPort)
{
    HSSocket* pSocket = new HSSocket(type,ip,iServPort);
    return pSocket;
}

void HSSocket::SetAddress(HSSocketType type,const char* ip,int iServPort)
{
    m_type = type;
    m_ip = ip;
    m_iServport = iServPort;
    m_isStart = false;
    Init(type,ip, m_iServport);
}

bool HSSocket::Handle(const void *pBuf, int size)
{
    HSFilter::ShareFilter()->CreaterMessage((char*)pBuf,size);
    if (m_type == HSSocket_Type_HTTP)
    {
        this->Closed();
    }
    m_isStart = false;
    return true;
}

bool HSSocket::Start()
{
    if(m_isStart && !IsConnected())
    {
        return false;
    }
    if(!m_isStart)
    {
        m_isStart = true;
    }
    if(IsConnected())
    {
        m_isStart = false;
        return true;
    }
    bool isOK = Open();
    return false;
}

void HSSocket::SetTag(int tag)
{
    m_tag = tag;
}

bool HSSocket::IsSend()
{
    if (GetType() == HSSocket_Type_HTTP)
    {
        if (IsIdle())
        {
            if (!m_sendDataQueue.empty())
            {
                if(!Start())
                {
                    return false;
                }
            }
        }
    }else if(GetType() == HSSocket_Type_SOCKET){
        
        if(!Start())
        {
            return false;
        }
    }
    return true;
}

//void HSSocket::ReceiveFinish( char* buf,int size )
//{
//	HSFilter::ShareFilter()->CreaterMessage(buf,size);
//}
//
//void HSSocket::ReceiveTimeoutNotification()
//{
//	//CCLog("---------------------------- ReceiveTimeoutNotification");
//}
//
//void HSSocket::ToReceiveDataNotification()
//{
//	//CCLog("---------------------------- ToReceiveDataNotification");
//}
//
//void HSSocket::ConnectTimeoutNotification()
//{
//	//CCLog("---------------------------- ConnectTimeoutNotification");
//}
//
//void HSSocket::ConnectSuccessfulNotification()
//{
//	//CCLog("---------------------------- ConnectSuccessfulNotification");
//}
//
//void HSSocket::ServerClosedNotification()
//{
//	//CCLog("---------------------------- ServerClosedNotification");
//}
