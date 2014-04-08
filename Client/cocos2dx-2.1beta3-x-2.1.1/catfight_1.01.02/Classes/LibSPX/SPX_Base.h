#ifndef __SPX_BASE_H__
#define __SPX_BASE_H__

#include "IO_InputFile.h"
#include "IO_InputDataStream.h"

typedef wstring SPX_String;
typedef cocos2d::CCTexture2D SPX_Texture;

enum SPX_ErrorCode
{
	Success = 0,
	Fail = 1,
	InvalidParameter = 2,
	OutOfMemory = 3,
	ValueOverflow = 4,
	FileNotFound = 5,
	Aborted = 6,
	NotImplemented = 7,
	InsufficientBuffer = 8,
	WrongState = 9,
	UnknownError = 10,
	StreamError = 11,
	InvalidFormat = 12,
};

enum SPX_Transform
{
	None = 0,
	Rotate90 = 5,
	Rotate180 = 3,
	Rotate270 = 6,
	Mirror = 2,
	MirrorRotate90 = 7,
	MirrorRotate180 = 1,
	MirrorRotate270 = 4,
	FlipX = 0x02,
	FlipY = 0x01,
	InvertedAxes = 0x04,
};

SPX_ErrorCode SPX_GetTransform(SPX_Transform a, SPX_Transform b, SPX_Transform& c);
SPX_ErrorCode SPX_GetRotate(SPX_Transform a, int b, SPX_Transform& c);

SPX_Texture* SPX_CreateTexture(const wstring& name);
void SPX_DeleteTexture(SPX_Texture* texture);
void SPX_RenderTexture(SPX_Texture *texture, float sx1, float sy1, float sx2, float sy2, int transform, float x, float y);

#endif /*__SPX_BASE_H__*/
