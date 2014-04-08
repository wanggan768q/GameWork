#include "HSTouchBalloonEffect.h"


HSTouchBalloonEffect::HSTouchBalloonEffect(void)
{
	m_pParticle1 = NULL;

	m_gcPool = NULL;

	this->m_isLister = false;
}


HSTouchBalloonEffect::~HSTouchBalloonEffect(void)
{
	m_gcPool = NULL;
}

HSTouchBalloonEffect* HSTouchBalloonEffect::create()
{
	HSTouchBalloonEffect* effect = new HSTouchBalloonEffect;
	if (effect && effect->Init())
	{
		effect->autorelease();
		return effect;
	}
	CC_SAFE_DELETE(effect);
	return NULL;
}

bool HSTouchBalloonEffect::Init()
{
	m_pParticle1 = CCParticleSystemQuad::create("Particle/xing.plist");

	m_pParticle1->stopSystem();

	this->addChild(m_pParticle1);

	this->schedule(schedule_selector(HSTouchBalloonEffect::Update));

	return true;
}

void HSTouchBalloonEffect::PlayEffectBegin( CCPoint pos )
{
	if (HS_GAME_CONFIG_DATA()->isKingEffect == true)
	{
		CCTexture2D* kingTexture = CCTextureCache::sharedTextureCache()->addImage("Particle/xing_1.png");
		m_pParticle1->setTexture(kingTexture);

	}else if(HS_GAME_CONFIG_DATA()->isMoneyEffect == true){

		CCTexture2D* goldTexture = CCTextureCache::sharedTextureCache()->addImage("Particle/xing_2.png");
		m_pParticle1->setTexture(goldTexture);

	}else{

		CCTexture2D* normalTexture = CCTextureCache::sharedTextureCache()->addImage("Particle/xing_0.png");
		m_pParticle1->setTexture(normalTexture);
	}
	HS_GAME_CONFIG_MUTABLE_DATA()->isMoneyEffect = false;


	m_pParticle1->setPosition(pos);


	m_pParticle1->resetSystem();
}

void HSTouchBalloonEffect::PlayEffectEnd()
{
	m_pParticle1->stopSystem();
}

void HSTouchBalloonEffect::Update(float dt)
{
	if (m_isLister)
	{
		if (!m_pParticle1->isActive())
		{
			m_isLister = false;
			this->PlayEffectEnd();

			if(!m_gcPool)
			{
				HSMessageBox("HSTouchBalloonEffect gcPool == NULL");
				return;
			}
			m_gcPool->AddNotUsedObjectFromEnd(this);
		}
	}
}

void HSTouchBalloonEffect::SetIsLister( bool b )
{
	this->m_isLister = b;
}

void HSTouchBalloonEffect::SetGcPool( HSObjectPool<HSTouchBalloonEffect*>* gcPool )
{
	this->m_gcPool = gcPool;
}
