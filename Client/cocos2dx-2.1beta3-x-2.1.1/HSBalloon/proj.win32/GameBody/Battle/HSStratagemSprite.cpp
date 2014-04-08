#include "HSStratagemSprite.h"

HSStratagemSprite::HSStratagemSprite( void )
{
	m_isMoveOver = true;
	m_moveStepList.clear();
	m_pNexyStratagem = NULL;
}

HSStratagemSprite::~HSStratagemSprite( void )
{
	m_moveStepList.clear();
	m_pNexyStratagem = NULL;
}

HSStratagemSprite* HSStratagemSprite::create( const message::StratagemData_StratagemBase* pBase,b2World* pWorld )
{
	HSStratagemSprite* sprite = new HSStratagemSprite;
	if (sprite && sprite->Init(pBase,pWorld))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSStratagemSprite::Init( const message::StratagemData_StratagemBase* pBase,b2World* pWorld )
{
	string textureName = "Image/Stratagem/";

	textureName += pBase->texturename();

	bool isOK = this->initWithFile(textureName.c_str());

	this->setPTMRatio(HS_PTM_RATIO);

	b2Body *body = createBody(pBase,pWorld);

	this->setB2Body(body);

	m_sourcePoint = ccp(pBase->sourcex(),pBase->sourcey());

	this->setPosition(m_sourcePoint);

	return !isOK || !body ? false : true;
}

b2Body* HSStratagemSprite::createBody( const message::StratagemData_StratagemBase* pBase,b2World* pWorld )
{
	HSAssert(pWorld,"pWorld == NULL");

	string shapeName = "";
	string textureName = pBase->texturename();
	int begin = textureName.find_last_of('/');
	int end = textureName.find_last_of('.');
	begin == string::npos ? begin = 0 : 1;

	HSAssert(end != string::npos,"textureName Error");

	shapeName = textureName.substr(0,end);

	b2BodyDef def;
	def.position.Set(0,0);
	b2Body* pBody = pWorld->CreateBody(&def);
	pBody->SetAwake(false);

	bool isSucceed = HSBox2dShapeCache::sharedGB2ShapeCache()->addFixturesToBody(pBody,shapeName);
	if(!isSucceed)
	{
		HSMessageBox(shapeName + " \nDoes not exist, please load before creating authority PLIST");
		pWorld->DestroyBody(pBody);
		return NULL;
	}
	return pBody;
}

void HSStratagemSprite::AddMoveStep( const message::StratagemData_StratagemStep* pStep )
{
	m_moveStepList.push_back(pStep);
}

void HSStratagemSprite::Start()
{
	if (m_moveStepList.size() == 0)
	{
		m_isMoveOver = true;
		return;
	}

	m_isMoveOver = false;

	const message::StratagemData_StratagemStep* pMoveStep = m_moveStepList[0];

	m_moveStepList.erase(m_moveStepList.begin());

	CCMoveTo* moveTo = CCMoveTo::create(pMoveStep->duration(),ccp(pMoveStep->x(),pMoveStep->y()));
	CCFiniteTimeAction*  action = CCSequence::create(
		moveTo,
		CCCallFunc::create(this, callfunc_selector(HSStratagemSprite::Over)), 
		NULL);

	//CCLog("%d   %d",pMoveStep->x(),pMoveStep->y());
	this->runAction(action);
}

void HSStratagemSprite::Over()
{
	if (m_pNexyStratagem != NULL)
	{
		m_pNexyStratagem->Start();
		m_pNexyStratagem = NULL;
	}
	m_isMoveOver = true;
}

bool HSStratagemSprite::GetIsMoveOver()
{
	return m_isMoveOver;
}

void HSStratagemSprite::SetNextStratagem( HSStratagemSprite* pNext )
{
	m_pNexyStratagem = pNext;
}

void HSStratagemSprite::MoveToZero()
{
	m_isMoveOver = false;
	CCMoveTo* moveTo = CCMoveTo::create(0.2f,m_sourcePoint);
	CCFiniteTimeAction*  action = CCSequence::create(
		moveTo,
		CCCallFunc::create(this, callfunc_selector(HSStratagemSprite::Over)), 
		NULL);

	this->runAction(action);
}
