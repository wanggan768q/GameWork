/********************************************************************
*  Copyright(C) 2013 Zrong ( All rights reserved. )
*	Created:	2013/04/18   14:03
*	File base:	HSCCLayer.h
*	Author:		Ambition
*	
*	Purpose:	
*********************************************************************/
#ifndef __HSCCLayer_H__
#define __HSCCLayer_H__
#pragma once
#include "HSBase.h"
#include "HSMacros.h"
#include "HSCCSprite.h"

class HSCCLayer : public CCLayer
{
public:
	HSCCLayer(void);
	~HSCCLayer(void);

protected:
	CCRect m_clipRect;
	map<string,HSCCSprite*> m_childMap;

public:
	static HSCCLayer* create();
/*

	void HSCCLayer::SetClip(float lx,float ly,float w,float h)
	{
		float scaleX = HS_SCREEN_WIDTH / HS_MAX_IMAGE_W;
		float scaleY = HS_SCREEN_HEIGHT / HS_MAX_IMAGE_H;
		lx = lx * scaleX;
		ly = ly * scaleY;
		w = w * scaleX;
		h = h * scaleY;
		CCPoint position = this->getPosition();
		CCSize size = this->getContentSize();

		CCPoint anchor = this->getAnchorPoint();
		if (anchor.equals(HS_ANCHOR_CENTER))		//HS_ANCHOR_CENTER
		{

			position.x -= size.width / 2.f;
			position.y -= size.height / 2.f;

		}else if(anchor.equals(HS_ANCHOR_LD)){
			//
		}else if(anchor.equals(HS_ANCHOR_LU)){

			position.y -= size.height;

		}else if(anchor.equals(HS_ANCHOR_L_CENTER)){

			position.y -= size.height / 2.f;

		}else if(anchor.equals(HS_ANCHOR_RD)){

			position.x -= size.width;

		}else if(anchor.equals(HS_ANCHOR_RU)){

			position.x -= size.width;
			position.y -= size.height;

		}else if(anchor.equals(HS_ANCHOR_R_CENTER)){

			position.x -= size.width;
			position.y -= size.height / 2.f;

		}else if(anchor.equals(HS_ANCHOR_U_CENTER)){

			position.x -= size.width / 2.f;
			position.y -= size.height;

		}else if(anchor.equals(HS_ANCHOR_D_CENTER)){

			position.x -= size.width / 2.f;

		}

		m_clipRect = CCRectMake(position.x + lx,position.y + ly,w,h);

	}

	virtual void visit()
	{
		glEnable(GL_SCISSOR_TEST);//¿ªÆô²Ã¼ô
		GLint L_X = (GLint)m_clipRect.getMinX();
		GLint L_Y = (GLint)m_clipRect.getMinY();
		GLsizei w = (GLsizei)(m_clipRect.size.width);
		GLsizei h = (GLsizei)(m_clipRect.size.height);
		glScissor(L_X,L_Y,w,h);
		CCLayer::visit();
		glDisable(GL_SCISSOR_TEST);//¹Ø±Õ²Ã¼ô
	}
*/
	void Push(string key,HSCCSprite* child);

	HSCCSprite* Find(string key);

	/*
	virtual void addChild(CCNode * child)
	{
	CCLayer::addChild(child);
	}
	virtual void addChild(CCNode * child, int zOrder)
	{
	CCLayer::addChild(child,zOrder);
	}
	virtual void addChild(CCNode* child, int zOrder, int tag)

	{

	CCLayer::addChild(child,zOrder,tag);

	}
	*/

};

#endif // __HSCCLayer_H____

