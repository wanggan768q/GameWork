/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/01/22   14:50
 *	File base:	HSSoundManage.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSoundManage_H__
#define __HSSoundManage_H__
#pragma once



class HSSoundManage
{
public:
	HSSoundManage(void);
	~HSSoundManage(void);

public:
	//生成本地音乐清单
	bool CreateInventory();

	void Load();

	void Play();

	void Stop();

	void SetVolume(float volume);
};

#endif // __HSSoundManage_H____
