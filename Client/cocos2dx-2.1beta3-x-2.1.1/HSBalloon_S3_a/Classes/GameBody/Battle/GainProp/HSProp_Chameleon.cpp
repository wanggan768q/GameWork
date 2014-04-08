#include "HSProp_Chameleon.h"
#include "HSBattleScene.h"

HSProp_Chameleon::HSProp_Chameleon(void)
{

}

HSProp_Chameleon::~HSProp_Chameleon(void)
{
}

bool HSProp_Chameleon::InitProp( const PropInfo* pPropInfo )
{
	pPropInfo = pPropInfo;

	std::string fileName = GetBasePath() + pPropInfo->localname();

	CCSprite* pNode_0 = CCSprite::create(fileName.c_str());
	HSGraySprite* pNode_1 = HSGraySprite::create(fileName.c_str());
	pNode_1->setScale(1.02f);

	CCMenuItemSprite* pItem = CCMenuItemSprite::create(pNode_0,pNode_1,this,menu_selector(HSProp_Chameleon::Call));

	CCMenu* pMenu = CCMenu::create(pItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}

void HSProp_Chameleon::Call( CCObject* pObj )
{
	HSPropIconInterface::Call(pObj);
	HS_GET_BattleLayer()->AddUserProp(this->GetPropInfoData());
	HS_GET_BattleLayer()->PlayUserPropEffect(this);
	this->Buy();
	this->AddCD(pObj);

	HS_Play_Sound("porp2_effect");
}

void HSProp_Chameleon::Updata( float dt )
{
	
}
