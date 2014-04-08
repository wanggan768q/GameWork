#include "HSBattleScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameGuide.h"

int HSBattleLayer::s_rhythm[HSBattleLayer::MAX_RHYTHM] = {1,2,3,4,5,6};

CCPoint HSBattleLayer::SCREEN_BESIDES = ccp(-1024,-1024);

HSBattleLayer::HSBattleLayer(void)
{
	m_pWorld = NULL;
	m_debugDraw = NULL;

	m_gameOverQueryAABB.lowerBound.Set(HS_VALUE_B2V(0),HS_VALUE_B2V(0));
	m_gameOverQueryAABB.upperBound.Set(HS_VALUE_B2V(HSBase::GetTemplateScreenW()),HS_VALUE_B2V(100));

	m_workingAreaQueryAABB.lowerBound.Set(HS_VALUE_B2V(0),HS_VALUE_B2V(100));
	m_workingAreaQueryAABB.upperBound.Set(HS_VALUE_B2V(HSBase::GetTemplateScreenW()),HS_VALUE_B2V(HSBase::GetTemplateScreenH()));

	m_iRhythmIndex = 0;
	m_iCurrterStepIndex = MAX_STEP;
	m_fLinearVelocityY = 5.f;

	m_iMinColorType = (int)BALLOON_COLOR_BLUE;
	m_iMaxColorType = (int)BALLOON_COLOR_PURPLE;

	m_bIsPause = false;
	m_bIsPauseWorld = false;

	m_pBalloonFactory = new HSBalloonFactory;

	m_fLightningMoveSpeed = 10.f;
	m_lightningCurrentPos = SCREEN_BESIDES;
	m_lightningLastPos = m_lightningCurrentPos;

	m_lightningPostionsSize = 0;

	m_pStratagemManager = NULL;

	m_pEnergyFrameProgress = NULL;
	m_pStratagemProgress = NULL;

	m_pGameGold = NULL;
	m_pGameScore = NULL;

	m_iFlyBalloonCount = 0;

	m_lastTouchBalloon = NULL;

	m_iBalloonIdIndex = 0;

	m_isListerHigh = true;

	m_pComboManager = NULL;

	m_pContacListener = NULL;

	m_isEnergyProgressFull = false;

	m_isFreeEnergy = false;

	m_fDt = 0.f;

	m_pSpxReadyGo = NULL;

	m_isPlayReadyGo = true;

	m_iMaxPosArraySize = 0;

	m_iGcInterval = 5;

	m_pSpriteSuperman = NULL;

	m_isPlaySuperman = true;

	m_pBufferPropManager = NULL;

	m_pGoldHeap = NULL;

	m_IsAllowRunBuffer = false;

	m_iComboIndex = 0;
	m_fGameGuideTime = 0;
	m_isStep_Six = true;
	m_isStep_Nine = false;
	m_isStep_Ten = true;
	m_isStep_Eleven = false;

	m_iGameTime = 120;

	
}

HSBattleLayer::~HSBattleLayer(void)
{
	CC_SAFE_DELETE(m_pWorld);
	CC_SAFE_DELETE(m_pContacListener);
	CC_SAFE_DELETE(m_debugDraw);
	CC_SAFE_DELETE(m_pBalloonFactory);

	m_lightningPostions.clear();
	m_workingAreaSprites.clear();
	//HSBalloonConfig::SharedBallonCofig()->Destroy();

	HSBalloonSprite::SetTouchBaloon(NULL);
}

bool HSBattleLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSLoadingLayer::ShareLoading()->setVisible(true);
	HSTool::SetLayerScale(this);
	this->Load();
	//this->setTouchEnabled(true);
	//this->setAccelerometerEnabled(true);

	return true;
}

