#include "HSRoomSprite.h"
#include "HSSeniortSystemScene.h"
#include "HSGamePairScene.h"

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
			CCSpriteFrame* pTexture = HS_RP_GetSpriteFrame(CCString::createWithFormat("Image/pindao_%d.png",i)->getCString());
			m_TextureMap.insert(pair<int,CCSpriteFrame*>(i,pTexture));
		}
	}
    CCSpriteFrame* pInitSpriteFrame = HS_RP_GetSpriteFrame("Image/xuanzepindao.png");
	this->initWithSpriteFrame(pInitSpriteFrame);
	this->setAnchorPoint(HS_ANCHOR_LD);

	m_pRoomName = HSCCSprite::create("Image/pindao_1.png");
	m_pRoomName->setPosition(ccp(272,123));
	this->addChild(m_pRoomName);

	m_pPlayerCountFrame = HSCCSprite::create("Image/Shuzidiandikuang.png");
	m_pPlayerCountFrame->setPosition(ccp(215,60));
	this->addChild(m_pPlayerCountFrame);

	m_pStakeGoldFrame = HSCCSprite::create("Image/Shuzidiandikuang.png");
	m_pStakeGoldFrame->setPosition(ccp(443,60));
	this->addChild(m_pStakeGoldFrame);
    
    CCNode* pItem_01 = HSCCSprite::create("Image/Pindaojinru_01.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/Pindaojinru_02.png");
    CCMenuItemSprite* pItem = CCMenuItemSprite::create(pItem_01, pItem_02, this, menu_selector(HSRoomSprite::ROOMCall));
    pItem->setPosition(ccp(438 ,126));
    CCMenu* pMenu = CCMenu::create(pItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
	return true;
}

void HSRoomSprite::ROOMCall(CCObject* pObj)
{
    RoomDataResponse* pRoomDataResponse = &HS_GAME_CACHE()->m_RoomDataResponse;
    
	int idx = m_id;
    
	CCLog("====================================================tableCellTouched: %d",idx);
	CCLog("1234567890c");
    
	if (pRoomDataResponse->roomlist_size() <= m_id)
	{
		return;
	}
    
	RoomDataResponse_Room pRoomInfo = pRoomDataResponse->roomlist(m_id);
    
	//CCLog("cell idx ==============>%d,roomId(%d),gold(%d),gold2(%d)",idx,pRoomInfo.id(),pRoomInfo.sweepstakegold(),pRoomInfo.stakegold());
    
	if (pRoomInfo.sweepstakegold() > HS_GAME_CACHE()->GetGold())
	{
		//CCLog("tableCellTouched 111");

		HSGoldInadequateDialog* pDialog = HSGoldInadequateDialog::create();

		//CCLog("tableCellTouched 222 gold %d",pRoomInfo.sweepstakegold() - HS_GAME_CACHE()->GetGold());

		const BuyGold* buyGold = HS_GAME_CACHE()->GetReasonableChargeId(pRoomInfo.sweepstakegold() - HS_GAME_CACHE()->GetGold());

		int num = HS_GAME_CACHE()->GetChargeNumber(pRoomInfo.sweepstakegold() - HS_GAME_CACHE()->GetGold(),buyGold->gold_number());

		pDialog->Set_BugGold(HS_GAME_CACHE()->GetReasonableChargeId(pRoomInfo.sweepstakegold() - HS_GAME_CACHE()->GetGold()),num);
		//CCLog("tableCellTouched 333");
        HSSeniortSystemScene* pSeniort = (HSSeniortSystemScene*)CCDirector::sharedDirector()->getRunningScene();
        //CCLog("tableCellTouched 444");
        pSeniort->GetHSSeniortSystemLayer()->addChild(pDialog);
        //CCLog("tableCellTouched 555");
	}
	else
	{
		HS_GAME_CACHE()->roomGold = pRoomInfo.stakegold();
		HS_GAME_CACHE()->m_roomId = pRoomInfo.id();
		HSRequest::ShareRequest()->SendTargetInfoRequest(pRoomInfo.id());
        
		HSGamePairLayer::s_CURRENT_ROOM_ID = pRoomInfo.id();
		HSLoadingLayer::ShareLoading()->setVisible(true);
		CCLog("tableCellTouched 222");
	}
	CCLog("tableCellTouched 333");
}

void HSRoomSprite::UpdataRoomInfo( int idx,const RoomDataResponse_Room& room )
{
    m_id = idx;
    
	std::map<int,CCSpriteFrame*>::iterator it = m_TextureMap.find(room.id());
	if (it == m_TextureMap.end())
	{
		return;
	}
    m_pRoomName->setDisplayFrame(it->second);

	if (!m_pPlayerCountTTF)
	{
		m_pPlayerCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",room.playercount())->getCString(),HS_FONT_HuaKang,25.f,m_pPlayerCountFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
        m_pPlayerCountTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
        m_pPlayerCountTTF->setPosition(ccp(0,m_pPlayerCountFrame->getContentSize().height / 2.f));
		m_pPlayerCountFrame->addChild(m_pPlayerCountTTF);
        m_pPlayerCountTTF->setColor(ccBLACK);
	}else{
		m_pPlayerCountTTF->setString(CCString::createWithFormat("%d",room.playercount())->getCString());
	}

	if (!m_pStakeCountTTF)
	{
		m_pStakeCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",room.stakegold())->getCString(),HS_FONT_HuaKang,25.f,m_pStakeGoldFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		m_pStakeCountTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
		m_pStakeCountTTF->setPosition(ccp(0,m_pStakeGoldFrame->getContentSize().height / 2.f));
		m_pStakeGoldFrame->addChild(m_pStakeCountTTF);
        m_pStakeCountTTF->setColor(ccBLACK);
	}else{
		m_pStakeCountTTF->setString(CCString::createWithFormat("%d",room.stakegold())->getCString());
	}
}
