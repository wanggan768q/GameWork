
/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/26   10:34
 *	File base:	HSBattlePauseLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBattlePauseLayer_H__
#define __HSBattlePauseLayer_H__
#pragma once
#include "HSTool.h"
#include "HSGameCache.h"
//Layer
class HSBattlePauseLayer:public CCLayer
{
public:
	HSBattlePauseLayer(void);
	~HSBattlePauseLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSBattlePauseLayer);

private:
	CCSprite* m_pFirstLine;
	CCSprite* m_pSecondLine;
	CCSprite* m_pThirdLine;
	CCSprite* m_pFourthLine;
	CCSprite* m_pFifthLine;

	CCSprite* m_pFirstLinePoint;
	CCSprite* m_pSecondLinePoint;
	CCSprite* m_pThirdLinePoint;
	CCSprite* m_pFourthLinePoint;
	CCSprite* m_pFifthLinePoint;

	HSCCSprite* m_pHighestScoreFrame;

	CCLabelAtlas* m_pMaxHighestScoreLable;

	CCLabelTTF* m_pCurrentRank;

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	virtual void setVisible(bool visible);

	void Updata(float dt);

	void ShowTendMap();

	//@ Call
	void CallPlay(CCObject* obj);

	void CallMusicMenu(CCObject* obj);

	void CallSoundEffectMenu(CCObject* obj);

	void CallAboutMenu(CCObject* obj);



	//@ Network
	void ResponseSearchRank(SearchRankResponse* pMsg);
	
};

#endif // __HSBattlePauseLayer_H____
