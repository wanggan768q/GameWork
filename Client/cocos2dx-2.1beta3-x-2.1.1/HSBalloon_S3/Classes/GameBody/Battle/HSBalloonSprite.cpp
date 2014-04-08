#include "HSBalloonSprite.h"
#include "HSBattleScene.h"

HSBalloonSprite* HSBalloonSprite::m_pTouchObject = NULL;

std::map<BalloonColorType,BalloonTexture2D> HSBalloonSprite::m_balloonColorMap;

HSBalloonSprite::HSBalloonSprite(void)
{
	m_fScale = 1.f;
	m_gcPool = NULL;
	m_isLister = false;
	m_isTouchEnabled = true;
	m_isLuminous = false;
	m_isCamouflage = false;
	m_willChangeColorType = BALLOON_COLOR_Unknow;
	m_pCrossBorderInterface = NULL;
	m_spxCamouflage = NULL;
	m_spxChameleon = NULL;
	m_destroyPos = CCPointZero;
    m_isWillDeath = false;
    m_isAllowUseFastProp = true;
}


HSBalloonSprite::~HSBalloonSprite(void)
{
	this->SetLuminous(false);
}

HSBalloonSprite* HSBalloonSprite::create( const char* fileName,b2World* world ,int id)
{
	HSBalloonSprite* sprite = new HSBalloonSprite;
	if (sprite && sprite->InitWithFile(fileName,world,id))
	{
		sprite->schedule(schedule_selector(HSBalloonSprite::Update));
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

HSBalloonSprite* HSBalloonSprite::create(CCTexture2D* texture,b2World* world,int id)
{
	HSBalloonSprite* sprite = new HSBalloonSprite;
	if (sprite && sprite->InitWithTexture(texture,world,id))
	{
		sprite->schedule(schedule_selector(HSBalloonSprite::Update));
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSBalloonSprite::InitWithTexture(CCTexture2D* texture,b2World* world,int id)
{
	HSAssert(world,"");

	m_id = id;

	m_pWorld = world;

	bool isInitOK = this->initWithTexture(texture);

	this->setPTMRatio(HS_PTM_RATIO);

	b2Body *body = this->CreateBody(world);
    
	this->setB2Body(body);
	
// 	CCLabelTTF* id_TTF = CCLabelTTF::create(CCString::createWithFormat("%d",id)->getCString(),"",32);
// 	this->addChild(id_TTF);

	return !isInitOK || !body ? false : true;
}

bool HSBalloonSprite::InitWithFile( const char* fileName,b2World* world ,int id)
{
	HSAssert(world,"");

	m_id = id;

	m_pWorld = world;
    
	bool isInitOK = this->initWithFile(fileName);
    //bool isInitOK = this->initWithSpriteFrame(pBalloonSpriteFrame);

	this->setPTMRatio(HS_PTM_RATIO);

	b2Body *body = this->CreateBody(world);
    
	this->setB2Body(body);
    
	return !isInitOK || !body ? false : true;
}

b2Body* HSBalloonSprite::CreateBody(b2World* world )
{
	HSAssert(world,"world");

	m_pWorld = world;

	b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	bodyDef.type = b2_staticBody;
	bodyDef.bullet = true;
	CCSize texturSize = this->getTexture()->getContentSize();
	bodyDef.position.Set(HS_VALUE_B2V(texturSize.width),HS_VALUE_B2V(texturSize.height));

	b2Body *body = world->CreateBody(&bodyDef);
	HSBox2dShapeCache::sharedGB2ShapeCache()->addFixturesToBody(body,"animal_1");
	body->SetUserData(this);
	body->SetAwake(false);
	body->SetSleepingAllowed(true);
	body->SetBullet(false);
    
    b2Fixture* fixture = body->GetFixtureList();
    while(fixture)
    {
        fixture->SetRestitution(HSFormula::TanXiang());
        fixture=fixture->GetNext();
    }


	//this->setVisible(false);

	return body;
}

bool HSBalloonSprite::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	if (!pTouch && !pEvent)
	{
		return true;
	}

	if ( !ContainsTouchLocation(pTouch) ) return false;

	if (m_BallonColorType == BALLOON_COLOR_Chameleon)
	{
		return true;
	}

	HSBalloonSprite::SetTouchObject(this);
    
    if (m_BallonColorType == BALLOON_COLOR_Bomb)
    {
        this->Logic_Bomb();
        return true;
    }
    
	
	//this->TouchBalloonBegin();
	return false;
}

void HSBalloonSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBalloonSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{	
	//TouchBalloonEnd();
}

void HSBalloonSprite::TouchBalloonEnd()
{
	Rest();
	m_isLister = true;
}

void HSBalloonSprite::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBalloonSprite::draw()
{
	CCPhysicsSprite::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();

#ifdef WIN32
// 	float lx = this->getPosition().x - this->getContentSize().width / 2.f;
// 	float ly = this->getPosition().y - this->getContentSize().height / 2.f;
// 	float w = this->getContentSize().width;
// 	float h = this->getContentSize().height;
// 	m_aabb.lowerBound.Set(HS_VALUE_B2V(lx),HS_VALUE_B2V(ly));
// 	m_aabb.upperBound.Set(HS_VALUE_B2V(w),HS_VALUE_B2V(h));

//	m_debugDraw->DrawAABB(&m_aabb,b2Color(255,0,0));

#endif // WIN32
	kmGLPopMatrix();
}

void HSBalloonSprite::onEnter()
{	
	CCPhysicsSprite::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
}

void HSBalloonSprite::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCPhysicsSprite::onExit();
}

void HSBalloonSprite::ActivateCollisions()
{
// 	b2Fixture *fixture = this->getB2Body()->GetFixtureList();
// 	b2Filter filter = fixture->GetFilterData();
// 	filter.categoryBits = 2;
// 	filter.maskBits = 2;
// 	fixture->SetFilterData(filter);
}

void HSBalloonSprite::DeactivateCollisions()
{
// 	b2Fixture *fixture = this->getB2Body()->GetFixtureList();
// 	b2Filter filter = fixture->GetFilterData();
// 	filter.categoryBits = 0;
// 	filter.maskBits = 0;
// 	fixture->SetFilterData(filter);
}

cocos2d::CCRect HSBalloonSprite::TextureRect()
{
// 	CCPoint p = this->getPosition();
// 	CCSize s = getTexture()->getContentSize();
// 	return CCRectMake(p.x - s.width / 2, p.y -s.height / 2, s.width, s.height);

	CCSize s = getTexture()->getContentSize();
    //CCSize s = getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool HSBalloonSprite::ContainsTouchLocation( CCTouch* touch )
{
	if(!touch || !m_isTouchEnabled)
	{
		return false;
	}

	//return TextureRect().containsPoint(touch->getLocation());
	return TextureRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void HSBalloonSprite::SetColorType( BalloonColorType type ,float petrifactionTime/* = 0.f*/)
{
    //设置石化球的时候 如果当前是石化状态 就跳过
    if (type == BALLOON_COLOR_Petrifaction && m_BallonColorType == BALLOON_COLOR_Petrifaction)
    {
        return;
    }
    this->SetLastColorType(m_BallonColorType);

	m_BallonColorType = type;

	std::map<BalloonColorType,BalloonTexture2D>::iterator it = m_balloonColorMap.find(m_BallonColorType);
	if (it != m_balloonColorMap.end())
	{
		this->setTexture(it->second.base);
		this->SetLuminousTexture2D(it->second.luminous);
	}
    
#define HS_BOMB_ACTION_TAG 0x2001
    if ( m_BallonColorType == BALLOON_COLOR_Bomb )
    {
        CCRepeatForever* pBombAction = CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleBy::create(0.5f, 1.1f),
                                                                                                CCScaleTo::create(0.5f, 1)));
        pBombAction->setTag(HS_BOMB_ACTION_TAG);
        this->runAction(pBombAction);
        //return;
    }else{
        if (this->getActionByTag(HS_BOMB_ACTION_TAG))
        {
            this->stopActionByTag(HS_BOMB_ACTION_TAG);
        }
    }

	if (m_BallonColorType == BALLOON_COLOR_Petrifaction)
	{
		//HSAssert(petrifactionTime > 2.f,"petrifactionTime > 2.f");
		petrifactionTime < 2.f ? petrifactionTime = 7.f : 0;

		CCDelayTime* pDelayTime = CCDelayTime::create(petrifactionTime /*- 2.f*/);
		CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBalloonSprite::CallRemovePetrifactionEffect_FirstTwoSeconds));
		this->runAction(CCSequence::create(pDelayTime,pCall,NULL));
	}

	if (m_BallonColorType == BALLOON_COLOR_Camouflage)
	{
		if (!m_spxCamouflage)
		{
			m_spxCamouflage = SPX_Manager::CreateSprite("SPX/Caisemao.sprite");
			m_spxCamouflage->SetAction(0,1);
			m_spxCamouflage->setPosition(HS_SizeHalf_Point(this->getContentSize()));
			m_spxCamouflage->setVisible(false);
			this->addChild(m_spxCamouflage);
		}
		m_isCamouflage = true;
	}else{
		m_isCamouflage = false;
	}

	if (m_BallonColorType == BALLOON_COLOR_Chameleon)
	{
		if (!m_spxChameleon)
		{
			m_spxChameleon = SPX_Manager::CreateSprite("SPX/Chameleon.sprite");
			m_spxChameleon->SetAction(0,1);
			m_spxChameleon->setPosition(HS_SizeHalf_Point(this->getContentSize()));
			m_spxChameleon->setVisible(false);
			this->addChild(m_spxChameleon);
		}
		m_spxChameleon->setVisible(true);
		m_spxChameleon->SetAction(0);

		CCDelayTime* pDelayTime = CCDelayTime::create(2.f);
		CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBalloonSprite::Call_BALLOON_COLOR_Chameleon));
		m_spxChameleon->runAction(CCSequence::create(pDelayTime,pCall,NULL));
	}
}

