#ifndef __SPX_ELEMENT_H__
#define __SPX_ELEMENT_H__

#include "SPX_Base.h"

class SPX_Sprite;

class SPX_Element
{
public:
	SPX_Element();
	virtual ~SPX_Element();

public:
	virtual void Render(SPX_Sprite* sprite, float x, float y);

public:
	int flagBits;
	float x;
	float y;
	int transform;
};

#endif /*__SPX_ELEMENT_H__*/
