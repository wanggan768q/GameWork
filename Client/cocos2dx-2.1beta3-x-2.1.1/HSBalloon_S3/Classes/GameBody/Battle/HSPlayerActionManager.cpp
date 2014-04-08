//
//  HSPlayerActionManager.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 14-2-26.
//
//

#include "HSPlayerActionManager.h"
#include "HSBattleScene.h"

HSPlayerActionManager::HSPlayerActionManager()
{
    m_ps = NULL;
    m_ts = NULL;
    
    m_playerActionState = PLAYER_ACTION_STAND;
    m_lastPlayerActionState = m_playerActionState;
}

HSPlayerActionManager::~HSPlayerActionManager()
{
    
}

HSPlayerActionManager* HSPlayerActionManager::Create(int playerImageID , int targetImageID)
{
    HSPlayerActionManager* manager = new HSPlayerActionManager;
    
    if (manager && manager->init(playerImageID, targetImageID,NULL))
    {
        manager->autorelease();
        return manager;
    }
    CC_SAFE_DELETE(manager);
    return NULL;
}

HSPlayerActionManager* HSPlayerActionManager::Create(CCLayer* layer)
{
    HSPlayerActionManager* manager = new HSPlayerActionManager;
    
    if (manager && manager->init(1000, 1000,layer))
    {
        manager->autorelease();
        return manager;
    }
    CC_SAFE_DELETE(manager);
    return NULL;
}

bool HSPlayerActionManager::init(int playerImageID , int targetImageID,CCLayer* layer)
{
    m_playerImageID = playerImageID;
    m_targetImageID = targetImageID;
    
    CCNode* psParent = HS_FIND_UI_PANEL("UI_TOUXIANG0");
    CCNode* tsParent = HS_FIND_UI_PANEL("UI_TOUXIANG1");
    
    CCString* psFileName = CCString::createWithFormat("Image/%d_STAND.png",m_playerImageID);
    CCString* tsFileName = CCString::createWithFormat("Image/%d_T_STAND.png",m_targetImageID);
    
    
    m_ps = HSCCSprite::create(psFileName->getCString());
    m_ts = HSCCSprite::create(tsFileName->getCString());
    m_ps->setAnchorPoint(HS_ANCHOR_D_CENTER);
    m_ts->setAnchorPoint(HS_ANCHOR_D_CENTER);
    psParent->addChild(m_ps);
    tsParent->addChild(m_ts);
    
    m_psPos = m_ps->getPosition();
    m_tsPos = m_ts->getPosition();
    
    CC_SAFE_RELEASE_NULL(psFileName);
    CC_SAFE_RELEASE_NULL(tsFileName);
    
    
    
    //隐藏 必杀 背景
    m_kills = HS_FIND_UI_PANEL_SPRITE("UI_Zhandouzhanxianbeijing","Bishazhanxianbeijing");
    m_kills->setVisible(false);
    HSAssert(m_kills, "");
    
    
    Run_Action_STAND();
    
    return true;
}

void HSPlayerActionManager::Restore()
{
    m_kills->setVisible(false);
    HS_GET_BattleLayer()->GetOtherScreen()->setVisible(true);
    
    m_ps->setPosition(m_psPos);
    m_ps->setScale(1);
    
    m_ts->setPosition(m_tsPos);
    m_ts->setScale(1);
    
}

void HSPlayerActionManager::SetActionSate(HSPlayerActionState state)
{
    m_playerActionState = state;
    this->Restore();
    
    switch (m_playerActionState)
    {
        case PLAYER_ACTION_STAND:
        {
            Run_Action_STAND();
        }
            break;
        case PLAYER_ACTION_ATTACK:
        {
            Run_Action_ATTACK();
        }
            break;
        case PLAYER_ACTION_BEAT:
        {
            Run_Action_BEAT();
        }
            break;
        case PLAYER_ACTION_KILL:
        {
            Run_Action_KILL();
        }
            break;
        case PLAYER_ACTION_KILL_BEAT:
        {
            Run_Action_Kill_BEAT();
        }
            break;
        default:
            break;
    }
}


