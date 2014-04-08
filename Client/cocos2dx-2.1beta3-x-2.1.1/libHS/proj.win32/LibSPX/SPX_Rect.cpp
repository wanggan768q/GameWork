#include "SPX_Rect.h"

SPX_Rect::SPX_Rect()
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

SPX_Rect::SPX_Rect(SPX_Rect* rect)
{
	SetRect(rect);
}

SPX_Rect::SPX_Rect(float x1, float y1, float x2, float y2)
{
	SetRect(x1, y1, x2, y2);
}

SPX_Rect::~SPX_Rect()
{

}

SPX_ErrorCode SPX_Rect::ReadData(IO_InputDataStream* stream)
{

	x1 = (float)stream->ReadShort();
	y1 = (float)stream->ReadShort();
	x2 = (float)stream->ReadShort();
	y2 = (float)stream->ReadShort();


	return Success;
}

void SPX_Rect::SetRect(SPX_Rect* rect)
{
	if(rect == NULL)
	{
		return;
	}

	this->x1 = rect->x1;
	this->y1 = rect->y1;
	this->x2 = rect->x2;
	this->y2 = rect->y2;
}

void SPX_Rect::SetRect(float x1, float y1, float x2, float y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void SPX_Rect::SetRect2(float x, float y, float width, float height)
{
	this->x1 = x;
	this->y1 = y;
	this->x2 = x + width;
	this->y2 = y + height;
}

float SPX_Rect::GetX()
{
	if(x1 < x2)
	{
		return x1;
	}

	return x2;
}

float SPX_Rect::GetY()
{
	if(y1 < y2)
	{
		return y1;
	}

	return y2;
}

float SPX_Rect::GetWidth()
{
	if(x1 < x2)
	{
		return x2 - x1;
	}

	return x1 - x2;
}

float SPX_Rect::GetHeight()
{
	if(y1 < y2)
	{
		return y2 - y1;
	}

	return y1 - y2;
}

float SPX_Rect::GetX1()
{
	return x1;
}

float SPX_Rect::GetY1()
{
	return y1;
}

float SPX_Rect::GetX2()
{
	return x2;
}

float SPX_Rect::GetY2()
{
	return y2;
}

bool SPX_Rect::Equals(SPX_Rect* rect)
{
	if(rect == NULL)
	{
		return false;
	}

	if((x1 != rect->x1) || (y1 != rect->y1) || (x2 != rect->x2) || (y2 != rect->y2))
	{
		return false;
	}

	return true;
}

bool SPX_Rect::IsEmpty()
{
	if((x1 == x2) || (y1 == y2))
	{
		return true;
	}

	return false;
}

void SPX_Rect::Translate(float x, float y)
{
	this->x1 += x;
	this->y1 += y;
	this->x2 += x;
	this->y2 += y;
}

void SPX_Rect::Scale(float x, float y)
{
	this->x1 *= x;
	this->y1 *= y;
	this->x2 *= x;
	this->y2 *= y;
}

void SPX_Rect::Transform(int transform)
{
	if(transform == None)
	{
		return;
	}

	float temp;
	if((transform & FlipX) != 0)
	{
		x1 = -x1;
		x2 = -x2;
	}
	if((transform & FlipY) != 0)
	{
		y1 = -y1;
		y2 = -y2;
	}
	if((transform & InvertedAxes) != 0)
	{
		temp = x1;
		x1 = y1;
		y1 = temp;
		temp = x2;
		x2 = y2;
		y2 = temp;
	}
}

void SPX_Rect::Normalize()
{
	float temp;
	if(x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}

	if(y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
}

bool SPX_Rect::IntersectTest(SPX_Rect* rect)
{
	if(rect == NULL)
	{
		return false;
	}

	if(IntersectTest(rect->x1, rect->y1, rect->x2, rect->x2))
	{
		return true;
	}

	return false;
}

bool SPX_Rect::IntersectTest(float x1, float y1, float x2, float y2)
{
	float tx1, ty1, tx2, ty2;

	if(this->x1 < this->x2)
	{
		tx1 = this->x1;
		tx2 = this->x2;
	}
	else
	{
		tx1 = this->x2;
		tx2 = this->x1;
	}

	if(this->y1 < this->y2)
	{
		ty1 = this->y1;
		ty2 = this->y2;
	}
	else
	{
		ty1 = this->y2;
		ty2 = this->y1;
	}

	float temp;
	if(x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}

	if(y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	if((y2 < ty1) || (y1 > ty2) || (x2 < tx1) || (x1 > tx2))
	{
		return false;
	}

	return true;
}
