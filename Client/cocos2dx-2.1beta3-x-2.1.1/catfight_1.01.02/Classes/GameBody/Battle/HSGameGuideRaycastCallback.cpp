#include "HSGameGuideRaycastCallback.h"
#include "HSGameGuide.h"
#include "HSBattleScene.h"

HSGameGuideRaycastCallback::HSGameGuideRaycastCallback(void)
{
	m_pTrackMove = NULL;
	m_isAddFrist = true;

	int battleLayoutCount = HSGameGuide::ShaderGameGuide()->m_pGameGuideData->battlelayoutlist_size();
	for (int i=0;i<battleLayoutCount;++i)
	{
		
		int trackCount = HSGameGuide::ShaderGameGuide()->m_pGameGuideData->battlelayoutlist(i).destroyballoonidlist_size();
		if (trackCount > 0)
		{
			std::vector< int >* pv = new std::vector< int >;
			for (int j=0;j<trackCount;++j)
			{
				pv->push_back(HSGameGuide::ShaderGameGuide()->m_pGameGuideData->battlelayoutlist(i).destroyballoonidlist(j));
			}
			m_destroyBalloonIDList.push_back(pv);
		}
	}

}


HSGameGuideRaycastCallback::~HSGameGuideRaycastCallback(void)
{
}

bool HSGameGuideRaycastCallback::AddBalloon( HSBalloonSprite* ps )
{
	if (!ps)
	{
		return false;
	}
	std::vector< std::vector< int >* >::iterator it = m_destroyBalloonIDList.begin();
	if (it != m_destroyBalloonIDList.end())
	{
		std::vector< int >* track = *it;
		if (m_isAddFrist)
		{
			if((*track)[0] != ps->GetID())
			{
				return false;
			}
			m_isAddFrist = false;
		}
	}
	return HSRaycastCallback::AddBalloon(ps);
}

void HSGameGuideRaycastCallback::Reset()
{
	m_isAddFrist = true;
	if (IsAllowDestroy())
	{
		std::vector< std::vector< int >* >::iterator it = m_destroyBalloonIDList.begin();
		if (it != m_destroyBalloonIDList.end())
		{
			if (m_pTrackMove)
			{
				m_pTrackMove->Stop();
			}
			delete *it;
			m_destroyBalloonIDList.erase(it);

			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSGameGuide::ShaderGameGuide()->Resume(pScene);
		}
		it = m_destroyBalloonIDList.begin();
		if (it != m_destroyBalloonIDList.end())
		{
			if (m_pTrackMove)
			{
				m_pTrackMove->SetTrack(*it);
				m_pTrackMove->Reset();
			}
		}
	}

	HSRaycastCallback::Reset();	
}

bool HSGameGuideRaycastCallback::IsAllowDestroy()
{
	std::vector< std::vector< int >* >::iterator it = m_destroyBalloonIDList.begin();
	if (it != m_destroyBalloonIDList.end())
	{
		int trackCount = ((int)(*it)->size());
		if (trackCount == (int)m_passBalloonList.size())
		{
			return true;
		}
	}
	return false;
}

void HSGameGuideRaycastCallback::StartGuide(CCNode* pNode)
{
	std::vector< std::vector< int >* >::iterator it = m_destroyBalloonIDList.begin();
	if (it != m_destroyBalloonIDList.end())
	{
		std::vector< int >* track = *it;
		if (!m_pTrackMove)
		{
			m_pTrackMove = new HSTrackMove(pNode,track);
			m_pTrackMove->Start();
		}
	}
}



//////////////////////////////////////////////////////////////////////////

HSTrackMove::HSTrackMove( CCNode* pNode ,std::vector< int >* pTrackID )
{
	m_pNode = pNode;
	this->SetTrack(pTrackID);
	m_actionState = ActionState_Run;
}

HSTrackMove::~HSTrackMove( void )
{
	m_pTrackID = NULL;	//不需要释放
}

void HSTrackMove::Start()
{
	HSBattleLayer* pBattleLayer = HS_GET_BattleLayer();
	map<int,HSBalloonSprite*>* pBalloonMap = pBattleLayer->GetBalloonMap();
	

	if (m_TrackID_It == m_pTrackID->end())
	{
		m_TrackID_It = m_pTrackID->begin();
		const GameGuide_BattleLayout_BalloonInfo* pTemp = HSGameGuide::ShaderGameGuide()->GetBallonInfo(*m_TrackID_It);
		CCPoint pNodePos = pBalloonMap->find(pTemp->id())->second->getPosition();
		m_pNode->setPosition(pNodePos/*ccp(pTemp->x(),pTemp->y())*/);
	}



	int currentStepID = HSGameGuide::ShaderGameGuide()->GetCurrentStepID();
	bool isShow = HSGameGuide::ShaderGameGuide()->isVisible();
	if (isShow && (currentStepID == 1004 || currentStepID == 1005 || currentStepID == 1006 || currentStepID == 1007 || currentStepID == 1008 || currentStepID == 1009  || currentStepID == 1010 || currentStepID == 1011) )
	{
		m_actionState = ActionState_Await;
		m_pNode->setVisible(false);
	}else{
		if (m_actionState == ActionState_Await )
		{
			m_TrackID_It = m_pTrackID->begin();
			const GameGuide_BattleLayout_BalloonInfo* pTemp = HSGameGuide::ShaderGameGuide()->GetBallonInfo(*m_TrackID_It);
			m_pNode->setPosition(ccp(pTemp->x(),pTemp->y()));
			m_actionState = ActionState_Run;
		}
		m_pNode->setVisible(true);
	}

	int lastID = *m_pTrackID->rbegin();
	int fristID = *m_pTrackID->begin();

	int id = *m_TrackID_It;
	const GameGuide_BattleLayout_BalloonInfo* pBalloonInfo = HSGameGuide::ShaderGameGuide()->GetBallonInfo(id);
	
	CCPoint pos = pBalloonMap->find(pBalloonInfo->id())->second->getPosition();
	CCMoveTo* pMoveTo = CCMoveTo::create(m_duration,pos/*ccp(pBalloonInfo->x(),pBalloonInfo->y())*/);
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSTrackMove::Next));
	CCSequence* pSequence = NULL;


	if(id == fristID){
		CCFadeIn* pFadeIn = CCFadeIn::create(0.2f);
		CCDelayTime* pDelayTime = CCDelayTime::create(0.5f);
		pSequence = CCSequence::create(pFadeIn,pDelayTime,pMoveTo,pCall,NULL);
	}else if (lastID == id){
		CCFadeOut* pFadeOut = CCFadeOut::create(0.2f);
		CCDelayTime* pDelayTime = CCDelayTime::create(1.f);
		pSequence = CCSequence::create(pMoveTo,pDelayTime,pFadeOut,pCall,NULL);
	}else{
		pSequence = CCSequence::create(pMoveTo,pCall,NULL);
	}
	m_pNode->runAction(pSequence);
}

void HSTrackMove::Next( CCNode* pNode )
{
	m_TrackID_It++;
	this->Start();
}

void HSTrackMove::Reset()
{
	m_pNode->setVisible(true);
	this->Start();
}

void HSTrackMove::Stop()
{
	m_pNode->setVisible(false);
	m_pNode->stopAllActions();
}

void HSTrackMove::SetTrack( std::vector< int >* pTrackID )
{
	m_pTrackID = pTrackID;
	m_TrackID_It = m_pTrackID->begin();
	m_duration = ((float)m_pTrackID->size() / 2.f) / (float)((int)m_pTrackID->size());
}

CCNode* HSTrackMove::GetMoveNode()
{
	return m_pNode;
}


