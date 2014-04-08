#ifndef __SPX_TILEELEMENT_H__
#define __SPX_TILEELEMENT_H__

#include "SPX_Element.h"

class SPX_TileElement : public SPX_Element
{
public:
	SPX_TileElement();
	virtual ~SPX_TileElement();

public:
	virtual void Render(SPX_Sprite* sprite, float x, float y);

public:
	int tileSetIndex;
	int tileIndex;
};

#endif /*__SPX_TILEELEMENT_H__*/
