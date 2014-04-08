#include "HSBallonSprite.h"


HSBallonSprite::HSBallonSprite(void)
{
	m_pWorld = NULL;
}


HSBallonSprite::~HSBallonSprite(void)
{
	
}

HSBallonSprite* HSBallonSprite::create( const char* fileName,b2World* world ,int id)
{
	HSBallonSprite* sprite = new HSBallonSprite;
	if (sprite && sprite->InitWithFile(fileName,world,id))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSBallonSprite::InitWithFile( const char* fileName,b2World* world ,int id)
{
	HSAssert(world,"");

	m_id = id;

	bool isInitOK = this->initWithFile(fileName);

	this->setPTMRatio(HS_PTM_RATIO);

	b2Body *body = createBody(world);

	this->setB2Body(body);
	
	return !isInitOK || !body ? false : true;
}

b2Body* HSBallonSprite::createBody(b2World* world )
{
	HSAssert(world,"");
	HSAssert(m_pBallonTestInfo,"");
	m_pWorld = world;

	b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	bodyDef.type = b2_staticBody;
	//bodyDef.linearVelocity.Set(0,10.f);
	//bodyDef.linearDamping = 0.5f;
	bodyDef.bullet = true;
	//CCSize screen = HSBase::GetScreenSize();
	//bodyDef.position.Set(HS_VALUE_B2V(screen.width),HS_VALUE_B2V(screen.height));
	CCSize texturSize = this->getTexture()->getContentSize();
	bodyDef.position.Set(HS_VALUE_B2V(texturSize.width),HS_VALUE_B2V(texturSize.height));

	b2Body *body = world->CreateBody(&bodyDef);
	body->SetUserData(this);
	body->SetAwake(true);

	//HSBox2dShapeCache::sharedGB2ShapeCache()->addFixturesToBody(body,"balloon_1");
	
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.87f;
	fixtureDef.restitution = 0.2f;
	fixtureDef.isSensor = false;

	b2PolygonShape shape;
	//shape.Set(vertices, 6);
	shape.SetAsBox(1.f, 1.2f);
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
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

bool HSBallonSprite::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) ) return false;

	CCLog("ccTouchBegan: %d",m_id);
	getB2Body()->SetType(b2_staticBody);
	getB2Body()->SetLinearVelocity(b2Vec2(0,0));
	m_pWorld->DestroyBody(getB2Body());
	//this->setPosition(ccp(HSMath::Random(15,920),0 - HSMath::Random(50,200)));
	return true;
}

void HSBallonSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBallonSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBallonSprite::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBallonSprite::draw()
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

void HSBallonSprite::onEnter()
{	
	CCPhysicsSprite::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void HSBallonSprite::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCPhysicsSprite::onExit();
}

void HSBallonSprite::ActivateCollisions()
{
	b2Fixture *fixture = this->getB2Body()->GetFixtureList();
	b2Filter filter = fixture->GetFilterData();
	filter.categoryBits = 0x0001;
	filter.maskBits = 0x0001;
	fixture->SetFilterData(filter);
}

void HSBallonSprite::DeactivateCollisions()
{
	b2Fixture *fixture = this->getB2Body()->GetFixtureList();
	b2Filter filter = fixture->GetFilterData();
	filter.categoryBits = 0;
	filter.maskBits = 0;
	fixture->SetFilterData(filter);
}

cocos2d::CCRect HSBallonSprite::TextureRect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool HSBallonSprite::ContainsTouchLocation( CCTouch* touch )
{
	return TextureRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void HSBallonSprite::SetColorType( BallonColorType type )
{
	m_BallonColorType = type;
}
