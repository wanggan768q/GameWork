#include "HSDailyRewardSystemLayer.h"

static HSDailyRewardSystemLayer* s_DailyRewardSystemLayer = NULL;

//Layer
HSDailyRewardSystemLayer::HSDailyRewardSystemLayer(void)
{
}

HSDailyRewardSystemLayer::~HSDailyRewardSystemLayer(void)
{
}

bool HSDailyRewardSystemLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	this->Load();
	//this->setIsTouchEnabled(true);

	this->setKeypadEnabled(true);

	return true;
}

void HSDailyRewardSystemLayer::Load()
{
	CCLayerColor* pLayerColor = CCLayerColor::create(ccc4(0,0,0,200),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	HSTool::SetNodeFilldScreen(pLayerColor);
	this->addChild(pLayerColor);

	HSReadUI::ShareReadUI()->ReadUI("Image/DailyRewardSystem/DailyRewardSystem.data","Image/DailyRewardSystem/",this);

	HS_SET_MENU_TARGET("UI_LingQuJiangLi",this,HSDailyRewardSystemLayer::Call_Claimed);

	int dayCount = HS_GAME_CACHE()->m_DailyRewardSystemData.dailyrewardlist_size();
	for (int i=0;i<dayCount;++i)
	{
		DailyRewardSystemData_DailyReward dailyReward = HS_GAME_CACHE()->m_DailyRewardSystemData.dailyrewardlist(i);
		CCString* UI = CCString::createWithFormat("UI_DengLuJiangLi_day%d",i);
		for (int j=0;j<7;++j)
		{
			if (j != i)
			{
				CCString* day = CCString::createWithFormat("day%d",j);
				CCSprite* s = HS_FIND_UI_PANEL_SPRITE(UI->getCString(),day->getCString());
				s->setVisible(false);
			}
		}

		CCSprite* pGoldFrame = HS_FIND_UI_PANEL_SPRITE(UI->getCString(),"Shuzidiandikuang");
		CCLabelTTF* pGoldTTF = CCLabelTTF::create(CCString::createWithFormat("%d",dailyReward.gold())->getCString(),"Marker Felt",25.f);
		pGoldTTF->setPosition(pGoldFrame->getAnchorPointInPoints());
		pGoldFrame->addChild(pGoldTTF);

		switch (dailyReward.state())
		//switch (DailyRewardSystemData_DailyReward_ClaimedState_ClaimedState_AllowClaimed)
		{
		case DailyRewardSystemData_DailyReward_ClaimedState_ClaimedState_Unclaimed:
			{
				//CCSprite* s = HS_FIND_UI_PANEL_SPRITE(UI->getCString(),"riqibiaoji");
				//s->setVisible(false);
			}
			break;
		case DailyRewardSystemData_DailyReward_ClaimedState_ClaimedState_Claimed:
			{
				CCSprite* pBlue = HS_FIND_UI_PANEL_SPRITE(UI->getCString(),"riqidiban0");
				pBlue->setVisible(false);

				CCSprite* s = HS_FIND_UI_PANEL_SPRITE(UI->getCString(),"riqibiaoji");
				s->setVisible(false);
			}
			break;
		case DailyRewardSystemData_DailyReward_ClaimedState_ClaimedState_AllowClaimed:
			{
				m_AllowClaimedDayID = dailyReward.dayid();
			}
			break;
		}
	}
}

void HSDailyRewardSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSDailyRewardSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSDailyRewardSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSDailyRewardSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSDailyRewardSystemLayer::keyBackClicked()
{

}
void HSDailyRewardSystemLayer::keyMenuClicked()
{

}

HSDailyRewardSystemLayer* HSDailyRewardSystemLayer::ShaderDailyRewardSystemLayer()
{
	if (!s_DailyRewardSystemLayer)
	{
		s_DailyRewardSystemLayer = HSDailyRewardSystemLayer::create();
	}

	return s_DailyRewardSystemLayer;
}

void HSDailyRewardSystemLayer::setVisible( bool visible )
{
#define HS_DailyRewardSystemLayer_Tag 0x75699
	if (visible)
	{
		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		if (!pScene->getChildByTag(HS_DailyRewardSystemLayer_Tag))
		{
			pScene->addChild(this,HS_DailyRewardSystemLayer_Tag);
		}

	}else{
		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		if (pScene->getChildByTag(HS_DailyRewardSystemLayer_Tag))
		{
			pScene->removeChildByTag(HS_DailyRewardSystemLayer_Tag);
		}
	}
	CCLayer::setVisible(visible);
}

void HSDailyRewardSystemLayer::Call_Claimed( CCObject* pObj )
{
	this->setVisible(false);
	HSRequest::ShareRequest()->SendClaimedDailyRewardRequest(m_AllowClaimedDayID);
}
