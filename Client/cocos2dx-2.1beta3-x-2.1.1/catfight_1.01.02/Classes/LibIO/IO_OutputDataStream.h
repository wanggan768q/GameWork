#ifndef __IO_OUTPUTDATASTREAM_H__
#define __IO_OUTPUTDATASTREAM_H__

#include "IO_OutputStream.h"
#include "IO_Exception.h"

class IO_OutputDataStream : public IO_OutputStream
{
public:
	IO_OutputDataStream();
	virtual ~IO_OutputDataStream();

public:
	bool Open(IO_OutputStream* stream);
	void Close();

public:
	virtual int Write(int ch);
	virtual int Write(const void* buffer, int size);

public:
	virtual int GetOutputSize();

public:
	void WriteByte(char data) ;
	void WriteShort(short data);
	void WriteInt(int data);
	void WriteInt64(int64 data) ;
	void WriteString(const wstring& text, int encode = IO_ENCODE_UTF8);
	void WriteFull(const void* buffer, int size);

private:
	IO_OutputStream* stream;
};

#endif /*__IO_OUTPUTDATASTREAM_H__*/