CCAffineTransform HSBalloonSprite::nodeToParentTransform()
{
	
	b2Vec2 pos = m_pB2Body->GetPosition();

	float x = pos.x * m_fPTMRatio;
	float y = pos.y * m_fPTMRatio;

	if (m_bIgnoreAnchorPointForPosition)
	{
		x += m_obAnchorPointInPoints.x;
		y += m_obAnchorPointInPoints.y;
	}

	// Make matrix
	float radians = m_pB2Body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);


	if (! m_obAnchorPointInPoints.equals(CCPointZero))
	{
		x += c*(-m_obAnchorPointInPoints.x) + -s*(-m_obAnchorPointInPoints.y);
		y += s*(-m_obAnchorPointInPoints.x) + c*(-m_obAnchorPointInPoints.y);
	}

	// Rot, Transition Matrix
	m_sTransform = CCAffineTransformMake(c * m_fScale, s * m_fScale,
		-s * m_fScale, c * m_fScale,
		x, y);

	//return CCPhysicsSprite::nodeToParentTransform();
	return m_sTransform;
}

BalloonColorType HSBalloonSprite::GetColorType()
{
	return m_BallonColorType;
}

void HSBalloonSprite::Update( float dt )
{
	if (m_isCamouflage)
	{
		if (m_spxCamouflage)
		{
			m_spxCamouflage->setVisible(true);
		}
	}
	if (this->GetColorType() != BALLOON_COLOR_Camouflage)
	{
		if (m_spxCamouflage)
		{
			m_spxCamouflage->setVisible(false);
		}
		m_isCamouflage = false;
	}
    
    
    








	m_fY = getPosition().y;
	

	if (m_pCrossBorderInterface)
	{
		CCPoint pos = this->getPosition();
		bool b1 = pos.x < 10.f && pos.y < HSBase::GetTemplateScreenH() - 140.f;
		bool b2 = pos.x > HSBase::GetTemplateScreenW() - 10.f &&  pos.y < HSBase::GetTemplateScreenH() - 140.f;
		//if (this->getPosition().y <  -this->getContentSize().height)
		if( b1 || b2 )
		{
			//this->setVisible(false);
			m_pCrossBorderInterface->HandleCross(this);
		}
	}
    
    
    
    
    this->Logic_WillDeath(dt);
    //this->Logic_Bomb(dt);

}

