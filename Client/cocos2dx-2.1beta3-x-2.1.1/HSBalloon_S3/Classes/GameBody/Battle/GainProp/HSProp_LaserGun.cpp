#include "HSProp_LaserGun.h"
#include "HSBattleScene.h"

HSProp_LaserGun::HSProp_LaserGun(void)
{
	m_maxCount = 0;
	m_currentCount = 0;
	m_pToggle = NULL;
}


HSProp_LaserGun::~HSProp_LaserGun(void)
{
}

bool HSProp_LaserGun::InitProp( const PropInfo* pPropInfo )
{
	std::string fileName = GetBasePath() + pPropInfo->localname();
	CCSprite* pNode_0 = HSCCSprite::create(fileName.c_str());
	HSGraySprite* pNode_1 = HSGraySprite::create(fileName.c_str());
	CCSprite* pNode_2 = HSCCSprite::create(fileName.c_str());
	HSGraySprite* pNode_3 = HSGraySprite::create(fileName.c_str());
	pNode_1->setScale(1.02f);
	pNode_3->setScale(1.02f);

	CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(pNode_0,pNode_2);
	CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(pNode_1,pNode_3);

	m_pToggle = CCMenuItemToggle::createWithTarget(this,menu_selector(HSProp_LaserGun::Call),itemImage1,itemImage2,NULL);
	CCMenu* pMenu = CCMenu::create(m_pToggle,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	m_maxCount = pPropInfo->usenumber();
	m_currentCount = m_maxCount;

	m_pCurrentCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",m_currentCount)->getCString(),"",40.f);
	m_pCurrentCountTTF->setVisible(false);
	m_pCurrentCountTTF->setColor(ccc3(0,255,0));
	this->addChild(m_pCurrentCountTTF);

	return true;
}

void HSProp_LaserGun::SetIsInvalid(bool is)
{
    if (!m_pToggle)
    {
        return;
    }
    if (is)
    {
        m_pToggle->setSelectedIndex(1);
        m_pToggle->setEnabled(false);
    }else{
        m_pToggle->setSelectedIndex(0);
        m_pToggle->setEnabled(true);
    }
    
}

void HSProp_LaserGun::Updata(float dt)
{
	CCNode* pParent = this->getParent();
	if (!pParent || m_currentCount == 0)
	{
		return;
	}

	CCSize frameSize = pParent->getContentSize();
	float x = frameSize.width / 2.f - m_pCurrentCountTTF->getContentSize().width;
	float y = -frameSize.height / 2.f + m_pCurrentCountTTF->getContentSize().height / 2.f;
	m_pCurrentCountTTF->setPosition(ccp(x,y));
	m_pCurrentCountTTF->setVisible(true);

	if (m_currentCount > 0 && GetIsActivate() && HSBalloonSprite::GetTouchObject())
	{
		bool isOK = HS_GET_BattleLayer()->DestroyBalloon(HSBalloonSprite::GetTouchObject());
		if (isOK)
		{
			HSBalloonSprite::SetTouchObject(NULL);
			m_currentCount--;

			HS_Play_Sound("porp1_effect");

			if (m_currentCount <= 0)
			{
				m_currentCount = 0;
				m_pToggle->setSelectedIndex(0);
				m_pToggle->setEnabled(false);
				this->SetIsActivate(false);
			}
			m_pCurrentCountTTF->setString(CCString::createWithFormat("%d",m_currentCount)->getCString());
		}
	}
}

void HSProp_LaserGun::Call( CCObject* pObj )
{
	if (m_currentCount <= 0 && !GetIsActivate())
	{
		return;
	}
	this->SetIsActivate(!GetIsActivate());
	HSPropIconInterface::Call(pObj);

	if (m_currentCount == 0)
	{
		this->Buy();
	}
}

