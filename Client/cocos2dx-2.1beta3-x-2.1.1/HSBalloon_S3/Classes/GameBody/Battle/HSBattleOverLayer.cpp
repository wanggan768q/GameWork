#include "HSBattleOverLayer.h"
#include "HSGameSceneJumpManage.h"

int HSBattleOverLayer::S_TARGET_FINGURE_ID = 7000;

HSBattleOverLayer::HSBattleOverLayer(void)
{
    m_pName = NULL;
    m_pSelfFigure = NULL;
    m_pTargetFigure = NULL;
    m_pLianSheng = NULL;
    m_pJinbi = NULL;
    m_pZhanJi = NULL;
	m_iswin = false;
}

HSBattleOverLayer::~HSBattleOverLayer(void)
{
	HS_GAME_CACHE()->m_isInOverLayer = false;
}

bool HSBattleOverLayer::init()
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

void HSBattleOverLayer::Load()
{
	CCLayerColor* pLayerColor = CCLayerColor::create(ccc4(0,0,0,200),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	HSTool::SetNodeFilldScreen(pLayerColor);
	this->addChild(pLayerColor);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/battleOver.data","Image/",this);
    
    //再来一句
    HS_SET_MENU_TARGET("UI_Zailaiyiju", this, HSBattleOverLayer::Call_Back);
    
}

void HSBattleOverLayer::SetTargetFingureID(int id)
{
    S_TARGET_FINGURE_ID = id;
}

void HSBattleOverLayer::Call_Back(CCObject* obj)
{
    CCLog("返回");
    HS_Play_Sound("UI_button");
    HS_GO_SCENE(HS_SCENE_FigureSystemScene);
}

void HSBattleOverLayer::Return()
{
    Call_Back(NULL);
}

void HSBattleOverLayer::Updata(float dt)
{
	
}

void HSBattleOverLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSBattleOverLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSBattleOverLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleOverLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleOverLayer::keyBackClicked()
{

}
void HSBattleOverLayer::keyMenuClicked()
{

}

void HSBattleOverLayer::SetIsWin(bool win)
{
    if(m_iswin)
    {
        return;
    }
    HS_Play_Sound("coin_effect");
    
    m_iswin = true;
    //星星动画
    {
        CCNode* p1 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_0","Zhanjixingxing_0");
        CCNode* p2 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_1","Zhanjixingxing_4");
        CCNode* p3 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_2","Zhanjixingxing_1");
        CCNode* p4 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_3","Zhanjixingxing_2");
        CCNode* p5 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_4","Zhanjixingxing_3");
        CCNode* p6 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_5","Zhanjixingxing_3");
        CCNode* p7 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_6","Zhanjixingxing_2");
        CCNode* p8 = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Xingxingtexiao_Xingxing_7","Zhanjixingxing_2");
        
        vector<CCNode*> v;
        v.push_back(p1);
        v.push_back(p2);
        v.push_back(p3);
        v.push_back(p4);
        v.push_back(p5);
        v.push_back(p6);
        v.push_back(p7);
        v.push_back(p8);
        
        for_each(v.begin(), v.end(), [](CCNode* p)
        {
            p->stopAllActions();
            p->setScale(0.7);
            CCDelayTime* a1 = CCDelayTime::create(HSMath::Random(0.f, 1.f));
            CCScaleTo* a2 = CCScaleTo::create(0.1, 1.5);
            CCScaleTo* a3 = CCScaleTo::create(1, 0.7);
            CCDelayTime* a4 = CCDelayTime::create(HSMath::Random(0.5f, 1.5f));
            CCSequence* a5 =CCSequence::create(a1,a2,a3,a4,NULL);
            CCRepeatForever* a6 = CCRepeatForever::create(a5);
            p->runAction(a6);
            
        });
        
    }
    
    //胜利 or 失败
    {
        CCNode* pWin = HS_FIND_UI_PANEL("UI_Benfangshengli");
        CCNode* pLose = HS_FIND_UI_PANEL("UI_Benfangshibai");
        CCNode* pSun = HS_FIND_UI_PANEL_SPRITE("UI_Benfangshengli", "Zhanjifaguangxiaoguo");
        pWin->setVisible(false);
        pLose->setVisible(false);
        if(win)
        {
            pWin->setVisible(true);
            CCRotateBy* rotate = CCRotateBy::create(24, 360);
            CCRepeatForever* forever = CCRepeatForever::create(rotate);
            pSun->runAction(forever);
            
            HS_Play_Sound("win_effect");
            
        }else{
            pLose->setVisible(true);
            HS_Play_Sound("lose_effect");
        }
    }
    
	//姓名 40
    {
        CCNode* pNode = HS_FIND_UI_PANEL("UI_Zhanjijiemian_Benfangxingming");
        if(!m_pName)
        {
            m_pName = CCLabelTTF::create(HS_TARGET_SELF().name().c_str(), HS_FONT_HuaKang, 40, CCSizeZero, kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
            m_pName->setPosition(pNode->getPosition());
            pNode->getParent()->addChild(m_pName,1100);
            m_pName->setColor(ccBLACK);
        }else{
            m_pName->setString(HS_TARGET_SELF().name().c_str());
        }
        
    }
    
    //本方形象
    {
        CCNode* pNode = HS_FIND_UI_PANEL("UI_Benfangxingxiang");
        if(!m_pSelfFigure)
        {
            CCString* fileName = NULL;
            if(win)
            {
                fileName = CCString::createWithFormat("Image/%d_WIN.png",HS_TARGET_SELF().figureid());
            }else{
                fileName = CCString::createWithFormat("Image/%d_LOSE.png",HS_TARGET_SELF().figureid());
            }
            m_pSelfFigure = HSCCSprite::create(fileName->getCString());
            m_pSelfFigure->setPosition(pNode->getPosition());
            pNode->getParent()->addChild(m_pSelfFigure,1100);
            CC_SAFE_RELEASE_NULL(fileName);
        }
    }
    
    //对方形象
    {
        //UI_Zhanjijiemian_Duifangxingxiang 位置   缩放50%
        CCNode* pNode = HS_FIND_UI_PANEL("UI_Zhanjijiemian_Duifangxingxiang");
        if(!m_pTargetFigure)
        {
            CCString* fileName = NULL;
            if(win)
            {
                fileName = CCString::createWithFormat("Image/%d_LOSE.png",S_TARGET_FINGURE_ID);
                
            }else{
                fileName = CCString::createWithFormat("Image/%d_WIN.png",S_TARGET_FINGURE_ID);
            }
            m_pTargetFigure = HSCCSprite::create(fileName->getCString());
            m_pTargetFigure->setScale(0.5);
            m_pTargetFigure->setPosition(pNode->getPosition());
            pNode->getParent()->addChild(m_pTargetFigure,1100);
            CC_SAFE_RELEASE_NULL(fileName);
        }
    }
    
    //连胜
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Zhanjiliansheng", "Zhanjiwenbenkuang");
        CCString* pStr = CCString::createWithFormat("%d 场",HS_TARGET_SELF().successionwincount());
        if(!m_pLianSheng)
        {
            m_pLianSheng = CCLabelTTF::create(pStr->getCString(), HS_FONT_HuaKang, 28, pNode->getContentSize(), kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);
            m_pLianSheng->setPosition(pNode->getAnchorPointInPoints());
            pNode->addChild(m_pLianSheng);
            m_pLianSheng->setColor(ccBLACK);
        }else{
            m_pLianSheng->setString(pStr->getCString());
        }
        CC_SAFE_RELEASE_NULL(pStr);
    }
    
    //战绩
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Zhanjizhanji", "Zhanjiwenbenkuang");
        CCString* pStr = CCString::createWithFormat("%d 胜 %d 负",HS_TARGET_SELF().wincount(),HS_TARGET_SELF().losecount());
        if(!m_pZhanJi)
        {
            m_pZhanJi = CCLabelTTF::create(pStr->getCString(), HS_FONT_HuaKang, 28, pNode->getContentSize(), kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);
            m_pZhanJi->setPosition(pNode->getAnchorPointInPoints());
            pNode->addChild(m_pZhanJi);
            m_pZhanJi->setColor(ccBLACK);
        }else{
            m_pZhanJi->setString(pStr->getCString());
        }
        CC_SAFE_RELEASE_NULL(pStr);
    }
    
    //金币
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Zhanjijiemian_Zhanjijinbi", "Zhanjiwenbenkuang");
        CCString* pStr = CCString::createWithFormat("%d",HS_GAME_CACHE()->m_pBattleResult->selfinfo().incomgolds());
        if(!m_pJinbi)
        {
            m_pJinbi = CCLabelTTF::create(pStr->getCString(), HS_FONT_HuaKang, 28, pNode->getContentSize(), kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);
            m_pJinbi->setPosition(pNode->getAnchorPointInPoints());
            pNode->addChild(m_pJinbi);
            m_pJinbi->setColor(ccBLACK);
        }else{
            m_pJinbi->setString(pStr->getCString());
        }
        CC_SAFE_RELEASE_NULL(pStr);
    }   
}
















