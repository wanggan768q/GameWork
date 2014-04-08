#include "HSPairSystemScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSSocketTemp.h"

int HSPairSystemLayer::S_CURRENT_ROOM_ID = 0;
bool HSPairSystemLayer::S_IS_CREATE_BATTLE_SERVER = false;

//Layer
HSPairSystemLayer::HSPairSystemLayer(void)
{
    m_pSelfReady = m_pTargetReady = NULL;
    
    m_pTIcon = NULL;
    m_pTFigure = NULL;
    m_pTName = NULL;
    m_pTSuccessionwincount = NULL;
    m_pTWinAndLose = NULL;
    m_pTargetPanelLoding = NULL;
}

HSPairSystemLayer::~HSPairSystemLayer(void)
{
    
}

bool HSPairSystemLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
    Load();
	//this->setTouchEnabled(true);
    
	//this->setIsKeypadEnabled(true);
    
	return true;
}

void HSPairSystemLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/PairSystem.data","Image/",this);

    //目标面板
    m_pTargetPanel = HS_FIND_UI_PANEL("UI_Duifangxinxiban");
    m_pTargetPanel->setVisible(false);
    
    //目标面板loding
    m_pTargetPanelLoding = HS_FIND_UI_PANEL_SPRITE("UI_Loading", "Loading");
    CCRotateBy* pRota = CCRotateBy::create(4, 360);
    m_pTargetPanelLoding->runAction(CCRepeatForever::create(pRota));
    
    //显示金币
    this->addChild(HSShowGlobal::create());
    
    //显示体力
    m_pShowEndurance = HSShowEndurance::create();
    this->addChild(m_pShowEndurance);
    
    //显示道具
    this->addChild(HSReadyProp::create());
    
    //显示自己信息
    this->ShowSlefInfo();
    
    if(HS_GAME_CACHE()->m_lastTargetUUID == HS_TARGET_TARGET().uid())
    {
        m_pTargetPanel->setVisible(true);
        m_pTargetPanelLoding->setVisible(false);
        //显示对方信息
        this->ShowTargetInfo();
    }
    
    //购买体力
    HS_SET_MENU_TARGET("UI_Benfangxinxiban_Nailijishiqi_Nailizengjia", this, HSPairSystemLayer::Call_BuyEndurance);
    //取消
    HS_SET_MENU_TARGET("UI_Benfangxinxiban_Quxiao", this, HSPairSystemLayer::Call_Cancel);
    
    //是否进入战斗服务器
    {
      if(!HSPairSystemLayer::S_IS_CREATE_BATTLE_SERVER)
      {
          HSPairSystemLayer::S_IS_CREATE_BATTLE_SERVER = true;
          
          CCDelayTime* delay = CCDelayTime::create(0.001);
          CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSPairSystemLayer::Call_SendFightingRequest));
          this->runAction(CCSequence::create(delay,call,NULL));
      }else{
          HSRequest::ShareRequest()->SendTargetInfoRequest(0);
      }
    }
}

void HSPairSystemLayer::Call_SendFightingRequest()
{
    HS_GAME_CACHE()->m_pTargetInfoResponse->Clear();
    
    HSRequest::ShareRequest()->SendFightingRequest();
}

