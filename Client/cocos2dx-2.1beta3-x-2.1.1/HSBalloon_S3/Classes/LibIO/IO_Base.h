#ifndef __IO_BASE_H__
#define __IO_BASE_H__

#include "GE_Base.h"
#include "cocos2d.h"
using namespace cocos2d;

#define IO_SEEK_BEGIN   0
#define IO_SEEK_CURRENT 1
#define IO_SEEK_END     2

#define IO_ENCODE_ASCII 1
#define IO_ENCODE_UNICODE 2 //FF FE
#define IO_ENCODE_UNICODE_BIG_ENDIAN 3 //FE FF
#define IO_ENCODE_UTF8 4 //EF BB BF
#define IO_ENCODE_DEFAULT 5
#define IO_ENCODE_UNKNOW 6

#define IO_ERROR_EOF -1
#define IO_ERROR_UTF_FORMAT 2
#define IO_ERROR_NO_OPEN 1
#define IO_ERROR_OVERFLOW 3
#define IO_ERROR_ENCODE 4
#define IO_ERROR_FORMAT 5

#define IO_CHAR_BUFFER_SIZE 32


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define IO_MODE_WIN32 1
#else
#define IO_MODE_WIN32 0
#endif

#define HS_IO_LOG
#ifdef HS_IO_LOG
#define IOMessageBox(strMsg) CCMessageBox(strMsg,"IO");
#endif


#endif /*__IO_BASE_H__*/
