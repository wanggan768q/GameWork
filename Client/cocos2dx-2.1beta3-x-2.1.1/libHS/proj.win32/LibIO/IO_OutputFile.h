#ifndef __IO_OUTPUTFILE_H__
#define __IO_OUTPUTFILE_H__

#include "IO_OutputStream.h"

class IO_OutputFile : public IO_OutputStream
{
public:
	IO_OutputFile();
	virtual ~IO_OutputFile();

public:
	bool Open(const wstring& name);
	void Close();
	void Flush();

public:
	virtual int Write(int ch);
	virtual int Write(const void* buffer, int size);

public:
	virtual int GetOutputSize();

private:
	FILE* file;
};

#endif /*__IO_OUTPUTFILE_H__*/


