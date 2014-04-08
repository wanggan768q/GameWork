#ifndef __IO_OUTPUTSTREAM_H__
#define __IO_OUTPUTSTREAM_H__

#include "IO_Base.h"

class IO_OutputStream
{
public:
	IO_OutputStream(){}
	virtual ~IO_OutputStream(){}

public:
	virtual int Write(int ch) = 0;
	virtual int Write(const void* buffer, int size);

public:
	virtual int GetOutputSize(){ return -1; }
};

#endif /*__IO_OUTPUTSTREAM_H__*/

