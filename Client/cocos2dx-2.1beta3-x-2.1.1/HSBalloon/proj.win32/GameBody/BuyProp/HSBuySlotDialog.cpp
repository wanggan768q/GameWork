#include "HSBuySlotDialog.h"
#include "HSPropItemSprite.h"

HSBuySlotDialog::HSBuySlotDialog(void)
{
	m_pTarget = NULL;
}

HSBuySlotDialog::~HSBuySlotDialog(void)
{


}
HSBuySlotDialog* HSBuySlotDialog::create(CCObject* pTarget)
{
	HSBuySlotDialog* pDialog = new HSBuySlotDialog;
	if (pDialog && pDialog->init(pTarget))
	{
		pDialog->autorelease();
		return pDialog;
	}
	CC_SAFE_DELETE(pDialog);
	return NULL;
}

bool HSBuySlotDialog::init( CCObject* pTarget )
{
	m_pTarget = pTarget;
	if (!HSModalDialogInterface::init())
	{
		return false;
	}
	

	return true;
}

bool HSBuySlotDialog::InitDialog()
{
	if (!m_pTarget)
	{
		return false;
	}
	CCSprite* pDialogBack = CCSprite::create("Image/dialog/ErCiQueRenBeiJingYun.png");// ErCiQueRenBeiJingYun 背景图
	pDialogBack->setPosition(ccp(320,480)); //中心坐标
	this->addChild(pDialogBack);

	CCSprite* pGoldMark = CCSprite::create("Image/dialog/k_JinBi.png");
	pGoldMark->setPosition(ccp(281,450)); //金币标志
	this->addChild(pGoldMark);

	CCLabelTTF* labelConsume = CCLabelTTF::create(L("consume"),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter); 
	labelConsume->setPosition(ccp(209,450)); //消费
	labelConsume->setColor(ccRED);
	this->addChild(labelConsume);

	int index = HSPropItemSprite::s_lastCCMenuItemImage->getTag()-1;
	CCLabelTTF* labelText = CCLabelTTF::create(CCString::createWithFormat(L("openslot"),index+1)->getCString(),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter); 
	labelText->setPosition(ccp(320,525)); //说明文字
	labelText->setColor(ccBLUE);
	this->addChild(labelText);

	
	CCLabelAtlas* buyMoney = CCLabelAtlas::create(CCString::createWithFormat("%d",index*100)->getCString(),"Image/PropMoney.png",190/10,23,'0');
	buyMoney->setAnchorPoint(HS_ANCHOR_L_CENTER);
	buyMoney->setPosition(ccp(pGoldMark->getPositionX()+30,pGoldMark->getPositionY()));
	this->addChild(buyMoney);

	CCMenuItemImage* Ok = CCMenuItemImage::create("Image/dialog/QueDing_01.png","Image/dialog/QueDing_02.png",m_pTarget,menu_selector(HSGameEquipManager::CallOk));
	Ok->setPosition(ccp(196,387));
	this->PushMenu(Ok);

	CCMenuItemImage* pCancle = CCMenuItemImage::create("Image/dialog/FouDing_01.png","Image/dialog/FouDing_02.png",m_pTarget,menu_selector(HSGameEquipManager::CallCancle));
	pCancle->setPosition(ccp(418,387));
	this->PushMenu(pCancle);



	return true;
}

