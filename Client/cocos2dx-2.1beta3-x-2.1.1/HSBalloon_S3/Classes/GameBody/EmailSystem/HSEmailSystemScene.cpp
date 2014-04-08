#include "HSEmailSystemScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSFeedbackLayer.h"

//Layer
HSEmailSystemLayer::HSEmailSystemLayer(void)
{
	m_pEmailListView = NULL;
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
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/EmailSystem.data","Image/",this);

    int emailCount = HS_GAME_CACHE()->m_EmailResponse.emaillist_size();
    if(emailCount != 0)
    {
        CCNode* pZeroEmail = HS_FIND_UI_PANEL("UI_Meiyouyoujian");
        pZeroEmail->setVisible(false);
        
        CCSprite* pEmailSystemFrame = HS_FIND_UI_PANEL_SPRITE("UI_Tongyongfanwei","Xingxianggenghuanfanwei");
        m_pEmailListView = HSEmailListVeiw::create(pEmailSystemFrame->getContentSize(),CCSizeMake(568,96),emailCount);
        CCPoint pos = CCPointZero;
        
        pos.y = pEmailSystemFrame->getPosition().y - pEmailSystemFrame->getContentSize().height / 2.f;
        m_pEmailListView->setPosition(pos);
        pEmailSystemFrame->getParent()->addChild(m_pEmailListView,1000);
        m_pEmailListView->reloadData();
    }
	
    if(emailCount == 0)
    {
        CCMenu* menu = HS_FIND_UI_MENU("UI_Youjianquanbushouqu");
        menu->setVisible(false);
    }

    //返回
	HS_SET_MENU_TARGET("UI_Tongyongguanbi", this, HSEmailSystemLayer::Call_Back);
    //全部领取
	HS_SET_MENU_TARGET("UI_Youjianquanbushouqu",this,HSEmailSystemLayer::Call_AllRevc);

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
	
}

void HSEmailSystemLayer::Call_Back( CCObject* pObj )
{
	HS_GO_SCENE(HS_SCENE_StartGameScene);
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










