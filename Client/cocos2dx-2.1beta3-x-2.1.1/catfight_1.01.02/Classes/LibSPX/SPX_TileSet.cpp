#include "SPX_TileSet.h"

SPX_TileSet::SPX_TileSet()
{
	type = Index;
	bitmapID = 0;
	bitmapIndex = 0;
	tileWidth = 0;
	tileHeight = 0;
	tileColumns = 0;
	tileRows = 0;
	tileCount = 0;
}

SPX_TileSet::~SPX_TileSet()
{
	tileList.clear();
}

SPX_ErrorCode SPX_TileSet::ReadData(IO_InputDataStream* stream)
{

	type = (TileSetType)stream->ReadByte();
	bitmapID = stream->ReadShort();

	if(type == Index)
	{
		tileWidth = stream->ReadShort();
		tileHeight = stream->ReadShort();
		tileColumns = stream->ReadShort();
		tileRows = stream->ReadShort();
		tileCount = tileColumns * tileRows;
	}
	else if(type == Clip)
	{
		tileCount = stream->ReadShort();
		tileList.resize(tileCount);

		for(int i = 0; i < tileCount; ++i)
		{
			SPX_ErrorCode errorCode = tileList[i].ReadData(stream);
			if(errorCode != Success)
			{
				return errorCode;
			}
		}
	}
	else
	{
		return NotImplemented;
	}


	return Success;
}

