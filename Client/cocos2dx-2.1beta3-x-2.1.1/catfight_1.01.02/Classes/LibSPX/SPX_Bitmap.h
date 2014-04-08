#ifndef __SPX_BITMAP_H__
#define __SPX_BITMAP_H__

#include "SPX_Base.h"

class SPX_Bitmap
{
public:
	SPX_Bitmap();
	~SPX_Bitmap();

public:
	SPX_ErrorCode ReadData(IO_InputDataStream* stream);

public:
	int bitmapID;
	int width;
	int height;
	SPX_Texture* texture;
};

#endif /*__SPX_BITMAP_H__*/
