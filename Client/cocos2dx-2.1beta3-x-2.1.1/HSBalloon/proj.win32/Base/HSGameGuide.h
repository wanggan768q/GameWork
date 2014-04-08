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

		void SetRect(const CCRect& eventRect)
		{
			rect = eventRect;
		}

		CCRect rect;
		CCPoint pos;
		bool isTouch;
	}HSListerEvent;

private:
	GameGuide* m_pGameGuideData;
	
	const GameGuide_Guide* m_pCurrentGuide;

	CCSprite* m_pMode;

	CCLayerColor* m_pMaskLayer;

	CCClippingNode* m_pClippingNode;

	//模板形状
	CCDrawNode* m_pShape;

	//描述信息
	CCSprite* m_pDescribeBigFrame;
	CCSprite* m_pDescribeFrame;
	CCLabelTTF* m_pDescribeInfo;

	std::vector<HSListerEvent> m_vListerEvent;

	std::vector<CCNode*> m_nodeList;

	int m_iMaxStep;
	int m_iStepIndex;

private:
	void Load();

	bool Read(const char* fileName);

	void ClearScreen();
	
	void DrawRect(const GameGuide_Guide_Rect& rect , const GameGuide_Guide_Point& point);

	void DrawRound(float diameter,const GameGuide_Guide_Point& point);

	void AddDefaultEvent();

public:
	CREATE_FUNC(HSGameGuide);

	static HSGameGuide* ShaderGameGuide();

	virtual bool init();

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void registerWithTouchDispatcher( void );

	int GetCurrentStep();

	void Pause();

	void Resume(CCNode* pNode);

	void Stop();

	void Run(int index);

	void Run();

	void RuntPrevious();

	void Update(float dt);

	bool TriggerEvent(const CCPoint& pos );

	


};

#endif // __HSGameGuide_H____


