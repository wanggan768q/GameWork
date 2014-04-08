/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/26   10:37
 *	File base:	HSBattleOverLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBattleOverLayer_H__
#define __HSBattleOverLayer_H__
#pragma once
#include "HSTool.h"
#include "HSBalloonConfig.h"
#include "HSInputDialogLayer.h"

//Layer
class HSBattleOverLayer:public CCLayer
{
public:
	HSBattleOverLayer(void);
	~HSBattleOverLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSBattleOverLayer);

private:
	CCLabelTTF* m_pNo0;
	CCLabelTTF* m_pNo1;
	CCLabelTTF* m_pNo2;
	CCLabelTTF* m_pNo3;
	CCLabelTTF* m_pNo4;

	CCLabelTTF* m_pGameScore;
	CCLabelTTF* m_pGameGold;

	HSCCSprite* m_pGameScoreIcon;
	HSCCSprite* m_pGameGoldIcon ;
	HSCCSprite* m_pGameTimeIcon ;

	const char* m_fontName;

	HSInputDialogLayer* m_inputLayer;

	float m_RankSceneTime;
	bool m_isRankSceneTimeStart;


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

	void LogicOfGameGuide();

	void Show();

	void Updata(float dt);

	void Show(int index,int reviseIndex,unsigned int score);

	HSInputDialogLayer* GetInputLayer();

	void ResponseSearchRank(SearchRankResponse* pMsg);

	//@Call
	void CallPlay(CCObject* obj);

	void CallMenu(CCObject* obj);

	void CallRanking(CCObject* obj);

};

#endif // __HSBattleOverLayer_H____