void HSBalloonSprite::Logic_WillDeath(float dt)
{
    //监听快死亡状态
    HSBattleLayer* pBattleLayer = HS_GET_BattleLayer();
    std::set<HSBalloonSprite*>* pDropList = pBattleLayer->GetDropBalloonList();
    if(pDropList && pDropList->size() > 40)
    {
        SetWillDeathStart(true);
        //濒死 状态
        pBattleLayer->PlayWillDieEffecr();
        
        if(m_isAllowUseFastProp)
        {
            m_isAllowUseFastProp = false;
            if(HS_GAME_CACHE()->m_isOpenFastProp)
            {
                if(pBattleLayer->GetPropWave() == NULL)
                {
                    pBattleLayer->SetPropWave(HSProp_Wave::create());
                }
            }
        }
        
        
        
    }else{
        SetWillDeathStart(false);
        //取消濒死 状态
        pBattleLayer->CancelPlayWillDieEffecr();
        
        m_isAllowUseFastProp = true;
    }
}

void HSBalloonSprite::SetWillDeathStart(bool isWillDeath)
{
    std::map<BalloonColorType,BalloonTexture2D>::iterator it = m_balloonColorMap.find(m_BallonColorType);
    
    if (it != m_balloonColorMap.end())
    {
        if (isWillDeath)
        {
            if (!m_isWillDeath)
            {
                m_isWillDeath = true;
            }
            
            if(it->second.willDeath)
            {
                this->setTexture(it->second.willDeath);
            }
            
        }else{
            if(m_isWillDeath)
            {
                this->SetColorType(m_BallonColorType);
                m_isWillDeath = false;
            }
            
        }

    }
}