void HSBattleLayer::Load()
{
	HS_GAME_CONFIG()->Reset();

	this->InitPhysics();


	//@背景图
	{
		if (HS_GAME_CACHE()->GetUseBackgroundID() == 0)
		{
			HS_GAME_CACHE()->SetUseBackgroundID(1);
		}		
		const char* fileName = CCString::createWithFormat("Image/BuyProp/GameSceneProp/%d_1.png",HS_GAME_CACHE()->GetUseBackgroundID())->getCString();
		CCSprite* background = CCSprite::create(fileName);
		background->setPosition(HSBase::GetTemplateScreenCentre());
		this->addChild(background);
	}

	//@加载气球纹理 const
	{
		for (int i=0;i<5;++i)
		{
			int colorTyep = (int)BALLOON_COLOR_BLUE;
			BalloonColorType newColorType = (BalloonColorType)(colorTyep + i);
			//string fileName = "Image/balloon_";
			string fileName = "Image/animal_";
			fileName += HSMath::ItoA(i + 1) +  ".png";
			CCTexture2D* t = CCTextureCache::sharedTextureCache()->addImage(fileName.c_str());
			m_balloonColorMap.insert(pair<BalloonColorType,CCTexture2D*>(newColorType,t));
		}
	}

	//@创建普通气球
	{
		HSBox2dShapeCache::sharedGB2ShapeCache()->addShapesWithFile("Image/animal.plist");
		m_liveBalloonList.SetCallbackNewObect(this,callfunc_selector(HSBattleLayer::CreateBalloon));
		m_liveBalloonList.SetNewMaxSize(0);
		for (int i=0;i<60;++i)
		{
			this->CreateBalloon();
		}
	}

	//@创建机关
	{
		m_pStratagemManager = HSStratagemManager::create("Image/Stratagem/50000.data",m_pWorld);
		this->addChild(m_pStratagemManager);
	}

	//@创建闪电效果
	{
		m_lightEffect.SetCallbackNewObect(this,callfunc_selector(HSBattleLayer::CreatLightEffect));
		m_liveBalloonList.SetNewMaxSize(50);
		for (int i=0;i<10;++i)
		{
			this->CreatLightEffect();
		}
	}

	//@创建变色效果
	{
		m_changeColorEffect.SetCallbackNewObect(this,callfunc_selector(HSBattleLayer::CreatChangeColorEffect));
		m_liveBalloonList.SetNewMaxSize(50);
		for (int i=0;i<10;++i)
		{
			this->CreatChangeColorEffect();
		}
	}

	//@界面UI
	{
		//能量槽
		HSReadUI::ShareReadUI()->ReadUI("Image/BattleLayer/BattleLayer.data","Image/BattleLayer/",this);
		//HSSoundManage::ShareSoundManage()->PlayMusic("back_01");
		//@创建道具气球
		{
			for (int i=0;i<1;++i)
			{
				HS_CREATE_PROP_BALLOON(HSProp_Bomb);
				HS_CREATE_PROP_BALLOON(HSProp_Money);
				HS_CREATE_PROP_BALLOON(HSProp_Fog);
				HS_CREATE_PROP_BALLOON(HSProp_StopStratagemTime);
				HS_CREATE_PROP_BALLOON(HSProp_AddStratagemLevel);
				HS_CREATE_PROP_BALLOON(HSProp_SubStratagemLevel);
				HS_CREATE_PROP_BALLOON(HSProp_King);
				HS_CREATE_PROP_BALLOON(HSProp_ChangeColor);
				HS_CREATE_PROP_BALLOON(HSProp_Shield);
				HS_CREATE_PROP_BALLOON(HSProp_Ink);
			}
		}

		//隐藏能量槽满的SPX的动画
		m_pSpxEnergyFull = HS_FIND_UI_SPX("SPX_xinlianjicao");
		m_pSpxEnergyFull->setVisible(false);
		m_pSpxEnergyFull->SetAction(0,1);

		HSCCSprite* energyFrame = HS_FIND_UI_PANEL_SPRITE("UI_LianJiTiao","k_LianJiTiao");
		energyFrame->setVisible(false);

		m_pEnergyhigHlightedFrame = HS_FIND_UI_PANEL_SPRITE("UI_LianJiZhao","k_LianJiZhao");
		m_pEnergyHead = CCParticleSystemQuad::create("Particle/energyParticle.plist");
		CCPoint energyHeadPos = CCPointZero;
		energyHeadPos.x = -20.f;
		energyHeadPos.y = m_pEnergyhigHlightedFrame->getContentSize().height / 2.f - 20.f;
		m_pEnergyHead->setPosition(energyHeadPos);
		m_pEnergyhigHlightedFrame->addChild(m_pEnergyHead);
		

		HSCCSprite* energySprite = HSCCSprite::create(energyFrame->getTexture());
		m_pEnergyFrameProgress = CCProgressTimer::create(energySprite);
		m_pEnergyFrameProgress->setType(kCCProgressTimerTypeBar);
		m_pEnergyFrameProgress->setMidpoint(ccp(0,0));
		m_pEnergyFrameProgress->setBarChangeRate(ccp(1, 0));
		m_pEnergyFrameProgress->setPosition(energyFrame->getPosition());
		energyFrame->getParent()->addChild(m_pEnergyFrameProgress);	

		//机关槽
		HSCCSprite* stratagemFrame = HS_FIND_UI_PANEL_SPRITE("UI_JiGuanZu_JiGuan","k_JiGuan");
		stratagemFrame->setVisible(false);
		m_pStratagemProgress = CCProgressTimer::create(HSCCSprite::create(stratagemFrame->getTexture()));
		m_pStratagemProgress->setType(kCCProgressTimerTypeRadial);
		m_pStratagemProgress->setReverseProgress(true);
		m_pStratagemProgress->setPosition(stratagemFrame->getPosition());
		m_pStratagemProgress->setPercentage(100.f);
		stratagemFrame->getParent()->addChild(m_pStratagemProgress);

		//金币
		HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_DeFenKuang_ZiKuang2","k_ZiKuang");
		CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
		CCSize gameGoldPngSize = CCSizeMake(250.f,30.f);
		m_pGameGold = CCLabelAtlas::create("0","Image/GameGold.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
		float scalfX = gameGoldFrameSize.width / gameGoldPngSize.width;
		float scalfY = gameGoldFrameSize.height / gameGoldPngSize.height;
		m_pGameGold->setPosition(ccp(45 * scalfX,0));
		m_pGameGold->setScaleX( scalfX);
		m_pGameGold->setScaleY( scalfX);
		gameGoldFrame->addChild(m_pGameGold);

		//得分
		HSCCSprite* gameScoreFrame = HS_FIND_UI_PANEL_SPRITE("UI_DeFenKuang_ZiKuang1","k_ZiKuang");
		CCSize gameScoreFrameSize = gameGoldFrame->getContentSize();
		CCSize gameScorePngSize = CCSizeMake(250.f,30.f);
		m_pGameScore = CCLabelAtlas::create("0","Image/GameScore.png",gameScorePngSize.width / 10,gameScorePngSize.height,'0');
		scalfX = gameScoreFrameSize.width / gameScorePngSize.width;
		scalfY = gameScoreFrameSize.height / gameScorePngSize.height;
		m_pGameScore->setPosition(ccp(45 * scalfX,0));
		m_pGameScore->setScaleX( scalfX );
		m_pGameScore->setScaleY( scalfY );
		gameScoreFrame->addChild(m_pGameScore);

		//时间
		m_pSpxClock = HS_FIND_UI_SPX("SPX_shijian");
		HSCCSprite* timeSprite = HS_FIND_UI_PANEL_SPRITE("UI_ShiJianBan_ShiJianBanYuo","k_ShiJianBanYuo");
		CCSize timeSpriteSize = timeSprite->getContentSize();
		CCSize timeSpritePngSize = CCSizeMake(264,31);
		int minute = m_iGameTime / 60;
		int sec = m_iGameTime % 60;
		m_pGameTimeLabel = CCLabelAtlas::create(CCString::createWithFormat("%02d:%02d",minute,sec)->getCString(),"Image/GameTime.png",timeSpritePngSize.width / 11,timeSpritePngSize.height,'0');
		scalfX = timeSpriteSize.width / timeSpritePngSize.width;
		scalfY = timeSpriteSize.height / timeSpritePngSize.height;
		m_pGameTimeLabel->setPosition(ccp(0,14.f));
		//m_pTime->setScaleX( scalfX );
		//m_pTime->setScaleY( scalfY );
		timeSprite->addChild(m_pGameTimeLabel);

		//暂停按钮
		HS_SET_MENU_TARGET("UI_zanting_01",this,HSBattleLayer::CallPasue);
	}

	//@添加模态屏蔽层
	{
		m_pMaskLayer = CCLayerColor::create(ccc4(0,0,0,153),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
		m_pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
		m_pMaskLayer->setVisible(false);
		this->addChild(m_pMaskLayer,1000);

		//添加超人猫
		m_pSpriteSuperman = CCSprite::create("Image/Superman.png");
		m_pSpriteSuperman->setVisible(false);
		m_pSpriteSuperman->setPosition(CCPointZero);
		m_pSpriteSuperman->setRotation(15.f);
		this->addChild(m_pSpriteSuperman,1010);
	}

	//@添加手动道具
	{
		HSUsePropManager* usePropManager = HSUsePropManager::create();
		this->addChild(usePropManager);
	}

	//@Combo | ReadyGo
	{
		m_pComboManager = HSComboManager::create();
		m_pComboManager->setPosition(HSBase::GetTemplateScreenCentre());
		this->addChild(m_pComboManager,1500);

		m_pSpxReadyGo = SPX_Manager::CreateSprite("SPX/ReadyGo.sprite");
		m_pSpxReadyGo->setPosition(HSBase::GetTemplateScreenCentre());
		m_pSpxReadyGo->setVisible(false);
		m_pSpxReadyGo->SetAction(0,1);
		this->addChild(m_pSpxReadyGo,1500);
	}

	//点击效果
	{
		m_touchBaloonEffectList.SetCallbackNewObect(this,callfunc_selector(HSBattleLayer::CreateTouchBalloonEffect));
		m_touchBaloonEffectList.SetNewMaxSize(5);
		for (int i=0;i<1;++i)
		{
			this->CreateTouchBalloonEffect();
		}
	}

	//魂魄
	{
		m_soulEffectList.SetCallbackNewObect(this,callfunc_selector(HSBattleLayer::CreatSoulEffect));
		m_soulEffectList.SetNewMaxSize(5);
		for (int i=0;i<5;++i)
		{
			this->CreatSoulEffect();
		}
	}

	//@新高分动画
	{
		m_spxHighScore = SPX_Manager::CreateSprite("SPX/zuigaofen.sprite");
		m_spxHighScore->setPosition(HSBase::GetTemplateScreenCentre());
		m_spxHighScore->SetAction(0,1);
		m_spxHighScore->setVisible(false);
		this->addChild(m_spxHighScore,2000);

		m_pSpxTimeUp = SPX_Manager::CreateSprite("SPX/timeup.sprite");
		m_pSpxTimeUp->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,HSBase::GetTemplateScreenH() / 2.f));
		m_pSpxTimeUp->SetAction(0,1);
		m_pSpxTimeUp->setVisible(false);
		this->addChild(m_pSpxTimeUp,2000);
	}

	this->SetPosArraySize(30);

	m_dNextFlyTime = HSTime::GetLocalityTime() + 100;

	this->schedule(schedule_selector(HSBattleLayer::Updata));
}

void HSBattleLayer::CreateTouchBalloonEffect()
{
	HSTouchBalloonEffect* effect = HSTouchBalloonEffect::create();
	this->addChild(effect,1100);
	m_touchBaloonEffectList.AddNotUsedObjectFromEnd(effect);
}

void HSBattleLayer::CreateBalloon()
{
	map<BalloonColorType,CCTexture2D*>::iterator it = m_balloonColorMap.find(BALLOON_COLOR_BLUE);
	if (it != m_balloonColorMap.end())
	{
		HSBalloonSprite* sprite = HSBalloonSprite::create(it->second,m_pWorld,m_iBalloonIdIndex++);
		sprite->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,-800));
#ifdef WIN32
		sprite->SetB2Draw(m_debugDraw);
#endif
		sprite->setVisible(false);
		this->addChild(sprite,900);
		sprite->SetGcPool(&m_liveBalloonList);
		m_liveBalloonList.AddNotUsedObjectFromEnd(sprite);
		m_allBalloonSpriteList.push_back(sprite);
	}
}

