#ifndef __IO_INPUTDATASTREAM_H__
#define __IO_INPUTDATASTREAM_H__

#include "IO_InputStream.h"
#include "IO_Exception.h"

class IO_InputDataStream : public IO_InputStream
{
public:
	IO_InputDataStream();
	virtual ~IO_InputDataStream();

public:
	bool Open(IO_InputStream* stream);
	void Close();

public:
	virtual int Read();
	virtual int Read(void* buffer, int size);

public:
	virtual int Seek(int offset, int origin);
	virtual int GetPosition();
	virtual int GetInputSize();

public:
	char ReadByte();
	short ReadShort();
	int ReadInt();
	int64 ReadInt64();
	wstring ReadString(int encode = IO_ENCODE_UTF8);
	void ReadFull(void* buffer, int size);

private:
	IO_InputStream* stream;
};

#endif /*__IO_INPUTDATASTREAM_H__*/
