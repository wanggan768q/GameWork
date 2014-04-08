003e:HSUseBufferLayer.cpp:000000493:1:14=526cb071:16=526cb071:#include "HSUseBufferLayer.h"
HSUseBufferLayer::HSUseBufferLayer(void)
{
}

HSUseBufferLayer::~HSUseBufferLayer(void)
{
}

bool HSUseBufferLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	this->setTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSUseBufferLayer::Load()
{
	//HSReadUI::ShareReadUI()->ReadUI("Image/pair/useBuffer/useBuffer.data","Image/pair/useBuffer/",this);
	//HS_SET_MENU_TARGET("UI_Guanbianniu_01",this,HSUseBufferLayer::Close);
}

void HSUseBufferLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSUseBufferLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(this->isVisible())
	{
		return true;
	}
	return false;
}

void HSUseBufferLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSUseBufferLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSUseBufferLayer::keyBackClicked()
{

}
void HSUseBufferLayer::keyMenuClicked()
{

}


003c:HSUseBufferLayer.h:0000003bc:1:14=526cb071:16=526cb071:/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/19   19:06
 *	File base:	HSUseBufferLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSUseBufferLayer_H__
#define __HSUseBufferLayer_H__
#pragma once
#include "HSTool.h"
class HSUseBufferLayer:public CCLayer
{
public:
	HSUseBufferLayer(void);
	~HSUseBufferLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSUseBufferLayer);

private:
	void Load();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};
#endif // __HSUseBufferLayer_H____



002b:.:000000000:3:14=5270d342:16=5270d342:0037:SeniortSystem:000000000:2:14=526f2bf2:16=526f2bf2:0044:HSGoldInadequateDialog.cpp:000000e0e:1:14=526cb070:16=526cb070:#include "HSGoldInadequateDialog.h"
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
0042:HSGoldInadequateDialog.h:000000350:1:14=526cb070:16=5270f3b0:/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   17:22
 *	File base:	HSGoldInadequateDialog.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGoldInadequateDialog_H__
#define __HSGoldInadequateDialog_H__
#pragma once
#include "HSTool.h"

class HSGoldInadequateDialog : public HSModalDialogInterface
{
public:
	HSGoldInadequateDialog(void);
	~HSGoldInadequateDialog(void);
public:
	CREATE_FUNC(HSGoldInadequateDialog);

	virtual bool InitBackground();

	virtual bool InitDialog();

private:
	void Call_GoRoom(CCObject* pObj);
	void Call_Buy(CCObject* pObj);

private:
	BuyGold m_buyGold;

};

#endif // __HSGoldInadequateDialog_H____

003c:HSRoomListView.cpp:000000724:1:14=526cb070:16=526cb070:#include "HSRoomListView.h"
#include "HSGamePairScene.h"

HSRoomListView::HSRoomListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
}


HSRoomListView::~HSRoomListView(void)
{
}

HSRoomListView* HSRoomListView::create( const CCSize& frameSize,const CCSize& itemSize,int onceCount )
{
	HSRoomListView* pListView = new HSRoomListView(frameSize,itemSize,onceCount);
	if (pListView && pListView->init())
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

bool HSRoomListView::init()
{
	return true;
}

CCNode* HSRoomListView::AddItem(int idx)
{
	RoomDataResponse_Room r = HS_GAME_CACHE()->m_RoomDataResponse.roomlist(idx);
	HSRoomSprite* s = HSRoomSprite::create();
	s->UpdataRoomInfo(r);
	return s;
}

bool HSRoomListView::UpdataItem( CCNode* pItem,int idx )
{
	HSRoomSprite* pSprite = dynamic_cast<HSRoomSprite*>(pItem);
	RoomDataResponse_Room r = HS_GAME_CACHE()->m_RoomDataResponse.roomlist(idx);
	pSprite->UpdataRoomInfo(r);
	return true;
}

void HSRoomListView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	RoomDataResponse* pRoomDataResponse = &HS_GAME_CACHE()->m_RoomDataResponse;
	if (pRoomDataResponse->roomlist_size() <= (int)cell->getIdx())
	{
		return;
	}
	RoomDataResponse_Room pRoomInfo = pRoomDataResponse->roomlist(cell->getIdx());

	if (pRoomInfo.sweepstakegold() > HS_GAME_CACHE()->GetGold())
	{
		//Show Diaog
		HSGoldInadequateDialog* pDialog = HSGoldInadequateDialog::create();
		this->getParent()->addChild(pDialog);

	}else{
		HSRequest::ShareRequest()->SendTargetInfoRequest(pRoomInfo.id());
		HSGamePairLayer::s_CURRENT_ROOM_ID = pRoomInfo.id();
		HSLoadingLayer::ShareLoading()->setVisible(true);
	}
}003a:HSRoomListView.h:0000003bd:1:14=526cb070:16=526cb070:/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   15:51
 *	File base:	HSRoomListView.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRoomListView_H__
