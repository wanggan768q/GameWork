#ifndef __SPX_DATA_H__
#define __SPX_DATA_H__

#include "SPX_Bitmap.h"
#include "SPX_TileSet.h"
#include "SPX_Frame.h"
#include "SPX_Action.h"

class SPX_Data
{
public:
	typedef vector<SPX_Bitmap> BitmapList;
	typedef vector<SPX_TileSet> TileSetList;
	typedef vector<SPX_Frame> FrameList;
	typedef vector<SPX_Action> ActionList;

public:
	SPX_Data();
	~SPX_Data();

public:
	SPX_ErrorCode ReadData(SPX_String name);

public:
	SPX_ErrorCode LoadBitmap(SPX_String name);
	SPX_ErrorCode LoadBitmap(SPX_String filename, int bitmapID);
	int GetActionIndex(const char* actionName);
	int GetBitmapIndex(int bitmapID);

public:
	SPX_String name;
	int refs;
	BitmapList bitmapList;
	TileSetList tileSetList;
	FrameList frameList;
	ActionList actionList;
};

#endif /*__SPX_DATA_H__*/
