#include "HSGamePlayerInfoLayer.h"
#include "HSPlayerInfoListView.h"
#include "HSHeadSprite.h"
#include "HSGameSceneJumpManage.h"

static HSGamePlayerInfoLayer* s_sharedPlayerInfoLayer = NULL;
HSGamePlayerInfoLayer::HSGamePlayerInfoLayer(void)
{
	m_pPlayerInfoListView = NULL;
	m_pHead = NULL;
	m_ppanle = NULL;
	m_p_foreLayer = NULL;
	m_p_background = NULL;
	m_flyin = false;
}

HSGamePlayerInfoLayer::~HSGamePlayerInfoLayer(void)
{
	m_pPlayerInfoListView = NULL;
	m_pHead = NULL;
	m_ppanle = NULL;
	m_p_foreLayer = NULL;
	m_p_background = NULL;

	CC_SAFE_RELEASE_NULL(s_sharedPlayerInfoLayer);
}

bool HSGamePlayerInfoLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//HSTool::SetLayerScale(this);
	Load();
	this->setTouchEnabled(true);

	//this->setKeypadEnabled(true);

	return true;
}

HSGamePlayerInfoLayer* HSGamePlayerInfoLayer::SharedPlayerInfoLayer()
{
	if(!s_sharedPlayerInfoLayer)
	{
		s_sharedPlayerInfoLayer = HSGamePlayerInfoLayer::create();
		s_sharedPlayerInfoLayer->retain();
	}

	return s_sharedPlayerInfoLayer;

}

void HSGamePlayerInfoLayer::Load()
{
	m_p_background = CCSprite::create("Image/main/playerInfo/BEIJING.png");
	m_p_background->setPosition(HSBase::GetScreenCentre());
	HSTool::SetNodeFilldScreen(m_p_background);
	this->addChild(m_p_background);

	m_p_foreLayer = CCLayer::create();
	HSTool::SetLayerScale(m_p_foreLayer);
	this->addChild(m_p_foreLayer);

	HSReadUI::ShareReadUI()->ReadUI("Image/main/playerInfo/playerInfo.data","Image/main/playerInfo/",m_p_foreLayer);
	HS_SET_MENU_TARGET("UI_fh_01",this,HSGamePlayerInfoLayer::CallReturn);
	HS_SET_MENU_TARGET("UI_huantouxianganniu",this,HSGamePlayerInfoLayer::CallChangeHead);

	m_iconId = HS_TARGET_SELF().iconid();
	CCSprite* pheadFrame = HS_FIND_UI_PANEL_SPRITE("UI_TOUXIANG","TOUXIANG");
	const char* pheadPath = CCString::createWithFormat("Image/head/%d.png",HS_TARGET_SELF().iconid())->getCString();
	m_pHead = CCSprite::create(pheadPath);
	m_pHead->setPosition(pheadFrame->getAnchorPointInPoints());
	pheadFrame->addChild(m_pHead);

	CCSprite* pFriendFrame = HS_FIND_UI_PANEL_SPRITE("UI_gerenxinxizongban_gerenxinxifanwei","gerenxinxilanfanwei");
	m_pPlayerInfoListView = HSPlayerInfoListView::create(&HS_TARGET_SELF(),pFriendFrame->getContentSize(),CCSizeMake(550,52),16);
	CCPoint pos = CCPointZero;
	//pos.x = -pFriendFrame->getContentSize().width / 2.f - 15.f;
	pos.x = pFriendFrame->getPosition().x - pFriendFrame->getContentSize().width / 2.f;
	pos.y = pFriendFrame->getPosition().y - pFriendFrame->getContentSize().height / 2.f;
	m_pPlayerInfoListView->setPosition(pos);
	pFriendFrame->getParent()->addChild(m_pPlayerInfoListView,1000);
	m_pPlayerInfoListView->reloadData();

	CCSprite* pNameFrame =  HS_FIND_UI_PANEL_SPRITE("UI_gerenxinxizongban_Wanjiamingzikuang","Wanjiamingzikuang");
	CCLabelTTF* nameLable = CCLabelTTF::create(HS_TARGET_SELF().name().c_str(),HS_FONT_HuaKang,25.f,pNameFrame->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	nameLable->setPosition(pNameFrame->getAnchorPointInPoints());
	pNameFrame->addChild(nameLable);

	m_ppanle = HS_FIND_UI_PANEL("UI_gerenxinxizongban");
	m_panlePosition = m_ppanle->getPosition();

	CCLOG("position x=%f,y=%f",m_panlePosition.x,m_panlePosition.y);

	PL_FlyIn(*m_ppanle,m_panlePosition);

	m_pHeadPanle =HS_FIND_UI_PANEL("UI_huantouxiangzu");
	m_pHeadPanle->setVisible(false);
	HS_SET_MENU_TARGET("UI_huantouxiangzu_guanbianniu",this,HSGamePlayerInfoLayer::CloseChangeHead);

	for(int i =0; i < 6; i++)
	{
		HSHeadSprite* phead = HSHeadSprite::create(HS_GAME_CACHE()->GetPropInfoData()->headlist(i),i);
		phead->setTag(i);
		phead->SetTarget(this,callfuncND_selector(HSGamePlayerInfoLayer::CloseChangeHead),NULL);

		this->addChild(phead);
	}

	this->schedule(schedule_selector(HSGamePlayerInfoLayer::Update));
}

void HSGamePlayerInfoLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSGamePlayerInfoLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
// 	if(m_pHeadPanle->isVisible())
// 	{
// 		return true;
// 	}
	return true;
}

void HSGamePlayerInfoLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGamePlayerInfoLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGamePlayerInfoLayer::keyBackClicked()
{
	if (!HS_IsRunGameGuide())
	{
		HS_GO_SCENE(HS_SCENE_CoverScene);
	}
}
void HSGamePlayerInfoLayer::keyMenuClicked()
{

}

void HSGamePlayerInfoLayer::CallReturn(CCObject*)
{
	PL_FlyOut(*m_ppanle,m_panlePosition);
}

void HSGamePlayerInfoLayer::CallChangeHead(CCObject*)
{
	m_pHeadPanle->setVisible(true);
}

void HSGamePlayerInfoLayer::CloseChangeHead(CCObject*)
{
	m_pHeadPanle->setVisible(false);
}

void HSGamePlayerInfoLayer::CloseChangeHead(CCNode* pTarget,void* data)
{
	int index = pTarget->getTag();
	m_pHeadPanle->setVisible(false);
	int id = HS_GAME_CACHE()->GetPropInfoData()->headlist(index).id();
	HSRequest::ShareRequest()->SendUserInfoUpdateRequest_IconId(id);
}

void HSGamePlayerInfoLayer::Update(float dt)
{
	if(m_iconId !=HS_TARGET_SELF().iconid())
	{
		m_iconId = HS_TARGET_SELF().iconid();

		const char* pheadPath = CCString::createWithFormat("Image/head/%d.png",m_iconId)->getCString();
		
		m_pHead->initWithFile(pheadPath);

		CCSprite* pheadFrame = HS_FIND_UI_PANEL_SPRITE("UI_TOUXIANG","TOUXIANG");
		m_pHead->setPosition(pheadFrame->getAnchorPointInPoints());
	}
}

void HSGamePlayerInfoLayer::PL_FlyIn( CCNode& ppanle,CCPoint& ppostion)
{
	if(!m_flyin)
	{
		ppanle.setPosition(ccp(ppostion.x,-ppostion.y));

		CCActionInterval* actionFlyIn =CCMoveTo::create(0.3f,ppostion);
		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGamePlayerInfoLayer::PL_FlyInFinish));
		ppanle.runAction(CCSequence::create(actionFlyIn,pCallFunc,NULL));
		m_flyin = true;
	}
	

	
}

void HSGamePlayerInfoLayer::PL_FlyOut( CCNode& ppanle,CCPoint& pposition )
{
	if(&ppanle)
	{
		CCActionInterval*  actionFlyOut =CCMoveTo::create(0.3f,ccp(pposition.x,-pposition.y));
		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGamePlayerInfoLayer::PL_FlyOutFinish));
		ppanle.runAction(CCSequence::create(actionFlyOut,pCallFunc,NULL));
	}
}

void HSGamePlayerInfoLayer::PL_FlyInFinish()
{
	m_flyin = false;
}

void HSGamePlayerInfoLayer::PL_FlyOutFinish()
{
	this->setVisible(false);
}

void HSGamePlayerInfoLayer::setVisible(bool visible)
{

	#define HS_PlayerInfo_Tag 0x75700


	CCLayer::setVisible(visible);
	if(visible)
	{

		//CCLOG("visible position x=%f,y=%f",m_panlePosition.x,m_panlePosition.y);
		 
		PL_FlyIn(*m_ppanle,m_panlePosition);

		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();

		if (!pScene->getChildByTag(HS_PlayerInfo_Tag))
		{
			pScene->addChild(this,HS_PlayerInfo_Tag,HS_PlayerInfo_Tag);
		}
	}
	else
	{
		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		if (pScene->getChildByTag(HS_PlayerInfo_Tag))
		{
			pScene->removeChildByTag(HS_PlayerInfo_Tag);
		}
	}
}




