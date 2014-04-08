#include "HSCCLayer.h"


HSCCLayer::HSCCLayer(void)
{
	this->m_clipRect = CCRectMake(0,0,HS_SCREEN_WIDTH,HS_SCREEN_HEIGHT);
}


HSCCLayer::~HSCCLayer(void)
{
}

HSCCLayer* HSCCLayer::create()
{
	HSCCLayer *pRet = new HSCCLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void HSCCLayer::Push( string key,HSCCSprite* child )
{
	int begin = key.find_last_of('/');
	begin == std::string::npos ? begin = 0 : 1;
	int end = key.find_last_of('.');
	string name = key.substr(begin,end);

	map<std::string,HSCCSprite*>::iterator it = m_childMap.find(name);
	if (it != m_childMap.end())
	{
		HSMessageBox("[ %s ] repeat ",key.c_str());
		return;
	}

	m_childMap.insert(pair<std::string,HSCCSprite*>(name,child));
}

HSCCSprite* HSCCLayer::Find( string key )
{
	map<std::string,HSCCSprite*>::iterator it = m_childMap.find(key);
	if (it != m_childMap.end())
	{
		return it->second;
	}
	HSMessageBox("[ %s ] The query fails ",key.c_str());
	return NULL;
}