void HSBalloonSprite::SetGcPool( HSObjectPool<HSBalloonSprite*>* gcPool )
{
	this->m_gcPool = gcPool;
}

void HSBalloonSprite::SetID( int id )
{
	this->m_id = id;
}

int HSBalloonSprite::GetID()
{
	return m_id;
}

void HSBalloonSprite::TouchBalloonBegin()
{
	m_fScale = 1.15f;
}

void HSBalloonSprite::SetIsLiester( bool b )
{
	m_isLister = b;
}

void HSBalloonSprite::Rest()
{
	m_fScale = 1.f;
	DeactivateCollisions();
	getB2Body()->SetType(b2_staticBody);
	this->setPosition(ccp(this->getContentSize().width + 100.f,-800.f));
}

void HSBalloonSprite::SetTouchEnabled( bool b )
{
	m_isTouchEnabled = b;
}

void HSBalloonSprite::SetB2Draw( GLESDebugDraw* debugDraw )
{
	m_debugDraw = debugDraw;
}

HSBalloonSprite* HSBalloonSprite::GetTouchObject()
{
	return HSBalloonSprite::m_pTouchObject;
}

void HSBalloonSprite::SetTouchObject( HSBalloonSprite* ps )
{
	HSBalloonSprite::m_pTouchObject = ps;
}

void HSBalloonSprite::SetLuminous( bool b )
{
    std::map<BalloonColorType,BalloonTexture2D>::iterator it = m_balloonColorMap.find(m_BallonColorType);
    
    if (it != m_balloonColorMap.end())
    {
        if (b)
        {
            if(it->second.luminous)
            {
                this->setTexture(it->second.luminous);
            }
            
            
            if (this->GetColorType() == BALLOON_COLOR_Camouflage)
            {
                if (m_spxCamouflage)
                {
                    m_spxCamouflage->SetAction(1);
                }
            }
        }else{
            if (it->second.base)
            {
                this->setTexture(it->second.base);
            }
            
            if (this->GetColorType() == BALLOON_COLOR_Camouflage)
            {
                if (m_spxCamouflage)
                {
                    m_spxCamouflage->SetAction(0);
                }
            }
        }
    }
}

