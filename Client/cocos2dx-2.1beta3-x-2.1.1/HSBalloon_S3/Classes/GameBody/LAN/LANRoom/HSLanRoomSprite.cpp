#include "HSLanRoomSprite.h"
#include "HSJava.h"
#include "HSGameSceneJumpManage.h"

HSLanRoomSprite::HSLanRoomSprite(void)
{
	m_pRoomName = NULL;
    m_pRoomInfo = NULL;
}

HSLanRoomSprite::~HSLanRoomSprite(void)
{
}

HSLanRoomSprite* HSLanRoomSprite::create()
{
	HSLanRoomSprite* pSprite = new HSLanRoomSprite();
	if(pSprite && pSprite->Init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSLanRoomSprite::Init()
{
    this->initWithFile("Image/Wififangjianlan.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
    
    CCNode* pItem_01 = HSCCSprite::create("Image/Wifijinru_01.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/Wifijinru_02.png");
	CCMenuItemSprite* pMenuItem = CCMenuItemSprite::create(pItem_01,pItem_02,this,menu_selector(HSLanRoomSprite::Call_Room));
	pMenuItem->setPosition(ccp(477,38));
	CCMenu* pMenu = CCMenu::create(pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
    
	return true;
}

void HSLanRoomSprite::UpdataRoomInfo(int index, LanSearchRoomResponse_room* pRoom )
{
    m_pRoom = pRoom;
    if(!m_pRoomInfo)
    {
        CCString* pInfo = CCString::createWithFormat("%d / %d",pRoom->jni_egg_room_curnum(),pRoom->jni_egg_room_maxnum());
        m_pRoomInfo = CCLabelTTF::create(pInfo->getCString(),HS_FONT_HuaKang, 25.f,CCSizeMake(100, 30.f),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
        //m_pRoomInfo = CCLabelTTF::create("1/2", "", 25.f);
        m_pRoomInfo->setPosition(ccp(30,this->getContentSize().height / 2.f));
        this->addChild(m_pRoomInfo);
        pInfo->release();
    }
    
    if(!m_pRoomName)
    {
        m_pRoomName = CCLabelTTF::create(pRoom->jni_egg_room_name().c_str(),HS_FONT_HuaKang, 25.f,CCSizeMake(300, 30.f),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
        m_pRoomName->setPosition(ccp(167,this->getContentSize().height / 2.f));
        this->addChild(m_pRoomName);
    }
}

void HSLanRoomSprite::Call_Room(CCObject* pObj)
{
    HS_ShowLoading();
    HSLoadingLayer::ShareLoading()->SetTime(20);
    
    HSLanRequest::ShareLanRequest()->SendLanJoinRoomRequest(HS_GAME_CACHE_DATA_LAN().name().c_str(), m_pRoom->jni_egg_room_name().c_str(),m_pRoom->jni_egg_ssid().c_str());
    
    //HS_GO_SCENE(HS_SCENE_GamePairScene);
}














