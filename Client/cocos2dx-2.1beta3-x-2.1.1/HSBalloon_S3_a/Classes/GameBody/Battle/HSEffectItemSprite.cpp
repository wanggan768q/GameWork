#include "HSEffectItemSprite.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameCache.h"
#include "HSBattleScene.h"
HSEffectItemSprite::HSEffectItemSprite()
{
	m_pLockSprite = NULL;
	lock = false;
}

HSEffectItemSprite::~HSEffectItemSprite()
{

}

bool HSEffectItemSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!ContainsTouchLocation(pTouch)||!this->isVisible() ) return false;

	if (HS_IsRunGameGuide())
	{
		return true;
	}

	if(lock)
	{
		//提示是否解锁
		return true;
	}
	
	const char* did = HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str();
	const char* uid = HS_TARGET_TARGET().uid().c_str();
	//使用道具
	if(HS_ONLINE)
	{
		HSRequest::ShareRequest()->SendUseBuffRequest(did,uid,m_propInfo.id());
		HS_GAME_CACHE()->m_pUseBuffRequest->set_did(did);
		HS_GAME_CACHE()->m_pUseBuffRequest->set_targetuid(uid);
		HS_GAME_CACHE()->m_pUseBuffRequest->set_propid(m_propInfo.id());
	}
	else
	{
		NotifyChangeBuff* pMsg = NotifyChangeBuff::default_instance().New();

		pMsg->set_targetuid(HS_TARGET_SELF().uid());
		pMsg->set_attacker("myself");
		pMsg->set_propid(m_propInfo.id());

		HS_GAME_CACHE()->ResponseNotifyChangeBuff(pMsg);
		CC_SAFE_DELETE(pMsg);
	}


	//HS_GO_SCENE(HS_SCENE_GamePairScene);
	CCScene * scene = CCDirector::sharedDirector()->getRunningScene();

	HSBattleScene* battleScene = (HSBattleScene*)scene;

	if(battleScene)
	{
		HSBattleOverLayer* battleOverLayer = battleScene->GetHSBattleOverLayer();

		battleOverLayer->Return();
	}
	return true;
}

void HSEffectItemSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void HSEffectItemSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void HSEffectItemSprite::onEnter()
{
	if (HS_IsRunGameGuide())
	{
		return; 
	}
	HSGraySprite::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
}

void HSEffectItemSprite::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	HSGraySprite::onExit();
}

HSEffectItemSprite* HSEffectItemSprite::create( const message::PropInfo propInfo ,int index )
{
	HSEffectItemSprite* sprite = new HSEffectItemSprite;
	if(sprite && sprite->Init(propInfo,index))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSEffectItemSprite::Init(const message::PropInfo propInfo,int index)
{
	m_propInfo.Clear();
	m_propInfo.CopyFrom(propInfo);

	this->initWithFile(CCString::createWithFormat("Image/prop/%s",m_propInfo.localname().c_str())->getCString());
	this->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
	//this->setAnchorPoint(HS_ANCHOR_LU);

	
	uint level = HS_TARGET_SELF().level();
	level = 20;
	if(level >= m_propInfo.unlocklevel())
	{
		this->lock = false;
		this->RecoverProgram();
	}
	else//加锁
	{
		this->lock = true;
		m_pLockSprite = CCSprite::create("Image/pair/selectProp/lock.png");
		m_pLockSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
		this->addChild(m_pLockSprite);
		this->GrayProgram();
	}
	const char* panleName; 
	if(index ==0)
	{
		panleName = "UI_Hebing_Jinbidiandikuang";
	}
	else
	{
		panleName = CCString::createWithFormat("UI_Hebing_Jinbidiandikuang%d",index)->getCString();
	}
	HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE(panleName,"Jinbidiandikuang");
	
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
	CCSize gameGoldPngSize = CCSizeMake(320.f,45.f);
	CCLabelAtlas* m_pGameGold = CCLabelAtlas::create(CCString::createWithFormat("%d",propInfo.gold())->getCString(),"Image/moneyNumber.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
	m_pGameGold->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pGameGold->setPosition(ccp(gameGoldFrameSize.width/2,gameGoldFrameSize.height/2));
	
	m_pGameGold->setScaleX(0.7f);
	gameGoldFrame->addChild(m_pGameGold);
	return true;
}