void HSBalloonSprite::SetLuminousTexture2D( CCTexture2D* texture)
{
	//m_pLuminousTexture = texture;
}

void HSBalloonSprite::CallRemovePetrifactionEffect_FirstTwoSeconds()
{
	CCTintTo* pTintTo1 = CCTintTo::create(0.5f,0,0,0);
	CCTintTo* pTintTo2 = CCTintTo::create(0.5f,255,255,255);
	CCTintTo* pTintTo3 = (CCTintTo*)pTintTo1->copy()->autorelease();
	CCTintTo* pTintTo4 = (CCTintTo*)pTintTo2->copy()->autorelease();
	CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBalloonSprite::CallRemovePetrifactionEffect_LastTwoSeconds));
	this->runAction(CCSequence::create(pTintTo1,pTintTo2,pTintTo3,pTintTo4,pCall,NULL));
}

void HSBalloonSprite::CallRemovePetrifactionEffect_LastTwoSeconds()
{
	if (m_willChangeColorType != BALLOON_COLOR_Unknow && m_willChangeColorType != BALLOON_COLOR_Petrifaction)
	{
		this->SetColorType(m_willChangeColorType);
        this->SetLastColorType(m_willChangeColorType);
        
		m_willChangeColorType = BALLOON_COLOR_Unknow;
	}else{
		this->SetColorType(BALLOON_COLOR_Blue);
	}
}

void HSBalloonSprite::SetLastColorType(BalloonColorType type)
{
    m_lastColorType = type;
}

std::map<BalloonColorType,BalloonTexture2D>* HSBalloonSprite::GetBalloonColorMap()
{
	return &HSBalloonSprite::m_balloonColorMap;
}

void HSBalloonSprite::setScalePhysics( float fScale )
{
	setScale(fScale);

	CCPhysicsSprite::setScale(fScale);

	b2Body* pBody = this->getB2Body();

	HSBox2dTool::ScaleBody(pBody,m_fScale);
}


void HSBalloonSprite::setScale( float fScale )
{
	m_fScale = fScale;
	this->setScaleX(m_fScale);
	this->setScaleY(m_fScale);
}

float HSBalloonSprite::getScale()
{
	return m_fScale;
}

void HSBalloonSprite::setScaleX( float fScaleX )
{
	m_fScale = fScaleX;
	CCPhysicsSprite::setScaleX(fScaleX);
}

void HSBalloonSprite::setScaleY( float fScaleY )
{
	m_fScale = fScaleY;
	CCPhysicsSprite::setScaleY(fScaleY);
}

float HSBalloonSprite::getScaleX()
{
	return CCPhysicsSprite::getScaleX();
}

float HSBalloonSprite::getScaleY()
{
	return CCPhysicsSprite::getScaleY();
}

void HSBalloonSprite::SetWillChangeColorType( BalloonColorType willColorType )
{
	m_willChangeColorType = willColorType;
}

void HSBalloonSprite::SetCrossBorderLister( HSCrossBorderInterface* pCross )
{
	m_pCrossBorderInterface = pCross;
}

void HSBalloonSprite::Call_BALLOON_COLOR_Chameleon( )
{
	m_spxChameleon->setVisible(false);
	m_spxChameleon->SetAction(0,1);
    
    BalloonColorType tempColorType = (BalloonColorType)HSMath::Random((int)BALLOON_COLOR_Blue,(int)BALLOON_COLOR_Green);
    this->SetLastColorType( tempColorType );
	this->SetColorType(tempColorType);
}