#pragma mark - PLAYER_ACTION_STAND,       //攻击
void HSPlayerActionManager::Run_Action_STAND()
{
    Run_Action_STAND_Player();
    
    Run_Action_STAND_Target();
}

void HSPlayerActionManager::Run_Action_STAND_Player()
{
    CCString* psFileName = CCString::createWithFormat("Image/%d_STAND.png",m_playerImageID);
    m_ps->setDisplayFrame(HS_RP_GetSpriteFrame(psFileName->getCString()));
}

void HSPlayerActionManager::Run_Action_STAND_Target(bool isHaveAction /*= true*/)
{
    CCString* tsFileName = CCString::createWithFormat("Image/%d_T_STAND.png",m_targetImageID);
    m_ts->setDisplayFrame(HS_RP_GetSpriteFrame(tsFileName->getCString()));
    
    if(isHaveAction)
    {
        CCScaleTo* pScaleTo = CCScaleTo::create(0.2f, 0.9);
        CCDelayTime* pDelay = CCDelayTime::create(0.3);
        CCScaleTo* pScaleTo1 = CCScaleTo::create(0.2f, 1);
        CCSequence* pSeq = CCSequence::create(pScaleTo,pDelay,pScaleTo1,(CCActionInterval*)pDelay->copy()->autorelease(),NULL);
        CCRepeatForever* pFor = CCRepeatForever::create(pSeq);
        pFor->setTag(PLAYER_ACTION_STAND);
        m_ts->runAction(pFor);
    }
}

#pragma mark - PLAYER_ACTION_ATTACK,       //攻击

void HSPlayerActionManager::Run_Action_ATTACK()
{
    m_ps->stopAllActions();
    m_ts->stopAllActions();
    
    CCString* psFileName = CCString::createWithFormat("Image/%d_STAND.png",m_playerImageID);
    CCString* tsFileName = CCString::createWithFormat("Image/%d_T_STAND.png",m_targetImageID);
    
    m_ps->setDisplayFrame(HS_RP_GetSpriteFrame(psFileName->getCString()));
    m_ts->setDisplayFrame(HS_RP_GetSpriteFrame(tsFileName->getCString()));
    
    
    CCMoveTo* pMove = CCMoveTo::create(0.2,ccp(m_psPos.x + 10,m_psPos.y));
    CCScaleTo* pScaleTo = CCScaleTo::create(0.2, 0.9);
    CCDelayTime* pDelayTime = CCDelayTime::create(0.3);
    
    CCSpawn* pSpawn = CCSpawn::create(pMove,pScaleTo,NULL);
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_ATTACK_01));
    
    CCSequence* pSeq = CCSequence::create(pSpawn,pDelayTime,pCall,NULL);
    m_ps->runAction(pSeq);
    
}


void HSPlayerActionManager::Run_Action_ATTACK_01()
{
    CCString* tsFileName = CCString::createWithFormat("Image/%d_T_BEAT.png",m_targetImageID);
    m_ts->setDisplayFrame(HS_RP_GetSpriteFrame(tsFileName->getCString()));
    
    CCMoveTo* pMove = CCMoveTo::create(0.1,ccp(m_tsPos.x + 10,m_tsPos.y - 5));
    
    CCMoveTo* R = CCMoveTo::create(0.025f,ccp( m_tsPos.x + 3,m_tsPos.y));
    CCMoveTo* L = CCMoveTo::create(0.025f,ccp(m_tsPos.x - 3,m_tsPos.y));
    CCMoveTo* U = CCMoveTo::create(0.025f,ccp(m_tsPos.x,m_tsPos.y + 3));
    CCMoveTo* D = CCMoveTo::create(0.025f,ccp(m_tsPos.x,m_tsPos.y - 3));
    
    CCDelayTime* pDelayTime = CCDelayTime::create(0.3);
    //CCCallFunc* PCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_ATTACK_02));
    
    // 目标边震动 边播放 三个受伤点
    CCRepeat* pRepeat = CCRepeat::create(CCSequence::create(R,L,U,D,NULL), 2);
    CCSequence* pSeq = CCSequence::create(pMove,pRepeat,pDelayTime,NULL);
    //CCSpawn* pSpawn = CCSpawn::create(pSeq,PCall);
    m_ts->runAction(pSeq);
    
    Run_Action_ATTACK_02();
}

