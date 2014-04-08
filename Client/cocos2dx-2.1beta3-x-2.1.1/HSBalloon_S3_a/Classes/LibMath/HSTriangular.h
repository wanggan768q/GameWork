/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/02/28   13:31
 *	File base:	HSTriangular.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSTriangular_H__
#define __HSTriangular_H__
#pragma once
#include "HSVector2d.h"

class HSTriangular 
{
public:

	//************************************
	// Method:    Process
	// FullName:  HSTriangular::Process
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: const HSVector2dV & contour	一个三角形 或者 一个多边形轮廓
	// Parameter: HSVector2dV & outResult		输出一个系列的三角形 拼成多边形的所有面片
	//************************************
	static bool Process(const HSVector2dV &contour,HSVector2dV &outResult);


	//************************************
	// Method:    Area
	// FullName:  HSTriangular::Area
	// Access:    public static 
	// Returns:   float
	// Qualifier:
	// Parameter: const HSVector2dV & contour  一个多边形的轮廓顶点计算其面积
	//************************************
	static  float Area(const HSVector2dV &contour);


	
	//************************************
	// Method:    InsideTriangle
	// FullName:  HSTriangular::InsideTriangle
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: float Ax
	// Parameter: float Ay
	// Parameter: float Bx
	// Parameter: float By
	// Parameter: float Cx
	// Parameter: float Cy
	// Parameter: float Px
	// Parameter: float Py  判断 P 点是否在 三角形（Ax.Ay, Bx.By, Cx,Cy） 内
	//************************************
	static bool InsideTriangle(float Ax, float Ay,
		float Bx, float By,
		float Cx, float Cy,
		float Px, float Py);

private:
	static bool Snip(const HSVector2dV &contour,int u,int v,int w,int Vsize,int *V);
};


#endif // __HSTriangular_H____
