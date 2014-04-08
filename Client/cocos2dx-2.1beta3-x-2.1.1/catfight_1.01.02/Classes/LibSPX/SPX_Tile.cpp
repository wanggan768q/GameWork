#include "SPX_Tile.h"

SPX_Tile::SPX_Tile()
{

}

SPX_Tile::~SPX_Tile()
{

}

SPX_ErrorCode SPX_Tile::ReadData(IO_InputDataStream* stream)
{
	SPX_ErrorCode errorCode = rect.ReadData(stream);

	if(errorCode != Success)
	{
		return errorCode;
	}

	return Success;
}
