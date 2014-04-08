#include "HSSoulEffect.h"


HSSoulEffect::HSSoulEffect(void)
{
	m_pPointArray = NULL;
	m_pSoul = NULL;
	m_fTension = 0.f;
	m_pSoulEffectPool = NULL;
	m_isLister = false;
}


HSSoulEffect::~HSSoulEffect(void)
{
}

HSSoulEffect* HSSoulEffect::create( CCLayer* layer )
{
	HSSoulEffect* effect = new HSSoulEffect;
	if (effect && effect->Init(layer))
	{			
		effect->autorelease();
		return effect;
	}
	CC_SAFE_DELETE(effect);
	return NULL;
}

bool HSSoulEffect::Init( CCLayer* layer )
{
	m_pSoul = CCParticleSystemQuad::create("Particle/SoulRed.plist");
	m_pSoul->setPosition(CCPointZero);
	m_pSoul->stopSystem();
	m_pSoul->setVisible(false);
	this->addChild(m_pSoul);
	
	m_defaultColor = m_pSoul->getStartColor();
	
	this->schedule(schedule_selector(HSSoulEffect::Updata));
	return true;
}

void HSSoulEffect::SetSoulColor( const ccColor4F& color )
{
	m_pSoul->setStartColor(color);
}

void HSSoulEffect::SetTrack( CCPointArray* track )
{
	m_pPointArray = track;
	m_pPointArray->retain();
}

void HSSoulEffect::SetTension( float tension )
{
	m_fTension = tension;
}

void HSSoulEffect::SetGcPool( HSObjectPool<HSSoulEffect*>* pool )
{
	m_pSoulEffectPool = pool;
}

void HSSoulEffect::Play()
{
	this->setPosition(CCPointZero);
	m_pSoul->setPosition(CCPointZero);

	float durationTime = 1.5f;
	if (!ccc4FEqual(m_pSoul->getStartColor(),m_defaultColor))
	{
		durationTime = HSMath::Random(1.5f,4.f);
	}

	CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSSoulEffect::CallFinish));
	CCCardinalSplineTo *move = CCCardinalSplineTo::create(durationTime, m_pPointArray,HSMath::Random(0.5f,1.5f));/*HSMath::Random(1.f,5.f)*/
	CCActionInterval* move_ease_in_out = CCEaseBounceIn::create(move );

	CCDelayTime *delay = CCDelayTime::create(0.3f);

	CCSequence* seq = CCSequence::create(move_ease_in_out, delay,call, NULL);

	m_pSoul->resetSystem();
	m_pSoul->setVisible(true);
	this->runAction(seq);	
}

void HSSoulEffect::CallFinish()
{
	HSSoundManage::ShareSoundManage()->PlayerEffect("special_clear_sound_effect");
	m_isLister = true;
	CC_SAFE_RELEASE_NULL(m_pPointArray);

	m_pSoul->stopSystem();
	m_pSoul->setVisible(false);

	if (!ccc4FEqual(m_pSoul->getStartColor(),m_defaultColor))
	{
		if (HS_GAME_CONFIG_DATA()->stratagemRollBackStepCount > 0)
		{
			//HS_GAME_CONFIG_MUTABLE_DATA()->stratagemCurSec += 3;
			HS_GAME_CONFIG()->AddStratagemTime(3);
			HS_GAME_CONFIG_MUTABLE_DATA()->stratagemRollBackStepCount -= 1;
			HS_GAME_CONFIG_MUTABLE_DATA()->gameScore += 2;
		}
		
	}else{
		HS_GAME_CONFIG()->AddEnergy();
	}

	m_pSoul->setStartColor(m_defaultColor);
	
}

void HSSoulEffect::Updata( float dt )
{
	if (!m_isLister)
	{
		return;
	}
	m_isLister = false;
	m_pSoulEffectPool->AddNotUsedObjectFromEnd(this);
}
