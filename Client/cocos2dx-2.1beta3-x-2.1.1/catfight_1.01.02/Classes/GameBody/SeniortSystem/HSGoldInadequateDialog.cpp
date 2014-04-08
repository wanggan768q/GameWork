#include "HSGoldInadequateDialog.h"
#include "HSJava.h"
#include "HSGamePairScene.h"

HSGoldInadequateDialog::HSGoldInadequateDialog(void)
{
	m_pGoldTTF = NULL;
	m_pMoneyTTF = NULL;
	m_num =0;
}


HSGoldInadequateDialog::~HSGoldInadequateDialog(void)
{
	m_pGoldTTF = NULL;
	m_pMoneyTTF = NULL;
}

bool HSGoldInadequateDialog::InitBackground()
{
	this->initWithColor(ccc4(0, 0, 0, 0),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());

	return true;
}

bool HSGoldInadequateDialog::InitDialog()
{
	CCSprite* pBackground = HSCCSprite::create("Image/goumaijinbidikuang.png");
	pBackground->setPosition(ccp(307,480));
	this->addChild(pBackground);


	CCSprite* pGoldFrame = HSCCSprite::create("Image/Mingziditu.png");
	pGoldFrame->setPosition(ccp(236,202));
	pBackground->addChild(pGoldFrame);

	CCSprite* pMoneyFrame = HSCCSprite::create("Image/Mingziditu.png");
	pMoneyFrame->setPosition(ccp(520,202));
	pBackground->addChild(pMoneyFrame);


	m_pGoldTTF = CCLabelTTF::create(CCString::createWithFormat("%d",0/*m_buyGold->gold_number()*/)->getCString(),HS_FONT_HuaKang,36.f);
	m_pGoldTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pGoldTTF->setPosition(ccp(0,m_pGoldTTF->getContentSize().height - m_pGoldTTF->getFontSize() / 2.f));
	pGoldFrame->addChild(m_pGoldTTF);

	m_pMoneyTTF = CCLabelTTF::create(CCString::createWithFormat("%d",0/*m_buyGold->money()*/)->getCString(),HS_FONT_HuaKang,36.f);
	m_pMoneyTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pMoneyTTF->setPosition(ccp(0,m_pMoneyTTF->getContentSize().height - m_pMoneyTTF->getFontSize() / 2.f));
	pMoneyFrame->addChild(m_pMoneyTTF);

    CCNode* pItemNode_01 = HSCCSprite::create("Image/dibeilvchang_01.png");
    CCNode* pItemNode_02 = HSCCSprite::create("Image/dibeilvchang_02.png");
	CCMenuItem* pGoRoomItem = CCMenuItemSprite::create(pItemNode_01,pItemNode_02,this,menu_selector(HSGoldInadequateDialog::Call_GoRoom));
	pGoRoomItem->setPosition(ccp(169,322));
	this->PushMenu(pGoRoomItem);

    CCNode* pItemNode_03 = HSCCSprite::create("Image/goumai_01.png");
    CCNode* pItemNode_04 = HSCCSprite::create("Image/goumai_02.png");
	CCMenuItem* pBuyItem = CCMenuItemSprite::create(pItemNode_03,pItemNode_04,this,menu_selector(HSGoldInadequateDialog::Call_Buy));
	pBuyItem->setPosition(ccp(456,322));
	this->PushMenu(pBuyItem);

	return true;
}

void HSGoldInadequateDialog::Set_BugGold(const BuyGold* buyGold,const int& num)
{
	this->m_buyGold = buyGold;
	this->m_num = num;
	m_pGoldTTF->setString(CCString::createWithFormat("%d",this->m_buyGold->gold_number()*num)->getCString());

	float money = buyGold->money()*num/100.0f;
	m_pMoneyTTF->setString(CCString::createWithFormat("%.2f",money)->getCString());
}

void HSGoldInadequateDialog::Call_GoRoom( CCObject* pObj )
{
	this->getParent()->removeChild(this);
	int idx = -1;
	for (int i=0;i<HS_GAME_CACHE()->m_RoomDataResponse.roomlist_size();++i)
	{
		if(HS_GAME_CACHE()->GetGold() > HS_GAME_CACHE()->m_RoomDataResponse.roomlist(i).sweepstakegold())
		{
			idx = i;
		}
	}
	if (idx == -1)
	{
		HSMessageBox("Didn't find the matched the room");
		return;
	}
	RoomDataResponse_Room r = HS_GAME_CACHE()->m_RoomDataResponse.roomlist(idx);

	HSRequest::ShareRequest()->SendTargetInfoRequest(r.id());

	HSGamePairLayer::s_CURRENT_ROOM_ID = r.id();
	HSLoadingLayer::ShareLoading()->setVisible(true);
}

void HSGoldInadequateDialog::Call_Buy( CCObject* pObj )
{
	this->getParent()->removeChild(this);

	HSJava::ShaderJava()->Pay(m_buyGold->gold_number()*this->m_num);

}
