#include "HSHeadSprite.h"
#include "HSTool.h"

HSHeadSprite::HSHeadSprite(void)
{
	m_propInfo = NULL;
	m_pMenu= NULL;
	m_pMoney= NULL;

	pTarget = NULL;
	selector = NULL;
	pData = NULL;
}


HSHeadSprite::~HSHeadSprite(void)
{
	m_propInfo = NULL;
	m_pMenu= NULL;
	m_pMoney= NULL;

	pTarget = NULL;
	selector = NULL;
	pData = NULL;
}

HSHeadSprite* HSHeadSprite::create(const message::PropInfo& propInfo ,int index)
{
	HSHeadSprite* sprite = new HSHeadSprite();

	if(sprite && sprite->Init(propInfo,index))
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);

	return NULL;
}

bool HSHeadSprite::Init(const message::PropInfo& propInfo,int index)
{
	m_propInfo = &propInfo;
	m_index = index;

	//CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_huantouxiangzu_jiagedikuang%d",index)->getCString(),"Shuzidiandikuang");
	

	HSCCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_huantouxiangzu_jiagedikuang%d",index)->getCString(),"Shuzidiandikuang");
	CCSize gameGoldFrameSize = pMoneyFrame->getContentSize();
	CCSize gameGoldPngSize = CCSizeMake(320.f,45.f);
	m_pMoney = CCLabelAtlas::create(CCString::createWithFormat("%d",propInfo.gold())->getCString(),"Image/moneyNumber.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	m_pMoney->setPosition(ccp(10.f,0));
	pMoneyFrame->addChild(m_pMoney);

// 	m_pMoney = CCLabelTTF::create(CCString::createWithFormat("%d",propInfo.gold())->getCString(),HS_FONT_HuaKang,25.f,pMoneyFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
// 	m_pMoney = CCLabelAtlas::create
// 	m_pMoney->setPosition(pMoneyFrame->getAnchorPointInPoints());
// 	pMoneyFrame->addChild(m_pMoney);


	CCSprite* pframe = HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_huantouxiangzu_dikuangda%d",index)->getCString(),"dikuangda");
	this->setPosition(pframe->getAnchorPointInPoints());

	const char* path = CCString::createWithFormat("Image/%s.png",m_propInfo->localname().c_str())->getCString();
	CCSprite* pNode_1 = HSCCSprite::create(path);
	HSGraySprite* pNode_2 = HSGraySprite::create(path);

	pNode_2->setScale(1.02f);
	CCMenuItemSprite* itemImage = CCMenuItemSprite::create(pNode_1,pNode_2,this,menu_selector(HSHeadSprite::Select));
	itemImage->setPosition(pframe->getAnchorPointInPoints());
	CCMenu* pMenu = CCMenu::create(itemImage,NULL);
	pMenu->setPosition(CCPointZero);
	pframe->addChild(pMenu);



	return true;
}

void HSHeadSprite::Select(CCObject* pSender)
{
	if (this->pTarget && this->selector)
	{
		(this->pTarget->*selector)(this,this->pData);
	}
}

void HSHeadSprite::SetTarget(CCObject* rec,SEL_CallFuncND selector,void* data)
{
	this->pTarget = rec;
	this->pTarget->retain();
	this->selector = selector;
	this->pData = data;
}

