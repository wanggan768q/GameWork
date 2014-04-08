#ifndef __IO_OUTPUTBUFFER_H__
#define __IO_OUTPUTBUFFER_H__

#include "IO_OutputStream.h"

class IO_OutputBuffer : public IO_OutputStream
{
public:
	IO_OutputBuffer();
	virtual ~IO_OutputBuffer();

public:
	bool Open(int initSize, int growSize);
	void Close();
	void* GetBase();
	void* GetBuffer();
	int GetPosition() { return position; } 
	int Seek(int offset, int origin);
	void SetSize(int size);
	int GetMaxSize();

public:
	virtual int Write(int ch);
	virtual int Write(const void* buffer, int size);

public:
	virtual int GetOutputSize();

private:
	void Grow(int newSize);

private:
	char* buffer;
	int size;
	int position;
	int growSize;
	int maxSize;
};

#endif /*__IO_OUTPUTBUFFER_H__*/


