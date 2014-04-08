/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/24   17:53
 *	File base:	HSClippingNode.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSClippingNode_H__
#define __HSClippingNode_H__
#pragma once
#include "HSBase.h"

class HSClippingNode : public CCNode
{
public:
	HSClippingNode(void);
	~HSClippingNode(void);

protected:
	CCNode* m_pStencil;
	GLfloat m_fAlphaThreshold;
	bool    m_bInverted;

public:
	/** Creates and initializes a clipping node without a stencil.
	 */
	static HSClippingNode* create();
	
	/** Creates and initializes a clipping node with an other node as its stencil.
	 The stencil node will be retained.
	 */
	static HSClippingNode* create(CCNode *pStencil);
	
	/** Initializes a clipping node without a stencil.
	 */
	virtual bool init();
	
	/** Initializes a clipping node with an other node as its stencil.
	 The stencil node will be retained, and its parent will be set to this clipping node.
	 */
	virtual bool init(CCNode *pStencil);
	
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	virtual void visit();
	
	/** The CCNode to use as a stencil to do the clipping.
	 The stencil node will be retained.
	 This default to nil.
	 */
	CCNode* getStencil() const;
	void setStencil(CCNode *pStencil);
	
	/** The alpha threshold.
	 The content is drawn only where the stencil have pixel with alpha greater than the alphaThreshold.
	 Should be a float between 0 and 1.
	 This default to 1 (so alpha test is disabled).
	 */
	GLfloat getAlphaThreshold() const;
	void setAlphaThreshold(GLfloat fAlphaThreshold);
	
	/** Inverted. If this is set to YES,
	 the stencil is inverted, so the content is drawn where the stencil is NOT drawn.
	 This default to NO.
	 */
	bool isInverted() const;
	void setInverted(bool bInverted);
};
#endif // __HSClippingNode_H____