void HSPairSystemLayer::ShowSlefInfo()
{
    UserBasicInfo info = HS_GAME_CACHE_DATA()->userinfo();
    
    //头像
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Benfangtouxiang", "Pipeitouxiang");
        CCString* pFileName = CCString::createWithFormat("Image/%d.png",info.iconid());
        CCSprite* pS = HSCCSprite::create(pFileName->getCString());
        pS->setPosition(pNode->getAnchorPointInPoints());
        pNode->addChild(pS);
        CC_SAFE_RELEASE_NULL(pFileName);
    }
    //形象
    {
        CCNode* pNode = HS_FIND_UI_PANEL("UI_Benfangxinxiban_Benfangxingxiang");
        CCString* pStr = CCString::createWithFormat("Image/%d_ME.png",info.figureid());
        HSCCSprite* pS = HSCCSprite::create(pStr->getCString());
        pNode->addChild(pS);
        CC_SAFE_RELEASE_NULL(pStr);
    }
    //姓名
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Benfangxinxiban_Benfangyonghuming", "Pipeiyonghuming");
        CCLabelTTF* ttf = CCLabelTTF::create(info.name().c_str(), HS_FONT_HuaKang, 20, pNode->getContentSize(), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        ttf->setPosition(pNode->getAnchorPointInPoints());
        pNode->addChild(ttf);
    }
    //连胜
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Benfangxinxiban_Benfangliansheng", "Pipeishengfudiban");
        CCString* pStr = CCString::createWithFormat("%d 场",info.successionwincount());
        CCLabelTTF* ttf = CCLabelTTF::create(pStr->getCString(), HS_FONT_HuaKang, 20, pNode->getContentSize(), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        ttf->setPosition(pNode->getAnchorPointInPoints());
        pNode->addChild(ttf);
        CC_SAFE_RELEASE_NULL(pStr);
    }
    //胜负
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Benfangxinxiban_Benfangshengfudiban", "Pipeishengfudiban");
        CCString* pStr = CCString::createWithFormat("%d 胜 %d 负",info.wincount(),info.losecount());
        CCLabelTTF* ttf = CCLabelTTF::create(pStr->getCString(), HS_FONT_HuaKang, 20, pNode->getContentSize(), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        ttf->setPosition(pNode->getAnchorPointInPoints());
        pNode->addChild(ttf);
        CC_SAFE_RELEASE_NULL(pStr);
    }
    //准备 字样
    {
        m_pSelfReady = HS_FIND_UI_PANEL_SPRITE("UI_Benfangxinxiban_Benfangzhunbei", "Pipeizhunbeizhuangtai");
        m_pSelfReady->setVisible(false);
        HS_SET_MENU_TARGET("UI_Benfangxinxiban_Zhunbei", this, HSPairSystemLayer::Call_Ready);
        
        this->SetIsAllowReady(false);
    }
    
    //目标 准备 字样
    {
        m_pTargetReady = HS_FIND_UI_PANEL_SPRITE("UI_Duifangxinxiban_Duifangzhunbei", "Pipeizhunbeizhuangtai");
        m_pTargetReady->setVisible(false);
    }
    
}

