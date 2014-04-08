#include "HSStratagemManager.h"

HSStratagemManager::HSStratagemManager( void )
{
	m_isFrsitUpdata = true;
	m_actionIndex = -1;
	m_isUseNextStratagemConfig = false;
}

HSStratagemManager::~HSStratagemManager( void )
{
	m_ConfigList.clear();
	m_actionQueue.clear();

	std::map<unsigned int,HSStratagemSprite*>::iterator it = m_StratagemSpriteMap.begin();
	for (;it!=m_StratagemSpriteMap.end();++it)
	{
		HSStratagemSprite* s = it->second;
		if (s)
		{
			CC_SAFE_RELEASE_NULL(s);
		}
	}
	m_StratagemSpriteMap.clear();

	CC_SAFE_DELETE(m_pData);
}

HSStratagemManager* HSStratagemManager::create( const char* configeDataName,b2World* pWorld )
{
	HSStratagemManager* manager = new HSStratagemManager;
	if (manager && manager->Init(configeDataName,pWorld))
	{
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return NULL;
}

bool HSStratagemManager::Init( const char* configeDataName,b2World* pWorld )
{
	
	HSFileData data(configeDataName,"rb");

	m_pData = message::StratagemData::default_instance().New();

	bool isOk = m_pData->ParsePartialFromArray((const void*)(data.GetBuffer() + sizeof(short)) ,data.GetSize() - sizeof(short));

	for (int i=0;isOk && i<m_pData->config_size();++i)
	{
		const message::StratagemData_StratagemConfig* pConfig = &m_pData->config(i);

		//添加刚体模型
		HSBox2dShapeCache::sharedGB2ShapeCache()->addShapesWithFile("Image/Stratagem/" + pConfig->bodyshapeplistname());

		for (int j=0;j<pConfig->stratagembaselist_size();++j)
		{
			const message::StratagemData_StratagemBase* pBase = &pConfig->stratagembaselist(j);
			HSStratagemSprite* pStratagemSprite = HSStratagemSprite::create(pBase,pWorld);
			pStratagemSprite->retain();
			this->m_StratagemSpriteMap.insert(pair<unsigned int,HSStratagemSprite*>(pBase->id(),pStratagemSprite));
		}

		m_ConfigList.push_back(pConfig);
	}
	m_ConfigIt = m_ConfigList.begin();

	this->schedule(schedule_selector(HSStratagemManager::Updata));

	return true;
}

void HSStratagemManager::Up()
{
	if (m_ConfigIt == m_ConfigList.end())
	{
		return;
	}
	const message::StratagemData_StratagemConfig* pConfig = *m_ConfigIt;
	
	if (m_actionIndex == -1)
	{
		return;
	}

	--m_actionIndex;

	if ( m_actionIndex == -1 )
	{
		m_actionQueue.push_back(NULL);
		return;
	}
	const message::StratagemData_StratagemAction* pAction = &pConfig->actionlist(m_actionIndex);

	m_actionQueue.push_back(pAction);
}

void HSStratagemManager::Down()
{	
	if (m_ConfigIt == m_ConfigList.end())
	{
		return;
	}

	if (true == m_isUseNextStratagemConfig)
	{
		m_isUseNextStratagemConfig = false;
		++m_ConfigIt;
		if (m_ConfigIt == m_ConfigList.end())
		{
			m_ConfigIt = m_ConfigList.begin();
		}
		//更换机关 动作ID 重置
		m_actionIndex = -1;
	}

	const message::StratagemData_StratagemConfig* pConfig = *m_ConfigIt;

	if (m_actionIndex >= pConfig->actionlist_size())
	{
		return;
	}

	++m_actionIndex;

	if (m_actionIndex == pConfig->actionlist_size())
	{
		m_actionIndex--;
		return;
	}

	const message::StratagemData_StratagemAction* pAction = &pConfig->actionlist(m_actionIndex);

	m_actionQueue.push_back(pAction);
}

void HSStratagemManager::Updata( float dt )
{
	if (m_isFrsitUpdata)
	{
		std::map<unsigned int,HSStratagemSprite*>::iterator it = m_StratagemSpriteMap.begin();
		for (;it != m_StratagemSpriteMap.end();++it)
		{
			CCNode* layer = this->getParent();
			if (layer != NULL)
			{
				m_isFrsitUpdata = false;
				layer->addChild(it->second);
			}
		}
		return;
	}

	bool isNextAction = true;
	std::map<unsigned int,HSStratagemSprite*>::iterator it = m_StratagemSpriteMap.begin();
	for (;it != m_StratagemSpriteMap.end();++it)
	{
		if (it->second->GetIsMoveOver() == false)
		{
			isNextAction = false;
			break;
		}
	}

	if ((int)m_actionQueue.size() > 0 && isNextAction == true)
	{
		const message::StratagemData_StratagemAction* pAction = m_actionQueue[0];
		m_actionQueue.erase(m_actionQueue.begin());

		if (pAction == NULL)
		{
			const message::StratagemData_StratagemConfig* pConfig = *m_ConfigIt;

			for (int i=0;i < pConfig->stratagembaselist_size();++i)
			{
				it = m_StratagemSpriteMap.find(pConfig->stratagembaselist(i).id());
				if (it != m_StratagemSpriteMap.end())
				{
					it->second->MoveToZero();
				}
			}
			m_actionQueue.erase(m_actionQueue.begin(),m_actionQueue.end());
			m_actionQueue.clear();
			HS_GAME_CONFIG()->ResetStratagemTime();
			m_isUseNextStratagemConfig = true;
			return;
		}

		//@一起运动
		for (int i=0;i<pAction->togethermovelist_size();++i)
		{
			const message::StratagemData_StratagemStep* pStep = &pAction->togethermovelist(i);
			it  = m_StratagemSpriteMap.find(pStep->stratagemid());
			if (it != m_StratagemSpriteMap.end())
			{
				it->second->AddMoveStep(pStep);
				it->second->Start();
			}
		}
		//@顺序运动
		HSStratagemSprite* lastSprite = NULL;
		HSStratagemSprite* willStartSprite = NULL;
		for (int i=0;i<pAction->sequencemoveslist_size();++i)
		{
			const message::StratagemData_StratagemStep* pStep = &pAction->sequencemoveslist(i);
			it  = m_StratagemSpriteMap.find(pStep->stratagemid());
			if (it != m_StratagemSpriteMap.end())
			{
				it->second->AddMoveStep(pStep);
				if (willStartSprite == NULL)
				{
					willStartSprite = it->second;
				}

				if (lastSprite != NULL)
				{
					lastSprite->SetNextStratagem(it->second);
				}
				lastSprite = it->second;
			}
		}
		if (willStartSprite != NULL)
		{
			willStartSprite->Start();
		}
	}
}

int HSStratagemManager::GetActionIndex()
{
	return m_actionIndex;
}