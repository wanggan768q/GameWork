#include "HSBuySceneDialog.h"
#include "HSBuyPropScene.h"

HSBuySceneDialog::HSBuySceneDialog(void)
{
	m_pTarget = NULL;
}

HSBuySceneDialog::~HSBuySceneDialog(void)
{


}
HSBuySceneDialog* HSBuySceneDialog::create(CCObject* pTarget)
{
	HSBuySceneDialog* pDialog = new HSBuySceneDialog;
	if (pDialog && pDialog->init(pTarget))
	{
		pDialog->autorelease();
		return pDialog;
	}
	CC_SAFE_DELETE(pDialog);
	return NULL;
}

bool HSBuySceneDialog::init( CCObject* pTarget )
{
	m_pTarget = pTarget;
	if (!HSModalDialogInterface::init())
	{
		return false;
	}


	return true;
}

bool HSBuySceneDialog::InitDialog()
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

	int index = HSGameScenePropSprite::s_lastSelectedGameSceneFrameNode->getTag();

	const char* key = CCString::createWithFormat("openlevel%d",index)->getCString();
	CCLabelTTF* labelText = CCLabelTTF::create(L(key),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter); 
	labelText->setPosition(ccp(320,525)); //说明文字
	labelText->setColor(ccBLUE);
	this->addChild(labelText);

	int money =0;

	if(index ==0)
	{
		money = 1500;
	}

    if(index ==1)
	{
		money = 500;
	}
	 
	if(index ==2)
	{
		money = 5000;
	}

	CCLabelAtlas* buyMoney = CCLabelAtlas::create(CCString::createWithFormat("%d",money)->getCString(),"Image/PropMoney.png",190/10,23,'0');

	buyMoney->setAnchorPoint(HS_ANCHOR_L_CENTER);
	buyMoney->setPosition(ccp(pGoldMark->getPositionX()+30,pGoldMark->getPositionY()));
	this->addChild(buyMoney);

	CCMenuItemImage* Ok = CCMenuItemImage::create("Image/dialog/QueDing_01.png","Image/dialog/QueDing_02.png",m_pTarget,menu_selector(HSBuyPropLayer::Call_Ok));
	Ok->setPosition(ccp(196,387));
	this->PushMenu(Ok);

	CCMenuItemImage* pCancle = CCMenuItemImage::create("Image/dialog/FouDing_01.png","Image/dialog/FouDing_02.png",m_pTarget,menu_selector(HSBuyPropLayer::Call_Cancel));
	pCancle->setPosition(ccp(418,387));
	this->PushMenu(pCancle);

	return true;
}

