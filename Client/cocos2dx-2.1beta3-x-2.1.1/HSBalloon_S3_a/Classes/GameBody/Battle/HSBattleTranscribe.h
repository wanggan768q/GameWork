/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/12   14:13
 *	File base:	HSBattleTranscribe.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBattleTranscribe_H__
#define __HSBattleTranscribe_H__
#pragma once
#include "HSTool.h"

class HSBattleTranscribe : public CCNode
{
public:
	HSBattleTranscribe(void);
	~HSBattleTranscribe(void);

private:
	BattleTranscribeDataList* m_pBattleTranscribeDataList;

public:
	CREATE_FUNC(HSBattleTranscribe);

	bool init();

	void AddFrame(const BattleInfo& battleInfo);

	void Save();
};

#endif // __HSBattleTranscribe_H____

