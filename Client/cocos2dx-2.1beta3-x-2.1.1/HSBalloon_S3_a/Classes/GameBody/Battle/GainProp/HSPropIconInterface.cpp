#include "HSPropIconInterface.h"
#include "HSGameCache.h"
#include "HSRequest.h"


HSPropIconInterface::HSPropIconInterface(void)
{
	m_pMenuItem = NULL;
	m_CD_Progress = NULL;
	m_isActivate = false;
	m_index = 0;
	m_pPropInfo = NULL;
	m_basePath = "Image/prop/";
	schedule(schedule_selector(HSPropIconInterface::Updata));
}


HSPropIconInterface::~HSPropIconInterface(void)
{
	m_pMenuItem = NULL;
}

const std::string& HSPropIconInterface::GetBasePath()
{
	return m_basePath;
}

void HSPropIconInterface::SetPropInfoData( const PropInfo* pPropInfo )
{
	m_pPropInfo = pPropInfo;
}

const PropInfo* HSPropIconInterface::GetPropInfoData() const
{
	return m_pPropInfo;
}

void HSPropIconInterface::SetIndex( int index )
{
	m_index = index;
}

int HSPropIconInterface::GetIndex()
{
	return m_index;
}

void HSPropIconInterface::SetIsActivate( bool b )
{
	m_isActivate = b;
}

bool HSPropIconInterface::GetIsActivate()
{
	return m_isActivate;
}

void HSPropIconInterface::Call( CCObject* pObj )
{
	CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(pObj);
	CCBlink* pBink = CCBlink::create(0.2f,1);
	pItem->runAction(pBink);
}

bool HSPropIconInterface::Buy() const
{
	bool isOK =  HS_GAME_CACHE()->AddGold(0 - GetPropInfoData()->gold());
	if (isOK)
	{
		HSRequest::ShareRequest()->SendUsePropRequest(m_pPropInfo->id(),UsePropRequest_OperateType_Type_use,HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
	}
	return isOK;
}

bool HSPropIconInterface::AddCD(CCObject* pMenuItem)
{
	float cdTime = this->GetPropInfoData()->cttime();
	this->m_pMenuItem = dynamic_cast<CCMenuItem*>(pMenuItem);
	if (cdTime < 1.f || !m_pMenuItem)
	{
		return false;
	}

	CCSprite* CDSprite = CCSprite::create("Image/propCD.png");

	m_CD_Progress = CCProgressTimer::create(CDSprite);

	m_CD_Progress->setType(kCCProgressTimerTypeRadial);

	m_CD_Progress->setPosition(HS_SizeHalf_Point(this->getContentSize()));

	m_CD_Progress->setReverseDirection(true);

	this->addChild(m_CD_Progress);


	CCProgressFromTo* pProgressFromTo = CCProgressFromTo::create(cdTime,100.f,0.f);
	CCCallFuncN* pCallFunc = CCCallFuncN::create(this,callfuncN_selector(HSPropIconInterface::Call_CDEnd));
	m_CD_Progress->runAction(CCSequence::create(pProgressFromTo,pCallFunc,NULL));
	m_pMenuItem->setEnabled(false);

	return true;
}

void HSPropIconInterface::Call_CDEnd(CCNode* pProgress)
{
	pProgress->getParent()->removeChild(pProgress);

	HSAssert(m_pMenuItem ,"");

	m_pMenuItem->setEnabled(true);
}
