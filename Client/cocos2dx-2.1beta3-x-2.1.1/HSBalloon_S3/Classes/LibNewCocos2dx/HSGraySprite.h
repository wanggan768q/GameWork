/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/26   20:10
 *	File base:	HSGraySprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGraySprite_H__
#define __HSGraySprite_H__
#pragma once
#include "HSCCSprite.h"

typedef enum
{
	HSGraySprite_Type_Normal = 0x0ef,
	HSGraySprite_Type_Gray,
}HSGraySpriteType;


class HSGraySprite : public HSCCSprite
{
public:
	HSGraySprite(void);
	~HSGraySprite(void);

private:
	HSGraySpriteType m_SpriteType;
    std::string m_fileName;
public:
	static HSGraySprite* create(const char* pszFileName);

    virtual bool initWithFile(const char *pszFilename);
    
	bool initWithTexture(cocos2d::CCTexture2D* pTexture, const cocos2d::CCRect&  tRect);

	virtual void draw();

	void RecoverProgram();	//恢复正常色

	void GrayProgram();	//灰度图

	virtual bool ContainsTouchLocation( CCTouch* touch );

	HSGraySpriteType GetType();
    
    const char* GetFileName();
};

#endif // __HSGraySprite_H____

