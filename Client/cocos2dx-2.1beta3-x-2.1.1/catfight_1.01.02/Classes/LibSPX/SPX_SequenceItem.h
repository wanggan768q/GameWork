#ifndef __SPX_SEQUENCEITEM_H__
#define __SPX_SEQUENCEITEM_H__

#include "SPX_Base.h"

class SPX_SequenceItem
{
public:
	SPX_SequenceItem();
	~SPX_SequenceItem();

public:
	short frameIndex;
	int frameDelay;
};

#endif /*__SPX_SEQUENCEITEM_H__*/
