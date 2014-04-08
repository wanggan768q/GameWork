#include "HSEffectItemSprite.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameCache.h"
#include "HSBattleScene.h"
#include "HSJava.h"
#include "MobClickCpp.h"
HSEffectItemSprite::HSEffectItemSprite()
{
	m_pLockSprite = NULL;
	lock = false;
}

HSEffectItemSprite::~HSEffectItemSprite()
{

}

void HSEffectItemSprite::UserEffect()
{
    
	string did = HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str();
	const char* uid = HS_TARGET_TARGET().uid().c_str();
    
    if(HS_IsLanMode())
    {
        if(did!="")
        {
            HS_GAME_CACHE()->m_pUseBuffRequest->set_did(did.c_str());
            HS_GAME_CACHE()->m_pUseBuffRequest->set_targetuid(uid);
            HS_GAME_CACHE()->m_pUseBuffRequest->set_propid(m_propInfo.id());
            
        }else{
            NotifyChangeBuff* pMsg = NotifyChangeBuff::default_instance().New();
            
            pMsg->set_targetuid(HS_TARGET_SELF().uid());
            pMsg->set_attacker("myself");
            pMsg->set_propid(m_propInfo.id());
            
            HS_GAME_CACHE()->ResponseNotifyChangeBuff(pMsg);
            CC_SAFE_DELETE(pMsg);
        }

        
    }else{
        if(HS_ONLINE)
        {
            if(did!="")
            {
                if(HS_GAME_CACHE()->GetGold()>=HS_GAME_CACHE()->roomGold+m_propInfo.gold())
                {
                    eventDict dict;
                    //CCLog("=================================BuffName(%s)",m_propInfo.name().c_str());
                    dict["name"] = m_propInfo.name().c_str();
                    MobClickCpp::event("HSUseBuff",&dict);
                    HSRequest::ShareRequest()->SendUseBuffRequest(did.c_str(),uid,m_propInfo.id());
                    HS_GAME_CACHE()->m_pUseBuffRequest->set_did(did.c_str());
                    HS_GAME_CACHE()->m_pUseBuffRequest->set_targetuid(uid);
                    HS_GAME_CACHE()->m_pUseBuffRequest->set_propid(m_propInfo.id());
                }
                else
                {
                    HSJava::ShaderJava()->Pay(HS_GAME_CACHE()->roomGold+m_propInfo.gold()-HS_GAME_CACHE()->GetGold());
                }
            }
            else
            {
                
                eventDict dict;
                dict["name"] = "nodid";
                MobClickCpp::event("HSUseBuff",&dict);
                CCLog("=================================no did");
            }
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
    }
	
    
    
	//HS_GO_SCENE(HS_SCENE_GamePairScene);
	CCScene * scene = CCDirector::sharedDirector()->getRunningScene();
    
	HSBattleScene* battleScene = (HSBattleScene*)scene;
    
	if(battleScene)
	{
		HSBattleOverLayer* battleOverLayer = battleScene->GetHSBattleOverLayer();
        
		battleOverLayer->Return();
	}

}

bool HSEffectItemSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!ContainsTouchLocation(pTouch)||!this->isVisible() )
        return false;
    
    if(lock)
	{
		return true;
	}

    UserEffect();
    

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

	this->initWithFile(CCString::createWithFormat("Image/%s",m_propInfo.localname().c_str())->getCString());
	this->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
	//this->setAnchorPoint(HS_ANCHOR_LU);

	
	uint level = HS_TARGET_SELF().level();
	level = 20;
	if(level >= m_propInfo.unlocklevel())
	{
		this->lock = false;
		this->RecoverProgram();
	}
	else//����
	{
		this->lock = true;
		m_pLockSprite = HSCCSprite::create("Image/lock.png");
		m_pLockSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
		this->addChild(m_pLockSprite);
		this->GrayProgram();
	}
	const char* panleName; 
	
    panleName = CCString::createWithFormat("UI_Hebing_Jinbidiandikuang%d",index)->getCString();
	
	HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE(panleName,"Jinbidiandikuang");
	
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
	CCSize gameGoldPngSize = CCSizeMake(320.f,45.f);
	CCLabelAtlas* m_pGameGold = CCLabelAtlas::create(CCString::createWithFormat("%d",propInfo.gold())->getCString(),"Image/moneyNumber.png",gameGoldPngSize.width / 11,gameGoldPngSize.height,'0');
	m_pGameGold->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pGameGold->setPosition(gameGoldFrame->getAnchorPointInPoints());
	
	m_pGameGold->setScaleX(0.7f);
	gameGoldFrame->addChild(m_pGameGold);
	return true;
}

