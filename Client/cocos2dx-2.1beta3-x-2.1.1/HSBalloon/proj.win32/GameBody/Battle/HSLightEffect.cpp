#include "HSLightEffect.h"


HSLightEffect::HSLightEffect(void)
{
}


HSLightEffect::~HSLightEffect(void)
{
}

HSLightEffect* HSLightEffect::create()
{
	HSLightEffect* effect = new HSLightEffect;
	if (effect && effect->Init())
	{		
		effect->autorelease();
		return effect;
	}
	CC_SAFE_DELETE(effect);
	return NULL;
}

bool HSLightEffect::Init()
{
	m_pSpx = SPX_Manager::CreateSprite("SPX/miaozhisandian.sprite");
	m_pSpx->SetAction(0,1);
	this->addChild(m_pSpx);
	this->schedule(schedule_selector(HSLightEffect::Updata));
	return true;
}

void HSLightEffect::SetGcPool( HSObjectPool<HSLightEffect*>* gc )
{
	m_gcPool = gc;
}

void HSLightEffect::Updata( float dt )
{

}

void HSLightEffect::PlayEffectBegin( HSBalloonSprite* balloon )
{
	this->setPosition(balloon->getPosition());
	this->setVisible(true);
	m_pSpx->setVisible(true);
	m_pSpx->SetAction(0,1,this,callfuncND_selector(HSLightEffect::PlayEffectEnd),NULL);
}

void HSLightEffect::PlayEffectEnd( CCNode* spxNode,void* data )
{
	this->setVisible(false);
	if (m_gcPool)
	{
		m_gcPool->AddNotUsedObjectFromEnd(this);
	}
}
