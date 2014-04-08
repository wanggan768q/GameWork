#include "SPX_Action.h"

SPX_Action::SPX_Action()
{
	memset(actionName, 0, sizeof(actionName));
}

SPX_Action::~SPX_Action()
{
	
}

SPX_ErrorCode SPX_Action::ReadData(IO_InputDataStream* stream)
{
	SPX_ErrorCode errorCode;

	int length = stream->ReadByte();
	stream->Read(actionName, length);
	actionName[length] = 0;

	int customDelay = stream->ReadByte();

	errorCode = collide.ReadData(stream);
	if(errorCode != Success)
	{
		return errorCode;
	}

	int sequenceItemCount = stream->ReadShort();

	errorCode = frameSequence.ReadData(stream, sequenceItemCount, customDelay == 1);
	if(errorCode != Success)
	{
		return errorCode;
	}

	return Success;
}