void HSPlayerActionManager::Run_Action_ATTACK_02()
{
    Run_Action_ATTACK_02_01(ccp(50,50),callfunc_selector(HSPlayerActionManager::Run_Action_ATTACK_02_02));
}

void HSPlayerActionManager::Run_Action_ATTACK_02_01(CCPoint pos,SEL_CallFunc pNextCall)
{
    CCSprite* pBeatEffect = HSCCSprite::create("Image/BeatEffect.png");
    pBeatEffect->setPosition(pos);
    //pBeatEffect->setAnchorPoint(HS_ANCHOR_D_CENTER);
    m_ts->addChild(pBeatEffect);
    
    CCDelayTime* pDelayTime = CCDelayTime::create(0.1);
    CCCallFuncN* pCall_01 = CCCallFuncN::create(this, callfuncN_selector(HSPlayerActionManager::Run_Action_ATTACK_02_05));
    CCCallFunc* pCall_02 = CCCallFunc::create(this, pNextCall);
    CCSequence* pSeq = CCSequence::create(pDelayTime,pCall_01,pCall_02,NULL);
    
    pBeatEffect->runAction(pSeq);
}

void HSPlayerActionManager::Run_Action_ATTACK_02_02()
{
    Run_Action_ATTACK_02_01(ccp(60 ,40 ),callfunc_selector(HSPlayerActionManager::Run_Action_ATTACK_02_03));
}

void HSPlayerActionManager::Run_Action_ATTACK_02_03()
{
    Run_Action_ATTACK_02_01(ccp(70,50),callfunc_selector(HSPlayerActionManager::Run_Action_ATTACK_02_04));
}

void HSPlayerActionManager::Run_Action_ATTACK_02_04()
{
    //目标移回到 目标的原始位置
    CCDelayTime* pDelay = CCDelayTime::create(0.3);
    CCMoveTo* pMove = CCMoveTo::create(0.3,m_tsPos);
    CCCallFunc* pCallStand = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_STAND_Target));
    m_ts->runAction(CCSequence::create(pDelay,pMove,pCallStand,NULL));
    
    
    //自己移回到 自己的原始位置
    CCDelayTime* pPlayerDelay = CCDelayTime::create(0.2);
    CCMoveTo* pMovePlayerPos = CCMoveTo::create(0.3,m_psPos);
    CCScaleTo* pScaleTo = CCScaleTo::create(0.3f, 1);
    CCSpawn* pSpawn = CCSpawn::create(pMovePlayerPos,pScaleTo,NULL);
    m_ps->runAction(CCSequence::create(pPlayerDelay,pSpawn,NULL));
    
    
}

void HSPlayerActionManager::Run_Action_ATTACK_02_05(CCNode* pNode)
{
    pNode->removeFromParent();
}


#pragma mark - PLAYER_ACTION_BEAT,         //被打
void HSPlayerActionManager::Run_Action_BEAT()
{
    m_ts->stopAllActions();
    
    CCMoveTo* pMove = CCMoveTo::create(0.2,ccp(m_tsPos.x - 10,m_psPos.y));
    CCScaleTo* pScaleTo = CCScaleTo::create(0.2, 1.1);
    
    CCSpawn* pSpawn = CCSpawn::create(pMove,pScaleTo,NULL);
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_BEAT_01));
    CCSequence* pSeq = CCSequence::create(pSpawn,pCall,NULL);
    m_ts->runAction(pSeq);
}

void HSPlayerActionManager::Run_Action_BEAT_01()
{
    //打火球
    Run_Action_BEAT_01_01();
}

