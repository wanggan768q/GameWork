/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/03/13   16:34
 *	File base:	HSVisibleRect.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSVisibleRect_H__
#define __HSVisibleRect_H__
#include "HSBase.h"

class HSVisibleRect
{
public:
	static CCRect getVisibleRect();

	static CCPoint left();
	static CCPoint right();
	static CCPoint top();
	static CCPoint bottom();
	static CCPoint center();
	static CCPoint leftTop();
	static CCPoint rightTop();
	static CCPoint leftBottom();
	static CCPoint rightBottom();
private:
	static void lazyInit();
	static CCRect s_visibleRect;
};

#endif // __HSVisibleRect_H____