void HSBattleLayer::CreatSoulEffect()
{
	HSSoulEffect* soul = HSSoulEffect::create(this);
	soul->SetGcPool(&m_soulEffectList);
	this->addChild(soul,1100);
	m_soulEffectList.AddNotUsedObjectFromEnd(soul);
}

void HSBattleLayer::CreatChangeColorEffect()
{
	HSChangeColorEffect* effect = HSChangeColorEffect::create();
	effect->setVisible(false);
	this->addChild(effect,2000);
	effect->SetGcPool(&m_changeColorEffect);
	m_changeColorEffect.AddNotUsedObjectFromEnd(effect);
}

void HSBattleLayer::CreatLightEffect()
{
	HSLightEffect* effect = HSLightEffect::create();
	effect->setVisible(false);
	this->addChild(effect,1100);
	effect->SetGcPool(&m_lightEffect);
	m_lightEffect.AddNotUsedObjectFromEnd(effect);
}

void HSBattleLayer::CallGameOver(CCObject* obj)
{
	HS_GAME_CONFIG()->Reset();
	HS_GO_SCENE(HS_SCENE_BuyProp);
}

void HSBattleLayer::CallRestart(CCObject* obj)
{
	HS_GAME_CONFIG()->Reset();
	HS_GO_SCENE(HS_SCENE_BattleScene);
}

void HSBattleLayer::CallGameTime(CCNode* spxNode,void* pData)
{
	m_pSpxClock->setVisible(true);
	m_pSpxClock->SetAction(0);
}

void HSBattleLayer::UseProp(CCObject* obj)
{

}

void HSBattleLayer::InitPhysics()
{
	
	b2Vec2 gravity;
	gravity.Set(0.f, 3.f);
	m_pWorld = new b2World(gravity);
	m_pContacListener = new HSContacListener;

	m_pWorld->SetContactListener(m_pContacListener);
	// Do we want to let bodies sleep?
	m_pWorld->SetAllowSleeping(true);

	m_pWorld->SetContinuousPhysics(false);

#ifdef WIN32

	m_debugDraw = new GLESDebugDraw( HS_PTM_RATIO );
	m_pWorld->SetDebugDraw(m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	// 	flags += b2Draw::e_jointBit;
	// 	flags += b2Draw::e_aabbBit;
	// 	flags += b2Draw::e_pairBit;
	// 	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);

#endif // WIN32	

	// Define the ground body.
	b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(HS_VALUE_B2V(HSBase::GetScreenWidth() / 2), HS_VALUE_B2V(HSBase::GetScreenHeight() / 2)); // bottom-left corner
	groundBodyDef.position.Set(0,0);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2EdgeShape groundBox;


	
	bottomX = HS_RATIO_b2Vec2(HSVisibleRect::leftBottom().x/* + 10.f*/ ,HSVisibleRect::leftBottom().y-1000.f);
	bottomY = HS_RATIO_b2Vec2(HSVisibleRect::rightBottom().x/* + 10.f*/ ,HSVisibleRect::rightBottom().y-1000.f);

	topX = HS_RATIO_b2Vec2(HSVisibleRect::leftTop().x/* + 10.f*/ ,HSVisibleRect::leftTop().y - 143.f);
	topY = HS_RATIO_b2Vec2(HSVisibleRect::rightTop().x/* + 10.f*/ ,HSVisibleRect::rightTop().y - 143.f);

	leftX = HS_RATIO_b2Vec2(HSVisibleRect::leftTop().x/* + 10.f*/,HSVisibleRect::leftTop().y);
	leftY = HS_RATIO_b2Vec2(HSVisibleRect::leftBottom().x/* + 10.f*/,HSVisibleRect::leftBottom().y);

	rightX = HS_RATIO_b2Vec2(HSVisibleRect::rightBottom().x/* - 10.f*/ ,HSVisibleRect::rightBottom().y);
	rightY = HS_RATIO_b2Vec2(HSVisibleRect::rightTop().x /*- 10.f*/,HSVisibleRect::rightTop().y);

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
	/*

	b2Vec2 gravity;
	gravity.Set(0.0f, 5.0f);
	m_pWorld = new b2World(gravity);
	m_debugDraw = new GLESDebugDraw( HS_PTM_RATIO );
	m_pWorld->SetDebugDraw(m_debugDraw);
	m_debugDraw->SetFlags(flags);

	b2BodyDef bodyDef;
	bodyDef.position.Set(HS_VALUE_B2V(HSBase::GetScreenWidth()/2),HS_VALUE_B2V(HSBase::GetScreenHeight()/2));
	b2Body* groundBody = m_pWorld->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(HS_VALUE_B2V(HSBase::GetScreenWidth()),HS_VALUE_B2V(HSBase::GetScreenHeight()));
	groundBody->CreateFixture(&shape,10.f);
	*/


}

void HSBattleLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -127 , true);
}

bool HSBattleLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//CCDirector::sharedDirector()->replaceScene(HSBattleScene::create());
	//HSSoundManage::ShareSoundManage()->PlayerEffect("hit_effect_11");
	CCLog("Begin1");
	return true;
}

void HSBattleLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	int a = 0;
	CCLog("Begin2");
}

void HSBattleLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	int a = 0;
	CCLog("Begin3");
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
	ccDrawLine(ccp(100,100),ccp(500,500));
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
	// 
	// #ifdef WIN32
	// 	m_pWorld->DrawDebugData();
	// 
	// 	m_debugDraw->DrawAABB(&m_workingAreaQueryAABB,b2Color(255,0,0));
	// 	m_debugDraw->DrawAABB(&m_gameOverQueryAABB,b2Color(255,0,0));

	// 	DrawLinhgtningPostion();
	// #endif
	
	kmGLPopMatrix();
}

bool HSBattleLayer::Fly(HSBalloonSprite* balloon)
{
	b2Body* spriteBody = balloon->getB2Body();

	spriteBody->SetAwake(true);
	spriteBody->SetLinearVelocity(b2Vec2(0.f,m_fLinearVelocityY));
	CCSize screenSize = HSBase::GetTemplateScreenSize();
	CCTexture2D* texture = balloon->getTexture();
	HSAssert(texture,"");

	float offsetMaxV = HS_MATH_MAX(texture->getPixelsWide(),texture->getPixelsHigh());

	float rangeMinX = offsetMaxV;
	float rangeMaxX = screenSize.width - offsetMaxV;
	float rangeMinY = offsetMaxV;
	float rangeMaxY = offsetMaxV * 6.f;
	float randomX = HSMath::Random(rangeMinX,rangeMaxX);
	float randomY = 0.f - HSMath::Random(rangeMinY,rangeMaxY);
	balloon->setPosition(ccp(randomX,randomY));
	balloon->ActivateCollisions();
	spriteBody->SetType(b2_dynamicBody);
	balloon->setVisible(true);
	if (balloon->getPosition().x < 0.f || balloon->getPosition().x > 640.f)
	{
		CCLog("Pos:%d __ %.2f__%.2f",balloon->GetID(),balloon->getPosition().x,balloon->getPosition().y);
	}
	return true;
}

bool HSBattleLayer::Fly_1(HSBalloonSprite* pBalloon)
{
	if (!pBalloon)
	{
		return false;
	}
	bool isSetBlockOk = false;
	int maxCount = m_vPosArray.size();
	int posArrayIndex = 0;
	int findCount = 0;
	do 
	{
		findCount++;
		posArrayIndex = HSMath::Random(0,maxCount - 1);
		HSBlock* pBlock = &m_vPosArray[posArrayIndex];

		if (pBlock->pBalloon == NULL )
		{
			pBalloon->setPosition(pBlock->pos);
			pBlock->pBalloon = pBalloon;
			isSetBlockOk = true;
		}

		
	} while (!isSetBlockOk && findCount < 5);

	return isSetBlockOk;
	
}

