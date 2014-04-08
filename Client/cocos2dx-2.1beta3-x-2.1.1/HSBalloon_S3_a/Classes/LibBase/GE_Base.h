#ifndef __GE_BASE_H__
#define __GE_BASE_H__

#include "cocos2d.h"
using namespace cocos2d;


/*
开发者: 黄小子
QQ: 776496203
opencai@126.com
版本: SPX 2011 +1
最后修改日期: 2012.4.16 14:56

1:修改了延时BUG，把原来时间相关的变量
都从int类型改成了utime类型
utime是用unsigned int定义的

2:修改了相对坐标问题 这个问题是由于
为了翻转Y轴，SPX绘制的都是后都减去
屏幕屏幕大小，实际上应该减去父层的大小

3:把SPX_Sprite 里面的update方法改成了update1了
因为和CCObject里面的冲突了，所以真机报错
2012.4.18 17.06
*/

//#ifndef _GLIBCXX_USE_WCHAR_T
//#define _GLIBCXX_USE_WCHAR_T
//#endif

#include <string>
#include <vector>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//LOCAL_CFLAGS += -fexceptions
//typedef basic_string<wchar_t> wstring;
#endif

#ifndef _MAX_PATH
#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE 3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME 256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */
#endif

using namespace std;

typedef long long int64;
typedef unsigned char byte;

typedef vector<wstring> wstrary;
typedef vector<string> strary;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef wchar_t wchar;
typedef unsigned int utime;

wstring GE_GetAbsolutePath(const wstring& name, const wstring& relative);
wstring GE_GetFilePath(const wstring& name);
bool GE_IsRelativePath(const wstring& name);
bool GE_GetResourcePath(const wstring& name, wstring& path);
string GE_U2A(const wstring& str);
wstring GE_A2U(const string& str);
utime GE_GetTime();

#define _T(x) L##x

#ifdef _MSC_VER
#pragma warning(disable:4290)
#pragma warning(disable:4996)
#endif /*_MSC_VER*/

#endif /*__GE_BASE_H__*/
