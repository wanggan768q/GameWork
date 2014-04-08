/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/20   13:38
 *	File base:	HSUserRankSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSUserRankSprite_H__
#define __HSUserRankSprite_H__
#pragma once
#include "HSTool.h"

typedef enum
{
	RankSprite_Bule,
	RankSprite_Red,
}RankSpriteType;

class HSUserRankSprite : public CCNode
{
public:
	HSUserRankSprite(void);
	~HSUserRankSprite(void);

private:
	HSCCSprite* m_pNameFrame;
	HSCCSprite* m_pRankIndexFrame;
	HSCCSprite* m_pRankChangeFrame;
	HSCCSprite* m_pRankUpOrDownFrame;
	HSCCSprite* m_pScoreFrame;

	const char* m_fontName;

	
	CCLabelTTF* m_pNameTTF;
	CCLabelTTF* m_pRankIndexTTF;
	CCLabelTTF* m_pRankChangeTTF;
	HSCCSprite* m_pRankUpOrDownSprite;
	CCLabelTTF* m_pScoreTTF;

	CCTexture2D* m_pUpTexture;
	CCTexture2D* m_pDownTexture;

public:
	static HSUserRankSprite* Create(const RankSpriteType& type,const SearchRankResponse_UserRank* pUserRank);

	bool init(const RankSpriteType& type,const SearchRankResponse_UserRank* pUserRank);

	void SetUserRank(const SearchRankResponse_UserRank* pUserRank);
};


#endif // __HSUserRankSprite_H____


