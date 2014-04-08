#ifndef __IO_CIRCULARBUFFER_H__
#define __IO_CIRCULARBUFFER_H__

#include "IO_InputStream.h"
#include "IO_OutputStream.h"

class IO_CircularBuffer : public IO_InputStream, public IO_OutputStream
{
public:
	IO_CircularBuffer();
	virtual ~IO_CircularBuffer();

public:
	bool Open(int initSize);
	void Close();
	int GetAvailable() { return available; }
	int GetFree() { return maxSize - available; }

public:
	virtual int Read();
	virtual int Read(void* buffer, int size);
	virtual int PeekRead();
	virtual int PeekRead(void* buffer, int size);

public:
	virtual int Seek(int offset, int origin){ return -1; };//no support
	virtual int GetPosition(){ return -1; }//no support
	virtual int GetInputSize(){ return available; }

	virtual int Skip(int size);

public:
	virtual int Write(int ch);
	virtual int Write(const void* buffer, int size);

public:
	virtual int GetOutputSize() { return available; }

private:
	char* buffer;
	int maxSize;
	int available;
	int readPosition;
	int writePosition;
};

#endif /*__IO_CIRCULARBUFFER_H__*/
