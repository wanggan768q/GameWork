#include "HSGameScenePropSprite.h"
#include "HSBuyPropScene.h"


HSGameScenePropSprite* HSGameScenePropSprite::s_TouchGameScenePropSprite = NULL;

CCNode* HSGameScenePropSprite::s_lastSelectedGameSceneFrameNode = NULL;
CCNode* HSGameScenePropSprite::s_lastSelectFrameNode = NULL;

HSGameScenePropSprite::HSGameScenePropSprite(void)
{
}


HSGameScenePropSprite::~HSGameScenePropSprite(void)
{
	m_PropInfo.Clear();
	HSGameScenePropSprite::s_TouchGameScenePropSprite = NULL;
	HSGameScenePropSprite::s_lastSelectedGameSceneFrameNode = NULL;
	HSGameScenePropSprite::s_lastSelectFrameNode = NULL;
}

HSGameScenePropSprite* HSGameScenePropSprite::create( int index )
{
	HSGameScenePropSprite* sprite = new HSGameScenePropSprite;
	if (sprite && sprite->Init(index))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

HSGameScenePropSprite* HSGameScenePropSprite::create( const message::PropInfo propInfo ,int index )
{
	HSGameScenePropSprite* sprite = new HSGameScenePropSprite;
	if (sprite && sprite->Init(propInfo,index))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSGameScenePropSprite::Init(int index)
{
	m_PropInfo.set_id(index);
	m_PropInfo.set_isbuy(false);
	if(index ==0)
	{
		m_PropInfo.set_buymoney(1500);
	}
	else if(index ==1)
	{
		m_PropInfo.set_buymoney(500);
	}
	else if(index ==2)
	{
		m_PropInfo.set_buymoney(5000);
	}

	
	m_PropInfo.set_describe("");

	return Init(m_PropInfo,index);
}

bool HSGameScenePropSprite::Init( const message::PropInfo propInfo ,int index)
{
	m_PropInfo.Clear();
	m_PropInfo.CopyFrom(propInfo);

	const char* uiName = CCString::createWithFormat("UI_ChangJingGeBan_x_ChangJingBan%d_ChangJinBiBanXiao",index)->getCString();
	const char* uiMoneyName = CCString::createWithFormat("UI_ChangJingGeBan_x_ChangJingBan%d_ChangJingJiaGeBanXiao",index)->getCString();
	m_pPropFirst = HS_FIND_UI_PANEL_SPRITE(uiName,"x_ChangJinBiBanXiao");
	m_pPropMoneyFirst = HS_FIND_UI_PANEL_SPRITE(uiMoneyName,"x_ChangJingJiaGeBanXiao");
	m_pSelectFrame = HS_FIND_UI_PANEL_SPRITE(uiName,"SceneSelect");
	m_pSelectFrame->setVisible(false);


	CCSize gameGoldPngSize = CCSizeMake(192.f,23.f);
	CCLabelAtlas* buyMoney = CCLabelAtlas::create(CCString::createWithFormat("%d",m_PropInfo.buymoney())->getCString(),"Image/PropMoney.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	CCSize buyMoneySize = buyMoney->getContentSize();

	CCPoint buyMoneyPos;
	buyMoneyPos.x = (gameGoldPngSize.width / 2.f - buyMoneySize.width) / 2.f ;
	buyMoney->setPosition(buyMoneyPos);
	m_pPropMoneyFirst->addChild(buyMoney);	

	//propFirst->setColor(ccc3(255,0,0));
	//propMoneyFirst->setColor(ccc3(255,255,0));	

	CCString* fileName = CCString::createWithFormat("Image/BuyProp/GameSceneProp/%d.png",m_PropInfo.id());
	bool isOk = this->initWithFile(fileName->getCString());
	this->setPosition(HS_SizeHalf_Point(m_pPropFirst->getContentSize()));
	m_pPropFirst->addChild(this);

	const char* frameNodeName = CCString::createWithFormat("UI_ChangJingGeBan_x_ChangJingBan%d",index)->getCString();
	m_pFrameNode = HS_FIND_UI_PANEL(frameNodeName);

	this->schedule(schedule_selector(HSGameScenePropSprite::Update));

	return isOk;
}

bool HSGameScenePropSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) ) return false;
	/**
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBuyPropLayer* layer = dynamic_cast<HSBuyPropLayer*>((dynamic_cast<HSBuyPropScene*>(scene))->getChildByTag(HS_BASE_TAG));
	if (layer)
	{
		if(layer->m_pDialogNode->isVisible() == true)
		{
			return false;
		}
	}*/

	HSSoundManage::ShareSoundManage()->PlayerEffect("botton");
	
	if (HSGameScenePropSprite::s_lastSelectedGameSceneFrameNode != m_pFrameNode)
	{
		if (HSGameScenePropSprite::s_lastSelectedGameSceneFrameNode)
		{
			s_lastSelectedGameSceneFrameNode->setScale(1.f);
			s_lastSelectFrameNode->setVisible(false);
		}
		HSGameScenePropSprite::s_lastSelectedGameSceneFrameNode = m_pFrameNode;
		HSGameScenePropSprite::s_lastSelectFrameNode = m_pSelectFrame;
		m_pFrameNode->setScale(1.1f);
		m_pSelectFrame->setVisible(true);		
		s_lastSelectedGameSceneFrameNode->setTag(m_PropInfo.id());
		//HS_GAME_CACHE()->SetUseBackgroundID(m_PropInfo.id());
	}

	if (!m_PropInfo.isbuy())//开启购买对话框
	{
		HSGameScenePropSprite::SetTouchGameScenePropSprite(this);
		m_pSceneDialog = HSBuySceneDialog::create(this);

		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
		HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();
		if (layer && m_pSceneDialog)
		{
			layer->addChild(m_pSceneDialog,10000);
		}
	}

	return true;
}

void HSGameScenePropSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameScenePropSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (HSGraySprite_Type_Gray == GetType())
	{
		return;
	}
}

void HSGameScenePropSprite::onEnter()
{
	HSGraySprite::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void HSGameScenePropSprite::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	HSGraySprite::onExit();
}

HSGameScenePropSprite* HSGameScenePropSprite::GetTouchGameScenePropSprite()
{
	return HSGameScenePropSprite::s_TouchGameScenePropSprite;
}

void HSGameScenePropSprite::SetTouchGameScenePropSprite( HSGameScenePropSprite* scene )
{
	HSGameScenePropSprite::s_TouchGameScenePropSprite = scene;
}

void HSGameScenePropSprite::SetBuy()
{
	HSAssert(&m_PropInfo,"HSGameScenePropSprite cannot be empty");
	
	RecoverProgram(); 
	
	m_PropInfo.set_isbuy(true);

	int index = m_PropInfo.id();

	HS_GAME_CACHE()->SetIsLevelLock(index,false);//此时id和index是一致的
}

void HSGameScenePropSprite::Buy()
{
	HSAssert(&m_PropInfo,"HSGameScenePropSprite cannot be empty");
	
	RecoverProgram();
	
	if(!HS_GAME_CACHE()->AddGold( -m_PropInfo.buymoney()))
	{
		HSMessageBox("Buy failed");
		return;
	}
	
	m_PropInfo.set_isbuy(true);

	int index = m_PropInfo.id();

	HS_GAME_CACHE()->SetIsLevelLock(index,false);//此时id和index是一致的
}

void HSGameScenePropSprite::CallOk(CCObject* obj)
{
	HS_GAME_CACHE()->SetUseBackgroundID(m_PropInfo.id());

	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	
	HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

	layer->removeChild(m_pSceneDialog,true);
	 
}

void HSGameScenePropSprite::CallCancel(CCObject* obj)
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

	layer->removeChild(m_pSceneDialog,true);
}

void HSGameScenePropSprite::Update( float dt )
{
	if (m_PropInfo.isbuy())
	{
		m_pPropMoneyFirst->setVisible(false);
	}
}