void HSPlayerActionManager::Run_Action_BEAT_01_01()
{
    CCSprite* pFireBall_01 = HSCCSprite::create("Image/FireBall.png");
    CCSprite* pFireBall_02 = HSCCSprite::create("Image/FireBall.png");
    CCSprite* pFireBall_03 = HSCCSprite::create("Image/FireBall.png");
    CCSprite* pFireBall_04 = HSCCSprite::create("Image/FireBall.png");
    
    pFireBall_01->setPosition(ccp(44,48));
    pFireBall_02->setPosition(ccp(44,48));
    pFireBall_03->setPosition(ccp(44,48));
    pFireBall_04->setPosition(ccp(44,48));
    
    pFireBall_01->setScale(0.2);
    pFireBall_02->setScale(0.2);
    pFireBall_03->setScale(0.2);
    pFireBall_04->setScale(0.2);
    
    pFireBall_01->setRotation(30);
    pFireBall_02->setRotation(135);
    pFireBall_03->setRotation(-15);
    pFireBall_04->setRotation(-105);
    
    m_ts->addChild(pFireBall_01);
    m_ts->addChild(pFireBall_02);
    m_ts->addChild(pFireBall_03);
    m_ts->addChild(pFireBall_04);
    
    CCMoveTo* pMove_01 = CCMoveTo::create(0.6, ccp(-137,168));
    CCMoveTo* pMove_02 = CCMoveTo::create(0.6, ccp(166,167));
    CCMoveTo* pMove_03 = CCMoveTo::create(0.6, ccp(-185,-10));
    CCMoveTo* pMove_04 = CCMoveTo::create(0.6, ccp(86,-88));
    
    CCScaleTo* pScale_01 = CCScaleTo::create(0.6, 1);
    CCScaleTo* pScale_02 = CCScaleTo::create(0.6, 1);
    CCScaleTo* pScale_03 = CCScaleTo::create(0.6, 1);
    CCScaleTo* pScale_04 = CCScaleTo::create(0.6, 1);
    
    CCSpawn* pSpawn_01 = CCSpawn::create(pMove_01,pScale_01,NULL);
    CCSpawn* pSpawn_02 = CCSpawn::create(pMove_02,pScale_02,NULL);
    CCSpawn* pSpawn_03 = CCSpawn::create(pMove_03,pScale_03,NULL);
    CCSpawn* pSpawn_04 = CCSpawn::create(pMove_04,pScale_04,NULL);
    
    CCCallFuncN* pCall = CCCallFuncN::create(this, callfuncN_selector(HSPlayerActionManager::Run_Action_BEAT_01_02));
    CCCallFunc* pCall_01 = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_BEAT_01_03));
    CCCallFunc* pCall_02 = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_BEAT_01_04));
    
    pFireBall_01->runAction(CCSequence::create(pSpawn_01,pCall,NULL));
    pFireBall_02->runAction(CCSequence::create(pSpawn_02,(CCActionInterval*)pCall->copy()->autorelease(),NULL));
    pFireBall_03->runAction(CCSequence::create(pSpawn_03,(CCActionInterval*)pCall->copy()->autorelease(),NULL));
    pFireBall_04->runAction(CCSequence::create(pSpawn_04,(CCActionInterval*)pCall->copy()->autorelease(),pCall_02,pCall_01,NULL));
    
}

void HSPlayerActionManager::Run_Action_BEAT_01_02(CCNode* pNode)
{
    pNode->removeFromParent();
}

void HSPlayerActionManager::Run_Action_BEAT_01_03()
{
    CCString* psFileName = CCString::createWithFormat("Image/%d_BEAT.png",m_playerImageID);
    m_ps->setDisplayFrame(HS_RP_GetSpriteFrame(psFileName->getCString()));
    
    CCMoveTo* pMove = CCMoveTo::create(0.1, ccp(m_psPos.x - 20,m_psPos.y));
    
    CCMoveTo* R = CCMoveTo::create(0.025f,ccp(m_psPos.x + 6,m_psPos.y));
    CCMoveTo* L = CCMoveTo::create(0.025f,ccp(m_psPos.x - 6,m_psPos.y));
    CCMoveTo* U = CCMoveTo::create(0.025f,ccp(m_psPos.x,m_psPos.y + 6));
    CCMoveTo* D = CCMoveTo::create(0.025f,ccp(m_psPos.x,m_psPos.y - 6));
    CCDelayTime* pDelayTime = CCDelayTime::create(0.3);
    
    CCRepeat* pRepeat = CCRepeat::create(CCSequence::create(R,L,U,D,NULL), 2);
    CCSequence* pSeq = CCSequence::create(pMove,pRepeat,pDelayTime,NULL);
    m_ps->runAction(pSeq);
    
    Run_Action_BEAT_02();
}