void HSPairSystemLayer::ShowTargetInfo()
{
    UserBasicInfo info = HS_TARGET_TARGET();
    
//    if(info.uid().size() < 32)
//    {
//        return;
//    }
    
    //头像
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Duifangxinxiban_Duifangtouxiang", "Pipeitouxiang");
        CCString* pFileName = CCString::createWithFormat("Image/%d.png",info.iconid());
        if(!m_pTIcon)
        {
            m_pTIcon = HSCCSprite::create(pFileName->getCString());
            m_pTIcon->setPosition(pNode->getAnchorPointInPoints());
            pNode->addChild(m_pTIcon);
        }else{
            m_pTIcon->setDisplayFrame(HS_RP_GetSpriteFrame(pFileName->getCString()));
        }
        CC_SAFE_RELEASE_NULL(pFileName);
    }
    //形象
    {
        CCNode* pNode = HS_FIND_UI_PANEL("UI_Duifangxinxiban_Duifangxingxiang");
        CCString* pFileName = CCString::createWithFormat("Image/%d_T_ME.png",info.figureid());
        if(!m_pTFigure)
        {
            m_pTFigure = HSCCSprite::create(pFileName->getCString());
            pNode->addChild(m_pTFigure);
        }else{
            m_pTFigure->setDisplayFrame(HS_RP_GetSpriteFrame(pFileName->getCString()));
        }
        CC_SAFE_RELEASE_NULL(pFileName);
    }
    //姓名
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Duifangxinxiban_Duifangyonghuming", "Pipeiyonghuming");
        if(!m_pTName)
        {
            m_pTName = CCLabelTTF::create(info.name().c_str(), HS_FONT_HuaKang, 20, pNode->getContentSize(), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
            m_pTName->setPosition(pNode->getAnchorPointInPoints());
            pNode->addChild(m_pTName);
        }else{
            m_pTName->setString(info.name().c_str());
        }
        
    }
    //连胜
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Duifangxinxiban_Duifangliansheng", "Pipeishengfudiban");
        CCString* pStr = CCString::createWithFormat("%d 场",info.successionwincount());
        if(!m_pTSuccessionwincount)
        {
            m_pTSuccessionwincount = CCLabelTTF::create(pStr->getCString(), HS_FONT_HuaKang, 20, pNode->getContentSize(), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
            m_pTSuccessionwincount->setPosition(pNode->getAnchorPointInPoints());
            pNode->addChild(m_pTSuccessionwincount);
        }else{
            m_pTSuccessionwincount->setString(pStr->getCString());
        }
        
        CC_SAFE_RELEASE_NULL(pStr);
    }
    //胜负
    {
        CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Duifangxinxiban_Duifangshengfudiban", "Pipeishengfudiban");
        CCString* pStr = CCString::createWithFormat("%d 胜 %d 负",info.wincount(),info.losecount());
        if(!m_pTWinAndLose)
        {
            m_pTWinAndLose = CCLabelTTF::create(pStr->getCString(), HS_FONT_HuaKang, 20, pNode->getContentSize(), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
            m_pTWinAndLose->setPosition(pNode->getAnchorPointInPoints());
            pNode->addChild(m_pTWinAndLose);
        }else{
            m_pTSuccessionwincount->setString(pStr->getCString());
        }
        CC_SAFE_RELEASE_NULL(pStr);
    }
    
}

void HSPairSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSPairSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    m_pShowEndurance->SubEndurance();
	return false;
}

void HSPairSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSPairSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSPairSystemLayer::keyBackClicked()
{
    
}
void HSPairSystemLayer::keyMenuClicked()
{
    
}

void HSPairSystemLayer::Call_Ready(CCObject* obj)
{
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }
    
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(obj);
    if (item)
    {
        item->setEnabled(false);
    }
    HSAssert(m_pSelfReady, "准备 字样");
    m_pSelfReady->setVisible(!m_pSelfReady->isVisible());
    
    //发送准备消息
    HSRequest::ShareRequest()->SendBattleReadyRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str(),BattleReadyRequest_TYPE_ACTION_ACTION_READY);
    
    //禁用 购买金币
    CCMenu* pBuyGold = HS_FIND_UI_MENU("UI_Tongyongjinbilan_Jinbizengjiaanniu");
    pBuyGold->setEnabled(false);
    //禁用 购买体力
    CCMenu* pBuyEndurance = HS_FIND_UI_MENU("UI_Benfangxinxiban_Nailijishiqi_Nailizengjia");
    pBuyEndurance->setEnabled(false);
    
}

void HSPairSystemLayer::Call_BuyEndurance(CCObject* obj)
{
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }
}

void HSPairSystemLayer::Call_Cancel(CCObject* obj)
{
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }
    if(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().size() > 0)
    {
        HSRequest::ShareRequest()->SendPlayerDisengageRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
    }else{
        HSSocket* s = HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle);
        if(s)
        {
            s->Closed(Close_Active);
            HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
        }
        HS_GO_SCENE(HS_SCENE_StartGameScene);
    }
}

void HSPairSystemLayer::SetIsAllowReady(bool b)
{
    CCArray* pReadyArray = HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent( "UI_Benfangxinxiban_Zhunbei" );
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pReadyArray,pObj)
    {
        CCMenuItemToggle* pItem = dynamic_cast<CCMenuItemToggle*>(pObj);
        if (pItem)
        {
            if(b)
            {
                pItem->setSelectedIndex(1);
                pItem->setEnabled(true);
            }else{
                pItem->setSelectedIndex(0);
                pItem->setEnabled(false);
            }
            
        }
    }
    
}

