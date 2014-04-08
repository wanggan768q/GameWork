#include "HSMath.h"

HSMath::HSMath(void)
{
}

HSMath::~HSMath(void)
{
}

float HSMath::Abs( float a )
{
	return HS_MATH_MAX(-a,a);
}

float HSMath::Sqrt(float v)
{
	float sum = v;
	long i;
	float x, y;
	const float f = 1.5F;
	x = sum * 0.5F;
	y = sum;
	i = *(long *) &y;
	i = MAGIC_NUMBER - (i >> 1);
	y = *(float *) &i;
	y = y * (f - (x * y * y));
	y = y * (f - (x * y * y));
	return sum * y;
}

float HSMath::Sqrt( CCPoint p1,CCPoint p2 )
{
	float px,py;
	px = p1.x - p2.x;
	py = p1.y - p2.y;	
	px = px * px;
	py = py * py;
	float sum = px + py;

	long i;
	float x, y;
	const float f = 1.5F;
	x = sum * 0.5F;
	y = sum;
	i = *(long *) &y;
	i = MAGIC_NUMBER - (i >> 1);
	y = *(float *) &i;
	y = y * (f - (x * y * y));
	y = y * (f - (x * y * y));
	return sum * y;
}

float HSMath::Acos( float x )
{
	float negate = float(x < 0);
	x = HSMath::Abs(x);
	float ret = -0.0187293f;
	ret = ret * x;
	ret = ret + 0.0742610f;
	ret = ret * x;
	ret = ret - 0.2121144f;
	ret = ret * x;
	ret = ret + 1.5707288f;
	ret = ret * HSMath::Sqrt(1.f-x);
	ret = ret - 2 * negate * ret;
	return (float)(negate * 3.14159265358979 + ret);
}

int HSMath::Round(double d)
{
	if (d >= 0.0) {
		return (int) (d + 0.5f);
	} else {
		return (int) (d - 0.5f);
	}
}

int HSMath::Random(int min,int max)
{
	if (min == max)
	{
		return min;
	}	
	timeb t;
	ftime(&t);
	unsigned int time = (unsigned int)(1000 * t.time + t.millitm);
	time += rand();
	srand(time);
	return min  + rand() % (max - min) + rand() % 2;
}

long HSMath::Random(long min,long max)
{
	if (min == max)
	{
		return min;
	}
	timeb t;
	ftime(&t);
	unsigned int time = (unsigned int)(1000 * t.time + t.millitm);
	time += rand();
	srand(time);
	return min  + rand() % (max - min) + rand() % 2;
}

float HSMath::Random(float min,float max)
{
	if (min == max)
	{
		return min;
	}
	timeb t;
	ftime(&t);
	unsigned int time = (unsigned int)(1000 * t.time + t.millitm);
	time += rand();
	srand(time);

	float r = (float)(rand() & RAND_MAX);
	r /= RAND_MAX;
	r = (max - min) * r + min;
	return r;
}

double HSMath::Random(double min,double max)
{
	if (min == max)
	{
		return min;
	}
	timeb t;
	ftime(&t);
	unsigned int time = (unsigned int)(1000 * t.time + t.millitm);
	srand(time);
	time += rand();
	double r = (double)(rand() & RAND_MAX);
	r /= RAND_MAX;
	r = (max - min) * r + min;
	return r;
}

string HSMath::ItoA(int v,int radix /*= 10*/)
{
	char buf[512] = {0};
#ifdef WIN32
	sprintf_s(buf,"%d",v);
#else
	sprintf(buf,"%d",v);
#endif
	return string(buf);
}

string HSMath::FtoA(float f)
{
	char buf[512] = {0};
#ifdef WIN32
	sprintf_s(buf,"%2.f",f);
#else
	sprintf(buf,"%2.f",f);
#endif
	return string(buf);

}

float HSMath::PointDistance(cocos2d::CCPoint p1,cocos2d::CCPoint p2)
{
	float px,py;
	px = p1.x - p2.x;
	py = p1.y - p2.y;	
	px = px * px;
	py = py * py;
	float sum = px + py;

	long i;
	float x, y;
	const float f = 1.5F;
	x = sum * 0.5F;
	y = sum;
	i = *(long *) &y;
	i = MAGIC_NUMBER - (i >> 1);
	y = *(float *) &i;
	y = y * (f - (x * y * y));
	y = y * (f - (x * y * y));
	return sum * y;
}

bool HSMath::EqualsWithFloat( float f,float f1 )
{
	return (fabs(f - f1) > HS_EPSILON) ? false : true;	
}

int HSMath::RandomInt()
{
	int v = HSMath::Random(0,RAND_MAX);
	return v;
}

float HSMath::RandomFloat()
{
	float r = (float)(rand() & (RAND_MAX));
	r /= RAND_MAX;
	r = 2.0f * r - 1.0f;
	return r;
}

float HSMath::Angle( CCPoint p1,CCPoint p2 )
{
	float x;
	float ix,iy;

	ix = p1.x - p2.x;
	iy = p1.y - p2.y;


	if (ix >= 0 && iy < 0) {	//右下
		if (ix == 0) {
			x= 270;
		} else {
			iy *= -1;
			x = 180 + (float) (atan(iy / ix) * 180 / (float)(M_PI));
		}
	} else if (ix > 0 && iy >= 0) {		//右上
		if (iy == 0) {
			x = 180;
		} else {
			x = 90+(float) (  atan(ix / iy) * 180 / (float)(M_PI));
		}
	} else if (ix <= 0 && iy > 0) {		//左上
		if (ix == 0) {
			x = 90;
		} else {
			ix *= -1;
			x = (float) ( atan(iy / ix) * 180 / (float)(M_PI));
		}
	} else {		//左下
		if (iy == 0) {
			x = 0;
		} else {
			ix *= -1;
			iy *= -1;
			x = 270 + (float) ( atan(ix / iy) * 180 / (float)(M_PI));
		}
	}
	return x;
}