void HSPlayerActionManager::Run_Action_BEAT_01_04()
{
    CCMoveTo* pMove_01 = CCMoveTo::create(0.2,ccp(m_psPos.x - 20,m_psPos.y));
    CCScaleTo* pScaleTo_01 = CCScaleTo::create(0.2, 1.1);
    CCSpawn* pSpawn_01 = CCSpawn::create(pMove_01,pScaleTo_01,NULL);
    m_ps->runAction(pSpawn_01);
}

void HSPlayerActionManager::Run_Action_BEAT_02()
{
    Run_Action_BEAT_02_01(ccp(50,50),callfunc_selector(HSPlayerActionManager::Run_Action_BEAT_02_02));
}

void HSPlayerActionManager::Run_Action_BEAT_02_01(CCPoint pos,SEL_CallFunc pNextCall)
{
    CCSprite* pBeatEffect = HSCCSprite::create("Image/BeatEffect.png");
    pBeatEffect->setPosition(pos);
    m_ps->addChild(pBeatEffect);
    
    CCDelayTime* pDelayTime = CCDelayTime::create(0.1);
    CCCallFuncN* pCall_01 = CCCallFuncN::create(this, callfuncN_selector(HSPlayerActionManager::Run_Action_ATTACK_02_05));
    CCCallFunc* pCall_02 = CCCallFunc::create(this, pNextCall);
    CCSequence* pSeq = CCSequence::create(pDelayTime,pCall_01,pCall_02,NULL);
    
    pBeatEffect->runAction(pSeq);
}

void HSPlayerActionManager::Run_Action_BEAT_02_02()
{
    Run_Action_BEAT_02_01(ccp(60 ,40 ),callfunc_selector(HSPlayerActionManager::Run_Action_BEAT_02_03));
}

void HSPlayerActionManager::Run_Action_BEAT_02_03()
{
    Run_Action_BEAT_02_01(ccp(70,50),callfunc_selector(HSPlayerActionManager::Run_Action_BEAT_02_04));
}

void HSPlayerActionManager::Run_Action_BEAT_02_04()
{
    //目标移回到 目标的原始位置
    CCMoveTo* pMove = CCMoveTo::create(0.3,m_tsPos);
    CCScaleTo* pScaleTo = CCScaleTo::create(0.3f, 1);
    CCSpawn* pSpawn_01 = CCSpawn::create(pMove,pScaleTo,NULL);
    CCCallFunc* pCallStand = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_STAND_Target));
    m_ts->runAction(CCSequence::create(pSpawn_01,pCallStand,NULL));
    
    
    //自己移回到 自己的原始位置
    CCDelayTime* pPlayerDelay = CCDelayTime::create(0.3);
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_BEAT_02_05));
    m_ps->runAction(CCSequence::create(pPlayerDelay,pCall,NULL));
    
}

void HSPlayerActionManager::Run_Action_BEAT_02_05()
{
    Run_Action_STAND_Player();
    
    CCMoveTo* pMovePlayerPos = CCMoveTo::create(0.6,m_psPos);
    CCScaleTo* pScaleTo_01 = CCScaleTo::create(0.6f, 1);
    CCSpawn* pSpawn = CCSpawn::create(pMovePlayerPos,pScaleTo_01,NULL);
    m_ps->runAction(CCSequence::create(pSpawn,NULL));
}






#pragma mark - PLAYER_ACTION_KILL,         //必杀

void HSPlayerActionManager::Run_Action_KILL()
{
    //显示 必杀 背景
    m_kills->setVisible(true);
    
    CCMoveTo* pMove = CCMoveTo::create(0.3,ccp(m_psPos.x - 250,m_psPos.y));
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_KILL_01));
    m_ps->runAction(CCSequence::create(pMove,pCall,NULL));
    
}

