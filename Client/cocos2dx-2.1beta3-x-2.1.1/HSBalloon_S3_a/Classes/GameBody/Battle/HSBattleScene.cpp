#include "HSBattleScene.h"
#include "HSGamePairScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameGuide.h"

HSBattleLayer::HSBattleLayer(void)
{
	m_isInitFinish = false;
	m_pFinger = NULL;
	m_isPauseWorld = false;
	m_pWorld = NULL;
	m_pDebugDraw = NULL;

	m_dropCount = 10;
	m_isPauseGame = false;
	m_dripIndex = 0;
	m_dropIntervalMinTime = 0.5f;
	m_dropIntervalMaxTime = 2.f;
	m_dropIntervalTime = 0.f;
	m_LinearVelocityMinY = 2.f;
	m_LinearVelocityMaxY = 2.f;	
	m_drawLineCount = 0;

	if (HS_IsRunGameGuide())
	{
		m_pRaycast = new HSGameGuideRaycastCallback;
	}else{
		m_pRaycast = new HSRaycastCallback;
	}
	
	m_pRaycast->SetLineList(&m_lineList);
	m_pRaycast->SetLineCount(&m_drawLineCount);
	m_pRaycast->SetPointList(&m_pointList);
	m_pContacListener = new HSContacListener;

	m_pOtherBattleScreen = NULL;
	m_lastTimestamp = 0;
	m_gameTime = 0.f;

	minColorType = BALLOON_COLOR_Blue;
	maxColorType = minColorType;

	m_isGameOver = false;

	m_pHSPropManager = NULL;
	m_lastMoney = 0;

	m_pBattleTranscribe = NULL; 
	m_isAllowRunGameGuide_1014 = true;
}

HSBattleLayer::~HSBattleLayer(void)
{
	CC_SAFE_DELETE(m_pRaycast);
	CC_SAFE_DELETE(m_pContacListener);
	CC_SAFE_DELETE(m_pWorld);
	CC_SAFE_DELETE(m_pDebugDraw);
	CC_SAFE_DELETE(m_pHSPropManager);
 }

bool HSBattleLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	this->setContentSize(CCSizeMake(0,0));
	this->Load();
	this->setTouchEnabled(true);
	//this->setKeypadEnabled(true);

	m_isInitFinish = true;

	return true;
}

void HSBattleLayer::Load()
{
	//@ Load UI
	this->LoadUI();

	//@ Init Prop
	this->InitProp();

	//@ Physics
	this->InitPhysics();

	//@
	this->LoadBalloonTexture2D();

	//@ Create HSBalloon
	this->CreateBalloon();

	//@
	this->InitOtherBattleScreen();

	m_pBattleTranscribe = HSBattleTranscribe::create();
	this->addChild(m_pBattleTranscribe);

// 	CCMenuItemLabel* pLabel = CCMenuItemLabel::create(CCLabelTTF::create("ShiBai","",25.f),this,menu_selector(HSBattleLayer::SendGameOver));
// 	pLabel->setPosition(ccp(50,30));
// 	CCMenu* pMenu = CCMenu::create(pLabel,NULL);
// 	this->addChild(pMenu,20000);

	HS_Play_Music("back_02");

	this->schedule(schedule_selector(HSBattleLayer::Updata));
}
static CCLabelTTF* isOK = NULL;
void HSBattleLayer::LoadUI()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/battle/BattleScene/BattleScene.data","Image/battle/BattleScene/",this);

	CCSprite* pBackground = CCSprite::create("Image/battle/BattleScene/Duizhanditu.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);

	m_pBlueFrame = HS_FIND_UI_PANEL_SPRITE("UI_Hudunxiaoguo","Hudunxiaoguo");
	m_pRedFrame = HS_FIND_UI_PANEL_SPRITE("UI_Shihuaxiaoguo","Shihuaxiaoguo");

	m_pBlueFrame->setVisible(false);
	m_pRedFrame->setVisible(false);

	//@ 头像
	CCSprite* pSelfHeadFrame = HS_FIND_UI_PANEL_SPRITE("UI_TOUXIANG0","TOUXIANG");
	CCSprite* pTargeterHeadFrame = HS_FIND_UI_PANEL_SPRITE("UI_TOUXIANG1","TOUXIANG");

	const char* selfHeadFilePath = CCString::createWithFormat("Image/head/%d.png",HS_TARGET_SELF().iconid())->getCString();

	const char* targeterHeadFilePath = CCString::createWithFormat("Image/head/%d.png",HS_TARGET_TARGET().iconid())->getCString();
	
	CCSprite* pSelfHead = CCSprite::create(selfHeadFilePath);
	CCSprite* pTargeterHead = CCSprite::create(targeterHeadFilePath);

	pSelfHead->setPosition(HS_SizeHalf_Point(pSelfHeadFrame->getContentSize()));
	pTargeterHead->setPosition(HS_SizeHalf_Point(pTargeterHeadFrame->getContentSize()));

	pSelfHeadFrame->addChild(pSelfHead);
	pTargeterHeadFrame->addChild(pTargeterHead);




	//@ Combo
	m_pComboFrame = CCSprite::create("Image/ComboFrame.png");
	m_pComboFrame->setVisible(false);
	m_pComboFrame->setAnchorPoint(HS_ANCHOR_LD);
	this->addChild(m_pComboFrame,1201);
	CCTexture2D* pComboNumberTexture = CCTextureCache::sharedTextureCache()->addImage("Image/ComboNumber.png");
	m_pComboNumber =  CCLabelAtlas::create("0","Image/ComboNumber.png",pComboNumberTexture->getPixelsWide() / 10,pComboNumberTexture->getPixelsHigh(),'0');
	m_pComboNumber->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pComboNumber->setPosition(HS_SizeHalf_Point(m_pComboFrame->getContentSize()));
	m_pComboFrame->addChild(m_pComboNumber);


	//@
	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinqiandituhei","Jinqiandituhei");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/secondNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/secondNumber.png",pMoneyTexture->getPixelsWide() / 10,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);
	



	m_pSelfBattleScreec = CCNode::create();
	m_pSelfBattleScreec->setAnchorPoint(HS_ANCHOR_CENTER);
	this->addChild(m_pSelfBattleScreec,1050);
	m_offsetTop = CCSizeMake(100,200);
	m_offsetBottom = CCSizeMake(10,140);
	m_offsetLeft = CCSizeMake(10,205);
	m_offsetRight = CCSizeMake(10,205);


	//@ 新手引导(指示)
	if(HS_IsRunGameGuide())
	{
		m_pFinger = CCSprite::create("Image/Finger.png");
		m_pFinger->setAnchorPoint(HS_ANCHOR_LD);
		m_pSelfBattleScreec->addChild(m_pFinger,950);
		m_pFinger->setVisible(false);
	}

	isOK = CCLabelTTF::create("","",50.f);
	//isOK->setPosition(ccp(20.f,480.f));
	isOK->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(isOK,1000000);
}

void HSBattleLayer::InitProp()
{
	if (!m_pHSPropManager)
	{
		m_pHSPropManager = new HSPropManager;
	}
}

