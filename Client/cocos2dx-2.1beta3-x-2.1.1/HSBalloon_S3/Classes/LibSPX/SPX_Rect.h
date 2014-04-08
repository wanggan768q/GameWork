#ifndef __SPX_RECT_H__
#define __SPX_RECT_H__

#include "SPX_Base.h"

class SPX_Rect
{
public:
	SPX_Rect();
	SPX_Rect(SPX_Rect* rect);
	SPX_Rect(float x1, float y1, float x2, float y2);
	~SPX_Rect();

public:
	SPX_ErrorCode ReadData(IO_InputDataStream* stream);

public:
	void SetRect(SPX_Rect* rect);
	void SetRect(float x1, float y1, float x2, float y2);
	void SetRect2(float x, float y, float width, float height);
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
	float GetX1();
	float GetY1();
	float GetX2();
	float GetY2();

public:
	bool Equals(SPX_Rect* rect);
	bool IsEmpty();

public:
	void Translate(float x, float y);
	void Scale(float x, float y);
	void Transform(int transform);
	void Normalize();

public:
	bool IntersectTest(SPX_Rect* rect);
	bool IntersectTest(float x1, float y1, float x2, float y2);

public:
	float x1;
	float y1;
	float x2;
	float y2;
};

#endif /*__SPX_RECT_H__*/