void HSPlayerActionManager::Run_Action_KILL_01()
{
    //换人物 必杀 形象
    CCString* psFileName = CCString::createWithFormat("Image/%d_KILL.png",m_playerImageID);
    m_ps->setDisplayFrame(HS_RP_GetSpriteFrame(psFileName->getCString()));
    
    CCMoveTo* pMove = CCMoveTo::create(0.3,ccp(m_psPos.x + 50,m_psPos.y));
    CCDelayTime* pDelay = CCDelayTime::create(0.8);
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_KILL_02));
    m_ps->runAction(CCSequence::create(pMove,pDelay,pCall,NULL));
    
}

void HSPlayerActionManager::Run_Action_KILL_02()
{
    m_kills->setVisible(false);
    Run_Action_STAND_Player();
    m_ps->setPosition(m_psPos);
    
    Run_Action_KILL_03();
}

void HSPlayerActionManager::Run_Action_KILL_03()
{
    m_ts->stopAllActions();
    
    CCString* tsFileName = CCString::createWithFormat("Image/%d_T_BEAT.png",m_targetImageID);
    m_ts->setDisplayFrame(HS_RP_GetSpriteFrame(tsFileName->getCString()));
    
    CCMoveTo* pMove = CCMoveTo::create(0.1,ccp(m_tsPos.x + 10,m_tsPos.y - 5));
    
    CCMoveTo* R = CCMoveTo::create(0.025f,ccp( m_tsPos.x + 3,m_tsPos.y));
    CCMoveTo* L = CCMoveTo::create(0.025f,ccp(m_tsPos.x - 3,m_tsPos.y));
    CCMoveTo* U = CCMoveTo::create(0.025f,ccp(m_tsPos.x,m_tsPos.y + 3));
    CCMoveTo* D = CCMoveTo::create(0.025f,ccp(m_tsPos.x,m_tsPos.y - 3));
    
    CCDelayTime* pDelayTime = CCDelayTime::create(0.3);
    CCCallFunc* PCall_01 = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_KILL_04));
    CCCallFunc* PCall_02 = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_KILL_05));
    
    
    // 目标边震动 边播放 三个受伤点
    CCRepeat* pRepeat = CCRepeat::create(CCSequence::create(R,L,U,D,NULL), 2);
    CCSequence* pSeq = CCSequence::create(pMove,pRepeat,PCall_01,pDelayTime,PCall_02,NULL);
    m_ts->runAction(pSeq);
    
    Run_Action_ATTACK_02();
    
}

void HSPlayerActionManager::Run_Action_KILL_04()
{
    Run_Action_STAND_Target();
}

void HSPlayerActionManager::Run_Action_KILL_05()
{
    static int count = 0;
    if(count == 0 || count == 1)
    {
        Run_Action_KILL_03();
        ++count;
    }else{
        count = 0;
        Run_Action_STAND_Target(false);
        CCMoveTo* pMove = CCMoveTo::create(0.1,m_tsPos);
        CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_KILL_06));
        m_ts->runAction(CCSequence::create(pMove,pCall,NULL));
    }
}

void HSPlayerActionManager::Run_Action_KILL_06()
{
    Run_Action_STAND_Target();
}




#pragma mark - PLAYER_ACTION_KILL_BEAT,    //必杀 被打
void HSPlayerActionManager::Run_Action_Kill_BEAT()
{
    m_ts->stopAllActions();
    
    //显示 必杀 图
    m_kills->setVisible(true);
    HS_GET_BattleLayer()->GetOtherScreen()->setVisible(false);
    
    CCMoveTo* pMove = CCMoveTo::create(0.3,ccp(m_tsPos.x + 150,m_tsPos.y));
    CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSPlayerActionManager::Run_Action_Kill_BEAT_01));
    m_ts->runAction(CCSequence::create(pMove,pCall,NULL));
}