void HSBattleLayer::LoadBalloonTexture2D()
{
	for (int i=0;i<6;++i)
	{
		int colorTyep = (int)BALLOON_COLOR_Blue;
		BalloonColorType newColorType = (BalloonColorType)(colorTyep + i);
		CCString* pBaseFileName = CCString::createWithFormat("Image/animal_%d.png",i + 1);
		CCString* pLuminousFileName = CCString::createWithFormat("Image/animal_%d_1.png",i + 1);

		CCTexture2D* t = NULL;
		CCTexture2D* t1 = NULL;
		t = CCTextureCache::sharedTextureCache()->addImage(pBaseFileName->getCString());
		if (i == 5)
		{
			t1 = t;
		}else{
			t1 = CCTextureCache::sharedTextureCache()->addImage(pLuminousFileName->getCString());
		}
		

		BalloonTexture2D ballonTexture;
		ballonTexture.base = t;
		ballonTexture.luminous = t1;
		HSBalloonSprite::GetBalloonColorMap()->insert(pair<BalloonColorType,BalloonTexture2D>(newColorType,ballonTexture));
	}
}

void HSBattleLayer::CreateBalloon()
{
	HSAssert(m_pWorld,"");

	int color = HSMath::Random(HS_MIN_BalloonColorType,HS_MAX_BalloonColorType);
	for (int i=0;i<HS_MAX_BalloonColorType;++i)
	{
		int tempColor = (color + i) % HS_MAX_BalloonColorType + 1;
		m_colorTypePool.push_back((BalloonColorType)tempColor);
	}
	if (HS_IsRunGameGuide())
	{
		int count = (int)HSGameGuide::ShaderGameGuide()->m_balloons.size();
		for (int i=0;i<count;++i)
		{
			const GameGuide_BattleLayout_BalloonInfo* pInfo = HSGameGuide::ShaderGameGuide()->GetBallonInfo(i + 1);
			HSBalloonSprite* sprite = HSBalloonSprite::create("Image/animal_3.png",m_pWorld,pInfo->id());
			sprite->setPosition(ccp(pInfo->x(),pInfo->y()));
#ifdef WIN32
			sprite->SetB2Draw(m_pDebugDraw);
#endif
			if (i!=110)
			{
				b2Body* body = sprite->getB2Body();
				body->SetType(b2_dynamicBody);
				body->SetAwake(true);
				body->ResetMassData();
				sprite->setVisible(true);
			}else{
				sprite->setVisible(false);
			}
			


			
			sprite->SetColorType((BalloonColorType)pInfo->color());
			sprite->SetCrossBorderLister(this);
			m_pSelfBattleScreec->addChild(sprite,900);
			m_notDropBalloonList.insert(sprite);
			m_balloonMap.insert(pair<int,HSBalloonSprite*>(pInfo->id(),sprite));
		}
	}else{
		int tempIndex = 0;
		for (int i=0;i<80;++i)
		{
			HSBalloonSprite* sprite = HSBalloonSprite::create("Image/animal_3.png",m_pWorld,tempIndex++);
			sprite->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,HSBase::GetTemplateScreenH() + 300.f));
#ifdef WIN32
			sprite->SetB2Draw(m_pDebugDraw);
#endif
			sprite->setVisible(false);
			sprite->SetCrossBorderLister(this);
			m_pSelfBattleScreec->addChild(sprite,900);
			m_notDropBalloonList.insert(sprite);
			m_balloonMap.insert(pair<int,HSBalloonSprite*>(tempIndex,sprite));
		}
	}
	
}

void HSBattleLayer::InitPhysics()
{
	HSBox2dShapeCache::sharedGB2ShapeCache()->addShapesWithFile("Image/animal.plist");

	b2Vec2 gravity;
	gravity.Set(0.f, -10.f);
	m_pWorld = new b2World(gravity);
	m_pWorld->SetContactListener(m_pContacListener);
	m_pWorld->SetAllowSleeping(true);
	m_pWorld->SetContinuousPhysics(false);
	//false时初始刚体不受重力影响，除非受力
	//m_pWorld->SetWarmStarting(false);
#ifdef WIN32

	m_pDebugDraw = new GLESDebugDraw( HS_PTM_RATIO );
	m_pWorld->SetDebugDraw(m_pDebugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	m_pDebugDraw->SetFlags(flags);

#endif // WIN32	

	b2BodyDef groundBodyDef;	
	groundBodyDef.position.Set(0,0);
	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);

	
	// Define the ground box shape.
	b2EdgeShape groundBox;
	
	m_bottomX = HS_RATIO_b2Vec2(HSVisibleRect::leftBottom().x + m_offsetBottom.width ,HSVisibleRect::leftBottom().y + m_offsetBottom.height);
	m_bottomY = HS_RATIO_b2Vec2(HSVisibleRect::rightBottom().x - m_offsetBottom.width,HSVisibleRect::rightBottom().y + m_offsetBottom.height);

	m_topX = HS_RATIO_b2Vec2(HSVisibleRect::leftTop().x + m_offsetTop.width ,HSVisibleRect::leftTop().y - m_offsetTop.height);
	m_topY = HS_RATIO_b2Vec2(HSVisibleRect::rightTop().x - m_offsetTop.width,HSVisibleRect::rightTop().y - m_offsetTop.height);

	m_leftX = HS_RATIO_b2Vec2(HSVisibleRect::leftTop().x + m_offsetLeft.width ,HSVisibleRect::leftTop().y - m_offsetLeft.height);
	m_leftY = HS_RATIO_b2Vec2(HSVisibleRect::leftBottom().x + m_offsetLeft.width,HSVisibleRect::leftBottom().y + m_offsetBottom.height);

	m_rightX = HS_RATIO_b2Vec2(HSVisibleRect::rightBottom().x - m_offsetRight.width ,HSVisibleRect::rightBottom().y + m_offsetBottom.height);
	m_rightY = HS_RATIO_b2Vec2(HSVisibleRect::rightTop().x - m_offsetRight.width ,HSVisibleRect::rightTop().y - m_offsetRight.height);

	// bottom
	groundBox.Set(m_bottomX,m_bottomY);
	groundBody->CreateFixture(&groundBox,0);

	// top
	//groundBox.Set(m_topX,m_topY);
	//groundBody->CreateFixture(&groundBox,0);

	// left
	groundBox.Set(m_leftX,m_leftY );
	groundBody->CreateFixture(&groundBox,0);

	// right
	groundBox.Set(m_rightX,m_rightY );
	groundBody->CreateFixture(&groundBox,0);


	b2Vec2 bevellL_X = HS_RATIO_b2Vec2(100.f,960.f);
	b2Vec2 bevellL_Y = HS_RATIO_b2Vec2(10.f,1500.f);
	groundBox.Set(bevellL_X,bevellL_Y );
	groundBody->CreateFixture(&groundBox,0);

	b2Vec2 bevellR_X = HS_RATIO_b2Vec2(540,960.f);
	b2Vec2 bevellR_Y = HS_RATIO_b2Vec2(640,1500.f);
	groundBox.Set(bevellR_X,bevellR_Y );
	groundBody->CreateFixture(&groundBox,0);


	m_workArea.lowerBound.Set(HS_VALUE_B2V(0),HS_VALUE_B2V(0));
	m_workArea.upperBound.Set(HS_VALUE_B2V(HSBase::GetTemplateScreenW()),HS_VALUE_B2V(HSBase::GetTemplateScreenH()));

	
}