#define __HSRoomListView_H__
#pragma once
#include "HSRoomSprite.h"
#include "HSGoldInadequateDialog.h"

class HSRoomListView : public HSListViewInterface
{
public:
	HSRoomListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSRoomListView(void);

public:
	static HSRoomListView* create(const CCSize& frameSize,const CCSize& itemSize,int onceCount);

	virtual bool init();

	virtual CCNode* AddItem(int idx);

	virtual bool UpdataItem( CCNode* pItem,int idx );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );
};

#endif // __HSRoomListView_H____003a:HSRoomSprite.cpp:0000008e8:1:14=526cb070:16=526cb070:#include "HSRoomSprite.h"


HSRoomSprite::HSRoomSprite(void)
{
	m_pPlayerCountTTF = NULL;
	m_pStakeCountTTF = NULL;
}


HSRoomSprite::~HSRoomSprite(void)
{
}

bool HSRoomSprite::init()
{
	if (m_TextureMap.empty())
	{
		for (int i=1;i<6;++i)
		{
			CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("Image/SelectChannel/pindao_%d.png",i)->getCString());
			m_TextureMap.insert(pair<int,CCTexture2D*>(i,pTexture));
		}
	}
	this->initWithFile("Image/SelectChannel/xuanzepindao.png");
	this->setAnchorPoint(HS_ANCHOR_LD);

	m_pRoomName = CCSprite::create("Image/SelectChannel/pindao_1.png");
	m_pRoomName->setPosition(ccp(272,123));
	this->addChild(m_pRoomName);

	m_pPlayerCountFrame = CCSprite::create("Image/SelectChannel/Shuzidiandikuang.png");
	m_pPlayerCountFrame->setPosition(ccp(215,55));
	this->addChild(m_pPlayerCountFrame);

	m_pStakeGoldFrame = CCSprite::create("Image/SelectChannel/Shuzidiandikuang.png");
	m_pStakeGoldFrame->setPosition(ccp(443,55));
	this->addChild(m_pStakeGoldFrame);

	return true;
}

void HSRoomSprite::UpdataRoomInfo( const RoomDataResponse_Room& room )
{
	std::map<int,CCTexture2D*>::iterator it = m_TextureMap.find(room.id());
	if (it == m_TextureMap.end())
	{
		return;
	}
	m_pRoomName->setTexture(it->second);

	if (!m_pPlayerCountTTF)
	{
		m_pPlayerCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",room.playercount())->getCString(),HS_FONT_HuaKang,25.f);
		m_pPlayerCountTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
		m_pPlayerCountTTF->setPosition(ccp(0,m_pPlayerCountTTF->getContentSize().height));
		m_pPlayerCountFrame->addChild(m_pPlayerCountTTF);
	}else{
		m_pPlayerCountTTF->setString(CCString::createWithFormat("%d",room.playercount())->getCString());
	}

	if (!m_pStakeCountTTF)
	{
		m_pStakeCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",room.stakegold())->getCString(),HS_FONT_HuaKang,25.f);
		m_pStakeCountTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
		m_pStakeCountTTF->setPosition(ccp(0,m_pStakeCountTTF->getContentSize().height));
		m_pStakeGoldFrame->addChild(m_pStakeCountTTF);
	}else{
		m_pStakeCountTTF->setString(CCString::createWithFormat("%d",room.stakegold())->getCString());
	}
}
0038:HSRoomSprite.h:00000035a:1:14=526cb070:16=5270f3b0:/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   15:54
 *	File base:	HSRoomSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRoomSprite_H__
#define __HSRoomSprite_H__
#pragma once
#include "HSTool.h"

class HSRoomSprite : public CCSprite
{
public:
	HSRoomSprite(void);
	~HSRoomSprite(void);

private:
	std::map<int,CCTexture2D*> m_TextureMap;
	CCSprite* m_pRoomName;
	CCSprite* m_pPlayerCountFrame;
	CCSprite* m_pStakeGoldFrame;
	CCLabelTTF* m_pPlayerCountTTF;
	CCLabelTTF* m_pStakeCountTTF;
public:
	CREATE_FUNC(HSRoomSprite);

	bool init();

	void UpdataRoomInfo(const RoomDataResponse_Room& room);
};

#endif // __HSRoomSprite_H____

