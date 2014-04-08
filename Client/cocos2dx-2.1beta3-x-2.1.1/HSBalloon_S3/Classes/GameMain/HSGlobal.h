#ifndef __HSGLOBAL_H__
#define __HSGLOBAL_H__
#pragma once
#include "HSTool.h"


class HSGlobal : private cocos2d::CCObject
{
public:
	HSGlobal(void);
	~HSGlobal(void);
public:
	static HSGlobal* ShaderGlobal();

	void CallCloud(CCNode* node);
	void AddCloud(CCLayer* pTarget);

	bool init();

	bool s1;
	bool s2;
	bool s3;
	bool s4;
	bool s5;
};


#endif