void HSBattleLayer::InitOtherBattleScreen()
{
	CCSprite* pOtherScreen = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	m_pOtherBattleScreen = CCNode::create();
	m_pOtherBattleScreen->setContentSize(pOtherScreen->getContentSize());
	pOtherScreen->addChild(m_pOtherBattleScreen,1100);

	if (HS_IsRunGameGuide())
	{
		CCSprite* p = CCSprite::create("Image/xinshouyindaotihuan.png");
		p->setPosition(pOtherScreen->getAnchorPointInPoints());
		pOtherScreen->addChild(p,1101);
	}
}

void HSBattleLayer::DestroyBalloon()
{
	this->DestroyLine();

	if ( !m_pRaycast)
	{
		return;
	}

#pragma region __发送销毁气球数据__
	DestroyBalloonRequest destroyBalloonRequest = DestroyBalloonRequest::default_instance();
	destroyBalloonRequest.set_dungoenid(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid());
#pragma endregion __发送销毁气球数据__
	

	const std::vector<HSBalloonSprite*>* passBalloonList = m_pRaycast->GetPassBalloonList();
	if ((int)passBalloonList->size() < 3)
	{
		m_pRaycast->Reset();
		return;
	}

#pragma region __新手引导__
	if (HS_IsRunGameGuide())
	{
		HSGameGuideRaycastCallback* pGameGuideRaycastCallback = dynamic_cast<HSGameGuideRaycastCallback*>(m_pRaycast);
		if (!pGameGuideRaycastCallback)
		{
			HSMessageBox("External behavior, please uninstall reinstall the client");
			return;
		}
		if (!pGameGuideRaycastCallback->IsAllowDestroy())
		{
			pGameGuideRaycastCallback->Reset();
			return;
		}
	}
#pragma endregion __新手引导__




	std::vector<HSBalloonSprite*>::const_iterator it = passBalloonList->begin();

	bool isRemoveLastBalloon = true;
	int passBalloonListSize = (int)passBalloonList->size();
	BalloonColorType tempColorType = (*passBalloonList)[0]->GetColorType();
	if (passBalloonListSize == 4)
	{
		this->SetBalloonColorType(*passBalloonList->rbegin(),BALLOON_COLOR_Camouflage);
		isRemoveLastBalloon = false;
#pragma region __发送销毁气球数据__
		DestroyBalloonRequest_DestroyBalloonInfo* tempDestroyBalloonInfoCamouflage = destroyBalloonRequest.add_destroyballoon();
		tempDestroyBalloonInfoCamouflage->set_count(1);
		tempDestroyBalloonInfoCamouflage->set_type(DestroyBalloonRequest_Type_BALLOON_COLOR_Camouflage);
#pragma endregion __发送销毁气球数据__
	}else if(passBalloonListSize > 4){

		std::vector<HSBalloonSprite*>::const_reverse_iterator crIt = passBalloonList->rbegin();
		if (crIt != passBalloonList->rend())
		{
			//播放连消5个以上球的效果
			HSBalloonSprite* lastS = *crIt;
			this->PlayDestroyBalloon5Effect(lastS->getPosition());
		}

		HSPetrifaction hsPetrifaction;
		hsPetrifaction.count = passBalloonListSize - 4;
		hsPetrifaction.colorType = tempColorType;
		m_PetrifactionBalloonNumList.push_back(hsPetrifaction);
#pragma region __发送销毁气球数据__
		DestroyBalloonRequest_DestroyBalloonInfo* tempDestroyBalloonInfoPetrifaction = destroyBalloonRequest.add_destroyballoon();
		tempDestroyBalloonInfoPetrifaction->set_count(hsPetrifaction.count);
		tempDestroyBalloonInfoPetrifaction->set_type(DestroyBalloonRequest_Type_BALLOON_COLOR_Petrifaction);
#pragma endregion __发送销毁气球数据__
	}

#pragma region __音效__
	switch (tempColorType)
	{
	case BALLOON_COLOR_Blue:
		HS_Play_Sound("effect_02");
		break;
	case BALLOON_COLOR_Purple:
		HS_Play_Sound("effect_04");
		break;
	case BALLOON_COLOR_Yellow:
		HS_Play_Sound("effect_01");
		break;
	case BALLOON_COLOR_Red:
		HS_Play_Sound("effect_00");
		break;
	case BALLOON_COLOR_Green:
		HS_Play_Sound("effect_03");
		break;
	}
#pragma endregion __音效__

	for (;it!= passBalloonList->end();++it)
	{
		HSBalloonSprite* s = *it;
		b2Body* pBody = s->getB2Body();
		
		if (!isRemoveLastBalloon && *it == *passBalloonList->rbegin() )
		{
			//Is the last one
			s->SetLuminous(false);
			this->SetBalloonColorType(s,BALLOON_COLOR_Camouflage);
		}else{

			//this->DestroyBalloon(s);
			s->Destroy();

		}
	}

#pragma region __发送销毁气球数据__
	DestroyBalloonRequest_DestroyBalloonInfo* tempDestroyBalloonInfoNormal = destroyBalloonRequest.add_destroyballoon();
	tempDestroyBalloonInfoNormal->set_count((int)passBalloonList->size());
	tempDestroyBalloonInfoNormal->set_type(DestroyBalloonRequest_Type_BALLOON_COLOR_Normal);

	if (HS_ONLINE)
	{
		HSRequest::ShareRequest()->SendDestroyBalloonRequest(destroyBalloonRequest);
	}
#pragma endregion __发送销毁气球数据__

	m_pRaycast->Reset();
}

bool HSBattleLayer::DestroyBalloon(HSBalloonSprite* s)
{
	if (!s)
	{
		return false;
	}

	//this->PlayDestroyBalloonEffect(s->getPosition());
	//s->Destroy();

	b2Body* pBody = s->getB2Body();
	pBody->SetType(b2_staticBody);
	s->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,HSBase::GetTemplateScreenH() + 300.f));
	s->setVisible(false);
	s->setScale(1.f);
	s->SetLuminous(false);
	pBody->SetAwake(false);

	m_notDropBalloonList.insert(s);

	std::set<HSBalloonSprite*>::iterator dropIt = m_dropBalloonList.find(s);
	if (dropIt != m_dropBalloonList.end())
	{
		m_dropBalloonList.erase(dropIt);
	}

	return true;
}

void HSBattleLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSBattleLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//m_beginPos = pTouch->getLocation();
	m_beginPos = convertTouchToNodeSpaceAR(pTouch);

	m_pRaycast->Reset();
	m_drawLineCount = 0;


	if (m_pWorld && m_pRaycast)
	{
		if (!m_pRaycast->AddBalloon(HSBalloonSprite::GetTouchObject()))
		{
			return false;
		}
	}
	return true;
}

void HSBattleLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	//m_endPos = pTouch->getLocation();
	m_endPos = convertTouchToNodeSpaceAR(pTouch);

	float moveDistancce = ccpDistance(m_beginPos,m_endPos);

	if (moveDistancce < 1.f)
	{
		return;
	}

	if (m_pWorld && m_pRaycast)
	{
		m_pWorld->RayCast(m_pRaycast,HS_CCPoint_To_b2Vec2(m_beginPos),HS_CCPoint_To_b2Vec2(m_endPos));
	}
	
	m_beginPos = m_endPos;
}

void HSBattleLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

	this->DestroyBalloon();

	HSBalloonSprite::SetTouchObject(NULL);
	CCLog("ccTouchEnded");
	/*CCScaleBy* p = CCScaleBy::create(0.5f,0.5f);
	m_pSelfBattleScreec->setContentSize(HSBase::GetTemplateScreenSize());
	m_pSelfBattleScreec->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pSelfBattleScreec->setPosition(HSBase::GetTemplateScreenCentre());
	m_pSelfBattleScreec->runAction(p);*/
}

void HSBattleLayer::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();

#ifdef WIN32
	m_pWorld->DrawDebugData();

	m_pDebugDraw->DrawAABB(&m_workArea,b2Color(255,0,0));
#endif // WIN32

	kmGLPopMatrix();
}

void HSBattleLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}
static float tempTime = 0.f;
static bool isOOK = false;
void HSBattleLayer::Updata( float dt )
{
	
	//isOK->setString(CCString::createWithFormat("%d -- %.4f---%.4f",isOOK,HSTool::S_SEND_TIME,HSTool::S_Receive_TIME)->getCString());
	
	if (m_isPauseGame)
	{
		return;
	}

	if (!IsGameOver())
	{
		if (tempTime > 3.f)
		{
			this->Send();
			tempTime = 0.f;
		}
		else
		{
			tempTime += dt;
		}

		this->Logic(dt);

		this->Logic_GameGuide(dt);

		this->DrawLine(dt);

		this->UpdataCombo(dt);
	}

	this->UpdataWord(dt);

	this->UpdataMoney(dt);
}

void HSBattleLayer::UpdataWord( float dt )
{
	const int32 velocityIterations = 8;
	const int32 positionIterations = 1;

	if (!m_isPauseWorld)
	{
		m_pWorld->Step(dt,velocityIterations,positionIterations);
	}
}

void HSBattleLayer::DrawLine( float dt )
{
	int passBalloonMapSize = (int)m_pRaycast->GetPassBalloonMap()->size();
	if (!m_pRaycast || passBalloonMapSize <= 1 || m_drawLineCount == passBalloonMapSize)
	{
		return;
	}

	HSBalloonSprite* s1 = NULL;
	HSBalloonSprite* s2 = NULL;

	const std::vector<HSBalloonSprite*>* passBalloonList = m_pRaycast->GetPassBalloonList();
	std::vector<HSBalloonSprite*>::const_reverse_iterator it = passBalloonList->rbegin();

	while (it != passBalloonList->rend())
	{
		s2 = *it;
		++it;
		if (it == passBalloonList->rend())
		{
			break;
		}
		s1 = *it;
		this->DrawLine(s1,s2);
		break;
	}
	m_drawLineCount = (int)passBalloonList->size();
}

void HSBattleLayer::DrawLine( HSBalloonSprite* s1,HSBalloonSprite* s2 )
{
	HSAssert(s1 && s2,"");

	CCPoint p1 = s1->getPosition();
	CCPoint p2 = s2->getPosition();

	//s1->setVisible(false);
	//s2->setVisible(false);

	//@ Line
	HSLine* pLine = HSLine::create(s1,s2);
	pLine->setAnchorPoint(HS_ANCHOR_L_CENTER);
	this->addChild(pLine,1200);
	m_lineList.push_back(pLine);

	//@ Point
	HSPoint* pPointA = HSPoint::create(s1);
	this->addChild(pPointA,1201);
	m_pointList.push_back(pPointA);

	this->DrawLine(p1,p2);
}

void HSBattleLayer::DrawLine( const CCPoint& p1,const CCPoint& p2 )
{
#ifdef WIN32
	m_pDebugDraw->DrawSegment(HS_CCPoint_To_b2Vec2(p1),HS_CCPoint_To_b2Vec2(p2),b2Color(0,255,0));
#endif
}

void HSBattleLayer::SetDropCount( int v )
{
	m_dropCount = v;
}

void HSBattleLayer::Logic( float dt )
{
	if (HS_IsRunGameGuide())
	{
		return;
	}
	this->Logic_Drop(dt);
}

void HSBattleLayer::Logic_Drop( float dt )
{
	static float tempPassTime = 0.f;

	m_gameTime += dt;

	if (m_dropCount <= 0)
	{
		m_dropCount = HSMath::Round(1.75f + m_gameTime / 60.f);	//掉落个数公式
		tempPassTime = 0.f;
		return;
	}

	if (HSMath::EqualsWithFloat(m_dropIntervalTime,HS_EPSILON))
	{
		//m_dropIntervalTime = HSMath::Random(m_dropIntervalMinTime,m_dropIntervalMaxTime);
		m_dropIntervalTime = 3.f;
		//m_dropIntervalTime = 0.2f;
	}

	if (tempPassTime < m_dropIntervalTime)
	{
		tempPassTime += dt;
	}else{
		if ((int)m_notDropBalloonList.size() > 0)
		{
			HSBalloonSprite* s =  *m_notDropBalloonList.begin();
			if (this->Drop(s))
			{
				m_notDropBalloonList.erase(m_notDropBalloonList.begin());
				m_dropIntervalTime = 0.f;
				m_dropCount--;
			}
		}
	}
}

bool HSBattleLayer::Drop( HSBalloonSprite* s )
{
	if (!s)
	{
		return false;
	}

	int colorCount = HSMath::Round(2.f + m_gameTime / 45.f);
	maxColorType = (BalloonColorType)(colorCount >= HS_MAX_BalloonColorType ? HS_MAX_BalloonColorType : colorCount);
	
	int colorTypeIndex = HSMath::Random(HS_MIN_BalloonColorType,maxColorType);
	BalloonColorType colorType = m_colorTypePool[colorTypeIndex - 1];
	//colorType = minColorType;

	if (m_dropPetrifaction.count > 0)
	{
		//this->SetBalloonColorType(s,BALLOON_COLOR_Petrifaction);
		s->SetColorType(BALLOON_COLOR_Petrifaction,7.f);
		s->SetWillChangeColorType(m_dropPetrifaction.colorType);
		m_dropPetrifaction.count -= 1;
		++m_dropCount;
		this->PlayRedFrameBlink(1.5f);
		HS_Play_Sound("alert_effect");
	}else{
		this->SetBalloonColorType(s,colorType);
	}
	if (m_dropPetrifaction.count == 0)
	{
		if ((int)m_dropPetrifactionList.size() > 0)
		{
			m_dropPetrifaction = *m_dropPetrifactionList.begin();
			m_dropPetrifactionList.erase(m_dropPetrifactionList.begin());
		}
	}
	

	b2Body* body = s->getB2Body();
	body->SetType(b2_dynamicBody);
	body->SetAwake(true);
	body->SetLinearVelocity(b2Vec2(0.f,HSMath::Random(m_LinearVelocityMinY,m_LinearVelocityMaxY)));
	s->setVisible(true);
	body->ResetMassData();
	m_dropBalloonList.insert(s);

	return true;
}

void HSBattleLayer::ResponseBattleData( BattleDataResponse* pMsg )
{
	if (!pMsg || !m_pOtherBattleScreen)
	{
		return;
	}

	this->UpdataOtherBattleScreen(pMsg->battleinfo());
}

