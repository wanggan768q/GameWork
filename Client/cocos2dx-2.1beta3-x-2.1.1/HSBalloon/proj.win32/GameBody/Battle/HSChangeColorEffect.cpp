#include "HSChangeColorEffect.h"


HSChangeColorEffect::HSChangeColorEffect(void)
{
	m_WillChangeColorType = BALLOON_COLOR_UNKNOW;
	m_pWillChanggeTexture = NULL;
	m_pWillChangeBalloon = NULL;
}


HSChangeColorEffect::~HSChangeColorEffect(void)
{
}

HSChangeColorEffect* HSChangeColorEffect::create()
{
	HSChangeColorEffect* effect = new HSChangeColorEffect;
	if (effect && effect->Init())
	{		
		effect->autorelease();
		return effect;
	}
	CC_SAFE_DELETE(effect);
	return NULL;
}

bool HSChangeColorEffect::Init()
{
	m_pSpx = SPX_Manager::CreateSprite("SPX/bianseqiqiu.sprite");
	//m_pSpx->SetAction(0,1);
	this->addChild(m_pSpx);
	this->schedule(schedule_selector(HSChangeColorEffect::Updata));
	return true;
}

void HSChangeColorEffect::SetGcPool( HSObjectPool<HSChangeColorEffect*>* gc )
{
	m_gcPool = gc;
}

void HSChangeColorEffect::Updata( float dt )
{

}

void HSChangeColorEffect::PlayEffectBegin(HSBalloonSprite* balloon,const BalloonColorType& type, CCTexture2D* pTexture)
{
	m_pWillChangeBalloon = balloon;
	m_WillChangeColorType = type;
	m_pWillChanggeTexture = pTexture;

	this->setPosition(m_pWillChangeBalloon->getPosition());
	this->setVisible(true);
	m_pSpx->setVisible(true);
	m_pSpx->SetAction(0,1,this,callfuncND_selector(HSChangeColorEffect::PlayEffectEnd),NULL);
}

void HSChangeColorEffect::PlayEffectEnd(CCNode* spxNode,void* data)
{
	this->setVisible(false);
	m_pWillChangeBalloon->setTexture(m_pWillChanggeTexture);
	m_pWillChangeBalloon->SetColorType(m_WillChangeColorType);
	if (m_gcPool)
	{
		m_gcPool->AddNotUsedObjectFromEnd(this);
	}
}