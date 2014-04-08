#ifndef __SPX_ACTION_H__
#define __SPX_ACTION_H__

#include "SPX_FrameSequence.h"
#include "SPX_Rect.h"

class SPX_Action
{
public:
	SPX_Action();
	~SPX_Action();

public:
	SPX_ErrorCode ReadData(IO_InputDataStream* stream);

public:
	char actionName[128];
	SPX_Rect collide;
	SPX_FrameSequence frameSequence;
};

#endif /*__SPX_ACTION_H__*/