0042:HSSeniortSystemScene.cpp:000001580:1:14=526f2bf2:16=526f2bf2:#include "HSSeniortSystemScene.h"
#include "HSGameSceneJumpManage.h"

//Layer
HSSeniortSystemLayer::HSSeniortSystemLayer(void)
{
	
}

HSSeniortSystemLayer::~HSSeniortSystemLayer(void)
{
}

bool HSSeniortSystemLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	this->Load();
	//this->setIsTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSSeniortSystemLayer::Load()
{
	CCSprite* pBackground = CCSprite::create("Image/SelectChannel/xuanzepindaodiban.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);

	HSReadUI::ShareReadUI()->ReadUI("Image/SelectChannel/SelectChannel.data","Image/SelectChannel/",this);

	HS_SET_MENU_TARGET("UI_fh_01",this,HSSeniortSystemLayer::CallBack);
	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSSeniortSystemLayer::CallShop);

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);

	CCNode *pNode = CCNode::create();
	pNode->setContentSize(CCSizeMake(544,862));
	//pNode->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pNode,2000);
	HSRoomListView* pRoomListView = HSRoomListView::create(CCSizeMake(544,862),CCSizeMake(544,250),HS_GAME_CACHE()->m_RoomDataResponse.roomlist_size());
	pRoomListView->setPosition(ccp(45,0));
	pNode->addChild(pRoomListView);
	pRoomListView->reloadData();
// 	HSRoomListView* pRoomListView = HSRoomListView::create(CCSizeMake(544,862),CCSizeMake(544,187),HS_GAME_CACHE()->m_RoomDataResponse.roomlist_size());
// 	pRoomListView->setPosition(ccp(45,0));
// 	this->addChild(pRoomListView);
// 	pRoomListView->reloadData();
	
	this->schedule(schedule_selector(HSSeniortSystemLayer::Updata));
}

void HSSeniortSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSSeniortSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSSeniortSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSSeniortSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSSeniortSystemLayer::keyBackClicked()
{

}
void HSSeniortSystemLayer::keyMenuClicked()
{

}

void HSSeniortSystemLayer::ResponseFighting( FightingResponse*r )
{
	FightingResponse_RequestStatus status = r->status();
	if(status ==FightingResponse_RequestStatus_SUCCESS)
	{
		NetAddress address= r->address();
		std::string ip = address.ip();
		int port = address.port();
		HSSocketPool::ShareSocketPool()->AddSocket(S_L_Battle,ip.c_str(),CCString::createWithFormat("%d",port)->getCString(),HSSocket_Type_SOCKET);
		HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
	}
	else if(status ==FightingResponse_RequestStatus_FAIL)
	{
		HSMessageBox("Response::Fighting Fail");
	}
}

void HSSeniortSystemLayer::ResponseTargetInfo( TargetInfoResponse*r )
{
	HS_GAME_CACHE()->m_pTargetInfoResponse->CopyFrom(*r);

	HS_GAME_CACHE()->CopyUser(r->self());

	HSSocketPool::ShareSocketPool()->SetPingShortLink(false);
	HSSocketPool::ShareSocketPool()->SetPingLongLink(true);

	if(HS_GAME_CACHE()->m_pTargetInfoResponse->status()== TargetInfoResponse_FindStatus_SUCCESS)
	{
		HSLoadingLayer::ShareLoading()->setVisible(false);
		CCLOG("did=%s",HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
		HS_GO_SCENE(HS_SCENE_GamePairScene);
	}
	else
	{
		HSMessageBox("HSSeniortSystemLayer::ResponseTargetInfo Response::TargetInfo fail");
	}
}

void HSSeniortSystemLayer::CallShop( CCObject* pObj )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSSeniortSystemScene* pSeniortSystemScene = (HSSeniortSystemScene*)scene;

	if(pSeniortSystemScene->GetHSGameShopLayer()==NULL)
	{
		pSeniortSystemScene->SetHSGameShopLayer(HSGameShopLayer::create());
	}
	else
	{
		pSeniortSystemScene->GetHSGameShopLayer()->setVisible(true);
	}
}

void HSSeniortSystemLayer::CallBack( CCObject* pObj )
{
	if (HS_ONLINE)
	{
		HSRequest::ShareRequest()->SendExitAdvancedRequest();
	}else{
		HS_GO_SCENE(HS_SCENE_CoverScene);
	}
}

void HSSeniortSystemLayer::ResponseExitAdvanced(ExitAdvancedResponse* r)
{
	HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
	HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
	HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed();
	HS_MUTABLE_TARGET_TARGET()->Clear();
	HS_GO_SCENE(HS_SCENE_CoverScene);
}

