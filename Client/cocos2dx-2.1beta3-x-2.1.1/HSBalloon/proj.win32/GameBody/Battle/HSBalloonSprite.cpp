#include "HSBalloonSprite.h"


HSBalloonSprite* HSBalloonSprite::s_TouchBalloon = NULL;

HSBalloonSprite::HSBalloonSprite(void)
{
	m_pWorld = NULL;
	m_pParticle4 = NULL;
	m_fScale = 1.f;

	m_isOnlyAddParticle = false;

	m_isTouchEndOver = false;

	m_pParticle1 = NULL;
	m_pParticle2 = NULL;
	m_pParticle3 = NULL;

	m_gcPool = NULL;
	m_isLister = false;

	m_spxShield = NULL;

	m_isTouchEnabled = true;
}


HSBalloonSprite::~HSBalloonSprite(void)
{
	
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

	b2Body *body = createBody(world);

	this->setB2Body(body);

	//m_PosTTF = CCLabelTTF::create("0","Marker Felt",32);
	//this->addChild(m_PosTTF);

	return !isInitOK || !body ? false : true;
}

bool HSBalloonSprite::InitWithFile( const char* fileName,b2World* world ,int id)
{
	HSAssert(world,"");

	m_id = id;

	m_pWorld = world;

	bool isInitOK = this->initWithFile(fileName);

	this->setPTMRatio(HS_PTM_RATIO);

	b2Body *body = createBody(world);

	this->setB2Body(body);

	return !isInitOK || !body ? false : true;
}

b2Body* HSBalloonSprite::createBody(b2World* world )
{
	HSAssert(world,"world");
	//HSAssert(m_pBallonTestInfo,"m_pBallonTestInfo");
	m_pWorld = world;

	b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	bodyDef.type = b2_staticBody;
	//bodyDef.linearVelocity.Set(0,7.f);
	//bodyDef.linearDamping = 0.5f;
	bodyDef.bullet = true;
	//CCSize screen = HSBase::GetScreenSize();
	//bodyDef.position.Set(HS_VALUE_B2V(screen.width),HS_VALUE_B2V(screen.height));
	CCSize texturSize = this->getTexture()->getContentSize();
	bodyDef.position.Set(HS_VALUE_B2V(texturSize.width),HS_VALUE_B2V(texturSize.height));

	b2Body *body = world->CreateBody(&bodyDef);
	HSBox2dShapeCache::sharedGB2ShapeCache()->addFixturesToBody(body,"animal_1");
	body->SetUserData(this);
	body->SetAwake(false);
	body->SetSleepingAllowed(true);
	body->SetBullet(true);
// 	b2Fixture* fixtureList = body->GetFixtureList();
// 	fixtureList->SetDensity(1.f);
// 	fixtureList->SetFriction(0.87f);
// 	fixtureList->SetRestitution(0.2f);
// 	fixtureList->SetSensor(true);








	
// 	b2FixtureDef fixtureDef;
// 	fixtureDef.density = 1.f;
// 	fixtureDef.friction = 0.87f;
// 	fixtureDef.restitution = 0.2f;
// 	fixtureDef.isSensor = false;
// 
// 	b2PolygonShape shape;
// 	//shape.Set(vertices, 6);
// 	//shape.SetAsBox(1.f, 1.2f);
// 	shape.SetAsBox(1.f, 1.f);
// 	fixtureDef.shape = &shape;
// 	body->CreateFixture(&fixtureDef);
// 
// 	m_pBallonTestInfo = HSBalloonConfig::SharedBallonCofig()->GetBalloonConfigData();
// 	b2BodyDef bodyDef;
// 	bodyDef.type = b2_dynamicBody;
// 	bodyDef.linearVelocity.Set(0,m_pBallonTestInfo->linearVelocity);
// 	//bodyDef.linearVelocity.Set(0,HSMath::Random(0.5f,20.f));
// 	bodyDef.linearDamping = m_pBallonTestInfo->linearDamping_;
// 	CCSize screen = HSBase::GetScreenSize();
// 	bodyDef.position.Set(HS_B2V_VALUE(screen.width),HS_B2V_VALUE(screen.height));
// 
// 	b2Body *body = world->CreateBody(&bodyDef);
// 
// 	//HSBox2dShapeCache::sharedGB2ShapeCache()->addFixturesToBody(body,"balloon_1");
// 
// 	b2FixtureDef fixtureDef;
// 	fixtureDef.density = m_pBallonTestInfo->density_______;
// 	fixtureDef.friction = m_pBallonTestInfo->friction______;
// 	fixtureDef.restitution = m_pBallonTestInfo->restitution___;
// 	fixtureDef.isSensor = false;
// 
// 	b2PolygonShape shape;
// 	//shape.Set(vertices, 6);
// 	shape.SetAsBox(1.f, 0.8f);
// 	fixtureDef.shape = &shape;
// 	body->CreateFixture(&fixtureDef);
	
	return body;
}

