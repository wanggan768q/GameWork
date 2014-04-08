#ifndef __SPX_SPRITE_H__
#define __SPX_SPRITE_H__

#include "SPX_ISpriteEvent.h"
#include "SPX_Manager.h"
#include "SPX_Skin.h"

class SPX_Data;

class SPX_Sprite : public cocos2d::CCNode
{
public:
	SPX_Sprite();
	~SPX_Sprite();

public:
	void InitSprite(SPX_Data* data);
	void update(float dt);
	virtual void draw();
	virtual void cleanup();

public:
	void Move(float x, float y);

public:
	//Ambition Add
	void SetAction(int actionIndex);
	void SetAction(int actionIndex,int playCount);
	void SetAction(int actionIndex,int playCount,CCObject* rec,SEL_CallFuncND selector,void* data);
	void SetTarget(CCObject* rec,SEL_CallFuncND selector,void* data);
	void Reset();

	void SetAction(const char* actionName);
	int GetActionCount();
	const char* GetActionName(int actionIndex);

	

public:
	void SetSequenceIndex(int sequenceIndex);
	void NextFrame();
	void PrevFrame();
	bool IsPlayEnd();

public:
	int GetSequenceCount();
	int GetSequenceIndex();
	int GetSequenceFrameIndex();
	utime GetSequenceFrameDelay();

public:
	void SetTransform(SPX_Transform transform);
	int GetTransform();

public:
	void Rotate90Clockwise();
	void Rotate90Anticlockwise();
	void MirrorHorizontal();
	void MirrorVertical();

public:
	void SetDelay(utime delay);

public:
	void Update(utime time);

public:
	void SetBitmap(int bitmapID, const SPX_String& bitmapName);

public:
	void SetEventProc(SPX_ISpriteEvent* eventProc);
	SPX_ISpriteEvent* GetEventProc();

public:
	SPX_Data* data;
	SPX_Skin skin;
	SPX_ISpriteEvent* eventProc;
	SPX_Transform transform;
	int actionIndex;
	int sequenceIndex;
	utime updateTime;
	utime delay;
	bool firstUpdate;
	bool playEnd;

	//Ambition Add
	int playCount;
	int playIndex;
	CCObject* pTarget;
	SEL_CallFuncND selector;
	void* pData;
};

#endif /*__SPX_SPRITE_H__*/
