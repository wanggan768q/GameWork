#include "HSRaycastCallback.h"


HSRaycastCallback::HSRaycastCallback(void)
{
	m_listerBalloonColorType = BALLOON_COLOR_Unknow;
	m_pLineList = NULL;
	m_pPointList = NULL;
	m_pDrawLineCount = NULL;
}


HSRaycastCallback::~HSRaycastCallback(void)
{
	m_pLineList = NULL;
}

float32 HSRaycastCallback::ReportFixture( b2Fixture *fixture,const b2Vec2 &point,const b2Vec2 &normal,float32 fraction )
{
	if (!fixture)
	{
		return HS_Raycast_continue;
	}
	HSBalloonSprite* ps = (HSBalloonSprite*)(fixture->GetBody()->GetUserData());
	if (ps)
	{
		std::map<int,HSBalloonSprite*>::iterator it = m_passBalloonMap.begin();
		int passBalloonMapSize = (int)m_passBalloonMap.size();
		if (passBalloonMapSize == 0)
		{
			//CCLog("illegal operation ");
		}
		if (m_listerBalloonColorType == BALLOON_COLOR_Unknow)
		{
			it = m_passBalloonMap.begin();
			if (it != m_passBalloonMap.end())
			{
				m_listerBalloonColorType = it->second->GetColorType();
			}

			if (m_listerBalloonColorType == BALLOON_COLOR_Petrifaction || m_listerBalloonColorType == BALLOON_COLOR_Chameleon)
			{
				//CCLog("    terminate  1");
				return HS_Raycast_terminate;
			}
		}
		if (ps->GetColorType() != BALLOON_COLOR_Camouflage)
		{
			if ( m_listerBalloonColorType != ps->GetColorType())
			{
				//CCLog("    terminate 2");
				return HS_Raycast_terminate;
			}
		}
		
		if ((int)m_passBalloonMap.size() > 1)
		{
			it = m_passBalloonMap.find(ps->GetID());
			if (it != m_passBalloonMap.end())
			{
				this->Reverse(ps);
				//CCLog("    continue ");
				return HS_Raycast_continue;
			}
		}
		
		
		this->AddBalloon(ps);
	}
	return HS_Raycast_continue;
}

void HSRaycastCallback::Reset()
{
	std::vector<HSBalloonSprite*>::iterator passBalloonListIt = m_passBalloonList.begin();

	for (;passBalloonListIt != m_passBalloonList.end();++passBalloonListIt)
	{
		(*passBalloonListIt)->SetLuminous(false);
	}

	m_passBalloonMap.clear();
	m_passBalloonList.clear();
	m_passBalloonList.resize(0);

	m_listerBalloonColorType = BALLOON_COLOR_Unknow;
}

const std::map<int,HSBalloonSprite*>* HSRaycastCallback::GetPassBalloonMap()
{
	return &m_passBalloonMap;
}

const std::vector<HSBalloonSprite*>* HSRaycastCallback::GetPassBalloonList()
{
	return &m_passBalloonList;
}

bool HSRaycastCallback::AddBalloon( HSBalloonSprite* ps )
{
	if (!ps)
	{
		return false;
	}
	std::vector<HSBalloonSprite*>::reverse_iterator rIt = m_passBalloonList.rbegin();
	if ((int)m_passBalloonList.size() > 0)
	{
		if (rIt == m_passBalloonList.rend())
		{
			return false;
		}
		CCPoint p1 = (*rIt)->getPosition();
		CCPoint p2 = ps->getPosition();
		float distancce = ccpDistance(p1,p2);
		//float maxDistance = (float)HS_MAX_DISTANCE;
        float maxDistance = HSFormula::LianXianJuLi();
		if (distancce > maxDistance)
		{
			//CCLog("%.2f ---- Add Fail Beyond the maximum distance",distancce);
			return false;
		}
	}else{
		if (ps->GetColorType() == BALLOON_COLOR_Camouflage || ps->GetColorType() == BALLOON_COLOR_Petrifaction)
		{
			return false;
		}
	}
	ps->SetLuminous(true);

	rIt = m_passBalloonList.rbegin();
	for (;rIt != m_passBalloonList.rend();++rIt)
	{
		if ((*rIt) == ps)
		{
			return true;
		}
	}
	m_passBalloonList.push_back(ps);
	m_passBalloonMap.insert(pair<int,HSBalloonSprite*>(ps->GetID(),ps));
    
    //经过动画
    ps->runAction(ps->PassAction());

    int count = m_passBalloonMap.size();
    count >= 15 ? count = 14 : 0;
    //音效
    CCString* pSoundFileName = CCString::createWithFormat("touch_%02d",count - 1);
    HS_Play_Sound(pSoundFileName->getCString());
    CC_SAFE_RELEASE_NULL(pSoundFileName);
    

#if 0
	CCLog("Add Balloon ID: %d     color:%d",ps->GetID(),ps->GetColorType());
#endif

	if (m_passBalloonList.size() != m_passBalloonMap.size())
	{
		HSMessageBox("------illegal size");
		return false;
	}

	return true;
}

