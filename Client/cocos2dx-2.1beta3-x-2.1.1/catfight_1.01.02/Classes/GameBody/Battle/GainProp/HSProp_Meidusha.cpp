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

	CCSprite* pNode_0 = HSCCSprite::create(fileName.c_str());
	HSGraySprite* pNode_1 = HSGraySprite::create(fileName.c_str());
	pNode_1->setScale(1.02f);

	m_pMenuItem = CCMenuItemSprite::create(pNode_0,pNode_1,this,menu_selector(HSProp_Meidusha::Call));
	
	CCMenu* pMenu = CCMenu::create(m_pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}

void HSProp_Meidusha::SetIsInvalid(bool is)
{
    if (!m_pMenuItem)
    {
        return;
    }
    if (is)
    {
        HSGraySprite* pTemp = (HSGraySprite*)m_pMenuItem->getSelectedImage();
        HSGraySprite* pSelectNode = HSGraySprite::create(pTemp->GetFileName());
        
        m_pMenuItem->setNormalImage(pSelectNode);
        m_pMenuItem->setEnabled(false);
    }    
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
