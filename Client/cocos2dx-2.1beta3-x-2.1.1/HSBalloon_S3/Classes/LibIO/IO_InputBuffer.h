#ifndef __IO_INPUTBUFFER_H__
#define __IO_INPUTBUFFER_H__

#include "IO_InputStream.h"

class IO_InputBuffer : public IO_InputStream
{
public:
	IO_InputBuffer();
	virtual ~IO_InputBuffer();

public:
	bool Open(const void* buffer, int size);
	void Close();
	void* GetBase();
	void* GetBuffer();

public:
	virtual int Read();
	virtual int Read(void* buffer, int size);

public:
	virtual int Seek(int offset, int origin);
	virtual int GetPosition();
	virtual int GetInputSize();

private:
	char* buffer;
	int maxSize;
	int position;
};

#endif /*__IO_INPUTBUFFER_H__*/