bool HSBattleLayer::Fly()
{
	m_vListerBalloonPosY.clear();

	int count = m_vPosArray.size();
	for (int i=0;i<count;++i)
	{
		HSBlock* pBlock = &m_vPosArray[i];
		if (pBlock->pBalloon)
		{
			b2Body* spriteBody = pBlock->pBalloon->getB2Body();

			spriteBody->SetType(b2_dynamicBody);
			spriteBody->SetAwake(true);
			spriteBody->SetLinearVelocity(b2Vec2(0.f,m_fLinearVelocityY));
			pBlock->pBalloon->setVisible(true);
			pBlock->pBalloon->getB2Body()->ResetMassData();
			m_vListerBalloonPosY.push_back(pBlock->pBalloon);
			pBlock->pBalloon = NULL;
		}
	}
	return true;
}

void HSBattleLayer::Logic_1()
{
// 	double curTime = HSTime::GetLocalityTime();
// 	if (curTime < m_dNextFlyTime)
// 	{
// 		return;
// 	}
	if (m_iFlyBalloonCount <= 0)
	{
		//m_iFlyBalloonCount = s_rhythm[m_iRhythmIndex] * 10;
		m_iFlyBalloonCount = m_vPosArray.size();
	}

	for (int i=0;i<m_iFlyBalloonCount;++i)
	{
		HSBalloonSprite* sprite = m_liveBalloonList.GetNotUsedObjectFromBegin();
		//HSBalloonSprite* sprite = NULL;
		if (sprite != NULL)
		{
			b2Body* spriteBody = sprite->getB2Body();
			if (spriteBody->GetType() == b2_staticBody)
			{
				int randomColorType = HSMath::Random(m_iMinColorType,m_iMaxColorType);
				sprite->SetColorType((BalloonColorType)randomColorType);
				//sprite->SetColorType(BALLOON_COLOR_BLUE);
				map<BalloonColorType,CCTexture2D*>::iterator it = m_balloonColorMap.find(sprite->GetColorType());
				if (it == m_balloonColorMap.end())
				{
					HSAssert(it != m_balloonColorMap.end(),"");
				}
				//道具气球不需要更换纹理 道具气球的ID [1000 - 2000]
				if (sprite->GetID() < 1000)
				{
					sprite->setTexture(it->second);
				}

				Fly_1(sprite);

			}
		}else{
			break;
		}
	}
	

	int dribbleCount = HS_GAME_CONFIG_DATA()->dribbleCount;
	if (dribbleCount > 0 && dribbleCount % 2 == 0)
	{
		int maxPropCount = this->m_propBalloonList.size();
		int index = HSMath::Random(0,maxPropCount - 1);

		HSPropSpriteInterface* propSprite = *(m_propBalloonList.begin() + index);
		if (propSprite)
		{
			if (propSprite->getB2Body()->GetType() == b2_staticBody)
			{
				Fly_1(propSprite);
			}
		}
	}

	this->Fly();

	if (m_iRhythmIndex + 1 == HSBattleLayer::MAX_RHYTHM)
	{
		m_iRhythmIndex = 0;
	}else{
		m_iRhythmIndex++;
	}

// 	int flyInterval = HSMath::Random(1,2);
// 	m_dNextFlyTime = curTime + flyInterval * 15000000.f;

	HS_GAME_CONFIG()->m_pBGD->curShowHowColorType = m_iMaxColorType;
}

void HSBattleLayer::Logic()
{
	
	return;

	this->LogicOfResponseTouchBalloon();

	double curTime = HSTime::GetLocalityTime();
	if (curTime < m_dNextFlyTime)
	{
		return;
	}

	if (m_iFlyBalloonCount <= 0)
	{
		m_iFlyBalloonCount = s_rhythm[m_iRhythmIndex] * 10;
	}

	HSBalloonSprite* sprite = m_liveBalloonList.GetNotUsedObjectFromBegin();
	//HSBalloonSprite* sprite = NULL;
	if (sprite != NULL)
	{
		b2Body* spriteBody = sprite->getB2Body();
		if (spriteBody->GetType() == b2_staticBody)
		{
			int randomColorType = HSMath::Random(m_iMinColorType,m_iMaxColorType);
			sprite->SetColorType((BalloonColorType)randomColorType);
			//sprite->SetColorType(BALLOON_COLOR_BLUE);
			map<BalloonColorType,CCTexture2D*>::iterator it = m_balloonColorMap.find(sprite->GetColorType());
			if (it == m_balloonColorMap.end())
			{
				HSAssert(it != m_balloonColorMap.end(),"");
			}
			//道具气球不需要更换纹理 道具气球的ID [1000 - 2000]
			if (sprite->GetID() < 1000)
			{
				sprite->setTexture(it->second);
			}

			this->Fly(sprite);

			m_iFlyBalloonCount--;
		}
	}
	
	int dribbleCount = HS_GAME_CONFIG_DATA()->dribbleCount;
	if (dribbleCount > 0 && dribbleCount % 2 == 0)
	{
		int maxPropCount = this->m_propBalloonList.size();
		int index = HSMath::Random(0,maxPropCount - 1);

		HSPropSpriteInterface* propSprite = *(m_propBalloonList.begin() + index);
		if (propSprite)
		{
			if (propSprite->getB2Body()->GetType() == b2_staticBody)
			{
				this->Fly(propSprite);
			}
		}
	}
	if (m_iFlyBalloonCount <= 0)
	{
		if (m_iRhythmIndex + 1 == HSBattleLayer::MAX_RHYTHM)
		{
			m_iRhythmIndex = 0;
		}else{
			m_iRhythmIndex++;
		}
	}

// 	if (m_iRhythmIndex != 0 && m_iRhythmIndex % m_iCurrterStepIndex == 0)
// 	{
// 		m_iCurrterStepIndex += 1;
// 		m_iRhythmIndex -= 1;
// 	}else{
// 		//m_iRhythmIndex++;
// 	}

// 	if (m_iRhythmIndex + 1 == MAX_RHYTHM)
// 	{
// 		m_iRhythmIndex = 0;
// 		m_iCurrterStepIndex = MAX_STEP;
// 		if ((BalloonColorType)m_iMaxColorType != m_SMAXCOLORTYPE)
// 		{
// 			m_iMaxColorType++;
// 		}else{
// 			m_fLinearVelocityY += 0.1f;
// 		}
// 	}

	if (m_iFlyBalloonCount <= 0)
	{
		int flyInterval = HSMath::Random(1,2);
		m_dNextFlyTime = curTime + flyInterval * 10.f;
	}else{
		int flyInterval = HSMath::Random(1,2);
		//m_dNextFlyTime = curTime + flyInterval * 10.f;
	}

	HS_GAME_CONFIG()->m_pBGD->curShowHowColorType = m_iMaxColorType;
}

void HSBattleLayer::LogicWithGCBalloon(float dt)
{
	static float d = 0.f;
	d += dt;
	if ((int)d > m_iGcInterval)
	{
		d = 0.f;
		b2Body* b = m_pWorld->GetBodyList();
		while (b)
		{
			HSBalloonSprite* sprite = (HSBalloonSprite*)b->GetUserData();
			b = b->GetNext();
			if (sprite == NULL)
			{
				continue;
			}
			if (sprite->getPosition().x < 0.f || sprite->getPosition().x > HSBase::GetTemplateScreenW())
			{
				sprite->setVisible(false);
				if (sprite->GetID() >= 1000)
				{
					HSPropSpriteInterface* prop = dynamic_cast<HSPropSpriteInterface*>(sprite);
					if (prop)
					{
						//prop->TouchBalloonEnd();
						//m_propBalloonList.push_back(prop);
						prop->SetIsLiester(true);
						//CCLog("GC_Prop : %d __ %.2f__%.2f",sprite->GetID(),sprite->getPosition().x,sprite->getPosition().y);
					}

				}else{
					sprite->SetIsLiester(true);
					//m_liveBalloonList.AddNotUsedObjectFromEnd(sprite);
					//CCLog("GC : %d __ %.2f__%.2f",sprite->GetID(),sprite->getPosition().x,sprite->getPosition().y);
				}
				//sprite->TouchBalloonEnd();
			}
		}
	}
}

