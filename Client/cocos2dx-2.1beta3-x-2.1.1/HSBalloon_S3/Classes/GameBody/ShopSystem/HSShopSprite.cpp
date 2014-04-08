#include "HSShopSprite.h"
#include "HSJava.h"
#include "MobClickCpp.h"
HSShopSprite::HSShopSprite(void)
{
	m_pIcon = NULL;
	m_pDescrib = NULL;
	m_pSale = NULL;
	m_pBuy = NULL;
    m_pName = NULL;
}


HSShopSprite::~HSShopSprite(void)
{
	m_pIcon = NULL;
	m_pDescrib = NULL;
	m_pSale = NULL;
	m_pBuy = NULL;
}

HSShopSprite* HSShopSprite::create(const CCSize& itemSize,const message::BuyGold& buyGold)
{
	HSShopSprite* sprite = new HSShopSprite();

	if(sprite && sprite->Init(itemSize,buyGold))
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSShopSprite::Init(const CCSize& itemSize,const message::BuyGold& buyGold)
{
    this->initWithFile("Image/Xingxiangkexuanzediban.png");
	this->setAnchorPoint(HS_ANCHOR_LD);


    CCNode* pItem_01 = HSCCSprite::create("Image/Shangchenggoumai_01.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/Shangchenggoumai_02.png");
    
	CCMenuItemSprite* itemSprite = CCMenuItemSprite::create(pItem_01,pItem_02,this,menu_selector(HSShopSprite::CallBuy));
	itemSprite->setPosition(ccp(495,53));
	m_pBuy = CCMenu::create(itemSprite,NULL);
	m_pBuy->setPosition(CCPointZero);
	this->addChild(m_pBuy);

	
	return true;
}

void HSShopSprite::UpdateShopInfo( const message::BuyGold& buyGold)
{
	m_BuyGold = buyGold;
    
    CCString* pIconFileName = CCString::createWithFormat("Image/%s",buyGold.localname().c_str());
    if(m_BuyGold.id() < 5000)
    {
        if(!m_pIcon)
        {
            m_pIcon = HSCCSprite::create(pIconFileName->getCString());
            m_pIcon->setPosition(ccp(50,53));
            this->addChild(m_pIcon);
        }
        else{
            m_pIcon->setDisplayFrame(HS_RP_GetSpriteFrame(pIconFileName->getCString()));
        }
        
        if(!m_pDescrib)
        {
            m_pDescrib = CCLabelTTF::create(m_BuyGold.describ().c_str(),HS_FONT_HuaKang,25.f,CCSizeMake(0,0),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
            m_pDescrib->setPosition(ccp(197,53));
            this->addChild(m_pDescrib);
        }else{
            m_pDescrib->setString(buyGold.describ().c_str());
        }
        
        CCString* pSaleStr = CCString::createWithFormat(L("shop_RMB"),buyGold.money() / 100.f);
        if(!m_pSale)
        {
            m_pSale = CCLabelTTF::create(pSaleStr->getCString(),HS_FONT_HuaKang,25.f,CCSizeMake(0,0),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
            m_pSale->setPosition(ccp(375,53));
            this->addChild(m_pSale);

        }else{
             m_pSale->setString(pSaleStr->getCString());
        }
    }
}

void HSShopSprite::CallBuy(CCObject* pSender)
{
	eventDict dict;
	dict["money"] = m_BuyGold.money();
	MobClickCpp::event("HSBuyGold",&dict);

	//MobClickCpp::endEventWithAttributes("HSBuyGold",&dict);

	Json::Value jsonData;
	jsonData["JNI_ID"] = Json::Value(1001);
	jsonData["PAY_UID"] = Json::Value(HS_GAME_CACHE_DATA()->uid().c_str());
	jsonData["goodID"] = m_BuyGold.id();
	jsonData["size"] = 1;
	jsonData["total"] = m_BuyGold.money();
	HSJson* pJson = HSJson::CreateWithWriter();
	std::string data = pJson->Writer(jsonData);

	HSJava::ShaderJava()->JavaExec(data.c_str());
}


