#include "HSLine.h"


HSLine::HSLine()
{
	m_pBegin = NULL;
	m_pEnd = NULL;
}


HSLine::~HSLine(void)
{
	m_pBegin = NULL;
	m_pEnd = NULL;
}

HSLine* HSLine::create( HSBalloonSprite* pBegin,HSBalloonSprite* pEnd )
{
	HSLine* pLine = new HSLine();
	if (pLine && pLine->Init(pBegin,pEnd))
	{
		pLine->autorelease();
		return pLine;
	}
	CC_SAFE_DELETE(pLine);
	return NULL;
}

bool HSLine::Init(HSBalloonSprite* pBegin,HSBalloonSprite* pEnd)
{
	m_pBegin = pBegin;
	m_pEnd = pEnd;
	if (!m_pBegin || !m_pEnd || !this->initWithFile("Image/Line.png"))
	{
		return false;
	}

	this->schedule(schedule_selector(HSLine::Updata));

	return true;
}

void HSLine::Updata( float dt )
{
	HSAssert(m_pBegin && m_pEnd,"");

	CCPoint p1 = m_pBegin->getPosition();
	CCPoint p2 = m_pEnd->getPosition();
	this->setPosition(p1);
	float scaleX = ccpDistance(p1,p2) / this->getContentSize().width;
	float rotation = HSMath::Angle(p1,p2);
	this->setScaleX(scaleX);
	this->setRotation(rotation);
}


