#include "HSBuyShopDialog.h"
#include "HSBuyPropScene.h"
HSBuyShopDialog::HSBuyShopDialog(void)
{
	m_pTarget = NULL;
	m_curpGold =0;
}

HSBuyShopDialog::~HSBuyShopDialog(void)
{


}
HSBuyShopDialog* HSBuyShopDialog::create(CCObject* pTarget)
{
	HSBuyShopDialog* pDialog = new HSBuyShopDialog;
	if (pDialog && pDialog->init(pTarget))
	{
		pDialog->autorelease();
		return pDialog;
	}
	CC_SAFE_DELETE(pDialog);
	return NULL;
}

bool HSBuyShopDialog::init( CCObject* pTarget)
{
	m_pTarget = pTarget;
	if (!HSModalDialogInterface::init())
	{
		return false;
	}

	return true;
}

bool HSBuyShopDialog::InitDialog()
{
	if (!m_pTarget)
	{
		return false;
	}
	HSReadUI::ShareReadUI()->ReadUI("Image/BuyProp/BuyShop/buyShop.data","Image/BuyProp/BuyShop/",this);

	CCSize gameGoldPngSize = CCSizeMake(250.f,30.f);
	//返回按钮
	HS_SET_MENU_TARGET("UI_FanHuiDe_01",m_pTarget,HSBuyPropLayer::CallDestoryShop);
	CCArray* pArrayReturn = HS_FIND_UI_MENUITEM_ARRAY("UI_FanHuiDe_01");
	this->PushMenu(pArrayReturn);
	//购买1
	HS_SET_MENU_TARGET("UI_BanKuai0_GouMai_01",m_pTarget,HSBuyPropLayer::Call_Buy1);
	CCArray* pArrayBuy1 = HS_FIND_UI_MENUITEM_ARRAY("UI_BanKuai0_GouMai_01");
	this->PushMenu(pArrayBuy1);
	//购买2
	HS_SET_MENU_TARGET("UI_BanKuai1_GouMai_01",m_pTarget,HSBuyPropLayer::Call_Buy2);
	CCArray* pArrayBuy2 = HS_FIND_UI_MENUITEM_ARRAY("UI_BanKuai1_GouMai_01");
	this->PushMenu(pArrayBuy2);
	//金币
	HSCCSprite* jinbi = HS_FIND_UI_PANEL_SPRITE("UI_GJinBi","k_JinBi");
	jinbi->setVisible(false);

	HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_QianGui","s_QianGui");
	gameGoldFrame->setVisible(false);
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
	
	m_pGameGold = CCLabelAtlas::create("0","Image/GameGold.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	m_pGameGold->setPosition(ccp(250.f - m_pGameGold->getContentSize().width - gameGoldPngSize.width / 10,0));
	m_pGameGold->setScaleX( gameGoldFrameSize.width / gameGoldPngSize.width);
	m_pGameGold->setScaleY( gameGoldFrameSize.height / gameGoldPngSize.height);
	gameGoldFrame->addChild(m_pGameGold);
	//第三个框暂时隐藏
	CCNode* chongZhi = HS_FIND_UI_PANEL("UI_BanKuai2");
	chongZhi->setVisible(false);
	 
	int index = HS_GAME_CACHE()->GetPropIndex();

	//第1个道具 打折道具
	const char* propIconPanleName1 = CCString::createWithFormat("UI_BanKuai%d_BanKuai1",0)->getCString();
	HSCCSprite* propIconFrame1 = HS_FIND_UI_PANEL_SPRITE(propIconPanleName1,"BanKuai1");
	CCSprite* propIcon1 = CCSprite::create(CCString::createWithFormat("Image/BuyProp/ManualProp/100%d.png",index)->getCString());
	propIcon1->setPosition(HS_SizeHalf_Point(propIconFrame1->getContentSize()));
	propIconFrame1->addChild(propIcon1);

	const char* propNamePanleName1 = CCString::createWithFormat("UI_BanKuai%d_BanKuai2",0)->getCString();
	HSCCSprite* propNameFrame1 = HS_FIND_UI_PANEL_SPRITE(propNamePanleName1,"BanKuai2");
	CCLabelTTF* propName1 = CCLabelTTF::create(HS_GAME_CACHE()->GetPropInfoData()->cheappropinfolist(index).name().c_str(),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	propName1->setPosition(HS_SizeHalf_Point(propNameFrame1->getContentSize()));
	propNameFrame1->addChild(propName1);

	const char* propDiscribPanleName1 = CCString::createWithFormat("UI_BanKuai%d_BanKuai3",0)->getCString();
	HSCCSprite* propDiscribFrame1 = HS_FIND_UI_PANEL_SPRITE(propDiscribPanleName1,"BanKuai3");
	CCLabelTTF* propDiscrib1 = CCLabelTTF::create(HS_GAME_CACHE()->GetPropInfoData()->cheappropinfolist(index).describe().c_str(),"华康海报体W12(P)",25.f,propDiscribFrame1->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	propDiscrib1->setPosition(HS_SizeHalf_Point(propDiscribFrame1->getContentSize()));
	propDiscribFrame1->addChild(propDiscrib1);

	const char* propMoneyName1 = CCString::createWithFormat("UI_BanKuai%d_BanKuai4",0)->getCString();
	HSCCSprite* propMoneyFrame1 = HS_FIND_UI_PANEL_SPRITE(propMoneyName1,"BanKuai4");
	CCSize propMoneyFrameSize1 = propMoneyFrame1->getContentSize();

	CCSprite* propMoneyIcon1 = CCSprite::create("Image/BuyProp/BuyShop/k_JinBi.png");
	propMoneyIcon1->setAnchorPoint(HS_ANCHOR_L_CENTER);
	propMoneyIcon1->setPosition(ccp(0.f,propMoneyFrame1->getContentSize().height/2.f));
	propMoneyFrame1->addChild(propMoneyIcon1);
	 
	CCLabelAtlas* propMoney1 = CCLabelAtlas::create(CCString::createWithFormat("%d",HS_GAME_CACHE()->GetPropInfoData()->cheappropinfolist(index).buymoney())->getCString(),"Image/GameGold.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	propMoney1->setPosition(ccp(propMoneyIcon1->getContentSize().width,0));
	propMoney1->setScaleX( propMoneyFrameSize1.width / gameGoldPngSize.width);
	propMoney1->setScaleY( propMoneyFrameSize1.height / gameGoldPngSize.height);
	propMoneyFrame1->addChild(propMoney1);

	//第2个道具 礼包道具
	const char* propIconPanleName2 = CCString::createWithFormat("UI_BanKuai%d_BanKuai1",1)->getCString();
	HSCCSprite* propIconFrame2 = HS_FIND_UI_PANEL_SPRITE(propIconPanleName2,"BanKuai1");
	CCSprite* propIcon2 = CCSprite::create(CCString::createWithFormat("Image/BuyProp/ManualProp/100%d.png",index)->getCString());
	propIcon2->setPosition(HS_SizeHalf_Point(propIconFrame2->getContentSize()));
	propIconFrame2->addChild(propIcon2);

	CCLabelTTF* propNumber = CCLabelTTF::create(CCString::createWithFormat("x%d",HS_GAME_CACHE()->GetPropInfoData()->giftbagpropinfolist(index).giftbag(0).count())->getCString(),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	propNumber->setPosition(ccp(propIconFrame2->getContentSize().width-30.f,0.f+30.f));
	propIconFrame2->addChild(propNumber);
	
	const char* propNamePanleName2 = CCString::createWithFormat("UI_BanKuai%d_BanKuai2",1)->getCString();
	HSCCSprite* propNameFrame2 = HS_FIND_UI_PANEL_SPRITE(propNamePanleName2,"BanKuai2");
	CCLabelTTF* propName2 = CCLabelTTF::create(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(index).name().c_str(),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	propName2->setPosition(HS_SizeHalf_Point(propNameFrame2->getContentSize()));
	propNameFrame2->addChild(propName2);

	

	const char* propDiscribPanleName2 = CCString::createWithFormat("UI_BanKuai%d_BanKuai3",1)->getCString();
	HSCCSprite* propDiscribFrame2 = HS_FIND_UI_PANEL_SPRITE(propDiscribPanleName2,"BanKuai3");
	CCLabelTTF* propDiscrib2 = CCLabelTTF::create(HS_GAME_CACHE()->GetPropInfoData()->giftbagpropinfolist(index).describe().c_str(),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	propDiscrib2->setPosition(HS_SizeHalf_Point(propDiscribFrame2->getContentSize()));
	propDiscribFrame2->addChild(propDiscrib2);

	const char* propMoneyName2 = CCString::createWithFormat("UI_BanKuai%d_BanKuai4",1)->getCString();
	HSCCSprite* propMoneyFrame2 = HS_FIND_UI_PANEL_SPRITE(propMoneyName2,"BanKuai4");
	CCSize propMoneyFrameSize2 = propMoneyFrame2->getContentSize();

	CCSprite* propMoneyIcon2 = CCSprite::create("Image/BuyProp/BuyShop/k_JinBi.png");
	propMoneyIcon2->setAnchorPoint(HS_ANCHOR_L_CENTER);
	propMoneyIcon2->setPosition(ccp(0.f,propMoneyFrame2->getContentSize().height/2.f));
	propMoneyFrame2->addChild(propMoneyIcon2);
	 
	CCLabelAtlas* propMoney2 = CCLabelAtlas::create(CCString::createWithFormat("%d",HS_GAME_CACHE()->GetPropInfoData()->giftbagpropinfolist(index).buymoney())->getCString(),"Image/GameGold.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	propMoney2->setPosition(ccp(propMoneyIcon2->getContentSize().width,0));
	propMoney2->setScaleX( propMoneyFrameSize2.width / gameGoldPngSize.width);
	propMoney2->setScaleY( propMoneyFrameSize2.height / gameGoldPngSize.height);
	propMoneyFrame2->addChild(propMoney2);


	this->schedule(schedule_selector(HSBuyShopDialog::Update));
	return true;
}

void HSBuyShopDialog::Update(float dt)
{
	/**
	if (m_curpGold != HS_GAME_CACHE()->GetGold())
	{
		m_curpGold =  HS_GAME_CACHE()->GetGold();
		m_pGameGold->setString(CCString::createWithFormat("%d",m_curpGold)->getCString());
		CCSize gameGoldPngSize = CCSizeMake(250.f,30.f);
		m_pGameGold->setPosition(ccp(250.f - m_pGameGold->getContentSize().width - gameGoldPngSize.width / 10,0));
	}*/
}

