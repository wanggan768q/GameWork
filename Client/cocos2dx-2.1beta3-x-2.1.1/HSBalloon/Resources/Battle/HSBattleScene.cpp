#include "HSBattleScene.h"
#include "HSGameSceneJumpManage.h"
//#include "../extensions/physics_nodes/CCPhysicsSprite.h"

static bool isRestarting = false;
static float s_iTime = 0.f;

//////////////////////////////////////////////////////////////////////////
//临时公式计算

static float s_fInterval = 3.f;
static int s_iDefaultCont = 3;
int GetIntervalBattonCont()
{
	int v = (s_iDefaultCont - 1) + (s_iDefaultCont - 2);
	return v;
}








//////////////////////////////////////////////////////////////////////////


HSBattleLayer::HSBattleLayer(void)
{
	m_pWorld = NULL;
	m_debugDraw = NULL;
	m_queryAABB.lowerBound.Set(0,0);
	m_queryAABB.upperBound.Set(480.f / HS_PTM_RATIO,320.f / HS_PTM_RATIO);
	b2Vec2 b = m_queryAABB.GetCenter();
}

HSBattleLayer::~HSBattleLayer(void)
{
	CC_SAFE_DELETE(m_pWorld);
	CC_SAFE_DELETE(m_debugDraw);
	
	vector<HSBallonSprite*>::iterator it = this->m_ballonList.begin();
	while (it != this->m_ballonList.end())
	{
		this->removeChild(*it,true);
		++it;
	}
	//HSBalloonConfig::SharedBallonCofig()->Destroy();
}

bool HSBattleLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//HSTool::SetLayerScale(this);
	this->Load();
	//this->setTouchEnabled(true);
	this->setAccelerometerEnabled(true);	
	return true;
}