void HSBattleLayer::Updata(float dt)
{
	if (m_isPlayReadyGo)
	{
		//@创建Buffer道具
		{
			m_pBufferPropManager = HSBufferPropManager::create();
			m_pBufferPropManager->setAnchorPoint(HS_ANCHOR_LD);
			this->addChild(m_pBufferPropManager,900);
		}

		m_bIsPause = true;
		m_isPlayReadyGo = false;
		m_pSpxReadyGo->setVisible(true);
		m_pSpxReadyGo->SetAction(0,1,this,callfuncND_selector( HSBattleLayer::CallPlayReadyGoFinish),NULL);

		this->CallGameStart();
	}

	BalloonGameData* pGameData = HS_GAME_CONFIG_MUTABLE_DATA();
	
	this->DrawUI(pGameData,dt);

	if (m_bIsPause)
	{
		return;
	}

	if (this->IsGameOver() == true)
	{
		m_bIsPause = true;
		return;
	}

	this->LogicOfGameGuide_Six(dt);

	this->LogicOfHighestScore();

	this->LogicWithGCBalloon(dt);

	this->LogicOfTouchBalloon();

	//this->DrawUI(pGameData,dt);

	//this->QueryAABB(pGameData);
	this->LogicWithListerEnergyFunn();

	if (m_pStratagemManager)
	{
		HSAssert(m_pStratagemManager,"");

		m_pStratagemManager->Updata(dt);
	}

	this->LogicWithGCBalloon(dt);

	this->LogicOfResponseTouchBalloon();

	if (IsFlyBalloon_1(dt))
	{
		this->Logic_1();
	}

	int32 velocityIterations = 8;
	int32 positionIterations = 1;

	if (!m_bIsPauseWorld)
	{
		m_pWorld->Step(dt,velocityIterations,positionIterations);
	}	

// 	if (IsFlyBalloon(dt))
// 	{
// 		this->Logic();
// 	}

// 	if (IsFlyBalloon_1(dt))
// 	{
// 		this->LogicWithGCBalloon(dt);
// 		this->Logic_1();
// 	}
	

	LogicOfLihgtning(dt);

	LogicOfStratagem(dt);

	LogicOfGameGuide_Eleven();

	HS_GAME_CONFIG()->Update(dt);
}

void HSBattleLayer::LogicOfStratagem(float dt)
{
	if(!m_pStratagemManager)
	{
		return;
	}


	int step = HS_GAME_CONFIG()->GetStratagemMoveStep();

	if ( step > 0 )
	{
		for (int i = 0;i<HS_MATH_MAX(step,-step);++i)
		{
			m_pStratagemManager->Down();
		}
	}else if( step < 0){

		for (int i = 0;i<HS_MATH_MAX(step,-step);++i)
		{
			m_pStratagemManager->Up();
		}
	}
	HS_GAME_CONFIG()->SetStratagemMoveStep(0);

	this->LogicOfGameGuide_Nine(dt);

	
}

void HSBattleLayer::DrawUI(BalloonGameData* pGameData , float dt)
{

	//能量进度条
	float energyProgress = pGameData->energy / pGameData->energyMax * 100.f;
	energyProgress > 100.f ? energyProgress = 100.f : 0;
	m_pEnergyFrameProgress->setPercentage(energyProgress);
	CCPoint energyHeadPos = CCPointZero;
	energyHeadPos.x = m_pEnergyhigHlightedFrame->getContentSize().width * energyProgress / 100.f;
	energyHeadPos.y = m_pEnergyhigHlightedFrame->getContentSize().height / 2.f;
	m_pEnergyHead->setPosition(energyHeadPos);
	if ((int)energyProgress == 100 )
	{
		/* 添加能量满了之后显示的粒子效果 */
		m_pSpxEnergyFull->setVisible(true);
		m_pSpxEnergyFull->SetAction(0);
		if (!m_isEnergyProgressFull)
		{
			m_isEnergyProgressFull = true;
			HSSoundManage::ShareSoundManage()->PlayerEffect("power_anergy_start");
		}
	}else{
		m_isEnergyProgressFull = false;
	}

	//机关进度条
	int sec = pGameData->stratagemCurSec % pGameData->stratagemEachCycleSec;
	float stratagemProgress = (float)sec / (float)pGameData->stratagemEachCycleSec * 100.f;
	stratagemProgress > 100.f ? stratagemProgress = 100.f : 0;
	m_pStratagemProgress->setPercentage(stratagemProgress);

	//金币数
	static int lastGameGold = 0;
	if (lastGameGold != HS_GAME_CACHE()->GetGold())
	{
		lastGameGold = HS_GAME_CACHE()->GetGold();
		m_pGameGold->setString(HSMath::ItoA(lastGameGold).c_str());
		CCActionInterval* gameGoldJump = CCJumpBy::create(0.2f, CCPointZero, 15, 1);
		m_pGameGold->runAction(gameGoldJump);
	}

	//得分
	static int lastGameScore = 0;
	if (lastGameScore != pGameData->gameScore)
	{
		lastGameScore = pGameData->gameScore;
		m_pGameScore->setString(HSMath::ItoA(pGameData->gameScore).c_str());
		CCActionInterval* gameScoreJump = CCJumpBy::create(0.2f, CCPointZero, 15, 1);
		//CCActionInterval *actionScaleToBack = CCScaleTo::create(0.3f, 1.f);
		CCSpawn* seq = CCSpawn::create(gameScoreJump, /*actionScaleToBack,*/ NULL);
		//m_pGameScore->runAction(gameScoreJump);
		m_pGameScore->runAction(seq);
	}

	if (m_fDt >= 1.f)
	{
		if (m_iGameTime > 0)
		{
			m_fDt = 0.f;
			--m_iGameTime;

			int minute = m_iGameTime / 60;
			int sec = m_iGameTime % 60;
			if (sec == 0)
			{
				m_pSpxClock->setVisible(true);
				m_pSpxClock->SetAction(1,1,this,callfuncND_selector(HSBattleLayer::CallGameTime),NULL);
			}
			CCString* strTime = CCString::createWithFormat("%02d:%02d",minute,sec);
			m_pGameTimeLabel->setString(strTime->getCString());
		}

	}else{
		m_fDt += dt;
	}
}

HSBalloonFactory* HSBattleLayer::QueryFullScreenBalloon()
{
	m_pBalloonFactory->Reset();
	m_pWorld->QueryAABB(m_pBalloonFactory,m_workingAreaQueryAABB);
	return m_pBalloonFactory;
}

void HSBattleLayer::QueryAABB( BalloonGameData* pGameData )
{
	HSAssert(pGameData,"");
	if (true == pGameData->isFreeEnergy)
	{
		pGameData->isFreeEnergy = false;
		pGameData->energy = 0.f;
		//m_bIsPauseWorld = true;

		m_pBalloonFactory = this->QueryFullScreenBalloon();

		std::vector<HSBalloonSprite*>* pSpriteList = m_pBalloonFactory->GetSpriteList();
		std::vector<HSBalloonSprite*>::iterator it = pSpriteList->begin();
		for (;it!= pSpriteList->end();++it)
		{
			HSBalloonSprite* sprite = (*it);
			if (sprite->GetColorType() == pGameData->freeFreeEnergyBalloonType)
			{
				m_lightningPostions.push_back(sprite->getPosition());
				m_workingAreaSprites.push_back(sprite);
			}
		}

		{
			int count = (int)m_workingAreaSprites.size();
			HSBalloonSprite* temp = NULL;
			for(int i=0;i<count;i++)
			{
				for(int j=0;j<count-i-1;j++)
				{
					if(m_workingAreaSprites[j]->m_fY > m_workingAreaSprites[j+1]->m_fY)
					{
						temp = m_workingAreaSprites[j];
						m_workingAreaSprites[j] = m_workingAreaSprites[j+1];
						m_workingAreaSprites[j+1] = temp;
					}
				}
			}
		}

		m_pSpxEnergyFull->setVisible(true);
		m_pSpxEnergyFull->SetAction(1,1,this,callfuncND_selector(HSBattleLayer::CallEnergyFull),NULL );

		m_lightningPostionsSize = (int)m_lightningPostions.size();
		//pGameData->stratagemRollBackStep = m_lightningPostionsSize;
		pGameData->stratagemRollBackStepCount = m_lightningPostionsSize;

		this->LayerShakeEffect();
		this->GetModalLayer()->setVisible(true);

		HSSoundManage::ShareSoundManage()->PlayerEffect("power_anergy_start");
	}
}

