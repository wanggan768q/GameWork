#ifndef __IO_INPUTTEXTSTREAM__H__
#define __IO_INPUTTEXTSTREAM__H__

#include "IO_InputDataStream.h"

class IO_InputTextStream : public IO_InputDataStream
{
public:
	IO_InputTextStream();
	virtual ~IO_InputTextStream();

public:
	bool Open(IO_InputDataStream* stream, int encode = IO_ENCODE_DEFAULT);
	void Close();
	int GetEncode();

public:
	virtual int Read();
	virtual int Read(void* buffer, int size);

public:
	virtual int Seek(int offset, int origin);
	virtual int GetPosition();
	virtual int GetInputSize();

public:
	wchar_t ReadChar();
	int ReadChars(wchar_t* buffer, int read);
	wstring ReadLine();

private:
	IO_InputDataStream* stream;
	int encode;
};

#endif /*__IO_INPUTTEXTSTREAM__H__*/
