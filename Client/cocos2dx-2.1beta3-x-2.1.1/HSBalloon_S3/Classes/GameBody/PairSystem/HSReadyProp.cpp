#include "HSReadyProp.h"

HSReadyProp::HSReadyProp(void)
{
}

HSReadyProp::~HSReadyProp(void)
{
}

HSReadyProp* HSReadyProp::create()
{
    HSReadyProp* p = new HSReadyProp;
    if (p && p->init())
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

bool HSReadyProp::init()
{
    //激光枪
    HSReadyPropItem* pProp_00 = HSReadyPropItem::create(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(0),0);
    this->addChild(pProp_00);
    int size = HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist_size();
    
    for (int i=0; i<size; ++i)
    {
        HSReadyPropItem* item = item = HSReadyPropItem::create(HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(i),i + 1);
        
        this->addChild(item);
    }
    
	return true;
}