void HSBattleLayer::LogicWithListerEnergyFunn()
{
	BalloonGameData* pGameData = HS_GAME_CONFIG_MUTABLE_DATA();
	if (pGameData->isShowSuperman && m_isPlaySuperman)
	{
		m_isPlaySuperman = false;
		this->GetModalLayer()->setVisible(true);
		this->PlaySupermanEffect();
	}
	if (true == pGameData->isFreeEnergy)
	{
		//能量满
		this->QueryAABB(pGameData);

		pGameData->isFreeEnergy = false;
	}
}

void HSBattleLayer::LogicOfTouchBalloon()
{
	if (m_lastTouchBalloon != HSBalloonSprite::GetTouchBaloon())
	{
		m_lastTouchBalloon = HSBalloonSprite::GetTouchBaloon();

		this->PlayTouchBalloonEffect(m_lastTouchBalloon->getPosition());

		if (m_pComboManager->GetIsShowCombo())
		{
			this->PlaySoulEffect(m_lastTouchBalloon);
		}
	}
}

void HSBattleLayer::LogicOfResponseTouchBalloon()
{
	if (!m_pMaskLayer)
	{
		return;
	}
	static bool isSet = false;

	float isResponse = m_pMaskLayer->isVisible();
	std::vector<HSBalloonSprite*>::iterator it = m_allBalloonSpriteList.begin();
	if (isResponse)
	{
		if (!isSet)
		{
			for (;it!=m_allBalloonSpriteList.end();++it)
			{
				(*it)->SetTouchEnabled(false);
			}
			isSet = true;
		}
	}else{
		if (isSet)
		{
			for (;it!=m_allBalloonSpriteList.end();++it)
			{
				(*it)->SetTouchEnabled(true);
			}
			isSet = false;
		}
	}
}

void HSBattleLayer::LogicOfLihgtning(float dt)
{
	double curTime = HSTime::GetLocalityTime();
	static double tempNextTime = 0;
	if (curTime < tempNextTime)
	{
		return;
	}

	if ((int)m_workingAreaSprites.size() > 0 && m_isFreeEnergy == true)
	{
		HSBalloonSprite* balloonSprite = this->m_workingAreaSprites[0] ;
		if (balloonSprite != NULL)
		{
			balloonSprite->ccTouchBegan(NULL,NULL);
			CCNode* node = HS_FIND_UI_PANEL("UI_JiGuanZu");
			CCPoint pos = node->getPosition();
			pos.x += node->getContentSize().width / 2.f;
			pos.y -= node->getContentSize().height / 2.f;

			this->PlaySoulEffect(balloonSprite,ccc4f(0,0,255,0),pos);
			this->PlayTouchBalloonEffect(balloonSprite->getPosition());
			this->PlayLightEffect(balloonSprite);
			balloonSprite->ccTouchEnded(NULL,NULL);
			this->m_workingAreaSprites.erase(m_workingAreaSprites.begin());
		}
		HS_GAME_CONFIG_MUTABLE_DATA()->dribbleIntervalTime = 20.f;
		tempNextTime = curTime + HSMath::Random(50.f,200.f);
	}else{
		this->m_bIsPauseWorld = false;
	}

	if (m_isFreeEnergy == true && (int)m_workingAreaSprites.size() == 0)
	{
		m_isFreeEnergy = false;
		HS_GAME_CONFIG_MUTABLE_DATA()->dribbleIntervalTime = 0.7f;
		this->GetModalLayer()->setVisible(false);

		//新手引导部分
		this->LogicOfGameGuide_Ten(dt);
	}
	
}

void HSBattleLayer::DrawLinhgtningPostion()
{
#ifdef WIN32
	std::vector<CCPoint>::iterator it = m_lightningTracks.begin();
	for (;it!=m_lightningTracks.end();++it)
	{
		CCPoint p = (*it);
		b2Vec2 v = HS_RATIO_b2Vec2(p.x,p.y);
		m_debugDraw->DrawPoint(v,10,b2Color(0,255,0));
	}
#endif
}

void HSBattleLayer::RemoveWorkingAreaOneBody()
{
	std::vector<HSBalloonSprite*>::iterator it = m_workingAreaSprites.begin();
	if (it != m_workingAreaSprites.end())
	{
		HSBalloonSprite* s = (*it);
		s->TouchBalloonEnd();
		m_workingAreaSprites.erase(it);
	}
}

bool HSBattleLayer::IsGameOver()
{
	//return false;
	if (m_iGameTime > 0)
	{
		if (m_iGameTime == 5)
		{
			this->PlayTimeTimeWillOver(5);
		}else if (m_iGameTime == 1){
			this->CallPlayTimeTimeWillOverEnd();
		}
		return false;
	}

	m_pSpxTimeUp->setVisible(true);
	m_pSpxTimeUp->SetAction(0,1,this,callfuncND_selector(HSBattleLayer::CallTimeupFinish),NULL);

	return true;
}

bool HSBattleLayer::IsFlyBalloon(float dt)
{
// 	static float time = 0;
// 	if (time < 5.f)
// 	{
// 		time += dt;
// 		return true;
// 	}
// 	time = 0.f;

	HSBalloonFactory factory;
	m_pWorld->QueryAABB(&factory,m_gameOverQueryAABB);
	std::vector<HSBalloonSprite*>* tempList = factory.GetSpriteList();
	std::vector<HSBalloonSprite*>::iterator it = tempList->begin();

	int count = (int)tempList->size();
	if (count > 5)
	{
		return false;
	}	
	return true;
}

bool HSBattleLayer::IsFlyBalloon_1(float dt)
{

	if (!IsFlyBalloon(dt))
	{
		return false;
	}
	
	const static float s_fMaxIntervalTime = 0.5f;
	static float recordTime = 0.f;
	if (recordTime < s_fMaxIntervalTime )
	{ 		recordTime += dt;
		return false;
	}
	recordTime = 0.f;
	


	int count = m_vListerBalloonPosY.size();
	bool isFly = true;
	static int s_iLastID = 0;
	static int repeatedCount = 0;
	for (int i = 0; i < count; i++)
	{
		HSBalloonSprite* s = m_vListerBalloonPosY[i];
		if(s)
		{
			CCPoint pos = s->getPosition();
			b2Body* pBody = s->getB2Body();
			if (pos.y > 50.f || pBody->GetType() == b2_staticBody)
			{
				isFly = true;
			}else{
				//CCLog("ID: %d",s->GetID());
				if (s_iLastID == s->GetID())
				{
					if (repeatedCount > 5)
					{
						s->SetIsLiester(true);
						m_vListerBalloonPosY.erase(m_vListerBalloonPosY.begin()+i);
						repeatedCount = 0;
					}else{
						++repeatedCount;
					}
				}else{
					s_iLastID = s->GetID();
					isFly = false;
				}
				
				break;
			}
		}
	}

	if (isFly)
	{
		m_vListerBalloonPosY.clear();
	}

	return isFly;
}

void HSBattleLayer::CallPasue(CCObject* obj)
{
	this->Pause();
}

void HSBattleLayer::LogicOfHighestScore()
{
	int highScore = HS_GAME_CACHE()->GetHistoryScore();
	if (!m_isListerHigh || highScore == 0)
	{
		return;
	}	
	if (highScore < HS_GAME_CONFIG_DATA()->gameScore)
	{
		m_isListerHigh = false;
		m_spxHighScore->setVisible(true);
		m_spxHighScore->SetAction(0,1);
		HSSoundManage::ShareSoundManage()->PlayerEffect("new_score");
	}
}

bool HSBattleLayer::compare(const HSBalloonSprite* s1,const HSBalloonSprite* s2 )
{
	bool b = s1 < s2;
	return b;
}

void HSBattleLayer::PlaySoulEffect( HSBalloonSprite* balloon )
{
	PlaySoulEffect(balloon,ccc4f(255,255,255,255),CCPointZero);
}