void HSBattleLayer::Load()
{
	InitPhysics();
	ccColor4B color = {255,255,255,255};
	//CCLayerColor* c = CCLayerColor::create(color,960,640);
	//this->addChild(c);
	// 	shape = NULL;
	// 	userData = NULL;
	// 	friction = 0.2f;	//摩擦力
	// 	restitution = 0.0f;	//弹性
	// 	density = 0.0f;		//密度
	// 	isSensor = false;	//是否电磁感应

	m_pBallonTestInfo = HSBalloonConfig::SharedBallonCofig()->ReadBallonConfig();
	
	
	HSAssert(m_pBallonTestInfo,"");
	HSBox2dShapeCache::sharedGB2ShapeCache()->addShapesWithFile("Image/qiqiu.plist");
	for (int i=0;i<100/*m_pBallonTestInfo->balloonNumber_*/;++i)
	{
		string fileName = "Image/balloon_";
		fileName += HSMath::ItoA(HSMath::Random(1,5),10) +  ".png";
		//fileName += string("1") +  ".png";

		HSBallonSprite* sprite = HSBallonSprite::create(fileName.c_str(),m_pWorld,i);
		//sprite->setPosition(ccp(HSMath::Random(15,920),0 - HSMath::Random(50,200)));
		sprite->setPosition(ccp(HSMath::Random(30,320),0 - HSMath::Random(50,200)));
		//sprite->setPosition(ccp(480,320));
		sprite->SetB2Draw(m_debugDraw);
		//sprite->setVisible(false);
		this->addChild(sprite);
		m_ballonList.push_back(sprite);		
	}


	{

		CCSize s = HSBase::GetScreenSize();
		float offsetX = s.width - 200.f;
		float offsetY = 20.f;
		float fontSize = 30.f;
		balloonNumber_ = CCLabelTTF::create("balloonNumber_:","Marker Felt",fontSize);
		balloonNumber_->setHorizontalAlignment(kCCTextAlignmentRight);
		balloonNumber_->setPosition(ccp(offsetX,offsetY));
		this->addChild(balloonNumber_);

		linearVelocity = CCLabelTTF::create("LinearVelocity:","Marker Felt",fontSize);
		linearVelocity->setHorizontalAlignment(kCCTextAlignmentRight);
		linearVelocity->setPosition(ccp(offsetX,offsetY+=fontSize));
		this->addChild(linearVelocity);

		linearDamping_ = CCLabelTTF::create("linearDamping_:","Marker Felt",fontSize);
		linearDamping_->setHorizontalAlignment(kCCTextAlignmentRight);
		linearDamping_->setPosition(ccp(offsetX,offsetY+=fontSize));
		this->addChild(linearDamping_);

		restitution___ = CCLabelTTF::create("restitution___:","Marker Felt",fontSize);
		restitution___->setHorizontalAlignment(kCCTextAlignmentRight);
		restitution___->setPosition(ccp(offsetX,offsetY+=fontSize));
		this->addChild(restitution___);

		density_______ = CCLabelTTF::create("density_______:","Marker Felt",fontSize);
		density_______->setHorizontalAlignment(kCCTextAlignmentRight);
		density_______->setPosition(ccp(offsetX,offsetY+=fontSize));
		this->addChild(density_______);

		friction______ = CCLabelTTF::create("friction______:","Marker Felt",fontSize);
		friction______->setHorizontalAlignment(kCCTextAlignmentRight);
		friction______->setPosition(ccp(offsetX,offsetY+=fontSize));
		this->addChild(friction______);

		balloonNumber_->setVisible(false);
		linearVelocity->setVisible(false);
		linearDamping_->setVisible(false);
		restitution___->setVisible(false);
		density_______->setVisible(false);
		friction______->setVisible(false);

		CCLabelTTF* balloonNumberAdd = CCLabelTTF::create("+","Marker Felt",fontSize);
		CCLabelTTF* balloonNumberSub = CCLabelTTF::create("-","Marker Felt",fontSize);

		CCLabelTTF* linearVelocityAdd = CCLabelTTF::create("+","Marker Felt",fontSize);
		CCLabelTTF* linearVelocitySub = CCLabelTTF::create("-","Marker Felt",fontSize);

		CCLabelTTF* linearDamping_Add = CCLabelTTF::create("+","Marker Felt",fontSize);
		CCLabelTTF* linearDamping_Sub = CCLabelTTF::create("-","Marker Felt",fontSize);

		CCLabelTTF* restitution___Add = CCLabelTTF::create("+","Marker Felt",fontSize);
		CCLabelTTF* restitution___Sub = CCLabelTTF::create("-","Marker Felt",fontSize);

		CCLabelTTF* density_______Add = CCLabelTTF::create("+","Marker Felt",fontSize);
		CCLabelTTF* density_______Sub = CCLabelTTF::create("-","Marker Felt",fontSize);

		CCLabelTTF* friction______Add = CCLabelTTF::create("+","Marker Felt",fontSize);
		CCLabelTTF* friction______Sub = CCLabelTTF::create("-","Marker Felt",fontSize);

		CCPoint point = balloonNumber_->getPosition();
		point.x -= balloonNumber_->getContentSize().width / 2.f + fontSize * 5;

		CCMenuItemLabel* balloonNumber_ItemAdd = CCMenuItemLabel::create(balloonNumberAdd,this,menu_selector(HSBattleLayer::BalloonNumberAdd));
		balloonNumber_ItemAdd->setPosition(point);
		point.x += 30.f;
		CCMenuItemLabel* balloonNumber_ItemSub = CCMenuItemLabel::create(balloonNumberSub,this,menu_selector(HSBattleLayer::BalloonNumberSub));
		balloonNumber_ItemSub->setPosition(point);

		point.x -= 30.f;
		point.y += fontSize;
		CCMenuItemLabel* linearVelocityItemAdd = CCMenuItemLabel::create(linearVelocityAdd,this,menu_selector(HSBattleLayer::LinearVelocityAdd));
		linearVelocityItemAdd->setPosition(point);
		point.x += 30.f;
		CCMenuItemLabel* linearVelocityItemSub = CCMenuItemLabel::create(linearVelocitySub,this,menu_selector(HSBattleLayer::LinearVelocitySub));
		linearVelocityItemSub->setPosition(point);

		point.x -= 30.f;
		point.y += fontSize;
		CCMenuItemLabel* linearDamping_ItemAdd = CCMenuItemLabel::create(linearDamping_Add,this,menu_selector(HSBattleLayer::LinearDampingAdd));
		linearDamping_ItemAdd->setPosition(point);
		point.x += 30.f;
		CCMenuItemLabel* linearDamping_ItemSub = CCMenuItemLabel::create(linearDamping_Sub,this,menu_selector(HSBattleLayer::LinearDampingSub));
		linearDamping_ItemSub->setPosition(point);

		point.x -= 30.f;
		point.y += fontSize;
		CCMenuItemLabel* restitution___ItemAdd = CCMenuItemLabel::create(restitution___Add,this,menu_selector(HSBattleLayer::RestitutionAdd));
		restitution___ItemAdd->setPosition(point);
		point.x += 30.f;
		CCMenuItemLabel* restitution___ItemSub = CCMenuItemLabel::create(restitution___Sub,this,menu_selector(HSBattleLayer::RestitutionSub));
		restitution___ItemSub->setPosition(point);

		point.x -= 30.f;
		point.y += fontSize;
		CCMenuItemLabel* density_______ItemAdd = CCMenuItemLabel::create(density_______Add,this,menu_selector(HSBattleLayer::DensityAdd));
		density_______ItemAdd->setPosition(point);
		point.x += 30.f;
		CCMenuItemLabel* density_______ItemSub = CCMenuItemLabel::create(density_______Sub,this,menu_selector(HSBattleLayer::DensitySub));
		density_______ItemSub->setPosition(point);

		point.x -= 30.f;
		point.y += fontSize;
		CCMenuItemLabel* friction______ItemAdd = CCMenuItemLabel::create(friction______Add,this,menu_selector(HSBattleLayer::FrictionAdd));
		friction______ItemAdd->setPosition(point);
		point.x += 30.f;
		CCMenuItemLabel* friction______ItemSub = CCMenuItemLabel::create(friction______Sub,this,menu_selector(HSBattleLayer::FrictionSub));
		friction______ItemSub->setPosition(point);
		

		CCMenu* balloonNuberMenu = CCMenu::create(balloonNumber_ItemAdd,balloonNumber_ItemSub,
			linearVelocityItemAdd,linearVelocityItemSub,
			linearDamping_ItemAdd,linearDamping_ItemSub,
			restitution___ItemAdd,restitution___ItemSub,
			density_______ItemAdd,density_______ItemSub,
			friction______ItemAdd,friction______ItemSub,
			NULL);	
		balloonNuberMenu->setPosition(CCPointZero);
		this->addChild(balloonNuberMenu);
		balloonNuberMenu->setVisible(false);


		CCLabelTTF* saveConfig = CCLabelTTF::create(HS_GBK_TO_UTF8("保存"),"Marker Felt",fontSize);
		CCLabelTTF* restConfig = CCLabelTTF::create(HS_GBK_TO_UTF8("重置"),"Marker Felt",fontSize);
		CCLabelTTF* defaultConfig = CCLabelTTF::create(HS_GBK_TO_UTF8("默认"),"Marker Felt",fontSize);
		CCMenuItemLabel* saveConfigItem = CCMenuItemLabel::create(saveConfig,this,menu_selector(HSBattleLayer::SaveConfig));
		CCMenuItemLabel* restConfigItem = CCMenuItemLabel::create(restConfig,this,menu_selector(HSBattleLayer::RestConfig));
		CCMenuItemLabel* defaultConfigItem = CCMenuItemLabel::create(defaultConfig,this,menu_selector(HSBattleLayer::DefaultConfig));
		saveConfigItem->setPosition(CCPointZero);
		restConfigItem->setPosition(CCPointZero);
		defaultConfigItem->setPosition(CCPointZero);

		CCMenu* menu = CCMenu::create(saveConfigItem,restConfigItem,defaultConfigItem,NULL);
		menu->alignItemsVertically();
		menu->setPosition(420,80);
		this->addChild(menu);
	}
	

	this->schedule(schedule_selector(HSBattleLayer::Update));
}

