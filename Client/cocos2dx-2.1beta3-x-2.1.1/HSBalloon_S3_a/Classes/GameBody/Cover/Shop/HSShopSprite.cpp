#include "HSShopSprite.h"
#include "HSJava.h"

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
	this->initWithFile("Image/main/shop/Chengjiudikuanghengtiao.png");

	//this->setAnchorPoint(HS_ANCHOR_CENTER);
	//this->setPosition(ccp(itemSize.width/2,this->getAnchorPointInPoints().y));
	this->setAnchorPoint(HS_ANCHOR_L_CENTER);

	const char* pIconPath = CCString::createWithFormat("Image/goldIcon/%s",buyGold.localname().c_str())->getCString();
	
	m_pIcon = CCSprite::create(pIconPath);
	m_pIcon->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pIcon->setPosition(ccp(10.f,this->getAnchorPointInPoints().y));
	this->addChild(m_pIcon);

	CCMenuItemImage* itemImage = CCMenuItemImage::create("Image/main/shop/Goumaianniuxiao_01.png","Image/main/shop/Goumaianniuxiao_02.png",this,menu_selector(HSShopSprite::CallBuy));
	itemImage->setAnchorPoint(HS_ANCHOR_R_CENTER);
	itemImage->setPosition(ccp(this->getContentSize().width-10.f,this->getAnchorPointInPoints().y));
	m_pBuy = CCMenu::create(itemImage,NULL);
	m_pBuy->setPosition(CCPointZero);
	this->addChild(m_pBuy);

	//********************
	float des_x = m_pIcon->getPositionX()+m_pIcon->getContentSize().width;
	float des_y = this->getContentSize().height;
	float des_w = this->getContentSize().width-20.f-m_pIcon->getContentSize().width-itemImage->getContentSize().width;
	float des_h = this->getContentSize().height/2;
	
	m_pDescrib = CCLabelTTF::create(buyGold.describ().c_str(),HS_FONT_HuaKang,25.f,CCSizeMake(des_w,des_h),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pDescrib->setPosition(ccp(des_x+des_w/2,des_y-des_h/2));
	this->addChild(m_pDescrib);
	//*********************
	float sale_x = m_pIcon->getPositionX()+m_pIcon->getContentSize().width;
	float sale_y = this->getContentSize().height/2;
	float sale_w = this->getContentSize().width-20.f-m_pIcon->getContentSize().width-itemImage->getContentSize().width;
	float sale_h = this->getContentSize().height/2;

	m_pSale = CCLabelTTF::create(CCString::createWithFormat(L("shop_RMB"),buyGold.money())->getCString(),HS_FONT_HuaKang,25.f,CCSizeMake(sale_w,sale_h),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pSale->setPosition(ccp(sale_x+sale_w/2,sale_y-sale_h/2));
	this->addChild(m_pSale);
	
	return true;
}

void HSShopSprite::UpdateShopInfo( const message::BuyGold& buyGold)
{
	m_BuyGold = buyGold;
}

void HSShopSprite::CallBuy(CCObject* pSender)
{
	Json::Value jsonData;
	jsonData["goodID"] = m_BuyGold.id();
	jsonData["size"] = 1;
	jsonData["total"] = m_BuyGold.money() * 100;
	HSJson* pJson = HSJson::CreateWithWriter();
	std::string data = pJson->Writer(jsonData);
	HSJava::ShaderJava()->Pay(data.c_str());

}


