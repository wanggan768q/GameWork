#include "SPX_Frame.h"
#include "SPX_TileElement.h"

SPX_Frame::SPX_Frame()
{
	flagBits = 0;
}

SPX_Frame::~SPX_Frame()
{
	for(uint i = 0; i < elementList.size(); ++i)
	{
		delete elementList[i];
	}

	elementList.clear();
}

SPX_ErrorCode SPX_Frame::ReadData(IO_InputDataStream* stream)
{

	SPX_ErrorCode errorCode;

	flagBits = stream->ReadInt();

	errorCode = aabb.ReadData(stream);
	if(errorCode != Success)
	{
		return errorCode;
	}

	int elementCount = stream->ReadShort();
	elementList.resize(elementCount);
	for(int i = 0; i < elementCount; ++i)
	{
		int elementType = stream->ReadByte();
		if(elementType == Tile)
		{
			SPX_TileElement* element = new SPX_TileElement();
			if(element == NULL)
			{
				return OutOfMemory;
			}

			element->flagBits = stream->ReadInt();
			element->tileSetIndex = stream->ReadShort();
			element->tileIndex = stream->ReadShort();
			element->transform = stream->ReadByte();
			element->x = stream->ReadShort();
			element->y = stream->ReadShort();

			elementList[i] = element;
		}
		else
		{
			return NotImplemented;
		}
	}

	int collideCount = stream->ReadShort();
	collideList.resize(collideCount);
	for(int i = 0; i < collideCount; ++i)
	{
		errorCode = collideList[i].ReadData(stream);
		if(errorCode != Success)
		{
			return errorCode;
		}
	}


	return Success;
}

void SPX_Frame::Render(SPX_Sprite* sprite, float x, float y)
{
	for(uint i = 0; i < elementList.size(); ++i)
	{
		SPX_Element* element = elementList[i];
		if(element != NULL)
		{
			element->Render(sprite, x, y);
		}
	}
}
