#include "HSEmailSystemScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSFeedbackLayer.h"

//Layer
HSEmailSystemLayer::HSEmailSystemLayer(void)
{
	m_pEmailListView = NULL;
	m_pMoney = NULL;
    m_iMoney = 0;
}

HSEmailSystemLayer::~HSEmailSystemLayer(void)
{
}

bool HSEmailSystemLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	this->Load();

	//this->setIsTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSEmailSystemLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/EmailSystem.data","Image/",this);

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);


	CCSprite* pEmailSystemFrame = HS_FIND_UI_PANEL_SPRITE("UI_FriendFrame","gerenxinxilanfanwei");
	m_pEmailListView = HSEmailListVeiw::create(pEmailSystemFrame->getContentSize(),CCSizeMake(505,100),HS_GAME_CACHE()->m_EmailResponse.emaillist_size());
	CCPoint pos = CCPointZero;
	pos.x = -pEmailSystemFrame->getContentSize().width / 2.f - 15.f;

	pos.y = pEmailSystemFrame->getPosition().y - pEmailSystemFrame->getContentSize().height / 2.f - 20.f;
	m_pEmailListView->setPosition(pos);
	pEmailSystemFrame->getParent()->addChild(m_pEmailListView,1000);
	m_pEmailListView->reloadData();

	HS_SET_MENU_TARGET("UI_fh_01",this,HSEmailSystemLayer::Call_Back);

	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSEmailSystemLayer::Call_Shop);
    
    if (HS_GAME_CACHE()->m_EmailResponse.emaillist_size() == 0)
    {
        CCMenu* pMenu = HS_FIND_UI_MENU("UI_quanbulingqu");
        pMenu->setVisible(false);
    }else{
        HS_SET_MENU_TARGET("UI_quanbulingqu",this,HSEmailSystemLayer::Call_AllRevc);
    }
    

	this->schedule(schedule_selector(HSEmailSystemLayer::Updata));
}

void HSEmailSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSEmailSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSEmailSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEmailSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEmailSystemLayer::keyBackClicked()
{

}
void HSEmailSystemLayer::keyMenuClicked()
{

}

void HSEmailSystemLayer::Updata( float dt )
{
	if (m_iMoney != HS_GAME_CACHE()->GetGold())
	{
		m_iMoney = HS_GAME_CACHE()->GetGold();
        CCString* temp = CCString::createWithFormat("%d",m_iMoney);
		m_pMoney->setString(temp->getCString());
	}
}

void HSEmailSystemLayer::Call_Shop( CCObject* pobj )
{
//	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
//
//	HSEmailSystemScene* pFriendsSystemScene = (HSEmailSystemScene*)scene;
//
//	if(pFriendsSystemScene->GetHSGameShopLayer()==NULL)
//	{
//		pFriendsSystemScene->SetHSGameShopLayer(HSGameShopLayer::create());
//	}
//	else
//	{
//		pFriendsSystemScene->GetHSGameShopLayer()->setVisible(true);
//	}
	HS_GO_SCENE(HS_SCENE_SHOPSCENE);
}

void HSEmailSystemLayer::Call_Back( CCObject* pObj )
{
	HS_GO_SCENE(HS_SCENE_FriendsSystemScene);
}

void HSEmailSystemLayer::Call_AllRevc(cocos2d::CCObject *pObj)
{
    std::vector<unsigned long long> v;
    for (int i=0; i< HS_GAME_CACHE()->m_EmailResponse.emaillist_size(); ++i)
    {
        v.push_back(HS_GAME_CACHE()->m_EmailResponse.emaillist(i).email_id());
    }
    HSRequest::ShareRequest()->SendOPenEmailRequest(v);
    
    if (0 != strcmp(HS_GAME_CACHE()->GetLoginType(), "99"))
    {
        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        HSFeedbackLayer* pFeedbackLayer = HSFeedbackLayer::create(L("GetAll"));
        pScene->addChild(pFeedbackLayer,1000);
    }
    
}




//Scene
HSEmailSystemScene::HSEmailSystemScene(void)
{
	this->hsEmailSystemLayer = NULL;
	this->hsGameShopLayer = NULL;
}

HSEmailSystemScene::~HSEmailSystemScene(void)
{
}

bool HSEmailSystemScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsEmailSystemLayer = HSEmailSystemLayer::create();
	this->addChild(this->hsEmailSystemLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}










