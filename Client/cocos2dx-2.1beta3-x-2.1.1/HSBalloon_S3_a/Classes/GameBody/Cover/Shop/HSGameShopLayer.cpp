#include "HSGameShopLayer.h"
#include "HSShopListView.h"

static HSGameShopLayer* s_sharedShopLayer = NULL;
HSGameShopLayer::HSGameShopLayer(void)
{
	m_p_shop_money = NULL;
	m_p_foregroundLayer = NULL;
	m_p_backgournd = NULL;
	m_shop_flyIn = false;
}

HSGameShopLayer::~HSGameShopLayer(void)
{
	m_p_shop_money = NULL;
	m_p_backgournd = NULL;
	m_p_foregroundLayer = NULL;

	CC_SAFE_RELEASE_NULL(s_sharedShopLayer);
}

bool HSGameShopLayer::init()
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

HSGameShopLayer* HSGameShopLayer::SharedShopLayer()
{
	if(!s_sharedShopLayer)
	{
		s_sharedShopLayer = HSGameShopLayer::create();
		s_sharedShopLayer->retain();
	}

	return s_sharedShopLayer;
}

void HSGameShopLayer::Load()
{
	m_p_backgournd = CCSprite::create("Image/main/shop/BEIJING.png");
	m_p_backgournd->setPosition(HSBase::GetScreenCentre());
	HSTool::SetNodeFilldScreen(m_p_backgournd);
	this->addChild(m_p_backgournd);

	m_p_foregroundLayer = CCLayer::create();
	HSTool::SetLayerScale(m_p_foregroundLayer);
	this->addChild(m_p_foregroundLayer);

	HSReadUI::ShareReadUI()->ReadUI("Image/main/shop/shop.data","Image/main/shop/",m_p_foregroundLayer);

	HS_SET_MENU_TARGET("UI_sc_fh_01",this,HSGameShopLayer::CallReturn);

	HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_sc_jinbitoumingdi","Jinbidiandikuang");
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");

	m_p_shop_money = CCLabelAtlas::create(CCString::createWithFormat("%d",HS_GAME_CACHE()->GetGold())->getCString(),"Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_p_shop_money->setAnchorPoint(HS_ANCHOR_R_CENTER);
	m_p_shop_money->setPosition(ccp(gameGoldFrameSize.width,gameGoldFrameSize.height/2));
	m_p_shop_money->setScaleX(0.7f);
	gameGoldFrame->addChild(m_p_shop_money);


	m_p_shop_frame = HS_FIND_UI_PANEL("UI_shangchengzu");
	m_shop_frame_Position = m_p_shop_frame->getPosition();

	CCSprite* shop_frame = HS_FIND_UI_PANEL_SPRITE("UI_shangchengzu","shangchengtoumingdi");
	m_p_shop_listview = HSShopListView::create(shop_frame->getContentSize(),CCSizeMake(558,100),4);

	CCPoint pos = CCPointZero;

	
	pos.x = shop_frame->getPositionX() - shop_frame->getContentSize().width / 2.f + 18.f;
	pos.y = shop_frame->getPositionY() - shop_frame->getContentSize().height / 2.f;
	m_p_shop_listview->setPosition(pos);
	shop_frame->getParent()->addChild(m_p_shop_listview,1000);
	m_p_shop_listview->reloadData();

	//Shop_FlyIn(*m_p_shop_frame,m_shop_frame_Position);

	this->schedule(schedule_selector(HSGameShopLayer::Update));
}

void HSGameShopLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool HSGameShopLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameShopLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameShopLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameShopLayer::keyBackClicked()
{
}
void HSGameShopLayer::keyMenuClicked()
{

}

void HSGameShopLayer::Update(float dt)
{

}

void HSGameShopLayer::CallReturn( CCObject* pObj )
{
	Shop_FlyOut(*m_p_shop_frame,m_shop_frame_Position);
}

void HSGameShopLayer::Shop_FlyIn( CCNode& shop_frame,CCPoint&frame_Position)
{
	if(!m_shop_flyIn)
	{
		shop_frame.setPosition(ccp(frame_Position.x,-frame_Position.y));

		CCActionInterval* actionFlyIn =CCMoveTo::create(0.3f,frame_Position);
		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGameShopLayer::Shop_FlyInFinish));
		shop_frame.runAction(CCSequence::create(actionFlyIn,pCallFunc,NULL));

		m_shop_flyIn = true;
	}
	
}

void HSGameShopLayer::Shop_FlyOut( CCNode& shop_frame,CCPoint& frame_Position )
{
	if(&shop_frame)
	{
		CCActionInterval* actionFlyOut =CCMoveTo::create(0.3f,ccp(frame_Position.x,-frame_Position.y));
		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGameShopLayer::Shop_FlyOutFinish));
		shop_frame.runAction(CCSequence::create(actionFlyOut,pCallFunc,NULL));
	}
}

void HSGameShopLayer::Shop_FlyInFinish()
{

	this->m_shop_flyIn = false;
}

void HSGameShopLayer::Shop_FlyOutFinish()
{
	this->setVisible(false);
}

void HSGameShopLayer::setVisible(bool visible)
{
	#define HS_Shop_Tag 0x75699

	CCLayer::setVisible(visible);
	if(visible)
	{

		Shop_FlyIn(*m_p_shop_frame,m_shop_frame_Position);

		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();

		if (!pScene->getChildByTag(HS_Shop_Tag))
		{
			pScene->addChild(this,HS_Shop_Tag,HS_Shop_Tag);
		}
	}
	else
	{
		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		if (pScene->getChildByTag(HS_Shop_Tag))
		{
			pScene->removeChildByTag(HS_Shop_Tag);
		}
	}
}










