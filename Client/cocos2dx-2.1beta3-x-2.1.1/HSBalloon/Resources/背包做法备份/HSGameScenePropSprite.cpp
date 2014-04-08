#include "HSGameScenePropSprite.h"


HSGameScenePropSprite::HSGameScenePropSprite(void)
{
	m_pLastSprite = NULL;
	m_pNextSprite = NULL;
	m_id = 0;
	m_isBuy = false;
}


HSGameScenePropSprite::~HSGameScenePropSprite(void)
{
}

HSGameScenePropSprite* HSGameScenePropSprite::create( const char* fileName,int id,bool isBuy )
{
	HSGameScenePropSprite* sprite = new HSGameScenePropSprite;
	if (sprite && sprite->Init(fileName,id,isBuy))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSGameScenePropSprite::Init( const char* fileName,int id,bool isBuy )
{
	this->m_id = id;
	this->m_isBuy = isBuy;

	//this->initWithFile(fileName);

	return true;
}

bool HSGameScenePropSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameScenePropSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameScenePropSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}
