#ifndef __IO_INPUTFILE_H__
#define __IO_INPUTFILE_H__

#include "IO_InputStream.h"




class IO_InputFile : public IO_InputStream
{
public:
	IO_InputFile();
	virtual ~IO_InputFile();

public:
	bool Open(const wstring& name);
	void Close();

public:
	virtual int Read();
	virtual int Read(void* buffer, int size);

public:
	virtual int Seek(int offset, int origin);
	virtual int GetPosition();
	virtual int GetInputSize();

private:

//#if IO_MODE_WIN32
	FILE* file;
// #else
// 	char* file;
// #endif

};

#endif /*__IO_INPUTFILE_H__*/

