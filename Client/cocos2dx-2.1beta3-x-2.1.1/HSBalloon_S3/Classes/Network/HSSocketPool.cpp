#include "HSSocketPool.h"
#include "HSRequest.h"

const float HSSocketPool::s_pingMaxD = 6;
const float HSSocketPool::s_pingMaxL = 6;
HSSocketPool::HSSocketPool(void)
{
	m_fPingTimeD = 0.f;
	m_fPingTimeL = 0.f;

	//SetPingShortLink(true);
	//SetPingLongLink(true);
}

HSSocketPool::~HSSocketPool(void)
{
	
}

HSSocketPool* HSSocketPool::ShareSocketPool()
{
	static HSSocketPool s_hsSocketPool;

	return &s_hsSocketPool;
}

void HSSocketPool::Destroy()
{
	map<int,HSSocket*>::iterator it = this->m_socketList.begin();
	for (;it!=this->m_socketList.end();++it)
	{
		if (it->second != NULL)
		{
			CC_SAFE_DELETE(it->second);
		}
	}
}

void HSSocketPool::AddSocket(HSSeverID tag,const char* ip,const char* port,HSSocketType type)
{

	map<int,HSSocket*>::iterator it = this->m_socketList.find(tag);
	if (it!=m_socketList.end())
	{

		HSSocket* pSocket = it->second;
		pSocket->SetAddress(type,ip,atoi(port));
		pSocket->SetTag(tag);

		if(pSocket->isClose())
		{
			pSocket->SetIsClose(false);
		}
	}
	else
	{
		HSSocket* tempSocket = HSSocket::Create(type,ip,atoi(port));
        tempSocket->SetTag(tag);
		if (tempSocket)
		{
			this->m_socketList.insert(pair<int,HSSocket*>(tag,tempSocket));
		}
	}
}

HSSocket* HSSocketPool::GetSocketWithTag(int hsSeverID)
{
	map<int,HSSocket*>::iterator it = this->m_socketList.find(hsSeverID);
	if (it != this->m_socketList.end())
	{
		return it->second;
	}
	//CCString* error = CCString::createWithFormat("The network access does not exist [ %d ]",hsSeverID);
	//HSMessageBox(error->getCString());
	//CCLog(CCString::createWithFormat("The network access does not exist [ %d ]",hsSeverID)->getCString());
	return NULL;
}

bool HSSocketPool::Remove(HSSeverID tag)
{
//    map<int,HSSocket*>::iterator it = this->m_socketList.find(tag);
//	if (it != this->m_socketList.end())
//	{
//        HSSocket* pSocket = it->second;
//        CC_SAFE_DELETE(pSocket);
//        m_socketList.erase(it);
//	}
    return true;
}

void HSSocketPool::Updata(float dt)
{
	map<int,HSSocket*>::iterator it = this->m_socketList.begin();
	for (;it!=this->m_socketList.end();++it)
	{
		if (it->second != NULL)
		{
			it->second->Updata(dt);
		}
	}
}

void HSSocketPool::PingShortLink(float dt)
{
	HSSocket* pGameServer = this->GetSocketWithTag(S_D_Logic);

	if(!pGameServer || pGameServer->isClose())
	{
		m_fPingTimeD = 0.f;
	}
	else
	{
		m_fPingTimeD += dt;
	}

	if(m_fPingTimeD >=s_pingMaxD)
	{
		m_fPingTimeD = 0.f;
		if(pGameServer && !pGameServer->isClose())
		{
			HSRequest::ShareRequest()->SendHeartbeatGameRequest();
		}
	}
}

void HSSocketPool::PingLongLink(float dt)
{

	HSSocket* pGameServer = this->GetSocketWithTag(S_L_Battle);

	if(!pGameServer || pGameServer->isClose())
	{
		m_fPingTimeL = 0.f;
	}
	else
	{
		m_fPingTimeL +=dt;
	}

	if(m_fPingTimeL >=s_pingMaxL)
	{
		m_fPingTimeL = 0.f;
		if(pGameServer && !pGameServer->isClose())
		{
			HSRequest::ShareRequest()->SendHeartbeatBattleRequest();
		}
	}
}



void HSSocketPool::SetPingShortLink( bool b )
{
	//return;
	if (b)
	{
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HSSocketPool::PingShortLink), this, 1.f, false);
	}else{
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(HSSocketPool::PingShortLink),this);
	}
}

void HSSocketPool::SetPingLongLink( bool b )
{
	//return;
	if (b)
	{
		m_fPingTimeL = 0.l;
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HSSocketPool::PingLongLink), this, 1.f, false);
	}else{
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(HSSocketPool::PingLongLink),this);
	}
}
