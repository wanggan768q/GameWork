#ifndef __SPX_FRAME_H__
#define __SPX_FRAME_H__

#include "SPX_Element.h"
#include "SPX_Rect.h"

class SPX_Frame
{
public:
	enum ElementType
	{
		Tile = 1,
		Group = 2,
		Shape = 3,
		Text = 4,
	};

public:
	typedef vector<SPX_Element*> ElementList;
	typedef vector<SPX_Rect> RectList;

public: 
	SPX_Frame();
	~SPX_Frame();

public:
	SPX_ErrorCode ReadData(IO_InputDataStream* stream);

public:
	void Render(SPX_Sprite* sprite, float x, float y);

public:
	int flagBits;
	SPX_Rect aabb;
	ElementList elementList;
	RectList collideList;
};

#endif /*__SPX_FRAME_H__*/
