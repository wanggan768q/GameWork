//
//  HSRankUpLayer.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-13.
//
//

#ifndef __HSBalloon_S3__HSRankUpLayer__
#define __HSBalloon_S3__HSRankUpLayer__
#include "HSTool.h"
#include "HSReadUI.h"

class HSRankUpLayer : public CCLayer
{
public:
    HSRankUpLayer();
    ~HSRankUpLayer();
    
public:
	CREATE_FUNC(HSRankUpLayer);
    virtual bool init();
    
private:
	//@ Init
	void Load();
    
public:
    void Call_Up();
    void Call_SendWeiBo(CCObject* pObj);
    void Call_Back(CCObject* pObj);
    
private:
    CCNode* m_pSun;
    CCNode* m_pStar;
    CCNode* m_pRankUP;
    FriendListResponse_PlayerInfo* m_pFriendInfo;
    
    int m_selfGameScore;
    
};

#endif /* defined(__HSBalloon_S3__HSRankUpLayer__) */