void HSBattleLayer::BalloonNumberAdd(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");	
	m_pBallonTestInfo->balloonNumber_ += 10;
	SaveConfig(NULL);
}

void HSBattleLayer::BalloonNumberSub(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->balloonNumber_ -= 10;
	SaveConfig(NULL);
}

void HSBattleLayer::LinearVelocityAdd(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->linearVelocity += 0.1f;
	SaveConfig(NULL);
}
void HSBattleLayer::LinearVelocitySub(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->linearVelocity -= 0.1f;
	SaveConfig(NULL);
}

void HSBattleLayer::LinearDampingAdd(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->linearDamping_ += 0.1f;
	SaveConfig(NULL);
}
void HSBattleLayer::LinearDampingSub(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->linearDamping_ -= 0.1f;
	SaveConfig(NULL);
}

void HSBattleLayer::RestitutionAdd(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->restitution___ += 0.01f;
	if (m_pBallonTestInfo->restitution___ > 1.f)
	{
		HSMessageBox("Value range [0,1]");
		m_pBallonTestInfo->restitution___ = 1.f;
	}
	SaveConfig(NULL);
}
void HSBattleLayer::RestitutionSub(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->restitution___ -= 0.01f;
	if (m_pBallonTestInfo->restitution___ < 0.f)
	{
		HSMessageBox("Value range [0,1]");
		m_pBallonTestInfo->restitution___ = 0.f;
	}
	SaveConfig(NULL);
}

