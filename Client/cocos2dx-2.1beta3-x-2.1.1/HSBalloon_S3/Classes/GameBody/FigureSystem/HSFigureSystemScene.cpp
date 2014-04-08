#include "HSFigureSystemScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameCache.h"
#include "HSPairSystemScene.h"

//Layer
HSFigureSystemLayer::HSFigureSystemLayer(void)
{
    m_pFigureIcon = NULL;
    m_pFigure = NULL;
    m_pFigureName = NULL;
    m_pFigureLevel = NULL;
    m_pFigureDescribe = NULL;
    m_pUpgradeGold = NULL;
    m_pSpx = NULL;
    m_userBaseInfo = HS_TARGET_SELF();
    m_pLoding = NULL;
}

HSFigureSystemLayer::~HSFigureSystemLayer(void)
{
}

bool HSFigureSystemLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
    Load();
	//this->setIsTouchEnabled(true);
    
	//this->setIsKeypadEnabled(true);
    
	return true;
}

void HSFigureSystemLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/FigureSystem.data","Image/",this);
    
    //目标面板loding
    m_pLoding = HS_FIND_UI_PANEL("UI_Loading");
    CCNode* pLoding = HS_FIND_UI_PANEL_SPRITE("UI_Loading", "Loading");
    CCRotateBy* pRota = CCRotateBy::create(4, 360);
    pLoding->runAction(CCRepeatForever::create(pRota));
    m_pLoding->setVisible(false);
    
    //显示金币
    this->addChild(HSShowGlobal::create());
    
    //返回
    HS_SET_MENU_TARGET("UI_Tongyongfanhui", this, HSFigureSystemLayer::Call_Back);
    //开始战斗
    HS_SET_MENU_TARGET("UI_Tongyongkaishizhandou", this, HSFigureSystemLayer::Call_StartBattle);
    //升级
    HS_SET_MENU_TARGET("UI_Gerenxinxiban_Xingxiangshengji", this, HSFigureSystemLayer::Call_Upgrade);
    //更换形象
    HS_SET_MENU_TARGET("UI_Gerenxinxiban_Genghuanxingxiang", this, HSFigureSystemLayer::Call_ChangeFigure);
    
    CCNode* pSpxPos = HS_FIND_UI_PANEL("UI_Gerenxinxiban_Shengjidonghuazuobiao");
    m_pSpx = SPX_Manager::CreateSprite("SPX/shengjixiaoguo.sprite");
    m_pSpx->SetAction(0,1);
    m_pSpx->setPosition(pSpxPos->getPosition());
    m_pSpx->setVisible(false);
    pSpxPos->getParent()->addChild(m_pSpx,1200);

    
    this->UpdataPlayerInfo();
    
    this->schedule(schedule_selector(HSFigureSystemLayer::Updata));
}

