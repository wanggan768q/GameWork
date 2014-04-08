/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/02   17:54
 *	File base:	HSTouchItemInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSTouchItemInterface_H__
#define __HSTouchItemInterface_H__
#pragma once
#include "HSCellInterface.h"

HS_namespace_HSListViewControl_Begin

class HSTouchItemInterface : public CCTableViewDelegate
{
public:
	HSTouchItemInterface(void);
	~HSTouchItemInterface(void);
public:
	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell ) = 0;

	virtual void tableCellHighlight( CCTableView* table, CCTableViewCell* cell );

	virtual void tableCellUnhighlight( CCTableView* table, CCTableViewCell* cell );

	virtual void tableCellWillRecycle( CCTableView* table, CCTableViewCell* cell );

	virtual void scrollViewDidScroll( CCScrollView* view );

	virtual void scrollViewDidZoom( CCScrollView* view );

};

HS_namespace_HSListViewControl_End

#endif // __HSTouchItemInterface_H____





