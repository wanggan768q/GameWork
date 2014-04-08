#ifndef __SPX_FRAMESEQUENCE_H__
#define __SPX_FRAMESEQUENCE_H__

#include "SPX_SequenceItem.h"

class SPX_FrameSequence
{
public:
	typedef vector<SPX_SequenceItem> SequenceItemList;

public:
	SPX_FrameSequence();
	~SPX_FrameSequence();

public:
	SPX_ErrorCode ReadData(IO_InputDataStream* stream, int itemCount, bool customDelay);

public:
	SequenceItemList itemList;
};

#endif /*__SPX_FRAMESEQUENCE_H__*/