void HSBattleLayer::UpdataOtherBattleScreen( const BattleInfo& info )
{
	if (m_lastTimestamp > info.timestamp())
	{
		HSMessageBox("Illegal information battle");
		return;
	}
	HSAssert(m_pOtherBattleScreen,"");

	//掉落石化气球的总数
	int tempDropPetrifactionCount = info.droppetrifactionlist_size();
	for (int i=0;i<tempDropPetrifactionCount;++i)
	{
		const ::message::BattleInfo_DropPetrifactionBalloon dropPet = info.droppetrifactionlist(i);
		HSPetrifaction hsPetrifaction;
		hsPetrifaction.count = dropPet.count();
		hsPetrifaction.colorType = (BalloonColorType)(dropPet.willchangecolortype());
		m_dropPetrifactionList.push_back(hsPetrifaction);
	}
	

	//使用道具
	this->UpdataOtherBattleScreen_UserPropInfo(info);

	std::vector<CCSprite*>::iterator otherScreenBalloonListIt = m_OtherScreenBalloonList.begin();
	for (;otherScreenBalloonListIt!=m_OtherScreenBalloonList.end();++otherScreenBalloonListIt)
	{
		m_pOtherBattleScreen->removeChild(*otherScreenBalloonListIt);
	}
	m_OtherScreenBalloonList.clear();


	CCSize screenSize = m_pOtherBattleScreen->getContentSize();
	float scaleX = screenSize.width / (HSBase::GetTemplateScreenW() - (m_offsetLeft.width + m_offsetRight.width - 126.f / 2.f));
	float scaleY = 0.f;
	scaleY = scaleX;

	for (int i=0;i<info.balloondatalist_size();++i)
	{
		const BattleInfo_Balloon balloon = info.balloondatalist(i);
		BalloonColorType balloonColorType = (BalloonColorType)balloon.colortype();
		map<BalloonColorType,BalloonTexture2D>::iterator it = HSBalloonSprite::GetBalloonColorMap()->find(balloonColorType);
		CCSprite* ps = NULL;
		if (it != HSBalloonSprite::GetBalloonColorMap()->end())
		{
			ps = CCSprite::createWithTexture(it->second.base);
			
		}else if(balloonColorType == BALLOON_COLOR_Camouflage){

			ps = CCSprite::create("Image/Camouflage.png");

		}else if(balloonColorType == BALLOON_COLOR_Chameleon){

			ps = CCSprite::create("Image/Chameleon.png");

		}else if(it == HSBalloonSprite::GetBalloonColorMap()->end()){

			continue;
		}
		float posX = balloon.x() * scaleX;
		float posY =  (balloon.y() - m_offsetBottom.height) * scaleY;
		ps->setPosition(ccp(posX,posY));
		float radians = 1.f - CC_RADIANS_TO_DEGREES(balloon.angle());
		ps->setRotation(radians);
		ps->setScaleX(scaleX);
		ps->setScaleY(scaleY);
		//ps->setColor(ccc3(0,255,0));
		m_pOtherBattleScreen->addChild(ps);
		m_OtherScreenBalloonList.push_back(ps);
	}
}

void HSBattleLayer::UpdataOtherBattleScreen_UserPropInfo(const BattleInfo& info)
{
	for (int i=0;i<info.userpropid_size();++i)
	{
		HS_Play_Sound("shot_effect");
		const message::PropInfo* pPropInfo = HS_GAME_CACHE()->GetPropInfo(info.userpropid(i));
		switch (pPropInfo->proptype())
		{
		case PropInfo_PropType_ManualProp:
			{
				switch (pPropInfo->manualproptype())
				{
				case PropInfo_ManualPropType_MANUAL_PROPS_LaserGun:
					{
						
					}
					break;
				default:
					HSMessageBox("Error manualproptype");
					break;
				}
			}
			break;
		case PropInfo_PropType_BufferProp:
			{
				switch (pPropInfo->bufferproptype())
				{
				case PropInfo_BufferPropType_BUFFER_PROPS_Chameleon:
					{
						HSBalloonFactory factory;
						m_pWorld->QueryAABB(&factory,m_workArea);

						std::set<HSBalloonSprite*>* pPool = factory.GetSpriteList();
						std::set<HSBalloonSprite*>::iterator it = pPool->begin();	
						for (;it!=pPool->end();++it)
						{
							int index = 0;
							std::vector<BalloonColorType>::iterator colorTypeIt = m_colorTypePool.begin();
							while (index < 3)
							{
								colorTypeIt = colorTypeIt + i;
								if (colorTypeIt == m_colorTypePool.end())
								{
									break;
								}
								HSBalloonSprite* ps = (*it);
								BalloonColorType type = ps->GetColorType();
								if (type == (*colorTypeIt))
								{
									ps->SetColorType(BALLOON_COLOR_Chameleon);
									break;
								}
								++index;
							}
						}
						this->PlayUserPropEffect_OtherScreen(pPropInfo);
					}
					break;
				case PropInfo_BufferPropType_BUFFER_PROPS_Meidusha:
					{
						HSBalloonFactory* pFactory = HS_GET_BattleLayer()->GetScreenAllBalloon();
						HSAssert(pFactory,"");
						
						std::set<HSBalloonSprite*>* pList = pFactory->GetSpriteList();
						std::set<HSBalloonSprite*>::iterator it = pList->begin();
						BalloonColorType tempColorType = BALLOON_COLOR_Unknow;
						for (;it!=pList->end();++it)
						{
							HSBalloonSprite* ps = (*it);
							if (tempColorType == BALLOON_COLOR_Unknow)
							{
								BalloonColorType curtColorType = ps->GetColorType();
								if (curtColorType > BALLOON_COLOR_Unknow && curtColorType <= BALLOON_COLOR_Green)
								{
									tempColorType = curtColorType;
								}else{
									tempColorType = BALLOON_COLOR_Green;
								}
							}
							ps->SetColorType(BALLOON_COLOR_Petrifaction,pPropInfo->duration());
							ps->SetWillChangeColorType(tempColorType);
						}
						CC_SAFE_DELETE(pFactory);

						this->PlayUserPropEffect_OtherScreen(pPropInfo);
					}
					break;
				case PropInfo_BufferPropType_BUFFER_PROPS_EnergyShield:
					{
						//this->PlayUserPropEffect_OtherScreen(pPropInfo);
						this->PlayUserPropEffect_EnergyShield_OtherScreen(pPropInfo);
					}
					break;
				default:
					HSMessageBox("Error bufferproptype");
					break;
				}
			}
			break;
		}
	}
}

