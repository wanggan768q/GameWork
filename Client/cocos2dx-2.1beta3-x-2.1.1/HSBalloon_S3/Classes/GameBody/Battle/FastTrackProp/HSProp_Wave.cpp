#include "HSProp_Wave.h"
#include "HSBattleScene.h"

HSProp_Wave::HSProp_Wave(void)
{
}

HSProp_Wave::~HSProp_Wave(void)
{
}

HSProp_Wave* HSProp_Wave::create()
{
    HSProp_Wave* p = new HSProp_Wave;
    if (p && p->init())
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

bool HSProp_Wave::init()
{
    CCNode* pFrame = GetDialog();
    this->addChild(pFrame);
    
    CCSprite* s1 = HSCCSprite::create("Image/Wave.png");
    CCSprite* s2 = HSCCSprite::create("Image/Wave.png");
    CCMenuItem* item = CCMenuItemSprite::create(s1, s2, this, menu_selector(HSPropFastTrackInterface::Call_Sure) );
    item->setPosition(ccp(259,94));
    CCMenu* menu = CCMenu::create(item,NULL);
    menu->setPosition(CCPointZero);
    pFrame->addChild(menu);
    
    CCRotateTo* a1 = CCRotateTo::create(1, 3);
    CCRotateTo* a2 = CCRotateTo::create(1, -3);
    CCSequence* a3 = CCSequence::create(a1,a2,NULL);
    CCRepeatForever* a4 = CCRepeatForever::create(a3);
    menu->runAction(a4);
    
	return true;
}

void HSProp_Wave::Function()
{    
    HSBattleLayer* pBattleLayer = HS_GET_BattleLayer();
    std::set<HSBalloonSprite*>* pDropList = pBattleLayer->GetDropBalloonList();
    
    for_each(pDropList->begin(), pDropList->end(), [](HSBalloonSprite* s)
    {
        s->Destroy();
    });
}












