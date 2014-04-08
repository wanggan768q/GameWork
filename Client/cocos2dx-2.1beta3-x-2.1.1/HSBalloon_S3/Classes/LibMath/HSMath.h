/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/20   11:28
 *	File base:	HSMath.h
 *	Author:		Ambition
 *	
 *	Purpose:	��ѧ��
*********************************************************************/
#ifndef __HSMath_H__
#define __HSMath_H__
#pragma once
#include "HSTime.h"
#include <string>
using namespace std;




#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0x5f3759df	//�����ħ����
#endif

#ifndef HS_MATH_MAX
#define HS_MATH_MAX(a,b) ((a)>(b)?(a):(b)) 
#endif

#ifndef HS_MATH_MIN
#define HS_MATH_MIN(a,b) ((a)<(b)?(a):(b))
#endif


#ifndef HS_MATH_SWAP
#define HS_MATH_SWAP(a,b) { \
	int c = (a);    \
	(a) = (b);      \
	(b) = c;        \
	}
#endif

#ifndef HS_ARRAYSIZE
#define HS_ARRAYSIZE(__Array__) \
	((sizeof(__Array__) / sizeof(*(__Array__))) / \
	static_cast<size_t>(!(sizeof(__Array__) % sizeof(*(__Array__)))))
#endif


#ifndef HS_EPSILON
#define HS_EPSILON 0.00001f
#endif

#ifndef HS_PI
#define HS_PI 3.14159265359f
#endif

class HSMath
{
public:
	HSMath(void);
	~HSMath(void);

	static float Abs(float a);

	static float Sqrt(float v);

	static float Sqrt(CCPoint p1,CCPoint p2);

	static int Round(double d);	

	static int Random(int min,int max);

	static long Random(long min,long max);

	static float Random(float min,float max);

	static int RandomInt();

	static float RandomFloat();

	static double Random(double min,double max);	

	static float Acos(float x);

	static string ItoA(int v,int radix = 10);

	static string FtoA(float f);

	static float PointDistance(cocos2d::CCPoint p1,cocos2d::CCPoint p2);

	static bool EqualsWithFloat(float f,float f1);

	static float Angle(CCPoint p1,CCPoint p2);
    
    static const char* GetUUID(int byteSize = 32);
};





















#endif // __HSMath_H__
