/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-12
 *	File base:	HSFigureSystem.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSFigureSystemScene_H__
#define __HSFigureSystemScene_H__
#pragma once
#include "HSTool.h"
#include "HSShowGlobal.h"

//Layer
class HSFigureSystemLayer : public CCLayer
{
public:
	HSFigureSystemLayer(void);
	~HSFigureSystemLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSFigureSystemLayer);
    
private:
	void Load();
    void UpdataPlayerInfo();
    
    void SetIsShowLoading(bool b);
    
    void Call_Back(CCObject* obj);
    void Call_StartBattle(CCObject* obj);
    void Call_Upgrade(CCObject* obj);
    void Call_ChangeFigure(CCObject* obj);
    
    void Updata(float dt);
    
public:
    void ResponseGameUpgradeFigureLevel(GameUpgradeFigureLevelResponse* pMsg);
    void ResponseValidateStrength(ValidateStrengthResponse* pMsg);
    
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
    
private:
    CCSprite* m_pFigureIcon;
    CCSprite* m_pFigure;
    CCLabelTTF* m_pFigureName;
    CCLabelTTF* m_pFigureLevel;
    CCLabelTTF* m_pFigureDescribe;
    CCLabelTTF* m_pUpgradeGold;
    SPX_Sprite* m_pSpx;
    UserBasicInfo m_userBaseInfo;
    CCNode* m_pLoding;
    
};




//Scene
class HSFigureSystemScene : public CCScene
{
public:
	HSFigureSystemScene(void);
	~HSFigureSystemScene(void);
private:
	HSFigureSystemLayer* m_pHSFigureSystemLayer;
    
public:
	virtual bool init();
	CREATE_FUNC(HSFigureSystemScene);
    
	inline HSFigureSystemLayer* GetHSFigureSystemLayer(){return this->m_pHSFigureSystemLayer;};
    
};






#endif /* defined(__HSFigureSystemScene_H__) */





