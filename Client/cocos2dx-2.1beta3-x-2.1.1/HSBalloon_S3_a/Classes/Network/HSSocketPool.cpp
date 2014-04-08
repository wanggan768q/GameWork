#include "HSSocketPool.h"
#include "HSRequest.h"

HSSocketPool::HSSocketPool(void)
{
	m_fPingTimeD = 20.f;
	m_fPingTimeL = 20.f;

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
        
//		HSSocket* pSocket = it->second;
//		pSocket->SetAddress(type,ip,atoi(port));
//        pSocket->SetTag(tag);
	}else{
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
    map<int,HSSocket*>::iterator it = this->m_socketList.find(tag);
	if (it != this->m_socketList.end())
	{
        HSSocket* pSocket = it->second;
        CC_SAFE_DELETE(pSocket);
        m_socketList.erase(it);
	}
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
	static float pingTimeD = 0.f;
	HSSocket* pGameServer = this->GetSocketWithTag(S_D_Logic);
	if (pGameServer)
	{
		if (pGameServer->GetSendDataInterval() < m_fPingTimeD)
		{
			pingTimeD = 0.f;
			return;
		}
	}else{
		return;
	}
	

	
	if (pingTimeD > 1.f)
	{
		pingTimeD = 0.f;

		map<int,HSSocket*>::iterator it = m_socketList.find(S_D_Logic);
		if (it != m_socketList.end())
		{
			HSRequest::ShareRequest()->SendHeartbeatGameRequest();
		}

	}else{
		pingTimeD += dt;
	}
}

void HSSocketPool::PingLongLink(float dt)
{
	static float pingTimeL = 0.f;
	HSSocket* pBattleServer = this->GetSocketWithTag(S_L_Battle);
	if (pBattleServer)
	{
		if (pBattleServer->GetSendDataInterval() < m_fPingTimeL)
		{
			pingTimeL = 0.f;
			return;
		}
	}else{
		return;
	}
	

	
	if (pingTimeL > 1.f)
	{
		pingTimeL = 0.f;

		map<int,HSSocket*>::iterator it = m_socketList.find(S_L_Battle);
		if (it != m_socketList.end())
		{
			HSSocket* pSocket = it->second;
			if (pSocket)
			{
				HSRequest::ShareRequest()->SendHeartbeatBattleRequest();
			}
		}
	}else{
		pingTimeL += dt;
	}
}

void HSSocketPool::SetPingShortLink( bool b )
{
	return;
	if (b)
	{
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HSSocketPool::PingShortLink), this, 1.f, false);
	}else{
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(HSSocketPool::PingShortLink),this);
	}
}

void HSSocketPool::SetPingLongLink( bool b )
{
	return;
	if (b)
	{
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HSSocketPool::PingLongLink), this, 1.f, false);
	}else{
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(HSSocketPool::PingLongLink),this);
	}
}
