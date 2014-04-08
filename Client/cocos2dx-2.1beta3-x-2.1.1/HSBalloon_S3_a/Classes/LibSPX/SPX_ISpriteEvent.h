#ifndef __SPX_ISPRITEEVENT_H__
#define __SPX_ISPRITEEVENT_H__

#include "SPX_Base.h"

class SPX_Sprite;
class SPX_Element;

class SPX_ISpriteEvent
{
public:
	virtual void OnStartSpriteDraw(SPX_Sprite* sprite){}
	virtual void OnEndSpriteDraw(SPX_Sprite* sprite){}

public:
	virtual void OnStartElementDraw(SPX_Sprite* sprite, SPX_Element* element){}
	virtual void OnEndElementDraw(SPX_Sprite* sprite, SPX_Element* element){}
};

#endif /*__SPX_ISPRITEEVENT_H__*/
