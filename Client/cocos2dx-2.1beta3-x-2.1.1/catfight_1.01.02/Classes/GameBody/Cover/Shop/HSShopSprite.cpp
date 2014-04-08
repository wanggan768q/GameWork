#include "HSShopSprite.h"
#include "HSJava.h"
#include "MobClickCpp.h"
HSShopSprite::HSShopSprite(void)
{
	m_pIcon = NULL;
	m_pDescrib = NULL;
	m_pSale = NULL;
	m_pBuy = NULL;

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
	this->initWithFile("Image/Chengjiudikuanghengtiao.png");

	//this->setAnchorPoint(HS_ANCHOR_CENTER);
	//this->setPosition(ccp(itemSize.width/2,this->getAnchorPointInPoints().y));
	this->setAnchorPoint(HS_ANCHOR_L_CENTER);
	this->setPosition(ccp(0,this->getAnchorPointInPoints().y + 6.f));

	const char* pIconPath = CCString::createWithFormat("Image/%s",buyGold.localname().c_str())->getCString();
	
	m_pIcon = HSCCSprite::create(pIconPath);
	m_pIcon->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pIcon->setPosition(ccp(10.f,this->getAnchorPointInPoints().y));
	this->addChild(m_pIcon);

    CCNode* pItem_01 = HSCCSprite::create("Image/Goumaianniuxiao_01.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/Goumaianniuxiao_02.png");
    
	CCMenuItemSprite* itemSprite = CCMenuItemSprite::create(pItem_01,pItem_02,this,menu_selector(HSShopSprite::CallBuy));
	itemSprite->setAnchorPoint(HS_ANCHOR_R_CENTER);
	itemSprite->setPosition(ccp(this->getContentSize().width-10.f,this->getAnchorPointInPoints().y));
	m_pBuy = CCMenu::create(itemSprite,NULL);
	m_pBuy->setPosition(CCPointZero);
	this->addChild(m_pBuy);

	//********************
	float des_x = m_pIcon->getPositionX()+m_pIcon->getContentSize().width;
	float des_y = this->getContentSize().height;
	float des_w = this->getContentSize().width-20.f-m_pIcon->getContentSize().width-itemSprite->getContentSize().width;
	float des_h = this->getContentSize().height/2;
	
	m_pDescrib = CCLabelTTF::create(buyGold.describ().c_str(),HS_FONT_HuaKang,25.f,CCSizeMake(des_w,des_h),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pDescrib->setPosition(ccp(des_x+des_w/2,des_y-des_h/2));
	this->addChild(m_pDescrib);
	//*********************
	float sale_x = m_pIcon->getPositionX()+m_pIcon->getContentSize().width;
	float sale_y = this->getContentSize().height/2;
	float sale_w = this->getContentSize().width-20.f-m_pIcon->getContentSize().width-itemSprite->getContentSize().width;
	float sale_h = this->getContentSize().height/2;

	float money = buyGold.money()/100.0f;

	CCLog("buyGold.money(%d),money(%f)",buyGold.money(),money);


	m_pSale = CCLabelTTF::create(CCString::createWithFormat(L("shop_RMB"),money)->getCString(),HS_FONT_HuaKang,25.f,CCSizeMake(sale_w,sale_h),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pSale->setPosition(ccp(sale_x+sale_w/2,sale_y-sale_h/2));
	this->addChild(m_pSale);
	
	return true;
}

void HSShopSprite::UpdateShopInfo( const message::BuyGold& buyGold)
{
	m_BuyGold = buyGold;
	float money = buyGold.money()/100.0f;
	m_pDescrib->setString(buyGold.describ().c_str());
	m_pSale->setString(CCString::createWithFormat(L("shop_RMB"),money)->getCString());

	const char* pIconPath = CCString::createWithFormat("Image/%s",buyGold.localname().c_str())->getCString();
	CCSpriteFrame* pIconSpriteFrame = HS_RP_GetSpriteFrame(pIconPath);
	if(pIconSpriteFrame)
	{
		m_pIcon->setDisplayFrame(pIconSpriteFrame);
	}
}

void HSShopSprite::CallBuy(CCObject* pSender)
{
	eventDict dict;
	dict["money"] = m_BuyGold.money();
	MobClickCpp::event("HSBuyGold",&dict);

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


