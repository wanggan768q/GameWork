//
//  HSFeedbackLayer.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-15.
//
//

#ifndef __HSBalloon_S3__HSFeedbackLayer__
#define __HSBalloon_S3__HSFeedbackLayer__
#include "HSTool.h"
#include "HSReadUI.h"
#include "HSGameSceneJumpManage.h"

class HSFeedbackLayer : public CCLayer
{
private:
    HSFeedbackLayer();
public:
    ~HSFeedbackLayer();
    
public:
    static HSFeedbackLayer* create(const char* pText,CCNode* pShareLayer = NULL,GameSceneID sceneID = HS_SCENE_UNKOWN);
    virtual bool init(const char* pText,CCNode* pShareLayer,GameSceneID sceneID);
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
private:
	//@ Init
	void Load();
    
public:
    void Call_Back(CCObject* pObj);
    
private:
    GameSceneID m_goSceneID;
    CCNode* m_pShareLayer;
};
#endif /* defined(__HSBalloon_S3__HSFeedbackLayer__) */
