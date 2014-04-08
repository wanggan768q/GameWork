#include "HSGoldInadequateDialog.h"
#include "HSJava.h"
#include "HSGamePairScene.h"

HSGoldInadequateDialog::HSGoldInadequateDialog(void)
{
}


HSGoldInadequateDialog::~HSGoldInadequateDialog(void)
{
}

bool HSGoldInadequateDialog::InitBackground()
{
	this->initWithColor(ccc4(0, 0, 0, 0),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());

	return true;
}

bool HSGoldInadequateDialog::InitDialog()
{
	CCSprite* pBackground = CCSprite::create("Image/SelectChannel/goumaijinbidikuang.png");
	pBackground->setPosition(ccp(307,480));
	this->addChild(pBackground);


	CCSprite* pGoldFrame = CCSprite::create("Image/SelectChannel/Mingziditu.png");
	pGoldFrame->setPosition(ccp(236,202));
	pBackground->addChild(pGoldFrame);

	CCSprite* pMoneyFrame = CCSprite::create("Image/SelectChannel/Mingziditu.png");
	pMoneyFrame->setPosition(ccp(520,202));
	pBackground->addChild(pMoneyFrame);

	const message::PropInfoData* pPropInfodata = HS_GAME_CACHE()->GetPropInfoData();

	for (int i =0;i<pPropInfodata->buygoldlist_size();++i)
	{
		int temp = pPropInfodata->buygoldlist(i).gold_number();
		if ((int)m_buyGold.gold_number() < temp)
		{
			m_buyGold = pPropInfodata->buygoldlist(i);
		}
		if (temp > HS_GAME_CACHE()->GetGold())
		{
			m_buyGold = pPropInfodata->buygoldlist(i);
			break;
		}
	}


	CCLabelTTF* pGoldTTF = CCLabelTTF::create(CCString::createWithFormat("%d",m_buyGold.gold_number())->getCString(),HS_FONT_HuaKang,36.f);
	pGoldTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
	pGoldTTF->setPosition(ccp(0,pGoldTTF->getContentSize().height - pGoldTTF->getFontSize() / 2.f));
	pGoldFrame->addChild(pGoldTTF);

	CCLabelTTF* pMoneyTTF = CCLabelTTF::create(CCString::createWithFormat("%d",m_buyGold.money())->getCString(),HS_FONT_HuaKang,36.f);
	pMoneyTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
	pMoneyTTF->setPosition(ccp(0,pMoneyTTF->getContentSize().height - pMoneyTTF->getFontSize() / 2.f));
	pMoneyFrame->addChild(pMoneyTTF);

	CCMenuItem* pGoRoomItem = CCMenuItemImage::create("Image/SelectChannel/dibeilvchang_01.png","Image/SelectChannel/dibeilvchang_02.png",this,menu_selector(HSGoldInadequateDialog::Call_GoRoom));
	pGoRoomItem->setPosition(ccp(169,322));
	this->PushMenu(pGoRoomItem);

	CCMenuItem* pBuyItem = CCMenuItemImage::create("Image/SelectChannel/goumai_01.png","Image/SelectChannel/goumai_02.png",this,menu_selector(HSGoldInadequateDialog::Call_Buy));
	pBuyItem->setPosition(ccp(456,322));
	this->PushMenu(pBuyItem);


	return true;
}

void HSGoldInadequateDialog::Call_GoRoom( CCObject* pObj )
{
	this->getParent()->removeChild(this);
	int idx = -1;
	for (int i=0;i<HS_GAME_CACHE()->m_RoomDataResponse.roomlist_size();++i)
	{
		if (HS_GAME_CACHE()->GetGold() > HS_GAME_CACHE()->m_RoomDataResponse.roomlist(i).sweepstakegold())
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
	//发送数据 进入房间ID
	HSRequest::ShareRequest()->SendTargetInfoRequest(r.id());
	HSGamePairLayer::s_CURRENT_ROOM_ID = r.id();
	HSLoadingLayer::ShareLoading()->setVisible(true);
}

void HSGoldInadequateDialog::Call_Buy( CCObject* pObj )
{
	this->getParent()->removeChild(this);
	//购买金币
	Json::Value jsonData;
	jsonData["goodID"] = m_buyGold.id();
	jsonData["size"] = 1;
	jsonData["total"] = m_buyGold.money() * 100;
	HSJson* pJson = HSJson::CreateWithWriter();
	std::string data = pJson->Writer(jsonData);
	HSJava::ShaderJava()->Pay(data.c_str());

}