bool HSBalloonSprite::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	if (!pTouch && !pEvent)
	{
		HSBalloonSprite::s_TouchBalloon = this;
		return true;
	}	

	if ( !ContainsTouchLocation(pTouch) ) return false;

	if (m_spxShield)
	{
		m_spxShield->setVisible(true);
		m_spxShield->SetAction(2,1,this,callfuncND_selector(HSBalloonSprite::CallSpxShieldAction_2),NULL);
		return false;
	}

	this->TouchBalloonBegin();
	
	return true;
}

void HSBalloonSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBalloonSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{	
	if (m_isTouchEndOver)
	{
	}

	TouchBalloonEnd();

}

void HSBalloonSprite::TouchBalloonEnd()
{
	Rest();
	m_isLister = true;
}

void HSBalloonSprite::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBalloonSprite::SetIsTouchEndOver(bool b)
{
	m_isTouchEndOver = b;
}

void HSBalloonSprite::draw()
{
	CCPhysicsSprite::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();

	//m_debugDraw->DrawSolidPolygon(vertices,6,b2Color(255,255,0));
	//CCPoint p = this->getPosition();
	//m_debugDraw->DrawCircle(b2Vec2(p.x,p.y),31.f,b2Color(255,255,0));
	//m_debugDraw->DrawString(0,0,)
	kmGLPopMatrix();
}

void HSBalloonSprite::onEnter()
{	
	CCPhysicsSprite::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
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
// 	filter.categoryBits = 0x0001;
// 	filter.maskBits = 0x0001;
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
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool HSBalloonSprite::ContainsTouchLocation( CCTouch* touch )
{
	if(!touch || !m_isTouchEnabled)
	{
		return false;
	}

	if (this->getPosition().y < 100.f )
	{
		return false;
	}

	return TextureRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void HSBalloonSprite::SetColorType( BalloonColorType type )
{
	m_BallonColorType = type;
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
	m_fY = getPosition().y;
	if (this->getPosition().x < 0.f || this->getPosition().x > HSBase::GetTemplateScreenW())
	{
		this->setVisible(false);
	}
	if (m_isLister)
	{
		Rest();
		m_isLister = false;
		if(!m_gcPool)
		{
			HSMessageBox("HSBalloonSprite gcPool == NULL");
			return;
		}
		m_fScale = 1.f;
		m_gcPool->AddNotUsedObjectFromEnd(this);
		//this->setVisible(true);
	}
}

HSBalloonSprite* HSBalloonSprite::GetTouchBaloon()
{
	return HSBalloonSprite::s_TouchBalloon;
}

void HSBalloonSprite::SetTouchBaloon( HSBalloonSprite* balloon )
{
	HSBalloonSprite::s_TouchBalloon = balloon;
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
	HSBalloonSprite::s_TouchBalloon = this;

	m_fScale = 1.15f;

	HSBalloonConfig::SharedBalloonCofig()->DribbleLogic(m_BallonColorType,this->GetID());
}

void HSBalloonSprite::AddShield()
{
	if (m_spxShield == NULL)
	{
		m_spxShield = SPX_Manager::CreateSprite("SPX/hudun.sprite");
		m_spxShield->SetAction(0,1,this,callfuncND_selector(HSBalloonSprite::CallSpxShieldAction_1),NULL);
		m_spxShield->setPosition(HS_SizeHalf_Point(this->getContentSize()));

		this->addChild(m_spxShield);
	}
	
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
	//this->setPosition(HSBase::GetTemplateScreenCentre());
	if (m_spxShield)
	{
		this->removeChild(m_spxShield,true);
		m_spxShield = NULL;
	}
	//this->setVisible(false);
}

void HSBalloonSprite::CallSpxShieldAction_1( CCNode* spxNode,void* pData )
{
	m_spxShield->setVisible(true);
	m_spxShield->SetAction(1);
}

void HSBalloonSprite::CallSpxShieldAction_2( CCNode* spxNode,void* pData )
{
	this->removeChild(m_spxShield,true);
	m_spxShield = NULL;
}

void HSBalloonSprite::SetTouchEnabled( bool b )
{
	m_isTouchEnabled = b;
}
