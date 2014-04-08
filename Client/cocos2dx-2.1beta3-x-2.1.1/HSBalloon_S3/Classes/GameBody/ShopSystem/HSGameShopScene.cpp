#include "HSGameShopScene.h"
#include "HSShopListView.h"
#include "HSGameSceneJumpManage.h"
#include "HSJava.h"
#include "HSShowGlobal.h"

static HSGameShopLayer* s_sharedShopLayer = NULL;
HSGameShopLayer::HSGameShopLayer(void)
{

}

HSGameShopLayer::~HSGameShopLayer(void)
{

}

bool HSGameShopLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	//this->setTouchEnabled(true);

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
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/shop.data","Image/",this);

    //显示金币
    this->addChild(HSShowGlobal::create());
    
    //返回
	HS_SET_MENU_TARGET("UI_Tongyongguanbi", this, HSGameShopLayer::Call_Back);
	

    CCSprite* pFrame = HS_FIND_UI_PANEL_SPRITE("UI_Shangchengliebiaofanwei","Xingxianggenghuanfanwei");
    HSShopListView* m_p_shop_listview = HSShopListView::create(pFrame->getContentSize(),CCSizeMake(583,126),HS_GAME_CACHE()->GetPropInfoData()->buygoldlist_size());
    
	CCPoint pos = CCPointZero;
    
	pos.y = pFrame->getPosition().y - pFrame->getContentSize().height / 2.f;
	m_p_shop_listview->setPosition(pos);
	pFrame->getParent()->addChild(m_p_shop_listview,1000);
	m_p_shop_listview->reloadData();
    
	if(HSJava::ShaderJava()->GetChannel() == 10004)//联通
	{
		CCSprite* liantongLogo = HS_FIND_UI_PANEL_SPRITE("UI_shangchengzu","Liantong");

		CCSprite* logo = HSCCSprite::create("Image/LOGO1.png");
		logo->setAnchorPoint(ccp(0.5f,0.5f));
		logo->setPosition(ccp(logo->getContentSize().width/2,logo->getContentSize().height/2));
		liantongLogo->addChild(logo);
	}

	//Shop_FlyIn(*m_p_shop_frame,m_shop_frame_Position);

	this->schedule(schedule_selector(HSGameShopLayer::Updata));
}

void HSGameShopLayer::Call_Back(CCObject* obj)
{
    HS_GO_SCENE(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID());
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

void HSGameShopLayer::Updata(float dt)
{
	
}

void HSGameShopLayer::Shop_FlyIn( CCNode& shop_frame,CCPoint&frame_Position)
{
//	if(!m_shop_flyIn)
//	{
//		shop_frame.setPosition(ccp(frame_Position.x,-frame_Position.y));
//
//		CCActionInterval* actionFlyIn =CCMoveTo::create(0.3f,frame_Position);
//		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGameShopLayer::Shop_FlyInFinish));
//		shop_frame.runAction(CCSequence::create(actionFlyIn,pCallFunc,NULL));
//
//		m_shop_flyIn = true;
//	}

}

void HSGameShopLayer::Shop_FlyOut( CCNode& shop_frame,CCPoint& frame_Position )
{
//	if(&shop_frame)
//	{
//		CCActionInterval* actionFlyOut =CCMoveTo::create(0.3f,ccp(frame_Position.x,-frame_Position.y));
//		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGameShopLayer::Shop_FlyOutFinish));
//		shop_frame.runAction(CCSequence::create(actionFlyOut,pCallFunc,NULL));
//	}
}

void HSGameShopLayer::Shop_FlyInFinish()
{

	//this->m_shop_flyIn = false;
}

void HSGameShopLayer::Shop_FlyOutFinish()
{
	HS_GO_SCENE(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID());
}









HSGameShopScene::HSGameShopScene()
{
	shopLayer = NULL;
}

HSGameShopScene::~HSGameShopScene()
{
	shopLayer = NULL;
}

bool HSGameShopScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->shopLayer = HSGameShopLayer::create();
	this->addChild(this->shopLayer,HS_BASE_TAG,HS_BASE_TAG);
	return true;
}







