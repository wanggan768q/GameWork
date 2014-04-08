#include "HSBuyPropInfoDialog.h"
#include "HSBuyPropScene.h"
#include "HSGameSceneJumpManage.h"

HSBuyPropInfoDialog::HSBuyPropInfoDialog(void)
{
	m_pTarget = NULL;
}

HSBuyPropInfoDialog::~HSBuyPropInfoDialog(void)
{


}
HSBuyPropInfoDialog* HSBuyPropInfoDialog::create(CCObject* pTarget)
{
	HSBuyPropInfoDialog* pDialog = new HSBuyPropInfoDialog;
	if (pDialog && pDialog->init(pTarget))
	{
		pDialog->autorelease();
		return pDialog;
	}
	CC_SAFE_DELETE(pDialog);
	return NULL;
}

bool HSBuyPropInfoDialog::init( CCObject* pTarget )
{
	m_pTarget = pTarget;
	if (!HSModalDialogInterface::init())
	{
		return false;
	}

	return true;
}

bool HSBuyPropInfoDialog::InitDialog()
{
	if (!m_pTarget)
	{
		return false;
	}

	HSReadUI::ShareReadUI()->ReadUI("Image/BuyProp/PropInfo/propInfo.data","Image/BuyProp/PropInfo/",this);

	m_PropId = 0;
	//返回按钮
	HS_SET_MENU_TARGET("UI_FanHuiDe",this,HSBuyPropInfoDialog::Close);
	CCArray* pArrayReturn = HS_FIND_UI_MENUITEM_ARRAY("UI_FanHuiDe");
	this->PushMenu(pArrayReturn);
	//购买
	HS_SET_MENU_TARGET("UI_GouMai",this,HSBuyPropInfoDialog::Buy);
	CCArray* pArrayBuy = HS_FIND_UI_MENUITEM_ARRAY("UI_GouMai");
	this->PushMenu(pArrayBuy);

	//道具图
	HSCCSprite* propIconFrame = HS_FIND_UI_PANEL_SPRITE("UI_YuanQuan","s_YuanQuan");
	m_pPropIcon = CCSprite::create(CCString::createWithFormat("Image/BuyProp/ManualProp/100%d.png",0)->getCString());
	m_pPropIcon->setPosition(HS_SizeHalf_Point(propIconFrame->getContentSize()));
	propIconFrame->addChild(m_pPropIcon);
	//道具名
	HSCCSprite* propNameFrame = HS_FIND_UI_PANEL_SPRITE("UI_MingChengTiao","s_MingChengTiao");
	m_pPropName = CCLabelTTF::create(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(0).name().c_str(),"华康海报体W12(P)",25.f,CCSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	m_pPropName->setPosition(HS_SizeHalf_Point(propNameFrame->getContentSize()));
	propNameFrame->addChild(m_pPropName);

	CCSize gameGoldPngSize = CCSizeMake(250.f,30.f);

	HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_SQianGui","s_QianGui");
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
	m_curpGold = HS_GAME_CACHE()->GetGold();
	m_pGameGold = CCLabelAtlas::create(CCString::createWithFormat("%d",m_curpGold)->getCString(),"Image/GameGold.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	m_pGameGold->setPosition(ccp(0+gameGoldPngSize.width/10,0));
	m_pGameGold->setScaleX( gameGoldFrameSize.width / gameGoldPngSize.width);
	m_pGameGold->setScaleY( gameGoldFrameSize.height / gameGoldPngSize.height);
	gameGoldFrame->addChild(m_pGameGold);
	

	HSCCSprite* pPropMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_STouMingKuang","STouMingKuang");
	CCSize propMoneyFrameSize = pPropMoneyFrame->getContentSize();
	m_pPropMoney = CCLabelAtlas::create(CCString::createWithFormat("%d",HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(0).buymoney())->getCString(),"Image/GameGold.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	m_pPropMoney->setPosition(ccp(0+gameGoldPngSize.width/10,0));
	m_pPropMoney->setScaleX( gameGoldFrameSize.width / gameGoldPngSize.width);
	m_pPropMoney->setScaleY( gameGoldFrameSize.height / gameGoldPngSize.height);
	pPropMoneyFrame->addChild(m_pPropMoney);

	 
	 
	HSCCSprite* propDiscribFrame2 = HS_FIND_UI_PANEL_SPRITE("UI_s_ShangCheng1","s_ShangCheng1");
	m_pPropDiscrib = CCLabelTTF::create(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(0).describe().c_str(),"华康海报体W12(P)",25.f,CCSize(propDiscribFrame2->getContentSize().width-140,propDiscribFrame2->getContentSize().height),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	m_pPropDiscrib->setPosition(HS_SizeHalf_Point(propDiscribFrame2->getContentSize()));
	m_pPropDiscrib->setColor(ccBLACK);
	propDiscribFrame2->addChild(m_pPropDiscrib);
	this->schedule(schedule_selector(HSBuyPropInfoDialog::Update));
	return true;
}

void HSBuyPropInfoDialog::Update(float dt)
{
	if (m_curpGold != HS_GAME_CACHE()->GetGold())
	{
		m_curpGold =  HS_GAME_CACHE()->GetGold();
		m_pGameGold->setString(CCString::createWithFormat("%d",m_curpGold)->getCString());
		CCSize gameGoldPngSize = CCSizeMake(250.f,30.f);
		m_pGameGold->setPosition(ccp(0+gameGoldPngSize.width/10,0));
	}
}

void HSBuyPropInfoDialog::Buy(CCObject* obj)
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

	layer->m_pBuyPropInfoDialog->setVisible(false);

	if(HS_PROP_TYPE(m_PropId) ==HS_BUFFER_PROP_TYPE)
	{
		HSTool::ShareHSTool()->Buy(m_PropId,HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(0).buymoney(),L("prop5"),L("prop5char"));
	}
	else
	{
		int index = HS_PROP_INDEX(m_PropId);

		const char* titleKey = CCString::createWithFormat("prop%d",index+1)->getCString();
		const char* discribKey = CCString::createWithFormat("prop%dchar",index+1)->getCString();
		HSTool::ShareHSTool()->Buy(m_PropId,HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(index).buymoney(),L(titleKey),L(discribKey));
	}
	
}

void HSBuyPropInfoDialog::Close(CCObject* obj)
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

	layer->m_pBuyPropInfoDialog->setVisible(false);

	if(HS_PROP_TYPE(m_PropId) ==HS_BUFFER_PROP_TYPE)
	{
		HS_GO_SCENE(HS_SCENE_BattleScene);
	}
}

void HSBuyPropInfoDialog::setProp(int id)
{
	if(m_PropId != id)
	{
		this->m_PropId = id;
		//m_pPropIcon = CCSprite::create(CCString::createWithFormat("Image/BuyProp/ManualProp/100%d.png",0)->getCString());

		int type = HS_PROP_TYPE(id);
		int index = HS_PROP_INDEX(id);
		if(type ==HS_BUFFER_PROP_TYPE)//buffer道具
		{
			m_pPropIcon->initWithFile(CCString::createWithFormat("Image/BuyProp/bufferProp/100%d.png",index)->getCString());

			m_pPropName->setString(HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(index).name().c_str());

			m_pPropMoney->setString(CCString::createWithFormat("%d",HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(index).buymoney())->getCString());

			m_pPropDiscrib->setString(HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(index).describe().c_str());
			
		}
		else//默认手动道具
		{
			m_pPropIcon->initWithFile(CCString::createWithFormat("Image/BuyProp/ManualProp/100%d.png",index)->getCString());

			m_pPropName->setString(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(index).name().c_str());

			m_pPropMoney->setString(CCString::createWithFormat("%d",HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(index).buymoney())->getCString());

			m_pPropDiscrib->setString(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(index).describe().c_str());
		}
	}
}

