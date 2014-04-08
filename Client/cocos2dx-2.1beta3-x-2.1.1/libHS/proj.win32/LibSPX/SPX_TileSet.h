#ifndef __SPX_TILESET_H__
#define __SPX_TILESET_H__

#include "SPX_Tile.h"

class SPX_TileSet
{
public:
	enum TileSetType
	{
		Index = 1,
		Clip = 2,
	};

public:
	typedef vector<SPX_Tile> TileList;

public:
	SPX_TileSet();
	virtual ~SPX_TileSet();

public:
	SPX_ErrorCode ReadData(IO_InputDataStream* stream);

public:
	TileSetType type;
	int bitmapID;
	int bitmapIndex;
	int tileWidth;
	int tileHeight;
	int tileColumns;
	int tileRows;
	int tileCount;
	TileList tileList;
};

#endif /*__SPX_TILESET_H__*/

