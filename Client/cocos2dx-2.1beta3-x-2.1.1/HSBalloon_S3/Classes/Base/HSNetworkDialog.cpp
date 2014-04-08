//
//  HSNetworkDialog.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 14-1-6.
//
//

#include "HSNetworkDialog.h"
#include "HSGameSceneJumpManage.h"

static HSNetworkDialog* s_HSNetworkDialog = NULL;

HSNetworkDialog::HSNetworkDialog(void)
{
}


HSNetworkDialog::~HSNetworkDialog(void)
{
}

HSNetworkDialog* HSNetworkDialog::ShareNetworkDialog()
{
    if (!s_HSNetworkDialog)
    {
        s_HSNetworkDialog = HSNetworkDialog::create();
        s_HSNetworkDialog->retain();
    }
    
    return s_HSNetworkDialog;
}

void HSNetworkDialog::Show()
{
    CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
#define HS_NetworkDialog_Tag 0x75699
    if(pScene && !pScene->getActionByTag(HS_NetworkDialog_Tag))
    {
        pScene->addChild(this,HS_NetworkDialog_Tag);
    }
}

bool HSNetworkDialog::InitBackground()
{
    HSTool::SetLayerScale(this);
    
    CCLayerColor* pMaskLayer = CCLayerColor::create(ccc4(0, 0, 0, 200),
                                                    HSBase::GetTemplateScreenW() + 10.f, HSBase::GetTemplateScreenH());
	pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
	this->addChild(pMaskLayer);
    pMaskLayer->setPosition(ccp(-2.f,0));
    HSToolBase::SetNodeFilldScreen(pMaskLayer);
    
	this->initWithColor(ccc4(0, 0, 0, 0),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
    
	return true;
}

bool HSNetworkDialog::InitDialog()
{
    
    
    CCSprite* pBack = HSCCSprite::create("Image/Duankaiwangluolianjie.png");
    pBack->setPosition(ccp(320,577));
    this->addChild(pBack);
    
    {
        CCSprite* pItem_01 = HSCCSprite::create("Image/Chongxindenglu_01.png");
        CCSprite* pItem_02 = HSCCSprite::create("Image/Chongxindenglu_02.png");
        CCMenuItemSprite* pItem = CCMenuItemSprite::create(pItem_01, pItem_02, this, menu_selector(HSNetworkDialog::Call_Sure));
        pItem->setPosition(ccp(192,355));
        
        PushMenu(pItem);
    }
    
    {
        CCSprite* pItem_01 = HSCCSprite::create("Image/Jixudengdai_01.png");
        CCSprite* pItem_02 = HSCCSprite::create("Image/Jixudengdai_02.png");
        CCMenuItemSprite* pItem = CCMenuItemSprite::create(pItem_01, pItem_02, this, menu_selector(HSNetworkDialog::Call_Cancel));
        pItem->setPosition(ccp(446,355));
        PushMenu(pItem);
    }
    
	return true;
}

void HSNetworkDialog::Call_Sure(CCObject* pObj)
{
    //CCMenuItemSprite* pItem = (CCMenuItemSprite*)pObj;
    //pItem->setEnabled(false);
    this->removeFromParent();
    HS_GO_SCENE(HS_SCENE_GameMainScene);
}

void HSNetworkDialog::Call_Cancel(CCObject* pObj)
{
    //CCMenuItemSprite* pItem = (CCMenuItemSprite*)pObj;
    //pItem->setEnabled(false);
    this->removeFromParent();
}





