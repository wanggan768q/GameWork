#include "HSChangeFigureScene.h"
#include "HSGameSceneJumpManage.h"

//Layer
HSChangeFigureLayer::HSChangeFigureLayer(void)
{
    m_pListView = NULL;
    m_pLoding = NULL;
    m_pBack = NULL;
}

HSChangeFigureLayer::~HSChangeFigureLayer(void)
{
}

bool HSChangeFigureLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
    Load();
	//this->setTouchEnabled(true);
    
	//this->setIsKeypadEnabled(true);
    
	return true;
}

void HSChangeFigureLayer::Load()
{
	CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/ChangeFigure.data","Image/",this);
    
    //目标面板loding
    m_pLoding = HS_FIND_UI_PANEL("UI_Loading");
    CCNode* pLoding = HS_FIND_UI_PANEL_SPRITE("UI_Loading", "Loading");
    CCRotateBy* pRota = CCRotateBy::create(4, 360);
    pLoding->runAction(CCRepeatForever::create(pRota));
    m_pLoding->setVisible(false);
    
    //显示金币
    this->addChild(HSShowGlobal::create());
    
    //返回
    m_pBack = HS_FIND_UI_MENU("UI_Tongyongguanbi");
	HS_SET_MENU_TARGET("UI_Tongyongguanbi", this, HSChangeFigureLayer::Call_Back);

    this->UpdataFigureListView();
    this->schedule(schedule_selector(HSChangeFigureLayer::Updata));
}

void HSChangeFigureLayer::SetIsShowLoading(bool b)
{
    if(b)
    {
        m_pLoding->setVisible(true);
        m_pBack->setEnabled(false);
        this->setTouchEnabled(true);
    }else{
        m_pLoding->setVisible(false);
        m_pBack->setEnabled(true);
        this->setTouchEnabled(false);
    }
}

void HSChangeFigureLayer::UpdataFigureListView()
{
    CCSprite* pFrame = HS_FIND_UI_PANEL_SPRITE("UI_Tongyongfanwei","Xingxianggenghuanfanwei");
    m_pListView = HSFigureListView::create(pFrame->getContentSize(),CCSizeMake(583,116),HS_GAME_CACHE()->GetFigureList()->size());
    CCPoint pos = CCPointZero;
    
    pos.y = pFrame->getPosition().y - pFrame->getContentSize().height / 2.f;
    m_pListView->setPosition(pos);
    pFrame->getParent()->addChild(m_pListView,1000);
    m_pListView->reloadData();
}

void HSChangeFigureLayer::Call_Back(CCObject* obj)
{
    CCLog("返回");
    HS_GO_SCENE(HS_SCENE_FigureSystemScene);
}

void HSChangeFigureLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -400 , true);
}

bool HSChangeFigureLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSChangeFigureLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSChangeFigureLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSChangeFigureLayer::keyBackClicked()
{
    
}
void HSChangeFigureLayer::keyMenuClicked()
{
    
}

void HSChangeFigureLayer::ResponseGameBuyFigure(GameBuyFigureResponse* pMsg)
{
    if(pMsg->state() == GameBuyFigureResponse_ResultState_SUCCESS)
    {
        HSFigureSprite::SetLastFigureUnlock();
    }else{
        HSMessageBox("解锁形象失败");
    }
    this->SetIsShowLoading(false);
}

void HSChangeFigureLayer::ResponseChangeFigure(ChangeFigureResponse* pMsg)
{
    if(pMsg->state() == ChangeFigureResponse_ChangeState_SUCCESS)
    {
        HSFigureSprite::SetLastFigureChange();
    }else{
        HSMessageBox("更换形象失败");
    }
    this->SetIsShowLoading(false);
}

void HSChangeFigureLayer::Updata(float dt)
{
    
}






















//Scene
HSChangeFigureScene::HSChangeFigureScene(void)
{
	this->m_pHSChangeFigureLayer = NULL;
}

HSChangeFigureScene::~HSChangeFigureScene(void)
{
}

bool HSChangeFigureScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->m_pHSChangeFigureLayer = HSChangeFigureLayer::create();
	this->addChild(this->m_pHSChangeFigureLayer,HS_BASE_TAG,HS_BASE_TAG);
    
	return true;
}


