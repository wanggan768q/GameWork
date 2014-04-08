/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/11/20   16:16
 *	File base:	HSDataStruct.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSDataStruct_H__
#define __HSDataStruct_H__
#include "HSBase.h"
#include "HSStructure.h"
#include "HSCCSprite.h"
#include "SPX_Sprite.h"




#ifdef __cplusplus
extern "C"{

#ifndef _HSCCSpriteData_
#define _HSCCSpriteData_
	
	typedef struct _HSUIData
	{
		HSCCSprite* uiSprite;
		CCNode* uiPanle;
		SPX_Sprite* uiSpx;
		CCMenu* uiMenu;
		message::UI_Field field;
		std::string describe;

		_HSUIData()
		{
			uiSprite = NULL;
			uiPanle = NULL;
			uiSpx = NULL;
			uiMenu = NULL;
			describe = "";
		}

	}HSUIData;

#endif









}


#endif



#endif // __HSDataStruct_H____




// #pragma once
// 
// class HSDataStruct
// {
// public:
// 	HSDataStruct(void);
// 	~HSDataStruct(void);
// };
