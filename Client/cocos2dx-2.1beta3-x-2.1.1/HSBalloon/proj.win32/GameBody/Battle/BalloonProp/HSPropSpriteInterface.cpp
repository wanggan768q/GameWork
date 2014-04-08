#include "HSPropSpriteInterface.h"

int HSPropSpriteInterface::m_iDefaultID = 0x3e8;

HSPropSpriteInterface::HSPropSpriteInterface(void)
{
	m_type = BALLOON_PROPS_UnKnow;
	m_iMaxTouchCount = 1;
	m_isListerFristUpdata = true;

	this->SetID(m_iDefaultID++);
	this->schedule(schedule_selector(HSPropSpriteInterface::Updata));
}


HSPropSpriteInterface::~HSPropSpriteInterface(void)
{
}

void HSPropSpriteInterface::SetPropType( BalloonPropsType type )
{
	m_type = type;
}

BalloonPropsType HSPropSpriteInterface::GetPropType()
{
	return m_type;
}

void HSPropSpriteInterface::SetMaxTouchCount( int count )
{
	this->m_iMaxTouchCount = count;
}

int HSPropSpriteInterface::GetMaxTouchCount()
{
	return this->m_iMaxTouchCount;
}

void HSPropSpriteInterface::SetIsListerFristUpdata( bool b )
{
	this->m_isListerFristUpdata = b;
}

bool HSPropSpriteInterface::GetIsListerFristUpdata()
{
	return this->m_isListerFristUpdata;
}

void HSPropSpriteInterface::Updata( float dt )
{
	if (this->GetPropType() == BALLOON_PROPS_UnKnow)
	{
		HSMessageBox("Lack of prop type");
		return;
	}
	if (this->GetIsListerFristUpdata())
	{
		this->AddNodeToParent();
		this->SetIsListerFristUpdata(false);
	}

	if (m_isLister)
	{
		Rest();
		m_isLister = false;
		m_fScale = 1.f;
		this->setVisible(true);
	}
}
