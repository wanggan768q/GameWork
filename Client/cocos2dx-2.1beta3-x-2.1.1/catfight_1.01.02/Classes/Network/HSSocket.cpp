#include "HSSocket.h"
#include "HSTool.h"
#include "HSGameSceneJumpManage.h"
#include "HSJava.h"

HSSocket::HSSocket(HSSocketType type,const char* ip,int iServPort)
{
    SetAddress(type,ip, iServPort);
    m_connectionCloseType = Close_Nomal;
}

HSSocket::~HSSocket()
{

}

HSSocket* HSSocket::Create(HSSocketType type,const char* ip,int iServPort)
{
    HSSocket* pSocket = new HSSocket(type,ip,iServPort);
    pSocket->Start();
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
//    if (m_type == HSSocket_Type_HTTP)
//    {
//        this->Closed();
//    }
    m_isStart = false;
    return true;
}

bool HSSocket::Start()
{
//    if(m_isStart && !IsConnected())
//    {
//        return false;
//    }
//    if(!m_isStart)
//    {
//        m_isStart = true;
//    }
//    if(IsConnected())
//    {
//        m_isStart = false;
//        return true;
//    }
//    bool isOK = Open();
//    return false;
	Open();
}

void HSSocket::SetTag(int tag)
{
    m_tag = tag;
}

bool HSSocket::IsSend()
{
//    if (GetType() == HSSocket_Type_HTTP)
//    {
//        if (IsIdle())
//        {
//            if (!m_sendDataQueue.empty())
//            {
//                if(!Start())
//                {
//                    return false;
//                }
//            }
//        }
//    }else if(GetType() == HSSocket_Type_SOCKET){
//
//        if (!m_sendDataQueue.empty())
//        {
//            if(!Start())
//            {
//                return false;
//            }
//        }
//    }
    return true;
}

/* 连接关闭 */
void HSSocket::ConnectionCloseNotification()
{
    CCLOG("通知: 连接关闭");

    if (m_type == HSSocket_Type_SOCKET)
    {
        HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
    }

    if(this->m_connectionCloseType == Close_Nomal)
	{
		 if(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetGameSceneID() !=HS_SCENE_CoverScene)
		 {
			HS_GO_SCENE(HS_SCENE_CoverScene);
		 }
		 HSJava::ShaderJava()->ShowToast(L("Connection_Break"),0);
		 HSLoadingLayer::ShareLoading()->setVisible(false);
		 //HSMessageBox("connection break");
	}
    else if(this->m_connectionCloseType == Close_Active)
    {
    //如果是主动退出的这里什么也不干
    	this->m_connectionCloseType = Close_Nomal;
    }




}
/* 连接超时通知 */
void HSSocket::ConnectionTimeoutNotification()
{
    CCLOG("通知: 连接超时通知");
}
/* 连接成功通知 */
void HSSocket::ConnectionSucceedNotification(const char* ip,int iServPort)
{
    CCLOG("通知: 连接成功通知");
}
/* 发送数据异常通知 */
void HSSocket::SendDataErrorNotification()
{
    CCLOG("通知: 发送数据异常通知");
}
/* 接收数据异常通知 */
void HSSocket::RecvDataErrorNotification()
{
    CCLOG("通知: 接收数据异常通知");
}
/* 接收数据超时通知 */
void HSSocket::RecvDataTimeoutNotification()
{
    CCLOG("通知: 接收数据超时通知");
}