void HSSeniortSystemLayer::Updata( float dt )
{
	static int money = 0;
	if (money != HS_GAME_CACHE()->GetGold())
	{
		money = HS_GAME_CACHE()->GetGold();
		m_pMoney->setString(CCString::createWithFormat("%d",money)->getCString());
	}
}




//Scene
HSSeniortSystemScene::HSSeniortSystemScene(void)
{
	this->hsSeniortSystemLayer = NULL;
}

HSSeniortSystemScene::~HSSeniortSystemScene(void)
{
}

bool HSSeniortSystemScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsSeniortSystemLayer = HSSeniortSystemLayer::create();
	this->addChild(this->hsSeniortSystemLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}0040:HSSeniortSystemScene.h:0000007bc:1:14=526cb070:16=526cb070:/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   15:44
 *	File base:	HSSeniortSystemScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSeniortSystemScene_H__
#define __HSSeniortSystemScene_H__
#pragma once
#include "HSTool.h"
#include "HSRoomListView.h"
#include "HSGameShopLayer.h"
//Layer
class HSSeniortSystemLayer:public CCLayer
{
public:
	HSSeniortSystemLayer(void);
	~HSSeniortSystemLayer(void);

private:
	CCLabelAtlas* m_pMoney;
public:
	virtual bool init(); 
	CREATE_FUNC(HSSeniortSystemLayer);

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void Updata(float dt);

	void CallShop(CCObject* pObj);
	void CallBack(CCObject* pObj);

	//@ Net
	void ResponseFighting(FightingResponse*r);
	void ResponseTargetInfo(TargetInfoResponse*r);
	void ResponseExitAdvanced(ExitAdvancedResponse* pMsg);
};




//Scene
class HSSeniortSystemScene:public CCScene
{
public:
	HSSeniortSystemScene(void);
	~HSSeniortSystemScene(void);
private:
	HSSeniortSystemLayer* hsSeniortSystemLayer;
	HSGameShopLayer* hsGameShopLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSSeniortSystemScene);

	inline HSSeniortSystemLayer* GetHSSeniortSystemLayer(){return this->hsSeniortSystemLayer;};
	inline void SetHSGameShopLayer(HSGameShopLayer* layer)
	{
		this->hsGameShopLayer = layer;
		this->addChild(layer,HS_BASE_TAG,HS_BASE_TAG);
	}
	inline HSGameShopLayer* GetHSGameShopLayer(){return this->hsGameShopLayer;};

};

#endif // __HSSeniortSystemScene_H____002b:.:000000000:3:14=526f2bf2:16=526f2bf2:003f:HSGameDialogLayer.cpp:00000120e:1:14=526cb070:16=526cb070:#include "HSGameDialogLayer.h"
HSGameDialogLayer::HSGameDialogLayer(void)
{
	pTarget = NULL;
	pData = NULL;
	selector = NULL;
	m_pText = "";
}

HSGameDialogLayer::~HSGameDialogLayer(void)
{

}

bool HSGameDialogLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	this->setTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSGameDialogLayer::Load()
{
	//this->setContentSize(CCSizeMake(200.f,500.f));
}

HSGameDialogLayer* HSGameDialogLayer::create(DialogType type)
{
	HSGameDialogLayer* layer = new HSGameDialogLayer;
	if(layer && layer->Init(type))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool HSGameDialogLayer::Init(DialogType type)
{
	this->m_type = type;
	CCSprite* pback = CCSprite::create("Image/dialog/Huangsedikuang.png");

	pback->setAnchorPoint(HS_ANCHOR_CENTER);
	pback->setPosition(HSBase::GetScreenCentre());
	this->addChild(pback);
	CCMenu* pMenu =NULL;
	CCMenuItemImage *pOkItem = NULL;
	CCMenuItemImage *pCloseItem = NULL;
	//@menu
	if(m_type ==TYPE_SINGLE||m_type ==TYPE_NONO)
	{
		pOkItem = CCMenuItemImage::create("Image/dialog/Duigoutongyong.png",
			"Image/dialog/Duigoutongyong_02.png",
			this,
			menu_selector(HSGameDialogLayer::OK));
		pOkItem->setAnchorPoint(HS_ANCHOR_CENTER);
		pOkItem->setPosition(ccp(pback->getContentSize().width/2,80));

		pMenu = CCMenu::create(pOkItem, NULL);

		if(m_type ==TYPE_NONO)
		{
			pMenu->setVisible(false);
		}
	}
	else if(m_type == TYPE_DOUDLE)
	{
		pCloseItem = CCMenuItemImage::create(
			"Image/dialog/Chazitongyong.png",