void HSBattleLayer::DensityAdd(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->density_______ += 1.f;
	SaveConfig(NULL);
}
void HSBattleLayer::DensitySub(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");;
	m_pBallonTestInfo->density_______ -= 1.f;
	SaveConfig(NULL);
}

void HSBattleLayer::FrictionAdd(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->friction______ += 0.01f;
	if(m_pBallonTestInfo->friction______ > 1.f)
	{
		HSMessageBox("Value range [0,1]");
		m_pBallonTestInfo->friction______ = 1.f;
	}
	SaveConfig(NULL);
}
void HSBattleLayer::FrictionSub(CCObject* obj)
{
	HSAssert(m_pBallonTestInfo,"");
	m_pBallonTestInfo->friction______ -= 0.01f;
	if(m_pBallonTestInfo->friction______ < 0.f)
	{
		HSMessageBox("Value range [0,1]");
		m_pBallonTestInfo->friction______ = 0.f;
	}
	SaveConfig(NULL);
}

void HSBattleLayer::SaveConfig(CCObject* obj)
{
	//HSBalloonConfig::SharedBallonCofig()->SaveBallonConfig();
	CCDirector::sharedDirector()->replaceScene(HSBattleScene::create());
}

void HSBattleLayer::RestConfig(CCObject* obj)
{
	HSBalloonConfig::SharedBallonCofig()->ReadBallonConfig();
}

void HSBattleLayer::DefaultConfig(CCObject* obj)
{
	//HSBalloonConfig::SharedBallonCofig()->RestBallonConfig();
	CCDirector::sharedDirector()->replaceScene(HSBattleScene::create());
}

