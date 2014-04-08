#include "SPX_Sprite.h"
#include "SPX_Action.h"
#include "SPX_Data.h"
#include "cocoa/CCObject.h"
#include "SPX_Manager.h"

using namespace cocos2d;

SPX_Sprite::SPX_Sprite()
{
	data = NULL;
	eventProc = NULL;
	transform = None;
	actionIndex = 0;
	sequenceIndex = 0;
	updateTime = 0;
	delay = 0;
	firstUpdate = true;
	playEnd = true;


	playCount = -1;
	playIndex = 0;
	this->pTarget = NULL;
	this->selector = NULL;

	schedule(schedule_selector(SPX_Sprite::update));
}

SPX_Sprite::~SPX_Sprite()
{
	
}

void SPX_Sprite::InitSprite(SPX_Data* data)
{
	if(data == NULL)
	{
		return;
	}

	this->data = data;
	this->skin.textureList.resize(data->bitmapList.size());
}

void SPX_Sprite::draw()
{
	if(eventProc != NULL)
	{
		eventProc->OnStartSpriteDraw(this);
	}

	SPX_Action& action = data->actionList[actionIndex];
	int frameIndex = action.frameSequence.itemList[sequenceIndex].frameIndex;
	SPX_Frame& frame = data->frameList[frameIndex];

	//cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();

	//y = getContentSize().height - y;
	////float glAngle = fmod(360.0f - rotateAngle, 360.20f);
	//float glAngle = rotateAngle;

	//kmGLPushMatrix();
	// 	kmGLTranslatef(x, y, 0);
	// 	kmGLRotatef(glAngle, 0, 0, 1);
	// 	kmGLScalef(1, -1, 1);
	// 	kmGLTranslatef(-x, -y, 0);
	//glColor4f(1, 1, 1, opacity);
	//glColor4f(1, 1, 1, getOpacity() / 255.0);
	frame.Render(this, 0, 0);
	//kmGLPopMatrix();

	if(eventProc != NULL)
	{
		eventProc->OnEndSpriteDraw(this);
	}
}

void SPX_Sprite::cleanup()
{
	
}

void SPX_Sprite::update(float dt)
{
	Update(GE_GetTime());
}

void SPX_Sprite::Move(float x, float y)
{
	this->setPosition(this->getPositionX() + x, this->getPositionY() + y);
}

void SPX_Sprite::SetAction(int actionIndex)
{
	const char* actionName = this->GetActionName(actionIndex);
	this->SetAction(actionName);
}

void SPX_Sprite::Reset()
{
	this->sequenceIndex = 0;
}

void SPX_Sprite::SetAction(int actionIndex,int playCount)
{
	if(this->playCount != -1)
		return;
	this->Reset();
	this->SetAction(actionIndex);
	this->playCount = playCount;
}

void SPX_Sprite::SetAction(int actionIndex,int playCount,CCObject* rec,SEL_CallFuncND selector,void* data)
{
	SetAction(actionIndex,playCount);
	SetTarget(rec,selector,data);
}

void SPX_Sprite::SetTarget(CCObject* rec,SEL_CallFuncND selector,void* data)
{
	this->pTarget = rec;
	this->selector = selector;
	this->pData = data;
}

void SPX_Sprite::SetAction(const char* actionName)
{
	int actionIndex = data->GetActionIndex(actionName);
	if(actionIndex != -1 && this->actionIndex != actionIndex)
	{
		this->actionIndex = actionIndex;
		this->sequenceIndex = 0;
		this->firstUpdate = true;
		this->playEnd = false;
	}
}

int SPX_Sprite::GetActionCount()
{
	return (int)data->actionList.size();
}

const char* SPX_Sprite::GetActionName(int actionIndex)
{
	if(actionIndex < 0 || actionIndex >= (int)data->actionList.size())
	{
		return 0;
	}

	return data->actionList[actionIndex].actionName;
}

void SPX_Sprite::SetSequenceIndex(int sequenceIndex)
{
	//SPX_Action& action = data->actionList[actionIndex];

	if(sequenceIndex < 0 || sequenceIndex >= GetSequenceCount())
	{
		return;
	}
	this->sequenceIndex = sequenceIndex;
}

void SPX_Sprite::NextFrame()
{
	sequenceIndex++;

	if(sequenceIndex >= GetSequenceCount())
	{
		sequenceIndex = 0;
		playEnd = true;

		//播放次数为条件
		if (this->playCount > 0)
		{
			++playIndex;
			if (this->playIndex >= this->playCount)
			{
				this->playIndex = 0;
				this->playCount = -1;
				this->setVisible(false);
				if (this->pTarget && this->selector)
				{
					(this->pTarget->*selector)(this,this->pData);
				}
				return;
			}			
		}


	}
	else
	{
		playEnd = false;
	}
}

void SPX_Sprite::PrevFrame()
{
	if(sequenceIndex == 0)
	{
		sequenceIndex = GetSequenceCount() - 1;
	}
	else
	{
		sequenceIndex--;
	}
}

bool SPX_Sprite::IsPlayEnd()
{
	return playEnd;
}

int SPX_Sprite::GetSequenceCount()
{
	SPX_Action& action = data->actionList[actionIndex];
	int sequenceCount = action.frameSequence.itemList.size();
	return sequenceCount;
}

int SPX_Sprite::GetSequenceIndex()
{
	return sequenceIndex;
}

int SPX_Sprite::GetSequenceFrameIndex()
{
	SPX_Action& action = data->actionList[actionIndex];
	int frameIndex = action.frameSequence.itemList[sequenceIndex].frameIndex;
	return frameIndex;
}

utime SPX_Sprite::GetSequenceFrameDelay()
{
	SPX_Action& action = data->actionList[actionIndex];
	int frameDelay = action.frameSequence.itemList[sequenceIndex].frameDelay;
	return frameDelay + delay;
}

void SPX_Sprite::SetTransform(SPX_Transform transform)
{
	if(transform < 0 || transform > 7)
	{
		return;
	}

	this->transform = transform;
}

int SPX_Sprite::GetTransform()
{
	return transform;
}

void SPX_Sprite::Rotate90Clockwise()
{
	SPX_GetRotate(transform, 1, transform);
}

void SPX_Sprite::Rotate90Anticlockwise()
{
	SPX_GetRotate(transform, 0, transform);
}

void SPX_Sprite::MirrorHorizontal()
{
	SPX_GetRotate(transform, 2, transform);
}

void SPX_Sprite::MirrorVertical()
{
	SPX_GetRotate(transform, 3, transform);
}

void SPX_Sprite::SetDelay(utime delay)
{
	this->delay = delay;
}

void SPX_Sprite::Update(utime time)
{
	if(firstUpdate)
	{
		updateTime = time;
		firstUpdate = false;
	}

	if (time - updateTime >= GetSequenceFrameDelay())
	{
		NextFrame();

		updateTime = time;
	}
}

void SPX_Sprite::SetBitmap(int bitmapID, const SPX_String& bitmapName)
{
	int bitmapIndex = data->GetBitmapIndex(bitmapID);
	if(bitmapIndex != -1)
	{
		if(skin.textureList[bitmapIndex] != NULL)
		{
			delete skin.textureList[bitmapIndex];
			skin.textureList[bitmapIndex] = NULL;
		}

		skin.textureList[bitmapIndex] = SPX_CreateTexture(bitmapName);
	}
}

void SPX_Sprite::SetEventProc(SPX_ISpriteEvent* eventProc)
{
	this->eventProc = eventProc;
}

SPX_ISpriteEvent* SPX_Sprite::GetEventProc()
{
	return eventProc;
}
