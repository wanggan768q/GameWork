/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/20   12:11
 *	File base:	HSGameGuide.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameGuide_H__
#define __HSGameGuide_H__
#pragma once
#include "HSBase.h"
#include "HSMath.h"
#include "HSGameGuide.pb.h"
using namespace message;

class HSGameGuide : public CCLayer
{
public:
	HSGameGuide(void);
	~HSGameGuide(void);

private:

	typedef struct _HSListerEvent
	{
		_HSListerEvent()
		{
			pos = CCPointZero;
			rect = CCRectZero;
			isTouch = false;
		}
		void SetRect(const CCRect& guideRect , const CCPoint& point);

		void SetRect(float diameter,const CCPoint& point);

		void SetRect(const CCRect& eventRect);

		CCRect rect;
		CCPoint pos;
		bool isTouch;
	}HSListerEvent;

private:	
	GameGuide_Guide m_currentGuide;

	CCSprite* m_pMode;

	CCLayerColor* m_pMaskLayer;

	CCClippingNode* m_pClippingNode;

	//模板形状
	CCDrawNode* m_pShape;

	//描述信息
	CCSprite* m_pDescribeBigFrame;
	CCSprite* m_pDescribeFrame;
	CCSprite* m_pIndicationSprite;
	CCLabelTTF* m_pDescribeInfo;

	//std::vector<HSListerEvent> m_vListerEvent;
	HSListerEvent m_ListerEvent;

	std::vector<CCNode*> m_nodeList;

	int m_iMaxStep;
	int m_iStepIndex;


public:
	GameGuide* m_pGameGuideData;
	map<int,const GameGuide_BattleLayout_BalloonInfo*> m_balloons;




private:
	void Load();

	bool Read(const char* fileName);

	void ClearScreen();
	
	void DrawRect(const GameGuide_Guide& guide); 

	void DrawRound(const GameGuide_Guide& guide);

	void AddDefaultEvent();

public:
	CREATE_FUNC(HSGameGuide);

	static HSGameGuide* ShaderGameGuide();

	void Destroy();

	virtual bool init();

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void registerWithTouchDispatcher( void );

	int GetCurrentStep();

	int GetCurrentStepID();

	void Pause();

	void Resume(CCNode* pNode);

	void Stop();

	void Run(int index);

	void Run();

	void RuntPrevious();

	void RunNext();

	void Update(float dt);

	bool TriggerEvent(const CCPoint& pos );

	const GameGuide_BattleLayout_BalloonInfo* GetBallonInfo(int key);

};

#endif // __HSGameGuide_H____