void HSBattleLayer::Send()
{
	if (!m_pWorld)
	{
		return;
	}
	HSBalloonFactory factory;
	m_pWorld->QueryAABB(&factory,m_workArea);


	BattleDataRequest* pBattleDataRequest = BattleDataRequest::default_instance().New();
	BattleInfo* pBattleInfo = pBattleDataRequest->mutable_battleinfo();
	pBattleInfo->set_id(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid());

	// 添加石化气球
	for (int i=0;i<(int)m_PetrifactionBalloonNumList.size();++i)
	{
		HSPetrifaction hsPetrifaction = m_PetrifactionBalloonNumList[i];
		BattleInfo_DropPetrifactionBalloon* pDropPetrifactionBalloon = pBattleInfo->add_droppetrifactionlist();
		pDropPetrifactionBalloon->set_count(hsPetrifaction.count);
		pDropPetrifactionBalloon->set_willchangecolortype((int)hsPetrifaction.colorType);
	}
	m_PetrifactionBalloonNumList.clear();

	// 添加屏幕信息
	std::set<HSBalloonSprite*>* pPool = factory.GetSpriteList();
	std::set<HSBalloonSprite*>::iterator it = pPool->begin();	
	for (;it!=pPool->end();++it)
	{
		HSBalloonSprite* ps = (*it);
		BattleInfo_Balloon* pBalloon = pBattleInfo->add_balloondatalist();
		pBalloon->set_id(ps->GetID());
		pBalloon->set_x(ps->getPosition().x);
		pBalloon->set_y(ps->getPosition().y);
		pBalloon->set_angle(ps->getB2Body()->GetAngle());
		pBalloon->set_colortype((int)ps->GetColorType());
	}

	// 添加使用道具
	for (int i=0;i<(int)m_userPropList.size();++i)
	{
		pBattleInfo->add_userpropid((*(m_userPropList.begin() + i))->id());
	}
	this->ClearUserPropInfo();


	//设置时间戳
	pBattleInfo->set_timestamp(HSTime::GetLocalityTimeAccurate());

	if (m_pBattleTranscribe)
	{
		m_pBattleTranscribe->AddFrame(*pBattleInfo);
	}

	//发送网络信息
	if (HS_ONLINE)
	{
		HSRequest::ShareRequest()->SendBattleRequest(pBattleDataRequest);
	}
	else
	{
		this->UpdataOtherBattleScreen(*pBattleInfo);
	}


	pBattleDataRequest->Clear();
	CC_SAFE_DELETE(pBattleDataRequest);
}

void HSBattleLayer::SetBalloonColorType( HSBalloonSprite* ps,const BalloonColorType& colorType )
{
	HSAssert(ps,"");

	ps->SetColorType(colorType);
}

void HSBattleLayer::DestroyLine()
{
	m_pComboFrame->setVisible(false);

	std::vector<HSLine*>::iterator lineIt = m_lineList.begin();
	for (;lineIt!=m_lineList.end();++lineIt)
	{
		this->removeChild(*lineIt);
	}
	m_lineList.clear();
	m_drawLineCount = 0;

	std::vector<HSPoint*>::iterator pointIt = m_pointList.begin();
	for (;pointIt!=m_pointList.end();++pointIt)
	{
		this->removeChild(*pointIt);
	}
	m_pointList.clear();
}

void HSBattleLayer::HandleCross( CCObject* pObj )
{
	HSBalloonSprite* ps = dynamic_cast<HSBalloonSprite*>(pObj);
	if (ps)
	{
		ps->getB2Body()->SetGravityScale(0.2f);
		std::set<HSBalloonSprite*>::iterator dropIt = this->m_dropBalloonList.find(ps);
		if (dropIt != this->m_dropBalloonList.end())
		{
			this->m_dropBalloonList.erase(dropIt);


			if (!m_isGameOver)
			{
				CCScaleBy* p = CCScaleBy::create(1.f,0.6f);
				CCDelayTime* pDelay = CCDelayTime::create(1.f);
				CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::Call_GameOver));
				m_pSelfBattleScreec->setContentSize(HSBase::GetTemplateScreenSize());
				m_pSelfBattleScreec->setPosition(HSBase::GetTemplateScreenCentre());
				m_pSelfBattleScreec->runAction(CCSequence::create(p,pDelay,pCall,NULL));

				

				//缸
				CCScaleBy* p1 = CCScaleBy::create(0.5f,0.6f);
				CCDelayTime* pDelay1 = CCDelayTime::create(1.f);
				CCSprite* pVat = HS_FIND_UI_PANEL_SPRITE("UI_Kongqiceng","Kongqiceng");
				pVat->runAction(CCSequence::create(p1,pDelay1,NULL));

				this->SendGameOver();

				m_isGameOver = true;
				//m_isPauseGame = true;
			}

		}
		this->m_notDropBalloonList.insert(ps);
	}
}

void HSBattleLayer::SendGameOver()
{
	if(HS_ONLINE)
	{
		if (m_pBattleTranscribe)
		{
			m_pBattleTranscribe->Save();
		}
		HSRequest::ShareRequest()->SendBattleResultRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str(),BattleResultRequest_GameStatus_OVER);
	}
	else
	{
		//HS_GO_SCENE(HS_SCENE_GamePairScene);
		BattleResultResponse* pMsg = BattleResultResponse::default_instance().New();
		
		pMsg->set_result(BattleResultResponse_PlayerMatchResult_WIN);

		UpdateUserInfo* selfInfo = pMsg->mutable_selfinfo();
		selfInfo->set_level(1);
		selfInfo->set_experience(3);
		selfInfo->set_wincount(1);
		selfInfo->set_winrate(10.f);

		UpdateUserInfo* targetInfo = pMsg->mutable_tageterinfo();

		targetInfo->set_level(1);
		targetInfo->set_experience(3);
		targetInfo->set_wincount(1);
		targetInfo->set_winrate(10.f);
		ResponseBattleResult(pMsg);

		CC_SAFE_DELETE(targetInfo);
	}
}

void HSBattleLayer::ResponseBattleResult( BattleResultResponse* pMsg )
{
	HS_GAME_CACHE()->m_pBattleResult->Clear();
	HS_GAME_CACHE()->m_pBattleResult->CopyFrom(*pMsg);

	HS_MUTABLE_TARGET_SELF()->set_experience(pMsg->selfinfo().experience());
	HS_MUTABLE_TARGET_SELF()->set_level(pMsg->selfinfo().level());
	HS_MUTABLE_TARGET_SELF()->set_successionwincount(pMsg->selfinfo().successionwincount());
	HS_MUTABLE_TARGET_TARGET()->set_level(pMsg->tageterinfo().level());
	HS_MUTABLE_TARGET_TARGET()->set_successionwincount(pMsg->tageterinfo().successionwincount());
	HS_GAME_CACHE()->AddGold(pMsg->selfinfo().incomgolds());

	if(pMsg->result() == BattleResultResponse_PlayerMatchResult_WIN)//如果赢了，要先播放效果
	{
		this->PlayGameWinEffect();
	}
}

bool HSBattleLayer::IsGameOver()
{
	return m_isGameOver;
}

void HSBattleLayer::AddUserProp( const PropInfo* pPropInfo )
{
	HSAssert(pPropInfo,"");
	m_userPropList.push_back(pPropInfo);
}

void HSBattleLayer::ClearUserPropInfo()
{
	m_userPropList.clear();
}

void HSBattleLayer::PlayUserPropEffect(HSPropIconInterface* pIcon)
{
	HSAssert(pIcon,"");

	CCNode* pParent = HS_FIND_UI_PANEL(CCString::createWithFormat("UI_Daojudituhei%d",pIcon->GetIndex())->getCString());
	CCSprite* pIconFrame = HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_Daojudituhei%d",pIcon->GetIndex())->getCString(),"Daojudituhei");
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	HSAssert(pParent,"");
	HSAssert(pIconFrame,"");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");

	CCPoint targetPos = CCPointZero;
	targetPos.x = pOtherScreen->getPosition().x + pOtherScreenFrame->getContentSize().width / 2.f;
	targetPos.y = pOtherScreen->getPosition().y - pOtherScreenFrame->getContentSize().height / 2.f;

	CCParticleSystemQuad* pSoul = CCParticleSystemQuad::create("Particle/SoulRed.plist");
	CCPoint pos = CCPointZero;
	pos.x = pParent->getPosition().x + pIconFrame->getContentSize().width / 2.f;
	pos.y = pParent->getPosition().y - pIconFrame->getContentSize().height / 2.f;
	pSoul->setPosition(pos);
	//pSoul->setVisible(false);
	this->addChild(pSoul,1000);


	CCMoveTo* pMoveTo = CCMoveTo::create(1.f,targetPos);
	CCCallFuncND* pCall = CCCallFuncND::create(this,callfuncND_selector(HSBattleLayer::Call_PlayUserPropEffect),pIcon);
	pSoul->runAction(CCSequence::create(pMoveTo,pCall,NULL));

}