void HSBattleLayer::InitPhysics()
{
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);

	b2Vec2 gravity;
	gravity.Set(0.f, 5.f);
	m_pWorld = new b2World(gravity);

	// Do we want to let bodies sleep?
	m_pWorld->SetAllowSleeping(false);

	m_pWorld->SetContinuousPhysics(false);
	m_debugDraw = new GLESDebugDraw( HS_PTM_RATIO );
	m_pWorld->SetDebugDraw(m_debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner


	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2EdgeShape groundBox;

// 	bottomX = b2Vec2(HSVisibleRect::leftBottom().x/HS_PTM_RATIO,HSVisibleRect::leftBottom().y/HS_PTM_RATIO);
// 	bottomY = b2Vec2(HSVisibleRect::rightBottom().x/HS_PTM_RATIO,HSVisibleRect::rightBottom().y/HS_PTM_RATIO - 10000);
// 	
// 	topX = b2Vec2(HSVisibleRect::leftTop().x/HS_PTM_RATIO,HSVisibleRect::leftTop().y/HS_PTM_RATIO);
// 	topY = b2Vec2(HSVisibleRect::rightTop().x/HS_PTM_RATIO,HSVisibleRect::rightTop().y/HS_PTM_RATIO);
// 
// 	leftX = b2Vec2(HSVisibleRect::leftTop().x/HS_PTM_RATIO,HSVisibleRect::leftTop().y/HS_PTM_RATIO);
// 	leftY = b2Vec2(HSVisibleRect::leftBottom().x/HS_PTM_RATIO,HSVisibleRect::leftBottom().y/HS_PTM_RATIO);
// 	
// 	rightX = b2Vec2(HSVisibleRect::rightBottom().x/HS_PTM_RATIO,HSVisibleRect::rightBottom().y/HS_PTM_RATIO);
// 	rightY = b2Vec2(HSVisibleRect::rightTop().x/HS_PTM_RATIO,HSVisibleRect::rightTop().y/HS_PTM_RATIO);


	//bottomX = b2Vec2(HSVisibleRect::leftBottom().x /HS_PTM_RATIO,HSVisibleRect::leftBottom().y/HS_PTM_RATIO);
	//bottomY = b2Vec2(HSVisibleRect::rightBottom().x/HS_PTM_RATIO,HSVisibleRect::rightBottom().y/HS_PTM_RATIO - 100);
	bottomX = HS_RATIO_b2Vec2(HSVisibleRect::leftBottom().x,HSVisibleRect::leftBottom().y);
	bottomY = HS_RATIO_b2Vec2(HSVisibleRect::rightBottom().x,HSVisibleRect::rightBottom().y-100000.f);




	//topX = b2Vec2(HSVisibleRect::leftTop().x/HS_PTM_RATIO,(HSVisibleRect::leftTop().y + 40.f)/HS_PTM_RATIO);
	//topY = b2Vec2(HSVisibleRect::rightTop().x/HS_PTM_RATIO,(HSVisibleRect::rightTop().y + 40.f)/HS_PTM_RATIO);
	topX = HS_RATIO_b2Vec2(HSVisibleRect::leftTop().x,HSVisibleRect::leftTop().y - 20.f);
	topY = HS_RATIO_b2Vec2(HSVisibleRect::rightTop().x,HSVisibleRect::rightTop().y - 20.f);

	//leftX = b2Vec2((HSVisibleRect::leftTop().x + 30.f)/HS_PTM_RATIO,HSVisibleRect::leftTop().y/HS_PTM_RATIO);
	//leftY = b2Vec2((HSVisibleRect::leftBottom().x + 30.f)/HS_PTM_RATIO,HSVisibleRect::leftBottom().y/HS_PTM_RATIO);
	leftX = HS_RATIO_b2Vec2(HSVisibleRect::leftTop().x + 10.f,HSVisibleRect::leftTop().y);
	leftY = HS_RATIO_b2Vec2(HSVisibleRect::leftBottom().x + 10.f,HSVisibleRect::leftBottom().y);

	//rightX = b2Vec2((HSVisibleRect::rightBottom().x + 30.f)/HS_PTM_RATIO,HSVisibleRect::rightBottom().y/HS_PTM_RATIO);
	//rightY = b2Vec2((HSVisibleRect::rightTop().x + 30.f)/HS_PTM_RATIO,HSVisibleRect::rightTop().y/HS_PTM_RATIO);
	rightX = HS_RATIO_b2Vec2(HSVisibleRect::rightBottom().x - 10.f,HSVisibleRect::rightBottom().y);
	rightY = HS_RATIO_b2Vec2(HSVisibleRect::rightTop().x - 10.f,HSVisibleRect::rightTop().y);
	
	
	// bottom
	groundBox.Set(bottomX,bottomY);
	groundBody->CreateFixture(&groundBox,0);

	// top
	groundBox.Set(topX,topY);
	groundBody->CreateFixture(&groundBox,0);

	// left
	groundBox.Set(leftX,leftY );
	groundBody->CreateFixture(&groundBox,0);

	// right
	groundBox.Set(rightX,rightY );
	groundBody->CreateFixture(&groundBox,0);

	worldVectorl = groundBody->GetWorldCenter();

	
}

void HSBattleLayer::MenuEvent(CCObject* sender)
{
	CCLog("test");
}

void HSBattleLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSBattleLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//CCDirector::sharedDirector()->replaceScene(HSBattleScene::create());
	
	return true;
}

void HSBattleLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleLayer::ResponseBattleEnter(message::BattleEnterResponse* response)
{
	
}

