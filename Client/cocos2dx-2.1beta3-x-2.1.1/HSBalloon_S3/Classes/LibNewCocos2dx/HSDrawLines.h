/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/02/25   13:31
 *	File base:	HSDrawLines.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSDrawLines_H__
#define __HSDrawLines_H__
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define POINT_NUM 16
#define MIDDLE_POINT_R 255
#define MIDDLE_POINT_G 255
#define MIDDLE_POINT_B 255
#define MIDDLE_POINT_A 255
#define TOP_POINT_R	255
#define TOP_POINT_G	200
#define TOP_POINT_B	0
#define TOP_POINT_A	255
#define BOTTOM_POINT_R 255
#define BOTTOM_POINT_G 255
#define BOTTOM_POINT_B 0
#define BOTTOM_POINT_A 255

class HSDrawLines : public CCLayerColor
{
public:
	HSDrawLines(void);
	~HSDrawLines(void);

private:
	CCPoint m_pointPath[POINT_NUM];
	CCParticleSystem* m_pParticle;
	unsigned long m_Index;
	bool m_bTouched;
	CCPoint m_touchBeganPoint;
	CCPoint m_touchEndpoint;
	long m_timer;

public:

	virtual bool init();
	CREATE_FUNC(HSDrawLines);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void draw();
	void Line();
	void ErasureNail();
	void Triangle(CCPoint* vertex,CCPoint p1,CCPoint p2,GLfloat w);
};

#endif // __HSDrawLines_H____