void HSBalloonSprite::PlayDestroyBalloonEffect()
{
	this->setVisible(false);

	CCParticleSystemQuad* pParticle = CCParticleSystemQuad::create("Particle/DestroyBalloon.plist");
	pParticle->setPosition(m_destroyPos);
	HS_GET_BattleLayer()->addChild(pParticle,1100);
	CCDelayTime* pDelayTime = CCDelayTime::create(1.f);
	CCCallFuncND* pCall_01 = CCCallFuncND::create(this,callfuncND_selector(HSBalloonSprite::Call_PlayDestroyBalloonEffect),NULL);
	
	pParticle->runAction(CCSequence::create(pDelayTime,pCall_01,NULL));
}

void HSBalloonSprite::Call_PlayDestroyBalloonEffect( CCNode* pNode,void* pData )
{
	pNode->getParent()->removeChild(pNode);
}

CCFiniteTimeAction* HSBalloonSprite::PassAction()
{
    CCScaleTo* pScale_01 = CCScaleTo::create(0.1f,0.9f);
	CCScaleTo* pScale_02 = CCScaleTo::create(0.1f,1.2f);
    CCScaleTo* pScale_03 = CCScaleTo::create(0.1f,1.f);
    
    CCFiniteTimeAction* action = CCSequence::create(pScale_01,pScale_02,pScale_03,NULL);
    
    return action;
}

void HSBalloonSprite::Destroy()
{
	m_destroyPos = this->getPosition();
	CCCallFunc* pCall_01 = CCCallFunc::create(this,callfunc_selector(HSBalloonSprite::PlayDestroyBalloonEffect));
	CCCallFunc* pCall_02 = CCCallFunc::create(this,callfunc_selector(HSBalloonSprite::NotificationBattleLayerRecycle));
	this->runAction(CCSequence::create(this->PassAction(),pCall_01,pCall_02,NULL));
}

void HSBalloonSprite::NotificationBattleLayerRecycle()
{
	HS_GET_BattleLayer()->DestroyBalloon(this);
}

void HSBalloonSprite::RandomColorType()
{
    BalloonColorType colorType = (BalloonColorType)HSMath::Random(HS_MIN_BalloonColorType,HS_MAX_BalloonColorType);
    SetColorType(colorType);
    SetLastColorType(colorType);
}

void HSBalloonSprite::Logic_Bomb()
{
    
    HSBalloonSprite* ps = HSBalloonSprite::GetTouchObject();
    if ( ps )
    {
        if (ps->GetColorType() != BALLOON_COLOR_Bomb)
        {
            return;
        }
        
        CCPoint pos = this->getPosition();
        CCPoint LD , RU;
        LD.x = pos.x - 120.f / 2.f;
        LD.y = pos.y - 120.f / 2.f;
        
        RU.x = pos.x + 120.f / 2.f;
        RU.y = pos.y + 120.f / 2.f;
        
        HSBalloonFactory factory;
        b2AABB aabb;
        aabb.lowerBound.Set(HS_VALUE_B2V(LD.x),HS_VALUE_B2V(LD.y));
        aabb.upperBound.Set(HS_VALUE_B2V(RU.x),HS_VALUE_B2V(RU.y));
        
        m_pWorld->QueryAABB(&factory, aabb);
        
        std::set<HSBalloonSprite*>*  balloonList = factory.GetSpriteList();
        std::set<HSBalloonSprite*>::iterator it = balloonList->begin();
        
        for (;it != balloonList->end();++it)
        {
            HSBalloonSprite* balloon = (*it);
            if (balloon->GetColorType() != BALLOON_COLOR_Bomb)
            {
                balloon->Destroy();
            }
        }
        
        SPX_Sprite* pSpx = SPX_Manager::CreateSprite("SPX/bomb.sprite");
        pSpx->SetAction(0,1);
        pSpx->setPosition(ps->getPosition());
        ps->getParent()->addChild(pSpx,905);
        
        
        ps->stopAllActions();
        ps->Destroy();
        HS_Play_Sound("bomb");
        HSBalloonSprite::SetTouchObject(NULL);
    }
}

















