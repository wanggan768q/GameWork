#include "HSFigureSprite.h"
#include "HSChangeFigureScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSJava.h"

static HSFigureSprite* S_USEING_FIGURE = NULL;
static HSFigureSprite* S_LAST_FIGURE = NULL;

HSFigureSprite::HSFigureSprite(void)
{
    m_pFigure = NULL;
    m_pBuyDescribe = NULL;
    m_pPrice = NULL;
    m_pBuyFescribeFrame = NULL;
}

HSFigureSprite::~HSFigureSprite(void)
{
    S_USEING_FIGURE = NULL;
    S_LAST_FIGURE = NULL;
}

HSFigureSprite* HSFigureSprite::create(int index)
{
	HSFigureSprite* pSprite = new HSFigureSprite;
	if(pSprite && pSprite->Init(index))
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSFigureSprite::Init(int index)
{
    //m_pDefaualSpriteFrame = HS_RP_GetSpriteFrame("Image/Xingxiangkexuanzediban.png");
    //m_pCarrySpriteFrame = HS_RP_GetSpriteFrame("Image/Xingxiangshiyongzhongdiban.png");
    
    initWithSpriteFrame(HS_RP_GetSpriteFrame("Image/Xingxiangkexuanzediban.png"));
    this->setAnchorPoint(HS_ANCHOR_LD);
    
    //解锁按钮
    {
        CCNode* n = HSCCSprite::create("Image/Xingxiangjiesuo_01.png");
        CCNode* n1 = HSCCSprite::create("Image/Xingxiangjiesuo_02.png");
        CCMenuItemSprite* item = CCMenuItemSprite::create(n, n1, this, menu_selector(HSFigureSprite::Call_Unlock));
        item->setPosition(ccp(513,57));
        m_pUnlockMenu = CCMenu::create(item,NULL);
        m_pUnlockMenu->setPosition(CCPointZero);
        this->addChild(m_pUnlockMenu);
    }
    
    //更换按钮
    {
        CCNode* n = HSCCSprite::create("Image/Xingxianggenghuan_01.png");
        CCNode* n1 = HSCCSprite::create("Image/Xingxianggenghuan_02.png");
        m_pChangeMenu = CCMenuItemSprite::create(n, n1, this, menu_selector(HSFigureSprite::Call_Change));
        m_pChangeMenu->setPosition(ccp(513,57));
        CCMenu* menu = CCMenu::create(m_pChangeMenu,NULL);
        menu->setPosition(CCPointZero);
        this->addChild(menu);
    }
    
    //金币图标
    {
        m_pGoldIcon = HSCCSprite::create("Image/Tongyongjinbi.png");
        m_pGoldIcon->setPosition(ccp(549,22));
        this->addChild(m_pGoldIcon);
    }
    
    //使用中
    {
        m_pUse = HSCCSprite::create("Image/Xingxiangshiyongzhong.png");
        m_pUse->setPosition(ccp(513,57));
        this->addChild(m_pUse);
    }
    
    //头像
    {
        m_pFigureFrame = HSGraySprite::create("Image/Kaishigerenxinxibeijing.png");
        m_pFigureFrame->setPosition(ccp(69,54));
        this->addChild(m_pFigureFrame);
        
        m_pLock = HSCCSprite::create("Image/Pipeidaojusuo.png");
        m_pLock->setPosition(ccp( 69,57));
        this->addChild(m_pLock,1000);
    }
    
    //购买文字描述
    {
        m_pBuyFescribeFrame = HSCCSprite::create("Image/Xingxianggenghuanwenbenkuang.png");
        m_pBuyFescribeFrame->setPosition(ccp(292,53));
        this->addChild(m_pBuyFescribeFrame);
    }
    
    return true;
}

void HSFigureSprite::Call_Change(CCObject* obj)
{
    CCLog("更换形象");
    HS_Play_Sound("UI_button");
    
    CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(obj);
    pItem->setEnabled(false);
    
    S_LAST_FIGURE = this;
    
    if(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID() == HS_SCENE_BattleScene)
    {
        HSRequest::ShareRequest()->SendChangeFigureRequest(m_pData->id());
    }else{
        HSRequest::ShareRequest()->SendUserInfoUpdateRequest_Figure(m_pData->id());
        HSRequest::ShareRequest()->SendSearchUserInfoRequest();
    }
    //HS_MUTABLE_TARGET_SELF()->set_figureid(m_pData->id());
    
//    if(S_USEING_FIGURE)
//    {
//        S_USEING_FIGURE->SetUseing(false);
//    }
//    this->SetUseing(true);
    
    CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
    HSChangeFigureScene* pChangeFigureScene = dynamic_cast<HSChangeFigureScene*>(pScene);
    if(pChangeFigureScene)
    {
        pChangeFigureScene->GetHSChangeFigureLayer()->SetIsShowLoading(true);
    }
    
}

void HSFigureSprite::Call_Unlock(CCObject* obj)
{
    CCLog("解锁");
    HS_Play_Sound("UI_button");
    
    if(HS_GAME_CACHE()->GetGold() >= m_pData->price())
    {
        S_LAST_FIGURE = this;
        
        CCMenuItem* item = dynamic_cast<CCMenuItem*>(obj);
        item->setEnabled(false);
        
        if(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID() == HS_SCENE_BattleScene)
        {
            HSRequest::ShareRequest()->SendMatchBuyFigureRequest(m_pData->id());
            HS_GAME_CACHE()->AddGold(-m_pData->price());
        }else{
            HSRequest::ShareRequest()->SendGameBuyFigureRequest(m_pData->id());
            HSRequest::ShareRequest()->SendSearchUserInfoRequest();
        }
        //HS_MUTABLE_TARGET_SELF()->add_buyequipframe(m_pData->id());
        //this->SetUseing(false);
        //this->SetAlreadyBuy(true);
        
        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        HSChangeFigureScene* pChangeFigureScene = dynamic_cast<HSChangeFigureScene*>(pScene);
        if(pChangeFigureScene)
        {
            pChangeFigureScene->GetHSChangeFigureLayer()->SetIsShowLoading(true);
        }
    }else{
        HSJava::ShaderJava()->Pay(m_pData->price());
    }
}

void HSFigureSprite::SetLastFigureUnlock()
{
    if(S_LAST_FIGURE)
    {
        S_LAST_FIGURE->SetUseing(false);
        S_LAST_FIGURE->SetAlreadyBuy(true);
    }
    S_LAST_FIGURE = NULL;
}

void HSFigureSprite::SetLastFigureChange()
{
    if(S_LAST_FIGURE)
    {
        if(S_USEING_FIGURE)
        {
            S_USEING_FIGURE->SetUseing(false);
        }
        S_LAST_FIGURE->SetUseing(true);
    }
    S_LAST_FIGURE = NULL;
}

void HSFigureSprite::UpdataHSFigureSprite(int index,FigureData_FigureBase* base)
{
    m_pData = base;
    
    //形象
    {
        CCString* fileName = CCString::createWithFormat("Image/%d_FIGURE.png",m_pData->id());
        if(!m_pFigure)
        {
            m_pFigure = HSGraySprite::create(fileName->getCString());
            m_pFigure->setPosition(ccp(66,64));
            this->addChild(m_pFigure);
            
        }else{
            m_pFigure->setDisplayFrame(HS_RP_GetSpriteFrame(fileName->getCString()));
        }
        CC_SAFE_RELEASE_NULL(fileName);
    }
    
    //购买描述
    {
        if(!m_pBuyDescribe)
        {
            m_pBuyDescribe = CCLabelTTF::create(m_pData->buydescribe().c_str(), HS_FONT_HuaKang, 16, m_pBuyFescribeFrame->getContentSize(), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
            m_pBuyDescribe->setPosition(m_pBuyFescribeFrame->getAnchorPointInPoints());
            //m_pBuyDescribe->setColor(ccBLACK);
            m_pBuyFescribeFrame->addChild(m_pBuyDescribe);
        }else{
            m_pBuyDescribe->setString(m_pData->buydescribe().c_str());
        }
    }
    
    //价格
    {
        CCString* price = CCString::createWithFormat("%d",m_pData->price());
        if(!m_pPrice)
        {
            
            m_pBuyDescribe = CCLabelTTF::create(price->getCString(), HS_FONT_HuaKang, 25, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
            m_pBuyDescribe->setPosition(ccp(503,22));
            this->addChild(m_pBuyDescribe);
            
        }else{
            m_pBuyDescribe->setString(price->getCString());
        }
        CC_SAFE_RELEASE_NULL(price);
    }
    
    bool isAlreadyBuy = false;
    bool isUse = (HS_TARGET_SELF().figureid() == m_pData->id());
    for(int i=0;i<HS_TARGET_SELF().figures_size();++i)
    {
        if(HS_TARGET_SELF().figures(i).id() == m_pData->id())
        {
            isAlreadyBuy = true;
            break;
        }
    }
    
    //是否使用中
    SetUseing(isUse);
    
    //已经购买
    SetAlreadyBuy(isAlreadyBuy);
}

void HSFigureSprite::SetUseing(bool isUse)
{
    //是否使用中
    if(isUse)
    {
        m_pUse->setVisible(true);
        m_pChangeMenu->setVisible(false);
        this->setDisplayFrame(HS_RP_GetSpriteFrame("Image/Xingxiangshiyongzhongdiban.png"));
        S_USEING_FIGURE = this;
    }else{
        m_pUse->setVisible(false);
        m_pChangeMenu->setVisible(true);
        m_pChangeMenu->setEnabled(true);

        this->setDisplayFrame(HS_RP_GetSpriteFrame("Image/Xingxiangkexuanzediban.png"));
    }
    
}

void HSFigureSprite::SetAlreadyBuy(bool isAlreadyBuy)
{
    //已经购买
    if(isAlreadyBuy)
    {
        m_pFigure->RecoverProgram();    //彩色
        m_pFigureFrame->RecoverProgram();
        m_pLock->setVisible(false);
        m_pUnlockMenu->setVisible(false);
        m_pGoldIcon->setVisible(false);
        m_pBuyDescribe->setVisible(false);
    }else{
        m_pLock->setVisible(true);
        m_pUnlockMenu->setVisible(true);
        m_pGoldIcon->setVisible(true);
        m_pBuyDescribe->setVisible(true);
        m_pChangeMenu->setVisible(false);
        //m_pUse->setVisible(false);
    }
}







