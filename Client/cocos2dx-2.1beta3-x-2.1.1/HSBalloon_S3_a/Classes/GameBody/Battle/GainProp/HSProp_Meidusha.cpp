#include "HSProp_Meidusha.h"
#include "HSBattleScene.h"

HSProp_Meidusha::HSProp_Meidusha(void)
{
}


HSProp_Meidusha::~HSProp_Meidusha(void)
{
}

bool HSProp_Meidusha::InitProp( const PropInfo* pPropInfo )
{
	std::string fileName = GetBasePath() + pPropInfo->localname();

	CCSprite* pNode_0 = CCSprite::create(fileName.c_str());
	HSGraySprite* pNode_1 = HSGraySprite::create(fileName.c_str());
	pNode_1->setScale(1.02f);

	CCMenuItemSprite* pItem = CCMenuItemSprite::create(pNode_0,pNode_1,this,menu_selector(HSProp_Meidusha::Call));
	
	CCMenu* pMenu = CCMenu::create(pItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}

void HSProp_Meidusha::Call( CCObject* pObj )
{
	HSPropIconInterface::Call(pObj);
	HS_GET_BattleLayer()->AddUserProp(this->GetPropInfoData());
	HS_GET_BattleLayer()->PlayUserPropEffect(this);
	this->Buy();
	this->AddCD(pObj);

	HS_Play_Sound("porp3_effect");
}

void HSProp_Meidusha::Updata( float dt )
{
	
}
