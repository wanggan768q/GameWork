#include "HSSocketPool.h"

HSSocketPool::HSSocketPool(void)
{
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
			//it->second->ClosedSocket();
			CC_SAFE_DELETE(it->second);
		}
	}
}

void HSSocketPool::AddSocket(int tag,const char* ip,const char* port,int type)
{

	HSSocket* tempSocket = HSSocket::OpenSocket(ip,port,type);
	
	if (tempSocket)
	{
		this->m_socketList.insert(pair<int,HSSocket*>(tag,tempSocket));
	}
}

HSSocket* HSSocketPool::GetSocketWithTag(int tag)
{
	map<int,HSSocket*>::iterator it = this->m_socketList.find(tag);
	if (it != this->m_socketList.end())
	{
		return it->second;
	}
	CCString* error = CCString::createWithFormat("Socket Tag [%d] is NULL",tag);
	HSMessageBox(error->getCString());
	error->release();
	return NULL;
}

void HSSocketPool::Updata()
{
	map<int,HSSocket*>::iterator it = this->m_socketList.begin();
	for (;it!=this->m_socketList.end();++it)
	{
		if (it->second != NULL)
		{
			it->second->Updata();
		}
	}
}