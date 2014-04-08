//
//  HSPlayerActionManager.h
//  HSBalloon_S3
//
//  Created by Ambition on 14-2-26.
//
//

#ifndef __HSBalloon_S3__HSPlayerActionManager__
#define __HSBalloon_S3__HSPlayerActionManager__

#include "HSTool.h"

typedef enum
{
    PLAYER_ACTION_STAND = 0x10, //待机
    PLAYER_ACTION_ATTACK,       //攻击
    PLAYER_ACTION_BEAT,         //被打
    PLAYER_ACTION_KILL,         //必杀
    PLAYER_ACTION_KILL_BEAT,    //必杀 被打
}HSPlayerActionState;


class HSPlayerActionManager : public CCNode
{
    
public:
    HSPlayerActionManager();
    ~HSPlayerActionManager();
    
private:
    CCSprite* m_ps;
    CCSprite* m_ts;
    CCPoint m_psPos,m_tsPos;
    CCSprite* m_kills;
    
    int m_playerImageID,m_targetImageID;
    
    HSPlayerActionState m_playerActionState;
    HSPlayerActionState m_lastPlayerActionState;
    
public:
    static HSPlayerActionManager* Create(int playerImageID , int targetImageID);
    static HSPlayerActionManager* Create(CCLayer* layer);
    
    bool init(int playerImageID , int targetImageID,CCLayer* layer);
    
    void Restore();
    
    void SetActionSate(HSPlayerActionState state);


#pragma mark - PLAYER_ACTION_STAND,       //攻击
    void Run_Action_STAND();
    
    void Run_Action_STAND_Player();
    
    void Run_Action_STAND_Target(bool isHaveAction = true);
    
#pragma mark - PLAYER_ACTION_ATTACK,       //攻击
    void Run_Action_ATTACK();
    
    void Run_Action_ATTACK_01();
    
    void Run_Action_ATTACK_02();
    
    void Run_Action_ATTACK_02_01(CCPoint pos,SEL_CallFunc pNextCall);
    
    void Run_Action_ATTACK_02_02();
    
    void Run_Action_ATTACK_02_03();
    
    void Run_Action_ATTACK_02_04();
    
    void Run_Action_ATTACK_02_05(CCNode* pNode);
    
    
    
#pragma mark - PLAYER_ACTION_BEAT,         //被打
    void Run_Action_BEAT();
    
    void Run_Action_BEAT_01();
    
    void Run_Action_BEAT_01_01();
    
    void Run_Action_BEAT_01_02(CCNode* pNode);
    
    void Run_Action_BEAT_01_03();
    
    void Run_Action_BEAT_01_04();
    
    void Run_Action_BEAT_02();
    
    void Run_Action_BEAT_02_01(CCPoint pos,SEL_CallFunc pNextCall);
    
    void Run_Action_BEAT_02_02();
    
    void Run_Action_BEAT_02_03();
    
    void Run_Action_BEAT_02_04();
    
    void Run_Action_BEAT_02_05();
    
    
    
    
    
#pragma mark - PLAYER_ACTION_KILL,         //必杀
    void Run_Action_KILL();
    
    void Run_Action_KILL_01();
    
    void Run_Action_KILL_02();
    
    void Run_Action_KILL_03();
    
    void Run_Action_KILL_04();
    
    void Run_Action_KILL_05();
    
    void Run_Action_KILL_06();
    
    
    
#pragma mark - PLAYER_ACTION_KILL_BEAT,    //必杀 被打
    void Run_Action_Kill_BEAT();
    
    void Run_Action_Kill_BEAT_01();
    
    void Run_Action_Kill_BEAT_02();
    
    void Run_Action_Kill_BEAT_03();
    
    void Run_Action_Kill_BEAT_04();
    
    void Run_Action_Kill_BEAT_05();
    
    void Run_Action_Kill_BEAT_05_01();
    
    void Run_Action_Kill_BEAT_05_02();
    
    
        
};




































#endif /* defined(__HSBalloon_S3__HSPlayerActionManager__) */