void HSBattleLayer::PlaySoulEffect( HSBalloonSprite* balloon,const ccColor4F& color,const CCPoint& destPos )
{
	HSSoulEffect* soul = m_soulEffectList.GetNotUsedObjectFromBegin();
	if (soul)
	{
		CCNode* node = HS_FIND_UI_PANEL("UI_LianJiZhao");
		CCPointArray* array = CCPointArray::create(20);
		CCPoint beginPos = balloon->getPosition();
		array->addControlPoint(beginPos);
		array->addControlPoint(ccp(beginPos.x + HSMath::Random(-100.f,100.f),beginPos.y + HSMath::Random(-100.f,100.f)));
		if (!destPos.equals(CCPointZero))
		{
			array->addControlPoint(destPos);
		}else{
			array->addControlPoint(node->getPosition());
		}

		soul->SetTrack(array);

		if (!ccc4FEqual(color,ccc4f(255,255,255,255)))
		{
			soul->SetSoulColor(color);
		}		

		if (NULL != soul)
		{
			//soul->setPosition(m_lastTouchBalloon->getPosition());
			soul->Play();
		}
	}
}

void HSBattleLayer::ListenStratagem()
{
	if (m_bIsPauseWorld)
	{
		this->LayerShakeEffect();
	}
}

void HSBattleLayer::LayerShakeEffect()
{
	CCScene* f = CCDirector::sharedDirector()->getRunningScene();
	CCMoveBy* left = CCMoveBy::create(0.02f,ccp(10,0));
	CCMoveBy* right = CCMoveBy::create(0.02f,ccp(-10,0));
	CCMoveBy* top = CCMoveBy::create(0.02f,ccp(0,10));
	CCMoveBy* rom = CCMoveBy::create(0.02f,ccp(0,-10));
	CCCallFunc* call = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::ListenStratagem));
	CCFiniteTimeAction* action = CCSequence::create(left,right,top,rom,left->reverse(),right->reverse(),top->reverse(),rom->reverse(),NULL);
	//CCRepeat *action1 = CCRepeat::create(action,10);
	//f->runAction(action);

	CCFiniteTimeAction* action3 = CCSequence::create(action,call,NULL);


	f->runAction(action3);
}

void HSBattleLayer::PlayTouchBalloonEffect( const CCPoint& pos )
{
	HSTouchBalloonEffect* effect = this->m_touchBaloonEffectList.GetNotUsedObjectFromBegin();
	if (effect != NULL)
	{
		effect->SetIsLister(true);
		effect->SetGcPool(&m_touchBaloonEffectList);
		effect->PlayEffectBegin(pos);
	}
}

void HSBattleLayer::PlayChangeColorEffect(HSBalloonSprite* balloon,const BalloonColorType& type, CCTexture2D* pTexture)
{
	HSChangeColorEffect* effect = this->m_changeColorEffect.GetNotUsedObjectFromBegin();
	if (effect)
	{
		effect->SetGcPool(&m_changeColorEffect);
		effect->PlayEffectBegin(balloon,type,pTexture);
		HSSoundManage::ShareSoundManage()->PlayerEffect("turn_balloon");
	}
}

void HSBattleLayer::PlayLightEffect(HSBalloonSprite* balloon)
{
	HSLightEffect* effect = this->m_lightEffect.GetNotUsedObjectFromBegin();
	if (effect)
	{
		effect->SetGcPool(&m_lightEffect);
		effect->PlayEffectBegin(balloon);
	}
}

map<BalloonColorType,CCTexture2D*>* HSBattleLayer::GetBalloonAllTexture()
{
	return &this->m_balloonColorMap;
}

b2World* HSBattleLayer::GetWorld()
{
	return m_pWorld;
}

void HSBattleLayer::SetIsPauseWorld( bool b )
{
	m_bIsPauseWorld = b;
}

CCLayerColor* HSBattleLayer::GetModalLayer()
{
	return m_pMaskLayer;
}

void HSBattleLayer::CallEnergyFull( CCNode* spxNode,void* pData )
{
	m_isFreeEnergy = true;
}

HSStratagemManager* HSBattleLayer::GetStragemManager()
{
	return m_pStratagemManager;
}

void HSBattleLayer::SetIsPause( bool b )
{
	m_bIsPause = b;
}

void HSBattleLayer::Pause()
{
	HSBattleScene* pScene = dynamic_cast<HSBattleScene*>(CCDirector::sharedDirector()->getRunningScene());
	if (pScene)
	{
		this->GetModalLayer()->setVisible(true);

		this->SetIsPause(true);
		HS_GAME_CONFIG()->SetIsPause(true);
		this->onExit();
		pScene->GetHSBattlePauseLayer()->setVisible(true);
	}
}

void HSBattleLayer::Resume()
{
	HSBattleScene* pScene = dynamic_cast<HSBattleScene*>(CCDirector::sharedDirector()->getRunningScene());
	if (pScene)
	{
		this->GetModalLayer()->setVisible(false);

		this->SetIsPause(false);
		HS_GAME_CONFIG()->SetIsPause(false);
		this->onEnter();
		pScene->GetHSBattlePauseLayer()->setVisible(false);
	}
}

void HSBattleLayer::CallPlayReadyGoFinish( CCNode* spxNode,void* pData )
{
	CCActionInterval*  actionBy1 = CCScaleTo::create(0.5f, 1.5f);
	CCActionInterval*  actionBy2 = CCScaleTo::create(0.2f, 1.f);
	CCCallFunc* call = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::CallGameStart));
	m_pGameTimeLabel->runAction( CCSequence::create( actionBy1,actionBy2,call, NULL));
}

void HSBattleLayer::CallGameStart()
{
	this->SetIsPause(false);
}

void HSBattleLayer::AddOneFlyBalloon()
{
	m_iFlyBalloonCount++;
}

void HSBattleLayer::CreatePosArray()
{
	map<BalloonColorType,CCTexture2D*>::iterator it = m_balloonColorMap.find(BALLOON_COLOR_BLUE);
	if (it == m_balloonColorMap.end())
	{
		HSMessageBox("CreatePosArray Fail");
		return;
	}
	float screenW = HSBase::GetTemplateScreenW();
	float screenH = HSBase::GetTemplateScreenH();

	float maxV = HS_MATH_MAX(it->second->getPixelsWide(),it->second->getPixelsHigh());
	float imageW = maxV;
	float imageH = maxV;

	CCPoint posAnchor = ccp(imageW/2+2,0.f - imageH);

	int row = screenW / (imageW+2);
	int line = m_iMaxPosArraySize / row;
	if (m_iMaxPosArraySize % row > 0)
	{
		++line;
	}
	/**
	float redundantW = screenW - (float)row * imageW;
	if (redundantW > 0.f)
	{
		redundantW /= 2.f;
	}else{
		redundantW = 0;
	}*/

	//posAnchor.x += redundantW;

	for (int i=0;i<line;++i)
	{
		for (int j=0;j<row;++j)
		{
			HSBlock block;
			float x = posAnchor.x +j*(imageW+2);
			float y = posAnchor.y -i*(imageH+2);
			block.pos = ccp(x,y);
			m_vPosArray.push_back(block);
		}
	}
}

void HSBattleLayer::SetPosArraySize( int count )
{
	HSAssert(count >= 0,"");
	
	m_iMaxPosArraySize = count;

	m_vPosArray.clear();

	this->CreatePosArray();
}

bool HSBattleLayer::CallGoldErptEnd()
{

	CCSprite* pKingEffect_L = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_1","KingLight");
	CCSprite* pKingEffect_R = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_0","KingLight");
	pKingEffect_L->stopAllActions();
	pKingEffect_R->stopAllActions();

	pKingEffect_L->setVisible(false);
	pKingEffect_R->setVisible(false);

	pKingEffect_L->setColor(ccc3(255,255,255));
	pKingEffect_R->setColor(ccc3(255,255,255));


	////
	this->PlayGoldHeapEffect();

	return true;
}

void HSBattleLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	HSLoadingLayer::ShareLoading()->setVisible(false);
}

void HSBattleLayer::CallSupermanFinish()
{
	BalloonGameData* pGameData = HS_GAME_CONFIG_MUTABLE_DATA();
	pGameData->isListerLastBalloonType = true;
	m_isPlaySuperman = true;
	pGameData->isShowSuperman = false;
	this->GetModalLayer()->setVisible(false);
	m_pSpriteSuperman->setVisible(false);
}

