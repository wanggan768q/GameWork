#ifndef __IO_OUTPUTTEXTSTREAM__H__
#define __IO_OUTPUTTEXTSTREAM__H__

#include "IO_OutputDataStream.h"

class IO_OutputTextStream : public IO_OutputDataStream
{
public:
	IO_OutputTextStream();
	virtual ~IO_OutputTextStream();

public:
	bool Open(IO_OutputDataStream* stream, int encode = IO_ENCODE_DEFAULT);
	void Close();
	int GetEncode();

public:
	virtual int Write(int b);
	virtual int Write(const void* buffer, int size);

public:
	virtual int GetOutputSize();

public:
	void WriteChar(wchar_t ch) ;
	void WriteChars(const wchar_t* buffer, int size);
	void WriteLine(const wstring& text);

private:
	IO_OutputDataStream* stream;
	int encode;
};

#endif /*__IO_OUTPUTTEXTSTREAM__H__*/