void HSFigureSystemLayer::UpdataPlayerInfo()
{
    FigureData_FigureBase* base = HS_GAME_CACHE()->GetFigureBase(HS_TARGET_SELF().figureid());
    
    //小头像
    if(!m_pFigureIcon)
    {
        if(HS_TARGET_SELF().uid().size() > 30)
        {
            CCNode* p =  HS_FIND_UI_PANEL("UI_Gerenxinxiban_Xingxiangxiaotu");
            CCString* pFileName = CCString::createWithFormat("Image/%d_FIGURE.png",HS_TARGET_SELF().figureid());
            if(!m_pFigureIcon)
            {
                m_pFigureIcon = HSCCSprite::create(pFileName->getCString());
                m_pFigureIcon->setPosition(p->getPosition());
                p->getParent()->addChild(m_pFigureIcon,1100);
            }else{
                m_pFigureIcon->setDisplayFrame(HS_RP_GetSpriteFrame(pFileName->getCString()));
            }
            CC_SAFE_RELEASE_NULL(pFileName);
        }
    }
    
    //大形象
    {
        CCNode* p = HS_FIND_UI_PANEL("UI_Gerenxinxiban_Gerenxingxiang");
        CCString* str = CCString::createWithFormat("Image/%d_BODY.png",HS_TARGET_SELF().figureid());
        if(!m_pFigure)
        {
            m_pFigure = HSCCSprite::create(str->getCString());
            m_pFigure->setPosition(p->getPosition());
            p->getParent()->addChild(m_pFigure,1100);
        }else{
            m_pFigure->setDisplayFrame(HS_RP_GetSpriteFrame(str->getCString()));
        }
        
        CC_SAFE_RELEASE_NULL(str);
    }
    
    //等级
    {
        CCNode* p = HS_FIND_UI_PANEL("UI_Gerenxinxiban_Gerendengji");
        CCString* str = CCString::createWithFormat("Lv.%d",HS_TARGET_SELF().figurelevel());
        if(!m_pFigureLevel)
        {
            m_pFigureLevel = CCLabelTTF::create(str->getCString(), HS_FONT_HuaKang, 36);
            m_pFigureLevel->setPosition(p->getPosition());
            p->getParent()->addChild(m_pFigureLevel,1000);
            CC_SAFE_RELEASE_NULL(str);
        }else{
            m_pFigureLevel->setString(str->getCString());
        }
        
    }
    
    //升级金币数
    {
        
        FigureData_FigureLevelTable* table = HS_GAME_CACHE()->GetFigureLevelTable(HS_TARGET_SELF().figureid(), HS_TARGET_SELF().figurelevel());
        if(!table)
        {
            HSMessageBox("figureid: %d  figurelevel: %d",HS_TARGET_SELF().figureid(),HS_TARGET_SELF().figurelevel());
            HSAssert(0, "");
        }
        CCNode* p = HS_FIND_UI_PANEL("UI_Gerenxinxiban_Shengjijinbishu");
        CCString* str = NULL;
        if( table->nextlevelgold() == 0)
        {
            str = CCString::createWithFormat("MAX");
        }else{
            str = CCString::createWithFormat("%d",table->nextlevelgold());
        }
        if(!m_pUpgradeGold)
        {
            m_pUpgradeGold = CCLabelTTF::create(str->getCString(), HS_FONT_HuaKang, 24,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
            m_pUpgradeGold->setPosition(p->getPosition());
            m_pUpgradeGold->setColor(ccBLACK);
            p->getParent()->addChild(m_pUpgradeGold,1110);
        }else{
            m_pUpgradeGold->setString(str->getCString());
        }
        CC_SAFE_RELEASE_NULL(str);
    }
    
    //形象的名称
    {
        CCNode* p = HS_FIND_UI_PANEL("UI_Gerenxinxiban_Xingxiangmingcheng");
        if(!m_pFigureName)
        {
            m_pFigureName = CCLabelTTF::create(base->name().c_str(),HS_FONT_HuaKang,48,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
            m_pFigureName->setPosition(p->getPosition());
            p->getParent()->addChild(m_pFigureName,1000);
        }else{
            m_pFigureName->setString(base->name().c_str());
        }
        
    }
    //说明
    {
        CCNode* p = HS_FIND_UI_PANEL_SPRITE("UI_Gerenxinxiban_Xingxiangshuoming", "Xingxiangshuomingkuang");
        if(!m_pFigureDescribe)
        {
            m_pFigureDescribe = CCLabelTTF::create(base->describe().c_str(),HS_FONT_HuaKang,20,p->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
            m_pFigureDescribe->setPosition(p->getAnchorPointInPoints());
            p->addChild(m_pFigureDescribe);
        }else{
            m_pFigureDescribe->setString(base->describe().c_str());
        }
    }
    
    
    
    FigureData_FigureLevelTable* table = HS_GAME_CACHE()->GetFigureLevelTable(HS_TARGET_SELF().figureid(), HS_TARGET_SELF().figurelevel());
    //属性0
    {
        int i = 0;
        for(;i<10;++i)
        {
            CCString* str = CCString::createWithFormat("UI_Gerenxinxiban_Shuxing_0_Shuxingzhi_0_Shuxingzhi_%d",i);
            CCNode* p = HS_FIND_UI_PANEL(str->getCString());
            if(p)
            {
                p->setVisible(true);
            }
            CC_SAFE_RELEASE_NULL(str);
        }
        
        for(i = table->property_0();i<10;++i)
        {
            CCString* str = CCString::createWithFormat("UI_Gerenxinxiban_Shuxing_0_Shuxingzhi_0_Shuxingzhi_%d",i);
            CCNode* p = HS_FIND_UI_PANEL(str->getCString());
            if(p)
            {
                p->setVisible(false);
            }
        }
    }
    //属性1
    {
        int i = 0;
        for(;i<10;++i)
        {
            CCString* str = CCString::createWithFormat("UI_Gerenxinxiban_Shuxing_1_Shuxingzhi_1_Shuxingzhi_%d",i);
            CCNode* p = HS_FIND_UI_PANEL(str->getCString());
            if(p)
            {
                p->setVisible(true);
            }
            CC_SAFE_RELEASE_NULL(str);
        }
        
        for(i = table->property_1();i<10;++i)
        {
            CCString* str = CCString::createWithFormat("UI_Gerenxinxiban_Shuxing_1_Shuxingzhi_1_Shuxingzhi_%d",i);
            CCNode* p = HS_FIND_UI_PANEL(str->getCString());
            if(p)
            {
                p->setVisible(false);
            }
        }
    }
    //属性2
    {
        int i = 0;
        for(;i<10;++i)
        {
            CCString* str = CCString::createWithFormat("UI_Gerenxinxiban_Shuxing_2_Shuxingzhi_2_Shuxingzhi_%d",i);
            CCNode* p = HS_FIND_UI_PANEL(str->getCString());
            if(p)
            {
                p->setVisible(true);
            }
            CC_SAFE_RELEASE_NULL(str);
        }
        
        for(i = table->property_2();i<10;++i)
        {
            CCString* str = CCString::createWithFormat("UI_Gerenxinxiban_Shuxing_2_Shuxingzhi_2_Shuxingzhi_%d",i);
            CCNode* p = HS_FIND_UI_PANEL(str->getCString());
            if(p)
            {
                p->setVisible(false);
            }
        }
    }
}

void HSFigureSystemLayer::Call_Back(CCObject* obj)
{
    CCLog("返回");
    HS_Play_Sound("UI_button");
    
    HSSocket* pSocket = HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle);
    if(pSocket)
    {
        pSocket->Closed(Close_Active);
        HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
    }
   
    
    HSPairSystemLayer::S_IS_CREATE_BATTLE_SERVER = false;
    HS_GO_SCENE(HS_SCENE_StartGameScene);
}

void HSFigureSystemLayer::Call_StartBattle(CCObject* obj)
{
    CCLog("开始战斗");
    HS_Play_Sound("UI_button");
    
    CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(obj);
    pItem->setEnabled(false);
    
    HSRequest::ShareRequest()->SendValidateStrengthRequest();
}

void HSFigureSystemLayer::Call_Upgrade(CCObject* obj)
{
    CCLog("升级");
    HS_Play_Sound("UI_button");
    FigureData_FigureLevelTable* t  = HS_GAME_CACHE()->GetFigureLevelTable(HS_TARGET_SELF().figureid(), HS_TARGET_SELF().figurelevel());
    if(t->nextlevelgold() == 0 )
    {
        HSMessageBox("已经满级");
    }else if(t->nextlevelgold() <= HS_GAME_CACHE()->GetGold()){
        
        CCLog("Msg: 允许购买 ");
        if(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID() == HS_SCENE_BattleScene)
        {
            HSRequest::ShareRequest()->SendMatchUpgradeFigureLevelRequest();
            HS_GAME_CACHE()->AddGold(-t->nextlevelgold());
        }else{
            HSRequest::ShareRequest()->SendGameUpgradeFigureLevelRequest();
            HSRequest::ShareRequest()->SendSearchUserInfoRequest();
        }
        
        this->SetIsShowLoading(true);
    }else{
        HSMessageBox("金币不够 需要%d-%d",t->nextlevelgold(),HS_GAME_CACHE()->GetGold());
    }
}

void HSFigureSystemLayer::Call_ChangeFigure(CCObject* obj)
{
    CCLog("更换形象");
    HS_Play_Sound("UI_button");
    HS_GO_SCENE(HS_SCENE_ChangeFigureScene);
}

void HSFigureSystemLayer::SetIsShowLoading(bool b)
{
    if(!m_pLoding)
        return;
    
    if(b)
    {
        m_pLoding->setVisible(true);
        this->setTouchEnabled(true);
    }else{
        m_pLoding->setVisible(false);
        this->setTouchEnabled(false);
    }
}

void HSFigureSystemLayer::ResponseGameUpgradeFigureLevel(GameUpgradeFigureLevelResponse* pMsg)
{
    if(pMsg->status() == GameUpgradeFigureLevelResponse_Status_SUCCESS)
    {
        CCLog("形象升级成功");
        
        int level = HS_TARGET_SELF().figurelevel();
        HS_MUTABLE_TARGET_SELF()->set_figurelevel(++level);

        
        if(m_pSpx)
        {
            m_pSpx->setVisible(true);
            m_pSpx->SetAction(0, 1);
        }
    }else{
        HSMessageBox("升级失败");
    }
    this->SetIsShowLoading(false);
}

void HSFigureSystemLayer::ResponseValidateStrength(ValidateStrengthResponse* pMsg)
{
    switch (pMsg->result()) {
        case message::ValidateStrengthResponse_RESULT_TYPE_OK:
        {
            HS_GO_SCENE(HS_SCENE_PairSystemScene);
            
        }
            break;
        case message::ValidateStrengthResponse_RESULT_TYPE_NOT:
        {
            CCLog("体力不够");
            
            HSSocket* s = HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle);
            if(s)
            {
                s->Closed(Close_Active);
                HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
            }
            
            HS_GO_SCENE(HS_SCENE_StartGameScene);
        }
            break;
        default:
            break;
    }
}

void HSFigureSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -300 , true);
}

bool HSFigureSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSFigureSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSFigureSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSFigureSystemLayer::keyBackClicked()
{
    
}
void HSFigureSystemLayer::keyMenuClicked()
{
    
}

void HSFigureSystemLayer::Updata(float dt)
{
    if(m_userBaseInfo.figureid() != HS_TARGET_SELF().figureid()
       || m_userBaseInfo.figurelevel() != HS_TARGET_SELF().figurelevel())
    {
        m_userBaseInfo = HS_TARGET_SELF();
        this->UpdataPlayerInfo();
    }
}




//Scene
HSFigureSystemScene::HSFigureSystemScene(void)
{
	this->m_pHSFigureSystemLayer = NULL;
}

HSFigureSystemScene::~HSFigureSystemScene(void)
{
}

bool HSFigureSystemScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->m_pHSFigureSystemLayer = HSFigureSystemLayer::create();
	this->addChild(this->m_pHSFigureSystemLayer,HS_BASE_TAG,HS_BASE_TAG);
    
	return true;
}


