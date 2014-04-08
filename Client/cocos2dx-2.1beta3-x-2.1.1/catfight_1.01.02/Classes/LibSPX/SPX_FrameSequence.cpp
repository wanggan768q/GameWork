#include "SPX_FrameSequence.h"

SPX_FrameSequence::SPX_FrameSequence()
{

}

SPX_FrameSequence::~SPX_FrameSequence()
{

}

SPX_ErrorCode SPX_FrameSequence::ReadData(IO_InputDataStream* stream, int itemCount, bool customDelay)
{

	itemList.resize(itemCount);

	if(customDelay)
	{
		for(int i = 0; i < itemCount; ++i)
		{
			itemList[i].frameIndex = stream->ReadShort();
			itemList[i].frameDelay = stream->ReadInt();
		}
	}
	else
	{
		for(int i = 0; i < itemCount; ++i)
		{
			itemList[i].frameIndex = stream->ReadShort();
		}
	}


	return Success;
}