void HSBattleLayer::Call_PlayUserPropEffect(CCNode* pNode,void* pData)
{
	HSAssert(pData,"");

	CCNode* pOtherScreen = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");

	HSPropIconInterface* pIcon = static_cast<HSPropIconInterface*>(pData);
	HSAssert(pIcon,"");

	std::string fileName = pIcon->GetBasePath() + pIcon->GetPropInfoData()->localname();
	CCSprite* pIconSprite = CCSprite::create(fileName.c_str());
	pIconSprite->setPosition(HS_SizeHalf_Point(pOtherScreen->getContentSize()));
	pOtherScreen->addChild(pIconSprite,10000);

	CCActionInterval*  actionBy = CCScaleBy::create(0.5f, 2.0f, 2.0f);
	CCFadeTo* fadeTo = CCFadeTo::create(0.5f,0.f);
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayUserPropEffect));
	CCSequence* pSequence = CCSequence::create(CCSpawn::create(actionBy,fadeTo,NULL),pCall,NULL);
	pIconSprite->runAction(pSequence);
	pNode->getParent()->removeChild(pNode);
}

void HSBattleLayer::Call_PlayUserPropEffect(CCNode* pNode)
{
	pNode->getParent()->removeChild(pNode);
}

void HSBattleLayer::PlayUserPropEffect_OtherScreen(const PropInfo* propInfo)
{
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");

	CCPoint pos = CCPointZero;
	pos.x = pOtherScreen->getPosition().x + pOtherScreenFrame->getContentSize().width / 2.f;
	pos.y = pOtherScreen->getPosition().y - pOtherScreenFrame->getContentSize().height / 2.f;

	CCParticleSystemQuad* pSoul = CCParticleSystemQuad::create("Particle/SoulRed.plist");
	pSoul->setPosition(pos);
	this->addChild(pSoul,1000);

	CCString* pIconFileName = CCString::createWithFormat("Image/prop/%s",propInfo->localname().c_str());
	pIconFileName->retain();

	CCMoveTo* pMoveTo = CCMoveTo::create(1.f,HSBase::GetTemplateScreenCentre());
	CCCallFuncND* pCall = CCCallFuncND::create(this,callfuncND_selector(HSBattleLayer::Call_PlayUserPropEffect_OtherScreen),(void*)pIconFileName);
	pSoul->runAction(CCSequence::create(pMoveTo,pCall,NULL));
}

void HSBattleLayer::Call_PlayUserPropEffect_OtherScreen(CCNode* pNode,void* pData)
{
	HSAssert(pData,"");

	CCNode* pOtherScreen = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");

	CCString* pIconFileName = static_cast<CCString*>(pData);
	HSAssert(pIconFileName,"");

	

	CCSprite* pIconSprite = CCSprite::create(pIconFileName->getCString());
	pIconSprite->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pIconSprite,10000);

	CCActionInterval*  actionBy = CCScaleBy::create(0.5f, 2.0f, 2.0f);
	CCFadeTo* fadeTo = CCFadeTo::create(0.5f,0.f);
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayUserPropEffect_OtherScreen));
	CCSequence* pSequence = CCSequence::create(CCSpawn::create(actionBy,fadeTo,NULL),pCall,NULL);
	pIconSprite->runAction(pSequence);
	pNode->getParent()->removeChild(pNode);
}

void HSBattleLayer::Call_PlayUserPropEffect_OtherScreen(CCNode* pNode)
{
	pNode->getParent()->removeChild(pNode);
}

HSBalloonFactory* HSBattleLayer::GetScreenAllBalloon()
{
	HSBalloonFactory* pFactory = new HSBalloonFactory;

	this->m_pWorld->QueryAABB(pFactory,m_workArea);

	return pFactory;
}

std::vector<HSBattleLayer::HSPetrifaction>* HSBattleLayer::GetPetrifactionBalloonNumList()
{
	return &m_PetrifactionBalloonNumList;
}

std::vector<HSBattleLayer::HSPetrifaction>* HSBattleLayer::GetDropPetrifactionList()
{
	return &m_dropPetrifactionList;
}

void HSBattleLayer::PlayDestroyBalloonEffect( const CCPoint& pos )
{
	CCParticleSystemQuad* pParticle = CCParticleSystemQuad::create("Particle/DestroyBalloon.plist");
	pParticle->setPosition(pos);
	this->addChild(pParticle,1100);
	CCDelayTime* pDelayTime = CCDelayTime::create(1.f);
	CCCallFuncND* pCall = CCCallFuncND::create(this,callfuncND_selector(HSBattleLayer::Call_PlayDestroyBalloonEffect),NULL);
	pParticle->runAction(CCSequence::create(pDelayTime,pCall,NULL));
}

void HSBattleLayer::Call_PlayDestroyBalloonEffect( CCNode* pNode,void* pData )
{
	pNode->getParent()->removeChild(pNode);
}

void HSBattleLayer::PlayUserPropEffect_EnergyShield_OtherScreen( const PropInfo* propInfo )
{
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");

	CCPoint pos = CCPointZero;
	pos.x = pOtherScreen->getPosition().x + pOtherScreenFrame->getContentSize().width / 2.f;
	pos.y = pOtherScreen->getPosition().y - pOtherScreenFrame->getContentSize().height / 2.f;


	CCString* pIconFileName = CCString::createWithFormat("Image/prop/%s",propInfo->localname().c_str());
	CCSprite* pIconSprite = CCSprite::create(pIconFileName->getCString());
	pIconSprite->setPosition(HS_SizeHalf_Point(pOtherScreen->getContentSize()));
	pOtherScreenFrame->addChild(pIconSprite,10000);


	CCBlink* pBlink = CCBlink::create(propInfo->duration(),propInfo->duration());
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayUserPropEffect_EnergyShield_OtherScreen));
	CCSequence* pSequence = CCSequence::create(pBlink,pCall,NULL);

	pIconSprite->runAction(pSequence);
}

void HSBattleLayer::Call_PlayUserPropEffect_EnergyShield_OtherScreen( CCNode* pNode )
{
	pNode->getParent()->removeChild(pNode);
}

void HSBattleLayer::PlayBlinkEffect( CCNode* pNode , float duration)
{
	CCFadeOut* pFadeOut = CCFadeOut::create(0.2f);
	CCFadeIn* pFadein = CCFadeIn::create(0.5f);
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayBlinkEffect));
// 	CCBlink* pBlink = CCBlink::create(duration,10);
// 	
// 	pNode->runAction(CCSequence::create(pBlink,pCall,NULL));
	CCSequence* pFadeOutAndIn = CCSequence::create(pFadeOut,pFadein,NULL);
	CCRepeat* pRepeat = CCRepeat::create(pFadeOutAndIn,duration);
	pNode->runAction(CCSequence::create(pRepeat,pCall,NULL));
	pNode->setVisible(true);
}

