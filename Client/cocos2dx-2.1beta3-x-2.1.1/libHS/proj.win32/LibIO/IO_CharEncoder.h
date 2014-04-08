#ifndef __IO_CHARENCODER_H__
#define __IO_CHARENCODER_H__

#include "IO_OutputDataStream.h"

class IO_CharEncoder
{
private:
	IO_CharEncoder(){}
	~IO_CharEncoder(){}

public:
	static bool WriteASCII(IO_OutputDataStream* stream, const wstring& text) ;
	static bool WriteUTF8(IO_OutputDataStream* stream, const wstring& text);
	static bool WriteUNICODE(IO_OutputDataStream* stream, const wstring& text);
	static bool WriteBigEndianUNICODE(IO_OutputDataStream* stream, const wstring& text);
	static bool WriteChar(IO_OutputDataStream* stream, int encode, wchar_t ch);
};

#endif /*__IO_CHARENCODER_H__*/