//服务器通知 目标准备
void HSPairSystemLayer::ResponseBattleReady(BattleReadyResponse* pMsg)
{
    if(pMsg->player() == BattleReadyResponse_RequestPlayer_TARGET)
    {
        m_pTargetReady->setVisible(true);
    }else if(pMsg->player() == BattleReadyResponse_RequestPlayer_SELF){
        
    }
}
//服务器通知 开始战斗
void HSPairSystemLayer::ResponseStartBattle(NotifyStartBattle* pMsg)
{
	if(pMsg->type() == NotifyStartBattle_NotifyType_START)
	{
        HS_GAME_CACHE()->m_lastTargetUUID = HS_TARGET_TARGET().uid();
		HS_GO_SCENE(HS_SCENE_BattleScene);
	}
	else
	{
        HSMessageBox("开始战斗 失败");
	}
}

//自动主动离开 或者 被动离开
void HSPairSystemLayer::ResponsePlayerDisengage(PlayerDisengageResponse* pMsg)
{
    
	if(pMsg->status() == PlayerDisengageResponse_DisengageStatus_INITIATIVE)
	{
        CCLog("主动退出");
        
		HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed(Close_Active);
		HSSocketPool::ShareSocketPool()->SetPingLongLink(false);

        HSPairSystemLayer::S_IS_CREATE_BATTLE_SERVER = false;
        HS_GO_SCENE(HS_SCENE_StartGameScene);
	}
	else if(pMsg->status() == PlayerDisengageResponse_DisengageStatus_REACTIVE)
	{
        CCLog("被动退出");
        
		HS_MUTABLE_TARGET_TARGET()->Clear();
        
		this->SetIsAllowReady(false);
        
        m_pTargetPanel->setVisible(false);
        m_pTargetPanelLoding->setVisible(true);
        
		HSRequest::ShareRequest()->SendTargetInfoRequest(HSPairSystemLayer::S_CURRENT_ROOM_ID);
	}

}
//配对成功
void HSPairSystemLayer::ResponseTargetInfo(TargetInfoResponse* pMsg)
{
    this->SetIsAllowReady(true);
    
	if(HS_GAME_CACHE()->m_pTargetInfoResponse->status()== TargetInfoResponse_FindStatus_SUCCESS)
	{
        
		HSSocketPool::ShareSocketPool()->SetPingLongLink(true);
        
        m_pTargetPanel->setVisible(true);
        this->ShowTargetInfo();
        
        m_pTargetPanelLoding->setVisible(false);
	}
	else if(HS_GAME_CACHE()->m_pTargetInfoResponse->status() == TargetInfoResponse_FindStatus_NOMONEY)
	{
        
	}
	else if(HS_GAME_CACHE()->m_pTargetInfoResponse->status() == TargetInfoResponse_FindStatus_FAIL)
	{
		HSMessageBox("配对失败");
	}
}

void HSPairSystemLayer::ResponseFighting(FightingResponse* pMsg)
{
    FightingResponse_RequestStatus status = pMsg->status();
	if(status == FightingResponse_RequestStatus_SUCCESS)
	{
		NetAddress address= pMsg->address();
		std::string ip = address.ip();
		int port = address.port();
		HSSocketPool::ShareSocketPool()->AddSocket(S_L_Battle,ip.c_str(),CCString::createWithFormat("%d",port)->getCString(),HSSocket_Type_SOCKET);
        
        HSRequest::ShareRequest()->SendTargetInfoRequest(0);
	}
	else if(status == FightingResponse_RequestStatus_FAIL)
	{
		HSMessageBox("进入战斗服失败");
	}
}



















//Scene
HSPairSystemScene::HSPairSystemScene(void)
{
	this->m_pHSPairSystemLayer = NULL;
}

HSPairSystemScene::~HSPairSystemScene(void)
{
}

bool HSPairSystemScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->m_pHSPairSystemLayer = HSPairSystemLayer::create();
	this->addChild(this->m_pHSPairSystemLayer,HS_BASE_TAG,HS_BASE_TAG);
    
	return true;
}