void HSBattleLayer::Call_PlayBlinkEffect( CCNode* pNode )
{
	pNode->setVisible(false);
}

void HSBattleLayer::PlayBlueFrameBlink( float duration )
{
	this->PlayBlinkEffect(m_pBlueFrame,duration);
}

void HSBattleLayer::PlayRedFrameBlink( float duration )
{
	this->PlayBlinkEffect(m_pRedFrame,duration);
}

void HSBattleLayer::Call_GameOver()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleScene* battleScene = (HSBattleScene*)scene;
	HSBattleOverLayer* layer = battleScene->GetHSBattleOverLayer();
	if(layer == NULL)
	{
		layer = HSBattleOverLayer::create();
		battleScene->SetHSBattleOverLayer(layer);
	}
	else
	{
		layer->setVisible(true);
	}

	HSGamePairScene::s_status=status_again;

#pragma region __新手引导__
	if (HS_IsRunGameGuide())
	{
		layer->SetIsWin(true);
		return;
	}
#pragma endregion __新手引导__

	switch (HS_GAME_CACHE()->m_pBattleResult->result())
	{
	case BattleResultResponse_PlayerMatchResult_WIN:
		{
			layer->SetIsWin(true);
		}
		break;
	case BattleResultResponse_PlayerMatchResult_LOST:
		{
			layer->SetIsWin(false);
		}
		break;
	case BattleResultResponse_PlayerMatchResult_DRAW:
		{

		}
		break;
	}
}

void HSBattleLayer::PlayGameWinEffect()
{
	m_isPauseGame = true;

	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");

	CCMoveBy* pMoveBy = CCMoveBy::create(0.5f,HSBase::GetTemplateScreenCentre());
	CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::Call_GameOver));
	pOtherScreen->runAction(CCSequence::create(pMoveBy,pCall,NULL));
}

void HSBattleLayer::UpdataMoney( float dt )
{
	if (m_lastMoney != HS_GAME_CACHE()->GetGold())
	{
		m_lastMoney = HS_GAME_CACHE()->GetGold();
		m_pMoney->setString(CCString::createWithFormat("%d",m_lastMoney)->getCString());
	}
}

void HSBattleLayer::UpdataCombo(float dt)
{
	if (!m_pRaycast)
	{
		return;
	}
	static int lastDrawLineCount = 0;

	const std::vector<HSBalloonSprite*>* passBalloonList = m_pRaycast->GetPassBalloonList();
	std::vector<HSBalloonSprite*>::const_reverse_iterator it = passBalloonList->rbegin();
	m_drawLineCount = (int)passBalloonList->size();
	if (lastDrawLineCount != m_drawLineCount)
	{
		lastDrawLineCount = m_drawLineCount;
		if(m_drawLineCount >= 3)
		{
			HSBalloonSprite* lastBalloon = (*it);
			m_pComboFrame->setVisible(true);
			m_pComboFrame->setPosition(lastBalloon->getPosition());
			m_pComboNumber->setString(CCString::createWithFormat("%d",m_drawLineCount)->getCString());
			
		}else{
			m_pComboFrame->setVisible(false);
		}
	}
}

void HSBattleLayer::PlayDestroyBalloon5Effect(const CCPoint& pos)
{
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");

	CCPoint targetPos = CCPointZero;
	targetPos.x = pOtherScreen->getPosition().x + pOtherScreenFrame->getContentSize().width / 2.f;
	targetPos.y = pOtherScreen->getPosition().y - pOtherScreenFrame->getContentSize().height / 2.f;

	CCParticleSystemQuad* pSoul = CCParticleSystemQuad::create("Particle/SoulRed.plist");
	pSoul->setPosition(pos);
	this->addChild(pSoul,1000);

	CCMoveTo* pMoveTo = CCMoveTo::create(1.f,targetPos);
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayDestroyBalloon5Effect));
	pSoul->runAction(CCSequence::create(pMoveTo,pCall,NULL));
}

void HSBattleLayer::Call_PlayDestroyBalloon5Effect( CCNode* pNode )
{
	pNode->getParent()->removeChild(pNode);
}

HSBalloonSprite* HSBattleLayer::GetBalloonSprite( int key )
{
	map<int,HSBalloonSprite*>::iterator it = m_balloonMap.find(key);
	if (it != m_balloonMap.end())
	{
		return it->second;
	}
	return NULL;
}

CCSprite* HSBattleLayer::GetFingerSprite()
{
	return m_pFinger;
}

void HSBattleLayer::Logic_GameGuide( float dt )
{
	if (!HS_IsRunGameGuide())
	{
		return;
	}
	if (m_isInitFinish)
	{
		m_isInitFinish = false;
		HSGameGuideRaycastCallback* pGameGuideRaycastCallback = dynamic_cast<HSGameGuideRaycastCallback*>(m_pRaycast);
		if (pGameGuideRaycastCallback)
		{
			pGameGuideRaycastCallback->StartGuide(m_pFinger);
		}
	}

	static bool s_isRun_1013 = true;
	int currentStepID = HSGameGuide::ShaderGameGuide()->GetCurrentStepID();
	if (s_isRun_1013 && currentStepID == 1013)
	{
		s_isRun_1013 = false;
		CCSprite* pOtherScreen = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","Duifangduizhanchuangkou");

		CCSprite* s = CCSprite::create("Image/animal_1.png");
		s->setPosition(ccp(467,930));
		s->setScale(0.5f);
		this->addChild(s,11111);

		ccBezierConfig c;
		c.controlPoint_1 = ccp(433,944);
		c.controlPoint_2 = ccp(402,944);
		c.endPosition = ccp(402,891);
		CCBezierTo* pBezierTo = CCBezierTo::create(3.f,c);
		s->runAction(pBezierTo);
	}

	if (m_isAllowRunGameGuide_1014 && currentStepID == 1014)
	{
		m_isAllowRunGameGuide_1014 = false;
		this->Call_GameOver();
	}
}

void HSBattleLayer::keyBackClicked()
{

}

void HSBattleLayer::keyMenuClicked()
{
	if (!HS_IsRunGameGuide())
	{
		HSRequest::ShareRequest()->SendBattleResultRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str(),BattleResultRequest_GameStatus_OVER);
	}
}

map<int,HSBalloonSprite*>* HSBattleLayer::GetBalloonMap()
{
	return &m_balloonMap;
}





















//Scene
HSBattleScene::HSBattleScene(void)
{
	this->hsBattleLayer = NULL;
	this->hsBattleOverLayer = NULL;
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

	if (HS_IsRunGameGuide())
	{
		HSGameGuide::ShaderGameGuide()->Resume(this);
	}

	return true;
}

HSBattleLayer* HSBattleScene::GetHSBattleLayer()
{
	return this->hsBattleLayer;
}

HSBattleOverLayer* HSBattleScene::GetHSBattleOverLayer()
{
	return this->hsBattleOverLayer;
}

void HSBattleScene::SetHSBattleOverLayer( HSBattleOverLayer* hsBattleOverLayer )
{
	this->hsBattleOverLayer = hsBattleOverLayer;
	this->addChild(hsBattleOverLayer,HS_BASE_TAG,HS_BASE_TAG);
}
