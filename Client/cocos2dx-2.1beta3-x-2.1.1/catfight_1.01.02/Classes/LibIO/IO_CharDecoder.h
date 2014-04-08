#ifndef __IO_CHARDECODER_H__
#define __IO_CHARDECODER_H__

#include "IO_InputDataStream.h"

class IO_CharDecoder
{
private:
	IO_CharDecoder(){}
	~IO_CharDecoder(){}

public:
	static bool ReadASCII(IO_InputDataStream* stream, wstring& text) ;
	static bool ReadUTF8(IO_InputDataStream* stream, wstring& text);
	static bool ReadUNICODE(IO_InputDataStream* stream, wstring& text);
	static bool ReadBigEndianUNICODE(IO_InputDataStream* stream, wstring& text);
	static bool ReadChar(IO_InputDataStream* stream, int encode, wchar_t& ch);
};

#endif /*__IO_CHARDECODER_H__*/
