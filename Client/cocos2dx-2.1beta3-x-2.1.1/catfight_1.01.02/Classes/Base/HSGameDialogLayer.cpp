#include "HSGameDialogLayer.h"
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
	CCSprite* pback = HSCCSprite::create("Image/Huangsedikuang_dialog.png");

	pback->setAnchorPoint(HS_ANCHOR_CENTER);
	pback->setPosition(HSBase::GetScreenCentre());
	this->addChild(pback);
	CCMenu* pMenu =NULL;
	CCMenuItemSprite *pOkItem = NULL;
	CCMenuItemSprite *pCloseItem = NULL;
	//@menu
	if(m_type ==TYPE_SINGLE||m_type ==TYPE_NONO)
	{
        CCNode* pItem_01 = HSCCSprite::create("Image/Duigoutongyong.png");
        CCNode* pItem_02 = HSCCSprite::create("Image/Duigoutongyong_02.png");
        
		pOkItem = CCMenuItemSprite::create(pItem_01,
			pItem_02,
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
        CCNode* pItem_01_Cha = HSCCSprite::create("Image/Chazitongyong.png");
        CCNode* pItem_02_Cha = HSCCSprite::create("Image/Chazitongyong_02.png");

		pCloseItem = CCMenuItemSprite::create(
			pItem_01_Cha,
			pItem_02_Cha,
			this,
			menu_selector(HSGameDialogLayer::Close));
		pCloseItem->setAnchorPoint(HS_ANCHOR_CENTER);
		pCloseItem->setPosition(ccp(pback->getContentSize().width/6*5,80));

        CCNode* pItem_01 = HSCCSprite::create("Image/Duigoutongyong.png");
        CCNode* pItem_02 = HSCCSprite::create("Image/Duigoutongyong_02.png");
		pOkItem = CCMenuItemSprite::create(pItem_01,
			pItem_02,
			this,
			menu_selector(HSGameDialogLayer::OK));
		pOkItem->setAnchorPoint(HS_ANCHOR_CENTER);
		pOkItem->setPosition(ccp(pback->getContentSize().width/6,80));
		pMenu = CCMenu::create(pOkItem,pCloseItem, NULL);
	}
	else if(m_type ==TYPE_NONO)
	{

	}

	// Create a menu with the "close" menu item, it's an auto release object.
	 
	pMenu->setPosition(CCPointZero);
	pback->addChild(pMenu);

	//@title
	CCSprite* ptitleBar = HSCCSprite::create("Image/titleBar.png");
	ptitleBar->setAnchorPoint(HS_ANCHOR_U_CENTER);
	ptitleBar->setPosition(ccp(pback->getContentSize().width/2,pback->getContentSize().height));
	pback->addChild(ptitleBar);

	CCSprite* title = HSCCSprite::create("Image/Xitongtishi.png");
	title->setAnchorPoint(HS_ANCHOR_CENTER);
	title->setPosition(ccp(ptitleBar->getContentSize().width/2,ptitleBar->getContentSize().height/2+5));
	ptitleBar->addChild(title);

	//@text
	float height = pback->getContentSize().height-ptitleBar->getContentSize().height-80.f-pOkItem->getContentSize().height/2-20;
	CCSize textSize =  CCSizeMake(pback->getContentSize().width-40,height);
	m_pLable =CCLabelTTF::create(m_pText,HS_FONT_HuaKang,25.f,textSize,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	float y = height/2+80.f+pOkItem->getContentSize().height/2+20.f;
	m_pLable->setPosition(ccp(pback->getContentSize().width/2,y));
	m_pLable->setColor(ccBLACK);
	pback->addChild(m_pLable);

	return true;
}

void HSGameDialogLayer::OK(CCObject* obj)
{
	if(m_type==TYPE_NONO)return;
	if (this->pTarget && this->selector)
	{
		(this->pTarget->*selector)(this,this->pData);
	}
	this->removeFromParent();
}

void HSGameDialogLayer::Close(CCObject* obj)
{
	this->removeFromParent();
}

void HSGameDialogLayer::SetTarget(CCObject* rec,SEL_CallFuncND selector,void* data)
{
	this->pTarget = rec;
	this->selector = selector;
	this->pData = data;
}

void HSGameDialogLayer::SetText(const char* text)
{
	this->m_pText = text;
	m_pLable->setString(m_pText);
}

void HSGameDialogLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSGameDialogLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameDialogLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameDialogLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameDialogLayer::keyBackClicked()
{

}
void HSGameDialogLayer::keyMenuClicked()
{

}


