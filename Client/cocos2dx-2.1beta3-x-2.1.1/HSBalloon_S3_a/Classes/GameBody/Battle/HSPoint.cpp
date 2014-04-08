#include "HSPoint.h"


HSPoint::HSPoint(void)
{
	m_pPosNode = NULL;
}


HSPoint::~HSPoint(void)
{
	m_pPosNode = NULL;
}

HSPoint* HSPoint::create( CCNode* pPos )
{
	HSPoint* pPoint = new HSPoint();
	if (pPoint && pPoint->init(pPos))
	{
		pPoint->autorelease();
		return pPoint;
	}
	CC_SAFE_DELETE(pPoint);
	return NULL;
}

bool HSPoint::init( CCNode* pPos )
{
	if (!pPos ||  !this->initWithFile("Image/point.png"))
	{
		return false;
	}
	m_pPosNode = pPos;

	this->schedule(schedule_selector(HSPoint::Updata));
	return true;
}

void HSPoint::Updata( float dt )
{
	if (!m_pPosNode)
	{
		return;
	}
	this->setPosition(m_pPosNode->getPosition());
}
