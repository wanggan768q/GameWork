#ifndef __IO_EXCEPTION_H__
#define __IO_EXCEPTION_H__

#include "IO_Base.h"

class IO_Exception
{
public:
	IO_Exception(int code){ this->code = code; }

public:
	int code;
};

#endif /*__IO_EXCEPTION_H__*/