void HSBattleLayer::CallTimeupFinish( CCNode* pSpx,void* pData )
{
	
	
	if (this->m_IsAllowRunBuffer || !this->m_pBufferPropManager->IsHasBuffer())
	{
		//没有buffer的时候
		RunBattleOverLayer();
		this->m_IsAllowRunBuffer = false;
	}else{
		this->m_IsAllowRunBuffer = true;
	}
	
}

bool HSBattleLayer::IsAllowRunBuffer()
{
	return m_IsAllowRunBuffer;
}

void HSBattleLayer::RunBattleOverLayer()
{
	HSBattleScene* pScene = dynamic_cast<HSBattleScene*>(CCDirector::sharedDirector()->getRunningScene());

	if (pScene)
	{
		this->GetModalLayer()->setVisible(true);

		this->onExit();

		pScene->GetHSBattleOverLayer()->setVisible(true);

	}
}

void HSBattleLayer::PlayTimeTimeWillOver( float durationTime )
{
	CCSprite* pKingEffect_L = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_1","KingLight");
	CCSprite* pKingEffect_R = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_0","KingLight");
	pKingEffect_L->setVisible(true);
	pKingEffect_R->setVisible(true);

	CCActionInterval*  actionL = CCBlink::create(durationTime, HS_MATH_MAX(durationTime,1.f) * 2);
	CCActionInterval*  actionR = CCBlink::create(durationTime, HS_MATH_MAX(durationTime,1.f) * 2);
	CCCallFunc* callFinish = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::CallPlayTimeTimeWillOverEnd));
	pKingEffect_L->runAction(CCSequence::create(actionL,callFinish,NULL));
	pKingEffect_R->runAction(actionR);

	pKingEffect_L->setColor(ccc3(255,0,0));
	pKingEffect_R->setColor(ccc3(255,0,0));

	pKingEffect_L->setVisible(true);
	pKingEffect_R->setVisible(true);
}

void HSBattleLayer::CallPlayTimeTimeWillOverEnd()
{
	CCSprite* pKingEffect_L = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_1","KingLight");
	CCSprite* pKingEffect_R = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_0","KingLight");
	pKingEffect_L->setVisible(false);
	pKingEffect_R->setVisible(false);

	pKingEffect_L->stopAllActions();
	pKingEffect_R->stopAllActions();

	pKingEffect_L->setColor(ccc3(255,255,255));
	pKingEffect_R->setColor(ccc3(255,255,255));

	HS_GAME_CONFIG_MUTABLE_DATA()->dribbleCount = 0;
}

void HSBattleLayer::PlaySupermanEffect()
{
	m_pSpriteSuperman->setPosition(CCPointZero);
	m_pSpriteSuperman->setVisible(true);
	CCMoveBy* pMoveBy = CCMoveBy::create(0.5f,HSBase::GetTemplateScreenCentre());
	CCMoveBy* pMoveBy1 = CCMoveBy::create(0.5f,ccp(HSBase::GetTemplateScreenW() / 2.f,HSBase::GetTemplateScreenH() / 2.f + m_pSpriteSuperman->getContentSize().height * 2.f));
	CCDelayTime* pDelayTime = CCDelayTime::create(0.5f);
	CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::CallSupermanFinish));
	m_pSpriteSuperman->runAction(CCSequence::create(pMoveBy,pDelayTime,pMoveBy1,pCallFunc,NULL));
}

void HSBattleLayer::SetGoldHeapSprite( CCSprite* s )
{
	if (m_pGoldHeap)
	{
		m_pGoldHeap->getParent()->removeChild(s,true);
	}
	m_pGoldHeap = s;
}

void HSBattleLayer::PlayGoldHeapEffect()
{
	if (!m_pGoldHeap)
	{
		return;
	}
	m_pGoldHeap->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,0.f));
	CCMoveBy* pMoveBy = CCMoveBy::create(0.5f,ccp(0,m_pGoldHeap->getContentSize().height));
	CCDelayTime* pDelayTime = CCDelayTime::create(1.f);
	CCMoveBy* pMoveBy1 = CCMoveBy::create(0.5f,ccp(0,-m_pGoldHeap->getContentSize().height));
	CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::CallPlayGoldHeapEffectEnd));
	m_pGoldHeap->runAction(CCSequence::create(pMoveBy,pDelayTime,pMoveBy1,pCall,NULL));
}

void HSBattleLayer::CallPlayGoldHeapEffectEnd()
{
	m_pSpxTimeUp->setVisible(true);
	m_pSpxTimeUp->SetAction(0,1,this,callfuncND_selector(HSBattleLayer::CallTimeupFinish),NULL);
}

void HSBattleLayer::LogicOfGameGuide_Six( float dt )
{
	if (!HS_GAME_CACHE()->IsRunGameGuide() || !m_isStep_Six)
	{
		return;
	}

	if (HSGameGuide::ShaderGameGuide()->GetCurrentStep() == 6)
	{
		HSGameGuide::ShaderGameGuide()->setVisible(false);

		HSAssert(m_pComboManager,"");

		if (m_pComboManager->GetComboCount() >= 3)
		{
			HSGameGuide::ShaderGameGuide()->setVisible(true);
			HS_GAME_CONFIG_MUTABLE_DATA()->energy = HS_GAME_CONFIG_DATA()->energyMax;
			m_isStep_Six = false;
			m_isStep_Nine = true;
		}else{
			static float tempTime = 0.f;
			if (tempTime > 5.f)
			{
				tempTime = 0.f;
				HSGameGuide::ShaderGameGuide()->RuntPrevious();
			}else{
				tempTime += dt;
			}
		}
	}
}

void HSBattleLayer::LogicOfGameGuide_Nine( float dt )
{
	if (!HS_GAME_CACHE()->IsRunGameGuide() || !m_isStep_Nine)
	{
		return;
	}
	if (HSGameGuide::ShaderGameGuide()->GetCurrentStep() == 9)
	{
		HSGameGuide::ShaderGameGuide()->Pause();
		m_pStratagemManager->Down();
		m_pStratagemManager->Down();
		m_isStep_Nine = false;
	}
}

void HSBattleLayer::LogicOfGameGuide_Ten( float dt )
{
	if (!HS_GAME_CACHE()->IsRunGameGuide() || !m_isStep_Ten)
	{
		return;
	}

	if (HSGameGuide::ShaderGameGuide()->GetCurrentStep() == 9)
	{
		CCNode* pScene = CCDirector::sharedDirector()->getRunningScene();
		HSGameGuide::ShaderGameGuide()->Resume(pScene);
		m_isStep_Ten = false;
		m_isStep_Eleven = true;
	}
}

void HSBattleLayer::LogicOfGameGuide_Eleven()
{
	if (!HS_GAME_CACHE()->IsRunGameGuide() || !m_isStep_Eleven)
	{
		return;
	}

	if (HSGameGuide::ShaderGameGuide()->GetCurrentStep() == 10)
	{
		m_iGameTime = 1;
		m_isStep_Eleven = false;

		HSGameGuide::ShaderGameGuide()->Pause();

		HSBattleScene* scene = dynamic_cast<HSBattleScene*>(this->getParent());
		HSBattleOverLayer* layer = scene->GetHSBattleOverLayer();
		layer->LogicOfGameGuide();
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

	this->hsBattlePauseLayer = HSBattlePauseLayer::create();
	this->hsBattlePauseLayer->setVisible(false);
	this->addChild(this->hsBattlePauseLayer,HS_BASE_TAG + 1,HS_BASE_TAG + 1);

	this->hsBattleOverLayer = HSBattleOverLayer::create();
	this->hsBattleOverLayer->setVisible(false);
	this->addChild(this->hsBattleOverLayer,HS_BASE_TAG + 2,HS_BASE_TAG + 2);

	//创建新手引导
	{
		if (HS_GAME_CACHE()->IsRunGameGuide())
		{
			HSGameGuide::ShaderGameGuide()->Resume(this);
		}
	}
	return true;
}