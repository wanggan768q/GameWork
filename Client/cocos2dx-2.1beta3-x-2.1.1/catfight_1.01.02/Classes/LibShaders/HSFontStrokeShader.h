/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/24   16:36
 *	File base:	HSFontStrokeShader.h
 *	Author:		Ambition
 *	
 *	Purpose:	◊÷ÃÂ√Ë±ﬂshader
*********************************************************************/
#ifndef __HSFontStrokeShader_H__
#define __HSFontStrokeShader_H__

"																							\n\
attribute vec4 position;																	\n\
attribute vec4 inputTextureCoordinate;														\n\
uniform highp float texelWidth;																\n\
uniform highp float texelHeight;															\n\
varying vec2 textureCoordinate;																\n\
varying vec2 leftTextureCoordinate;															\n\
varying vec2 rightTextureCoordinate;														\n\
varying vec2 topTextureCoordinate;															\n\
varying vec2 topLeftTextureCoordinate;														\n\
varying vec2 topRightTextureCoordinate;														\n\
varying vec2 bottomTextureCoordinate;														\n\
varying vec2 bottomLeftTextureCoordinate;													\n\
varying vec2 bottomRightTextureCoordinate;													\n\
void main()																					\n\
{																							\n\
	gl_Position = position;																	\n\
	vec2 widthStep = vec2(texelWidth, 0.0);													\n\
	vec2 heightStep = vec2(0.0, texelHeight);												\n\
	vec2 widthHeightStep = vec2(texelWidth, texelHeight);									\n\
	vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);							\n\
																							\n\
	textureCoordinate = inputTextureCoordinate.xy;											\n\
	leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;							\n\
	rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;							\n\
																							\n\
	topTextureCoordinate = inputTextureCoordinate.xy - heightStep;							\n\
	topLeftTextureCoordinate = inputTextureCoordinate.xy - widthHeightStep;					\n\
	topRightTextureCoordinate = inputTextureCoordinate.xy + widthNegativeHeightStep;		\n\
																							\n\
	bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;						\n\
	bottomLeftTextureCoordinate = inputTextureCoordinate.xy - widthNegativeHeightStep;		\n\
	bottomRightTextureCoordinate = inputTextureCoordinate.xy + widthHeightStep;				\n\
}"
	;
#endif // __HSFontStrokeShader_H____