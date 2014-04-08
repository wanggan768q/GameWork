#ifndef __IO_ISERIALIZE__H__
#define __IO_ISERIALIZE__H__

#include "IO_InputDataStream.h"
#include "IO_OutputDataStream.h"

class IO_ISerialize
{
public:
	virtual bool Read(IO_InputDataStream* stream){ return false; }
	virtual bool Write(IO_OutputDataStream* stream){ return false; }
};

#endif /*__IO_ISERIALIZE__H__*/
