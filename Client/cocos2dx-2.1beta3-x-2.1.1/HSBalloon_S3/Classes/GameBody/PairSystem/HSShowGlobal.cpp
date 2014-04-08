#include "HSShowGlobal.h"
#include "HSGameSceneJumpManage.h"

HSShowGlobal::HSShowGlobal(void)
{
    m_curMoney = 0;
}

HSShowGlobal::~HSShowGlobal(void)
{
}

HSShowGlobal* HSShowGlobal::create()
{
    HSShowGlobal* p = new HSShowGlobal;
    if (p && p->init())
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

bool HSShowGlobal::init()
{
    HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_Tongyongjinbilan","Jinqiandituhei");
    HSAssert(gameGoldFrame, "左上角 金币框 元件名 不一致");
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
    
    CCTexture2D* temp = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
    m_pGameGold = CCLabelAtlas::create("0","Image/moneyNumber.png",temp->getPixelsWide() / 11.f,temp->getPixelsHigh(),'0');
	m_pGameGold->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pGameGold->setPosition(gameGoldFrame->getAnchorPointInPoints());
	gameGoldFrame->addChild(m_pGameGold);
    
    //购买金币
    HS_SET_MENU_TARGET("UI_Tongyongjinbilan_Jinbizengjiaanniu", this, HSShowGlobal::Call_BuyGold);
    
    this->schedule(schedule_selector(HSShowGlobal::Updata));
    
	return true;
}

void HSShowGlobal::Call_BuyGold(CCObject* obj)
{
    CCLog("商城");
    HS_Play_Sound("UI_button");
    HS_GO_SCENE(HS_SCENE_ShopScene);
}

void HSShowGlobal::Updata(float dt)
{
    if (m_curMoney != HS_GAME_CACHE()->GetGold())
	{
		m_curMoney = HS_GAME_CACHE()->GetGold();
        CCString* pStr = CCString::createWithFormat("%d",m_curMoney);
		m_pGameGold->setString(pStr->getCString());
        CC_SAFE_RELEASE_NULL(pStr);
	}

}