bool HSRaycastCallback::Reverse( HSBalloonSprite* ps )
{
	std::vector<HSBalloonSprite*>::reverse_iterator rIt = m_passBalloonList.rbegin();
	std::vector<HSBalloonSprite*>::iterator It = m_passBalloonList.begin();

    // #120
	//if ((*It) == ps)
	//{
	//	this->Reset();
	//	this->ReverseLineAll();
	//	return true;
	//}

	if ((int)m_passBalloonList.size() > 1)
	{
		int lastBalloonID = (*rIt)->GetID();
		
		++rIt;
		if (rIt != m_passBalloonList.rend())
		{
			if ((*rIt) == ps)
			{
				if (!this->ReverseLine())
				{
					return false;
				}
				this->RemoveBalloon(lastBalloonID);
				return true;
			}
		}else{
			
			if ((*It) == ps)
			{
				this->Reset();
			}
		}
	}

	return false;
}

void HSRaycastCallback::SetLineList( std::vector<HSLine*>* pLineList )
{
	m_pLineList = pLineList;
}


void HSRaycastCallback::SetPointList( std::vector<HSPoint*>* pPointList )
{
	m_pPointList = pPointList;
}

bool HSRaycastCallback::ReverseLine()
{
	if (!m_pLineList)
	{
		return false;
	}
	std::vector<HSLine*>::reverse_iterator lineIt = m_pLineList->rbegin();
	if (lineIt != m_pLineList->rend())
	{
		CCNode* pParent = (*lineIt)->getParent();
		if (pParent)
		{
			pParent->removeChild(*lineIt);
		}
		std::vector<HSLine*>::iterator tempIt = m_pLineList->end();
		--tempIt;
		m_pLineList->erase(tempIt);
		if (NULL != m_pDrawLineCount)
		{
			--(*m_pDrawLineCount);
		}
	}

	this->ReversePoint();
	
	return true;
}

bool HSRaycastCallback::ReversePoint()
{
	if (!m_pPointList)
	{
		return false;
	}
	std::vector<HSPoint*>::reverse_iterator pointIt = m_pPointList->rbegin();
	if (pointIt != m_pPointList->rend())
	{
		CCNode* pParent = (*pointIt)->getParent();
		if (pParent)
		{
			pParent->removeChild(*pointIt);
		}
		std::vector<HSPoint*>::iterator tempIt = m_pPointList->end();
		--tempIt;
		m_pPointList->erase(tempIt);
	}

	return true;
}

bool HSRaycastCallback::ReverseLineAll()
{
	if (!m_pLineList)
	{
		return false;
	}

	std::vector<HSLine*>::iterator It = m_pLineList->begin();
	for (;It != m_pLineList->end();++It)
	{
		CCNode* pParent = (*It)->getParent();
		pParent->removeChild(*It);
	}
	m_pLineList->clear();

	(*m_pDrawLineCount) = 0;

	this->ReversePointAll();

	return true;
}

bool HSRaycastCallback::ReversePointAll()
{
	std::vector<HSPoint*>::iterator pointIt = m_pPointList->begin();
	for (;pointIt != m_pPointList->end();++pointIt)
	{
		CCNode* pParent = (*pointIt)->getParent();
		if (pParent)
		{
			pParent->removeChild(*pointIt);
		}
	}
	m_pPointList->clear();
	return true;
}

bool HSRaycastCallback::RemoveBalloon( int balloonID )
{
	if (balloonID < 0)
	{
		return false;
	}
	std::map<int,HSBalloonSprite*>::iterator passBalloonMapIt = m_passBalloonMap.find(balloonID);
	std::vector<HSBalloonSprite*>::iterator passBalloonListIt = m_passBalloonList.begin();

	if (passBalloonMapIt != m_passBalloonMap.end())
	{
		passBalloonMapIt->second->SetLuminous(false);
		m_passBalloonMap.erase(passBalloonMapIt);
	}

	for (;passBalloonListIt != m_passBalloonList.end();++passBalloonListIt)
	{
		if ((*passBalloonListIt)->GetID() == balloonID)
		{
			m_passBalloonList.erase(passBalloonListIt);
			break;
		}
	}

	return true;
}

void HSRaycastCallback::SetLineCount( int* lineCount )
{
	m_pDrawLineCount = lineCount;
}



