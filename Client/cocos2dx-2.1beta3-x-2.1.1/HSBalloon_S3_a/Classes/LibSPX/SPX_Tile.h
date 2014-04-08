#ifndef __SPX_TILE_H__
#define __SPX_TILE_H__

#include "SPX_Rect.h"

class SPX_Tile
{
public:
	SPX_Tile();
	~SPX_Tile();

public:
	SPX_ErrorCode ReadData(IO_InputDataStream* stream);

public:
	SPX_Rect rect;
};

#endif /*__SPX_TILE_H__*/