void HSPlayerActionManager::Run_Action_Kill_BEAT_01()
{
    CCString* tsFileName = CCString::createWithFormat("Image/%d_T_KILL.png",m_targetImageID);
    m_ts->setDisplayFrame(HS_RP_GetSpriteFrame(tsFileName->getCString()));
    
    CCMoveTo* pMove = CCMoveTo::create(0.2,ccp(m_tsPos.x + 140,m_tsPos.y));
    CCScaleBy* pScale = CCScaleBy::create(0.2,1.2);
    CCSpawn* pSpawn = CCSpawn::create(pMove,pScale,NULL);
    CCDelayTime* pDelayTime = CCDelayTime::create(0.8);
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_Kill_BEAT_02));
    CCSequence* pSeq = CCSequence::create(pSpawn,pDelayTime,pCall,NULL);
    m_ts->runAction(pSeq);
}

void HSPlayerActionManager::Run_Action_Kill_BEAT_02()
{
    CCScaleTo* pScale = CCScaleTo::create(0.2,1);
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_Kill_BEAT_03));
    CCSequence* pSeq = CCSequence::create(pScale,pCall,NULL);
    m_ts->runAction(pSeq);
}

void HSPlayerActionManager::Run_Action_Kill_BEAT_03()
{
    //隐藏 必杀 背景
    m_kills->setVisible(false);
    
    Run_Action_STAND_Target(false);
    
    CCMoveTo* pMove = CCMoveTo::create(0.2,m_tsPos);
    CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_Kill_BEAT_04));
    CCSequence* pSeq = CCSequence::create(pMove,pCall,NULL);
    m_ts->runAction(pSeq);
}

void HSPlayerActionManager::Run_Action_Kill_BEAT_04()
{
    HS_GET_BattleLayer()->GetOtherScreen()->setVisible(true);
    
    Run_Action_STAND_Target();
    
    // 自己 被打
    Run_Action_Kill_BEAT_05();
    
}

void HSPlayerActionManager::Run_Action_Kill_BEAT_05()
{
    CCString* psFileName = CCString::createWithFormat("Image/%d_BEAT.png",m_playerImageID);
    m_ps->setDisplayFrame(HS_RP_GetSpriteFrame(psFileName->getCString()));
    
    CCMoveTo* pMove = CCMoveTo::create(0.1, ccp(m_psPos.x - 20,m_psPos.y));
    
    CCMoveTo* R = CCMoveTo::create(0.025f,ccp(m_psPos.x + 6,m_psPos.y));
    CCMoveTo* L = CCMoveTo::create(0.025f,ccp(m_psPos.x - 6,m_psPos.y));
    CCMoveTo* U = CCMoveTo::create(0.025f,ccp(m_psPos.x,m_psPos.y + 6));
    CCMoveTo* D = CCMoveTo::create(0.025f,ccp(m_psPos.x,m_psPos.y - 6));
    CCDelayTime* pDelayTime = CCDelayTime::create(0.3);
    
    CCCallFunc* PCall_01 = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_Kill_BEAT_05_01));
    CCCallFunc* PCall_02 = CCCallFunc::create(this, callfunc_selector(HSPlayerActionManager::Run_Action_Kill_BEAT_05_02));
    
    CCRepeat* pRepeat = CCRepeat::create(CCSequence::create(R,L,U,D,NULL), 2);
    CCSequence* pSeq = CCSequence::create(pMove,pRepeat,PCall_01,pDelayTime,PCall_02,NULL);
    m_ps->runAction(pSeq);
    
    Run_Action_BEAT_02();
}

void HSPlayerActionManager::Run_Action_Kill_BEAT_05_01()
{
    Run_Action_STAND_Player();
}

void HSPlayerActionManager::Run_Action_Kill_BEAT_05_02()
{
    static int count = 0;
    if(count == 0 || count == 1)
    {
        if(count == 0)
        {
            HS_GET_BattleLayer()->PlayBeatEffect();
        }
        Run_Action_Kill_BEAT_05();
        ++count;
    }else{
        count = 0;
        CCMoveTo* pMove = CCMoveTo::create(0.2,m_psPos);
        m_ps->runAction(pMove);
    }
}







