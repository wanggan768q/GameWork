/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/12/06   10:58
 *	File base:	HSCCSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSCCSprite_H__
#define __HSCCSprite_H__
#pragma once
#include "HSMacros.h"


class HSCCSprite : public cocos2d::CCSprite
{
public:
	HSCCSprite(void);
	~HSCCSprite(void);

protected:
	CCRect m_clipRect;


public:
	//static HSCCSprite* node();
	static HSCCSprite* create(const char *pszFileName);
	static HSCCSprite* create(CCTexture2D *pTexture);
	static HSCCSprite* create(const char* pszFileName,CCRect rect);
	static HSCCSprite* create(CCSpriteFrame* pSpriteFrame);
    static HSCCSprite* create(CCSprite* pSprite);
    
    virtual bool initWithFile(const char *pszFilename);
    
    bool initWithSprite(CCSprite* pSprite);
    

	virtual bool ContainsTouchLocation( CCTouch* touch );

	HSCCSprite* Copy();
};
#endif // __HSCCSprite_H____

