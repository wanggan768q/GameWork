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

	CCSprite* pNode_0 = HSCCSprite::create(fileName.c_str());
	HSGraySprite* pNode_1 = HSGraySprite::create(fileName.c_str());
	pNode_1->setScale(1.02f);

	m_pMenuItem = CCMenuItemSprite::create(pNode_0,pNode_1,this,menu_selector(HSProp_Chameleon::Call));

	CCMenu* pMenu = CCMenu::create(m_pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}

void HSProp_Chameleon::SetIsInvalid(bool is)
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

void HSProp_Chameleon::Call( CCObject* pObj )
{
	if(this->Buy())
    {
        HSPropIconInterface::Call(pObj);
        HS_GET_BattleLayer()->AddUserProp(this->GetPropInfoData());
        HS_GET_BattleLayer()->PlayUserPropEffect(this);
        this->AddCD(pObj);
        HS_Play_Sound("porp2_effect");
        
        //必杀 状态
        HS_GET_BattleLayer()->GetPlayerActionManager()->SetActionSate(PLAYER_ACTION_KILL);
    }
}

void HSProp_Chameleon::Updata( float dt )
{
	
}

















