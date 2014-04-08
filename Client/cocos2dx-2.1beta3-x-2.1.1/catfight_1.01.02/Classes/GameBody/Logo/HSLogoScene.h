#ifndef __HSLogoScene_H__
#define __HSLogoScene_H__
#pragma once
#include "HSTool.h"

class HSLogoLayer :public CCLayer
{
public:
	HSLogoLayer(void);
	~HSLogoLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSLogoLayer);
private:
	void Load();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};

class HSLogoScene:public CCScene
{
public:
	HSLogoScene(void);
	~HSLogoScene(void);
public:
	HSLogoLayer* hsLogoLayer;
public:
	virtual bool init();
	CREATE_FUNC(HSLogoScene);

};
#endif