void HSBattleLayer::draw()
{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommend to disable it
	//
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();

	m_pWorld->DrawDebugData();

// 	m_debugDraw->DrawPoint(bottomX,10,b2Color(255,0,0));
// 	m_debugDraw->DrawPoint(bottomY,10,b2Color(255,0,0));
// 
// 	m_debugDraw->DrawPoint(topX,10,b2Color(255,0,0));
// 	m_debugDraw->DrawPoint(topY,10,b2Color(255,0,0));
// 
// 	m_debugDraw->DrawPoint(leftX,10,b2Color(255,0,0));
// 	m_debugDraw->DrawPoint(leftY,10,b2Color(255,0,0));
// 
// 	m_debugDraw->DrawPoint(rightX,10,b2Color(255,0,0));
// 	m_debugDraw->DrawPoint(rightY,10,b2Color(255,0,0));

	m_debugDraw->DrawAABB(&m_queryAABB,b2Color(255,0,0));

	kmGLPopMatrix();
}

void HSBattleLayer::Update(float dt)
{
	int32 velocityIterations = 1;
	int32 positionIterations = 1;
	m_pWorld->Step(dt,velocityIterations,positionIterations);

	static const int bufSize = 1024;
	char buf[bufSize]= {0};

	if(m_pBallonTestInfo == NULL)
	{
		return;
	}
	memset(buf,'\0',bufSize);
	sprintf_s(buf,"balloonNumber_:  %d",m_pBallonTestInfo->balloonNumber_);
	this->balloonNumber_->setString(buf);

	memset(buf,'\0',bufSize);
	sprintf_s(buf,"linearVelocity:  %.2f",m_pBallonTestInfo->linearVelocity);
	this->linearVelocity->setString(buf);

	memset(buf,'\0',bufSize);
	sprintf_s(buf,"linearDamping_:  %.2f",m_pBallonTestInfo->linearDamping_);
	this->linearDamping_->setString(buf);

	memset(buf,'\0',bufSize);
	sprintf_s(buf,"restitution___:  %.2f",m_pBallonTestInfo->restitution___);
	this->restitution___->setString(buf);

	memset(buf,'\0',bufSize);
	sprintf_s(buf,"density_______:  %.2f",m_pBallonTestInfo->density_______);
	this->density_______->setString(buf);

	memset(buf,'\0',bufSize);
	sprintf_s(buf,"friction______:  %.2f",m_pBallonTestInfo->friction______);
	this->friction______->setString(buf);

	s_iTime += dt;
	if (s_iTime > s_fInterval)
	{
		s_iTime = 0.f;
		int intervalBallonCount = GetIntervalBattonCont();
		int index = 0;
		//ccTouchBegan(NULL,NULL);
		b2Body* b = m_pWorld->GetBodyList();
		b = b->GetNext();
		b = b->GetNext();
		b = b->GetNext();
		for (;b;b = b->GetNext())
		{
			HSBallonSprite* sprite = (HSBallonSprite*)b->GetUserData();
			if (sprite != NULL)
			{
				b2Body* spriteBody = sprite->getB2Body();
				if (spriteBody->GetType() == b2_staticBody)
				{
					spriteBody->SetType(b2_dynamicBody);
					spriteBody->SetLinearVelocity(b2Vec2(0.f,HSMath::Random(3.f,5.f)));
					CCLog("b2_dynamicBody : %d",sprite->GetID());
					index++;
					if (index == intervalBallonCount)
					{
						s_iDefaultCont++;
						return;
					}					
				}
			}else
			{				
				HSBattonFactory battonFactory;
				m_pWorld->QueryAABB(&battonFactory,m_queryAABB);
			}			
		}
	}
}




//Scene
HSBattleScene::HSBattleScene(void)
{
	this->hsBattleLayer = NULL;
}

HSBattleScene::~HSBattleScene(void)
{
}

bool HSBattleScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsBattleLayer = HSBattleLayer::create();
	this->addChild(this->hsBattleLayer,HS_BASE_TAG,HS_BASE_TAG);
	//this->addChild(HSDrawLines::create(),HS_BASE_TAG,HS_BASE_TAG);
	return true;
}