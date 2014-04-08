#include "SPX_Bitmap.h"

SPX_Bitmap::SPX_Bitmap()
{
	bitmapID = 0;
	width = 0;
	height = 0;
	texture = NULL;
}

SPX_Bitmap::~SPX_Bitmap()
{
	if(texture != NULL)
	{
		SPX_DeleteTexture(texture);
		texture = NULL;
	}
}

SPX_ErrorCode SPX_Bitmap::ReadData(IO_InputDataStream* stream)
{
	bitmapID = stream->ReadShort();
	width = stream->ReadShort();
	height = stream->ReadShort();
	return Success;
}
