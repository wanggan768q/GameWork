#include "HSBattleScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSRankUpLayer.h"
#include "HSJava.h"
#include "HSShowEndurance.h"

HSBattleLayer::HSBattleLayer(void)
{
	m_isInitFinish = false;
	m_pFinger = NULL;
	m_isPauseWorld = false;
	m_pWorld = NULL;
	m_pDebugDraw = NULL;
    m_pPlayerActionManager = NULL;
    
    //TODO: 局域网屏幕刷新时间 0.f
    if(HS_IsLanMode())
    {
        m_sendScreenInfoIntervalTime = 3.f;
    }else{
        m_sendScreenInfoIntervalTime = 3.f;
    }
    
	m_dropCount = 10;
	m_isPauseGame = false;
	m_dripIndex = 0;
	m_dropIntervalMinTime = 0.5f;
	m_dropIntervalMaxTime = 2.f;
	m_dropIntervalTime = 0.f;
	m_LinearVelocityMinY = 2.f;
	m_LinearVelocityMaxY = 2.f;
	m_drawLineCount = 0;
    
	m_pRaycast = new HSRaycastCallback;
	
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
    
    //FastProp
    m_pPropWave = NULL;
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
	this->setKeypadEnabled(true);
    
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
    
    //@
    this->InitPlayerAction();
    
	m_pBattleTranscribe = HSBattleTranscribe::create();
	this->addChild(m_pBattleTranscribe);
    
    // 	CCMenuItemLabel* pLabel = CCMenuItemLabel::create(CCLabelTTF::create("ShiBai","",25.f),this,menu_selector(HSBattleLayer::SendGameOver));
    // 	pLabel->setPosition(ccp(50,30));
    // 	CCMenu* pMenu = CCMenu::create(pLabel,NULL);
    // 	this->addChild(pMenu,20000);
    static bool isMusic03 = true;
    if(isMusic03)
    {
    	HS_Play_Music("back_03");
    }
    else
    {
    	HS_Play_Music("back_04");
    }
    
    
    m_pBombSpx = SPX_Manager::CreateSprite("SPX/baozha.sprite");
    m_pBombSpx->setVisible(false);
    m_pBombSpx->SetAction(0);
    this->addChild(m_pBombSpx);
    
	isMusic03 =!isMusic03;
    
    //流星
    {
        CCSprite* p1 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_0","Fengmianliuxing_0");
        CCSprite* p2 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_2","Fengmianliuxing_0");
        CCSprite* p3 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_6","Fengmianliuxing_0");
        CCSprite* p4 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_12","Fengmianliuxing_0");
        CCSprite* p5 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_8","Fengmianliuxing_0");
        CCSprite* p6 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_10","Fengmianliuxing_0");
        CCSprite* p7 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_4","Fengmianliuxing_0");
        
        CCSprite* p8 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_1","Fengmianliuxing_1");
        CCSprite* p9 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_3","Fengmianliuxing_1");
        CCSprite* p10 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_5","Fengmianliuxing_1");
        CCSprite* p11 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_7","Fengmianliuxing_1");
        CCSprite* p12 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_9","Fengmianliuxing_1");
        CCSprite* p13 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_11","Fengmianliuxing_1");
        
        p1->setOpacity(0);
        p2->setOpacity(0);
        p3->setOpacity(0);
        p4->setOpacity(0);
        p5->setOpacity(0);
        p6->setOpacity(0);
        p7->setOpacity(0);
        p8->setOpacity(0);
        p9->setOpacity(0);
        p10->setOpacity(0);
        p11->setOpacity(0);
        p12->setOpacity(0);
        p13->setOpacity(0);
        
        vector<CCNode*> v,v1;
        v.push_back(p1);
        v.push_back(p2);
        v.push_back(p3);
        v.push_back(p4);
        v.push_back(p5);
        v.push_back(p6);
        v.push_back(p7);
        v1.push_back(p8);
        v1.push_back(p9);
        v1.push_back(p10);
        v1.push_back(p11);
        v1.push_back(p12);
        v1.push_back(p13);
        
        
        for_each(v.begin(), v.end(), [](CCNode* p)
                 {
                     CCMoveTo* a5 = CCMoveTo::create(0.0001f, p->getPosition());
                     
                     CCFadeIn* a1 = CCFadeIn::create(0.1f);
                     CCMoveBy* a2 = CCMoveBy::create(HSMath::Random(0.5f, 1.f), ccp(-193,-249));
                     
                     CCSpawn* a3 = CCSpawn::create(a1,a2,NULL);
                     CCFadeOut* a4 = CCFadeOut::create(0.1);
                     
                     CCDelayTime* a6 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCDelayTime* a7 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCSequence* pSeq = CCSequence::create(a7,a3,a4,a5,a6,NULL);
                     CCRepeatForever* forever = CCRepeatForever::create(pSeq);
                     
                     p->runAction(forever);
                 });
        
        for_each(v1.begin(), v1.end(), [](CCNode* p)
                 {
                     
                     CCMoveTo* a5 = CCMoveTo::create(0.0001f, p->getPosition());
                     
                     CCFadeIn* a1 = CCFadeIn::create(0.1f);
                     CCMoveBy* a2 = CCMoveBy::create(HSMath::Random(0.5f, 1.f), ccp(-181,-233));
                     CCSpawn* a3 = CCSpawn::create(a1,a2,NULL);
                     CCFadeOut* a4 = CCFadeOut::create(0.1);
                     
                     CCDelayTime* a6 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCDelayTime* a7 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCSequence* pSeq = CCSequence::create(a7,a3,a4,a5,a6,NULL);
                     CCRepeatForever* forever = CCRepeatForever::create(pSeq);
                     
                     p->runAction(forever);
                 });
        
    }
    
    //扣除体力
    {
        HSShowEndurance::SubEndurance();
    }
    
    //ReadyGO
    {
        this->addChild(HSReadyGoSprite::create(),3000);
    }
	this->schedule(schedule_selector(HSBattleLayer::Updata));
}

void HSBattleLayer::LoadUI()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/BattleScene.data","Image/",this);
    
	CCSprite* pBackground = HSCCSprite::create("Image/zhandoubeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	m_pBlueFrame = HS_FIND_UI_PANEL_SPRITE("UI_Hudunxiaoguo","Hudunxiaoguo");
	m_pRedFrame = HS_FIND_UI_PANEL_SPRITE("UI_Shihuaxiaoguo","Shihuaxiaoguo");
    
	m_pBlueFrame->setVisible(false);
	m_pRedFrame->setVisible(false);
    
	//@ 头像
    //	CCSprite* pSelfHeadFrame = HS_FIND_UI_PANEL_SPRITE("UI_TOUXIANG0","Touxiangdikuang");
    //	CCSprite* pTargeterHeadFrame = HS_FIND_UI_PANEL_SPRITE("UI_TOUXIANG1","Touxiangdikuang");
    //
    //	const char* selfHeadFilePath = CCString::createWithFormat("Image/%d.png",HS_TARGET_SELF().iconid())->getCString();
    //
    //	const char* targeterHeadFilePath = CCString::createWithFormat("Image/%d.png",HS_TARGET_TARGET().iconid())->getCString();
    //
    //	CCSprite* pSelfHead = HSCCSprite::create(selfHeadFilePath);
    //	CCSprite* pTargeterHead = HSCCSprite::create(targeterHeadFilePath);
    //
    //	pSelfHead->setPosition(HS_SizeHalf_Point(pSelfHeadFrame->getContentSize()));
    //	pTargeterHead->setPosition(HS_SizeHalf_Point(pTargeterHeadFrame->getContentSize()));
    //
    //	pSelfHeadFrame->addChild(pSelfHead);
    //	pTargeterHeadFrame->addChild(pTargeterHead);
    
    
    
    
	//@ Combo
	m_pComboFrame = HSCCSprite::create("Image/ComboFrame.png");
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
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
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
    
    
    //@ 初始化奖励效果
    // #122
    CCSprite* pGood = HS_FIND_UI_PANEL_SPRITE("UI_Wenzitexiao", "Good");
    CCSprite* pCool = HS_FIND_UI_PANEL_SPRITE("UI_Wenzitexiao", "Cool");
    CCSprite* pPerfect = HS_FIND_UI_PANEL_SPRITE("UI_Wenzitexiao", "Perfect");
    pGood->setVisible(false);
    pCool->setVisible(false);
    pPerfect->setVisible(false);
    
    //@ 濒死效果
    m_pWillEffect = HS_FIND_UI_PANEL_SPRITE("UI_Binsi", "Binsi");
    m_pWillEffect->setVisible(false);
    
    
    //设置游戏结算界面目标的形象ID
    {
        HSBattleOverLayer::SetTargetFingureID(HS_TARGET_TARGET().figureid());
    }
}

void HSBattleLayer::InitProp()
{
	if (!m_pHSPropManager)
	{
		m_pHSPropManager = new HSPropManager;
	}
}

void HSBattleLayer::InitPlayerAction()
{
    m_pPlayerActionManager = HSPlayerActionManager::Create(HS_TARGET_SELF().figureid(), HS_TARGET_TARGET().figureid());
    this->addChild(m_pPlayerActionManager);
}

void HSBattleLayer::LoadBalloonTexture2D()
{
	for (int i=0;i<7;++i)
	{
		int colorTyep = (int)BALLOON_COLOR_Blue;
		BalloonColorType newColorType = (BalloonColorType)(colorTyep + i);
		CCString* pBaseFileName = CCString::createWithFormat("Image/animal_%d.png",i + 1);
		CCString* pLuminousFileName = CCString::createWithFormat("Image/animal_%d_1.png",i + 1);
        CCString* pWillDeathFileName = CCString::createWithFormat("Image/animal_%d_2.png",i + 1);
        
		CCTexture2D* t = NULL;
        CCTexture2D* t1 = NULL;
        CCTexture2D* t2 = NULL;
		t = CCTextureCache::sharedTextureCache()->addImage(pBaseFileName->getCString());
		if (i == 5) //石化球
		{
			t1 = t;
		}else if( i == 6 ){ //炸弹球
            t1 = t;
            t2 = t;
        }else{
			t1 = CCTextureCache::sharedTextureCache()->addImage(pLuminousFileName->getCString());
            t2 = CCTextureCache::sharedTextureCache()->addImage(pWillDeathFileName->getCString());
		}
		
        
		BalloonTexture2D ballonTexture;
		ballonTexture.base = t;
		ballonTexture.luminous = t1;
        ballonTexture.willDeath = t2;
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

void HSBattleLayer::InitPhysics()
{
	HSBox2dShapeCache::sharedGB2ShapeCache()->addShapesWithFile("Image/animal.plist");
    
	b2Vec2 gravity;
	gravity.Set(0.f, -10.f);
	m_pWorld = new b2World(gravity);
	m_pWorld->SetContactListener(m_pContacListener);
	m_pWorld->SetAllowSleeping(true);
	m_pWorld->SetContinuousPhysics(false);
	//falseʱ��ʼ���岻������Ӱ�죬�������
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
	CCSprite* pOtherScreen = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
	m_pOtherBattleScreen = CCNode::create();
	m_pOtherBattleScreen->setContentSize(pOtherScreen->getContentSize());
	pOtherScreen->addChild(m_pOtherBattleScreen,1100);
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
        // #121
        for_each(passBalloonList->begin(), passBalloonList->end(), [](HSBalloonSprite* ps)
                 {
                     ps->runAction(ps->PassAction());
                 });
		m_pRaycast->Reset();
		return;
	}  
    
    
	std::vector<HSBalloonSprite*>::const_iterator it = passBalloonList->begin();
    
    // #122
    this->PlayRewardsEffect(passBalloonList->size());
    
	bool isRemoveBeginBalloon = true;
	int passBalloonListSize = (int)passBalloonList->size();
	BalloonColorType tempColorType = (*passBalloonList)[0]->GetColorType();
	if (passBalloonListSize == 4)
	{
        m_dropCamouflage.count += 1;
        
#pragma region __发送销毁气球数据__
		DestroyBalloonRequest_DestroyBalloonInfo* tempDestroyBalloonInfoCamouflage = destroyBalloonRequest.add_destroyballoon();
		tempDestroyBalloonInfoCamouflage->set_count(1);
		tempDestroyBalloonInfoCamouflage->set_type(DestroyBalloonRequest_Type_BALLOON_COLOR_Camouflage);
#pragma endregion __发送销毁气球数据__
	}else if(passBalloonListSize == 7){
        
        isRemoveBeginBalloon = false;
        this->SetBalloonColorType(*passBalloonList->rbegin(),BALLOON_COLOR_Bomb);
    }
    
    if(passBalloonListSize > 4){
        
        
		HSDropApply hsPetrifaction;
		hsPetrifaction.count = passBalloonListSize - 4;
        hsPetrifaction.count = HSFormula::ShiHuaQiuShuLiang(passBalloonListSize);
		hsPetrifaction.colorType = tempColorType;
        if(hsPetrifaction.count > 0)
        {
            m_PetrifactionBalloonNumList.push_back(hsPetrifaction);
        }
		
        
        // #119
        std::vector<HSBalloonSprite*>::const_reverse_iterator crIt = passBalloonList->rbegin();
		if (crIt != passBalloonList->rend())
		{
            //播放连消5个以上球的效果
            HSBalloonSprite* lastS = *crIt;
            if(hsPetrifaction.count > 0)
            {
                this->PlayDestroyBalloon5Effect(lastS->getPosition(),hsPetrifaction.count);
            }
            
            
            CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
            HSAssert(pOtherScreenFrame,"");
            CCPoint OtherScreenFramePos = pOtherScreenFrame->getPosition();
            
            float mvRange = HSMath::Round(pow(passBalloonListSize + 4, 0.8f));  //=ROUND((A1+4)^0.8,0)
            
            CCDelayTime* pDelayTime = CCDelayTime::create(0.8f);
            CCMoveTo* left1 = CCMoveTo::create(0.05,ccp(OtherScreenFramePos.x + mvRange,OtherScreenFramePos.y));
            CCMoveTo* right1 = CCMoveTo::create(0.05,ccp(OtherScreenFramePos.x - mvRange,OtherScreenFramePos.y));
            CCMoveTo* top1 = CCMoveTo::create(0.05,ccp(OtherScreenFramePos.x,OtherScreenFramePos.y + mvRange));
            CCMoveTo* rom1 = CCMoveTo::create(0.05,ccp(OtherScreenFramePos.x,OtherScreenFramePos.y - mvRange));
            CCMoveTo* restore = CCMoveTo::create(0.05,OtherScreenFramePos);
            CCFiniteTimeAction* action3 = CCSequence::create(pDelayTime,left1,right1,top1,rom1,restore,NULL);
            CCRepeat* pRepeat = CCRepeat::create(action3, 1);
            pOtherScreenFrame->runAction(pRepeat);
		}
        
#pragma region __发送销毁气球数据__
        if(hsPetrifaction.count > 0)
        {
            DestroyBalloonRequest_DestroyBalloonInfo* tempDestroyBalloonInfoPetrifaction = destroyBalloonRequest.add_destroyballoon();
            tempDestroyBalloonInfoPetrifaction->set_count(hsPetrifaction.count);
            tempDestroyBalloonInfoPetrifaction->set_type(DestroyBalloonRequest_Type_BALLOON_COLOR_Petrifaction);
        }
#pragma endregion __发送销毁气球数据__
        
        //攻击动作
        m_pPlayerActionManager->SetActionSate(PLAYER_ACTION_ATTACK);
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
        default:
            break;
	}
#pragma endregion __音效__
    
	for (;it!= passBalloonList->end();++it)
	{
		HSBalloonSprite* s = *it;
		//b2Body* pBody = s->getB2Body();
		
		//if (!isRemoveBeginBalloon && *it == *passBalloonList->begin() )
        if (!isRemoveBeginBalloon && *it == *passBalloonList->rbegin() )
		{
			//Is the last one
			s->SetLuminous(false);
            if(passBalloonListSize == 7){
                
                this->SetBalloonColorType(s,BALLOON_COLOR_Bomb);
            }
            
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
        if(!m_isGameOver)
        {
            // TODO: 支持局域网消球
            //HSRequest::ShareRequest()->SendDestroyBalloonRequest(destroyBalloonRequest);
            this->SendDestroyBalloon(&destroyBalloonRequest);
        }
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
    
    s->RandomColorType();
    
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
    
	if (moveDistancce < 0.8f)
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

void HSBattleLayer::Updata( float dt )
{
	
	//isOK->setString(CCString::createWithFormat("%d -- %.4f---%.4f",isOOK,HSTool::S_SEND_TIME,HSTool::S_Receive_TIME)->getCString());
	
	if (m_isPauseGame)
	{
		return;
	}
    
	if (!IsGameOver())
	{
        static float tempTime = 0.f;
		if (tempTime > m_sendScreenInfoIntervalTime)
		{
			this->Send();
			tempTime = 0.f;
		}
		else
		{
			tempTime += dt;
		}
        
        this->Logic(dt);
        
        this->DrawLine(dt);
        
        this->Logic_LineChange(dt);
        
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

void HSBattleLayer::Logic_LineChange(float dt)
{
    if (!m_pRaycast)
    {
        return;
    }
    const std::vector<HSBalloonSprite*>* passBalloonList = m_pRaycast->GetPassBalloonList();
    int count = (int)passBalloonList->size();
    
    if (count < 2)
    {
        return;
    }
    
    
    string lineFileName = "";
    if (count >= 2 && count <= 4)
    {
        
        lineFileName = "Image/Line_0.png";
        
    }else if(count >= 5 && count <= 7){
        
        lineFileName = "Image/Line_1.png";
        
    }else if(count >= 8){
        
        lineFileName = "Image/Line_2.png";
        
    }
    
    for_each(m_lineList.begin(), m_lineList.end(), [&](HSLine* pLine)
             {
                 CCSpriteFrame* pTempFrame = HS_RP_GetSpriteFrame(lineFileName.c_str());
                 if( !pLine->isFrameDisplayed(pTempFrame) )
                 {
                     pLine->setDisplayFrame(pTempFrame);
                 }
             });
    
    
}

void HSBattleLayer::SetDropCount( int v )
{
	m_dropCount = v;
}

void HSBattleLayer::Logic( float dt )
{
	this->Logic_Drop(dt);
}

void HSBattleLayer::Logic_Drop( float dt )
{
	static float tempPassTime = 0.f;
    
	m_gameTime += dt;
    
	if (m_dropCount <= 0)
	{
		//m_dropCount = HSMath::Round(1.75f + m_gameTime / 60.f);	//掉落数量公式
        //ROUNDDOWN(1.75+B2/60,0)+ABS（rand（18,24)-X)
        int parma_1 = (HSMath::Random(18, 24) - (int)m_dropBalloonList.size());
        parma_1 < 0 ? parma_1 = 0 : 0;
        //m_dropCount = HSMath::Round(1.75f + m_gameTime / 60.f) + parma_1;
        m_dropCount = HSFormula::DiaoLuoShuLiang(m_gameTime) + parma_1;
		tempPassTime = 0.f;
		return;
	}
    
	if (HSMath::EqualsWithFloat(m_dropIntervalTime,HS_EPSILON))
	{
		//m_dropIntervalTime = 3.f;
        m_dropIntervalTime = HSFormula::DiaoLuoShiJianJianGe();
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
        //s->SetColorType(BALLOON_COLOR_Petrifaction,7.0);
		s->SetColorType(BALLOON_COLOR_Petrifaction,HSFormula::ShiHuaShiJian());
		s->SetWillChangeColorType(m_dropPetrifaction.colorType);
		m_dropPetrifaction.count -= 1;
		++m_dropCount;
		this->PlayRedFrameBlink(1.5f);
		HS_Play_Sound("alert_effect");
	}else if(m_dropCamouflage.count > 0){
        
        s->SetColorType(BALLOON_COLOR_Camouflage);
		m_dropCamouflage.count -= 1;
		++m_dropCount;
        
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

CCNode* HSBattleLayer::GetOtherScreen()
{
    return HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");;
}

HSPlayerActionManager* HSBattleLayer::GetPlayerActionManager()
{
    return m_pPlayerActionManager;
}

void HSBattleLayer::UpdataOtherBattleScreen( const BattleInfo& info )
{
	if (m_lastTimestamp > info.timestamp())
	{
		HSMessageBox("Illegal information battle");
		return;
	}
	HSAssert(m_pOtherBattleScreen,"");
    
	
	int tempDropPetrifactionCount = info.droppetrifactionlist_size();
	for (int i=0;i<tempDropPetrifactionCount;++i)
	{
        if (i == 0)
        {
            //被打 状态
            m_pPlayerActionManager->SetActionSate(PLAYER_ACTION_BEAT);
            //被攻击 缸体 震动效果
            this->PlayBeatEffect();
        }
		const ::message::BattleInfo_DropPetrifactionBalloon dropPet = info.droppetrifactionlist(i);
		HSDropApply hsPetrifaction;
		hsPetrifaction.count = dropPet.count();
		hsPetrifaction.colorType = (BalloonColorType)(dropPet.willchangecolortype());
		m_dropPetrifactionList.push_back(hsPetrifaction);
	}
	
    
	
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
    
    //@ 小屏幕上的信息
	for (int i=0;i<info.balloondatalist_size();++i)
	{
		const BattleInfo_Balloon balloon = info.balloondatalist(i);
		BalloonColorType balloonColorType = (BalloonColorType)balloon.colortype();
		map<BalloonColorType,BalloonTexture2D>::iterator it = HSBalloonSprite::GetBalloonColorMap()->find(balloonColorType);
		CCSprite* ps = NULL;
		if (it != HSBalloonSprite::GetBalloonColorMap()->end())
		{
			ps = HSCCSprite::createWithTexture(it->second.base);
			
		}else if(balloonColorType == BALLOON_COLOR_Camouflage){
            
			ps = HSCCSprite::create("Image/Camouflage.png");
            
		}else if(balloonColorType == BALLOON_COLOR_Chameleon){
            
			ps = HSCCSprite::create("Image/Bianselong.png");
            
		}else if(balloonColorType == BALLOON_COLOR_Bomb){
            
            ps = HSCCSprite::create("Image/animal_7.png");
            
        }else if(it == HSBalloonSprite::GetBalloonColorMap()->end()){
            
			continue;
		}
		float posX = balloon.x() * scaleX + 5.f;
		float posY =  (balloon.y() - m_offsetBottom.height) * scaleY + 5.f;
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
                        CCDelayTime* pDelayTime = CCDelayTime::create(1.5f);
                        CCCallFunc*  pcall = CCCallFunc::create(this, callfunc_selector(HSBattleLayer::Function_Chameleon));
                        this->runAction(CCSequence::create(pDelayTime,pcall,NULL));
						
						this->PlayUserPropEffect_OtherScreen(pPropInfo);
                        
                        //必杀 状态
                        m_pPlayerActionManager->SetActionSate(PLAYER_ACTION_KILL_BEAT);
					}
                        break;
                    case PropInfo_BufferPropType_BUFFER_PROPS_Meidusha:
					{
                        CCDelayTime* pDelayTime = CCDelayTime::create(1.5f);
                        CCCallFunc*  pcall = CCCallFunc::create(this, callfunc_selector(HSBattleLayer::Function_Meidusha));
                        this->runAction(CCSequence::create(pDelayTime,pcall,NULL));
                        
						this->PlayUserPropEffect_OtherScreen(pPropInfo);
                        
                        //必杀 状态
                        m_pPlayerActionManager->SetActionSate(PLAYER_ACTION_KILL_BEAT);
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
            default:
                break;
		}
	}
}

void HSBattleLayer::Function_Chameleon()
{
    HSBalloonFactory factory;
    m_pWorld->QueryAABB(&factory,m_workArea);
    
    std::set<HSBalloonSprite*>* pPool = factory.GetSpriteList();
    std::set<HSBalloonSprite*>::iterator it = pPool->begin();
    for (;it!=pPool->end();++it)
    {
        
        HSBalloonSprite* ps = (*it);
        BalloonColorType type = ps->GetColorType();
        if (type != BALLOON_COLOR_Petrifaction)
        {
            ps->SetColorType(BALLOON_COLOR_Chameleon);
        }
    }
}

void HSBattleLayer::Function_Meidusha()
{
    HSBalloonFactory* pFactory = HS_GET_BattleLayer()->GetScreenAllBalloon();
    HSAssert(pFactory,"");
    
    std::set<HSBalloonSprite*>* pList = pFactory->GetSpriteList();
    std::set<HSBalloonSprite*>::iterator it = pList->begin();
    BalloonColorType tempColorType = BALLOON_COLOR_Unknow;
    for (;it!=pList->end();++it)
    {
        HSBalloonSprite* ps = (*it);
        if (ps->GetColorType() != BALLOON_COLOR_Petrifaction)
        {
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
            ps->SetColorType(BALLOON_COLOR_Petrifaction,3.5f);
            ps->SetWillChangeColorType(tempColorType);
        }
        
    }
    CC_SAFE_DELETE(pFactory);
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
    
	// ���ʯ������
	for (int i=0;i<(int)m_PetrifactionBalloonNumList.size();++i)
	{
		HSDropApply hsPetrifaction = m_PetrifactionBalloonNumList[i];
		BattleInfo_DropPetrifactionBalloon* pDropPetrifactionBalloon = pBattleInfo->add_droppetrifactionlist();
		pDropPetrifactionBalloon->set_count(hsPetrifaction.count);
		pDropPetrifactionBalloon->set_willchangecolortype((int)hsPetrifaction.colorType);
	}
	m_PetrifactionBalloonNumList.clear();
    
	// �����Ļ��Ϣ
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
    
	// ���ʹ�õ���
	for (int i=0;i<(int)m_userPropList.size();++i)
	{
		pBattleInfo->add_userpropid((*(m_userPropList.begin() + i))->id());
	}
	this->ClearUserPropInfo();
    
    
	//����ʱ���
	pBattleInfo->set_timestamp(HSTime::GetLocalityTimeAccurate());
    
	if (m_pBattleTranscribe)
	{
		m_pBattleTranscribe->AddFrame(*pBattleInfo);
	}
    
	//����������Ϣ
	if (HS_ONLINE)
	{
        // TODO: 支持局域网对战发送战斗数据
		//HSRequest::ShareRequest()->SendBattleRequest(pBattleDataRequest);
        this->SendBattleData(pBattleDataRequest);
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
    ps->SetLastColorType(colorType);
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
				//HSJava::ShaderJava()->ShowToast("HandleCross",1);
				CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::Call_GameOver));
				m_pSelfBattleScreec->setContentSize(HSBase::GetTemplateScreenSize());
				m_pSelfBattleScreec->setPosition(HSBase::GetTemplateScreenCentre());
				m_pSelfBattleScreec->runAction(CCSequence::create(p,pDelay,pCall,NULL));
				HS_GAME_CACHE()->m_pBattleResult->set_result(BattleResultResponse_PlayerMatchResult_LOST);
				
                
				//越界
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
        // TODO: 支持局域网对战结果
		//HSRequest::ShareRequest()->SendBattleResultRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str(),BattleResultRequest_GameStatus_OVER);
        this->SendBattleResultRequest();
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
    HSRequest::ShareRequest()->SendMatchSearchStrengthRequest();
    
    if (m_pBattleTranscribe)
    {
        m_pBattleTranscribe->Save();
    }
	HS_GAME_CACHE()->m_pBattleResult->Clear();
	HS_GAME_CACHE()->m_pBattleResult->CopyFrom(*pMsg);
    
	HS_MUTABLE_TARGET_SELF()->set_experience(pMsg->selfinfo().experience());
	HS_MUTABLE_TARGET_SELF()->set_level(pMsg->selfinfo().level());
	HS_MUTABLE_TARGET_SELF()->set_successionwincount(pMsg->selfinfo().successionwincount());
    HS_MUTABLE_TARGET_SELF()->set_wincount(pMsg->selfinfo().wincount());
    HS_MUTABLE_TARGET_SELF()->set_losecount(pMsg->selfinfo().lostcount());
    
	HS_MUTABLE_TARGET_TARGET()->set_level(pMsg->tageterinfo().level());
	HS_MUTABLE_TARGET_TARGET()->set_successionwincount(pMsg->tageterinfo().successionwincount());
    HS_MUTABLE_TARGET_TARGET()->set_wincount(pMsg->tageterinfo().wincount());
    HS_MUTABLE_TARGET_TARGET()->set_losecount(pMsg->tageterinfo().lostcount());
    
	HS_GAME_CACHE()->AddGold(pMsg->selfinfo().incomgolds());
    
	if(pMsg->result() == BattleResultResponse_PlayerMatchResult_WIN)
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
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
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
    
	CCNode* pOtherScreen = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
    
	HSPropIconInterface* pIcon = static_cast<HSPropIconInterface*>(pData);
	HSAssert(pIcon,"");
    
	std::string fileName = pIcon->GetBasePath() + pIcon->GetPropInfoData()->localname();
	CCSprite* pIconSprite = HSCCSprite::create(fileName.c_str());
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
	pNode->removeFromParent();
}

void HSBattleLayer::PlayUserPropEffect_OtherScreen(const PropInfo* propInfo)
{
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");
    
	CCPoint pos = CCPointZero;
	pos.x = pOtherScreen->getPosition().x + pOtherScreenFrame->getContentSize().width / 2.f;
	pos.y = pOtherScreen->getPosition().y - pOtherScreenFrame->getContentSize().height / 2.f;
    
	CCParticleSystemQuad* pSoul = CCParticleSystemQuad::create("Particle/SoulRed.plist");
	pSoul->setPosition(pos);
	this->addChild(pSoul,1000);
    
    string localName = propInfo->localname();
    int index = localName.find(".png");
    localName.insert(index, "_01");
    
	CCString* pIconFileName = CCString::createWithFormat("Image/%s",localName.c_str());
	pIconFileName->retain();
    
	CCMoveTo* pMoveTo = CCMoveTo::create(1.f,HSBase::GetTemplateScreenCentre());
	CCCallFuncND* pCall = CCCallFuncND::create(this,callfuncND_selector(HSBattleLayer::Call_PlayUserPropEffect_OtherScreen),(void*)pIconFileName);
	pSoul->runAction(CCSequence::create(pMoveTo,pCall,NULL));
}

void HSBattleLayer::Call_PlayUserPropEffect_OtherScreen(CCNode* pNode,void* pData)
{
	HSAssert(pData,"");
    
	CCNode* pOtherScreen = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
    
	CCString* pIconFileName = static_cast<CCString*>(pData);
	HSAssert(pIconFileName,"");
    
	
    
	CCSprite* pIconSprite = HSCCSprite::create(pIconFileName->getCString());
	pIconSprite->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pIconSprite,10000);
    
	CCActionInterval*  actionBy = CCScaleBy::create(0.5f, 2.0f, 2.0f);
	CCFadeTo* fadeTo = CCFadeTo::create(0.5f,0.f);
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayUserPropEffect_OtherScreen));
	CCSequence* pSequence = CCSequence::create(CCSpawn::create(actionBy,fadeTo,NULL),pCall,NULL);
	pIconSprite->runAction(pSequence);
	pNode->removeFromParent();
    
    CC_SAFE_RELEASE_NULL(pIconFileName);
}

void HSBattleLayer::Call_PlayUserPropEffect_OtherScreen(CCNode* pNode)
{
	pNode->removeFromParent();
}

HSBalloonFactory* HSBattleLayer::GetScreenAllBalloon()
{
	HSBalloonFactory* pFactory = new HSBalloonFactory;
    
	this->m_pWorld->QueryAABB(pFactory,m_workArea);
    
	return pFactory;
}

std::vector<HSBattleLayer::HSDropApply>* HSBattleLayer::GetPetrifactionBalloonNumList()
{
	return &m_PetrifactionBalloonNumList;
}

std::vector<HSBattleLayer::HSDropApply>* HSBattleLayer::GetDropPetrifactionList()
{
	return &m_dropPetrifactionList;
}

std::set<HSBalloonSprite*>* HSBattleLayer::GetDropBalloonList()
{
    return &m_dropBalloonList;
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

void HSBattleLayer::PlayRewardsEffect(int destroyCount)
{
    if(destroyCount < 5)
    {
        return;
    }
    // #122
    HSCCSprite* pRunSprite = NULL;
    
    CCScaleBy* action_00 = CCScaleBy::create(0.001f, 0.5f);
    CCScaleBy* action_01 = CCScaleBy::create(0.2f, 2.5f);
    CCDelayTime* action_02 = CCDelayTime::create(0.8f);
    CCFadeTo* action_03 = CCFadeTo::create(0.3f, 0);
    CCCallFuncN* action_04 = CCCallFuncN::create(this, callfuncN_selector(HSBattleLayer::Call_PlayRewardsEffect));
    
    CCSequence* action = CCSequence::create(action_00,action_01,action_02,action_03,action_04,NULL);
    
    CCPoint pos = HSBase::GetTemplateScreenCentre();
    pos.y += 150.f;
    if (destroyCount >= 5 && destroyCount <= 7)
    {
        // good
        pRunSprite = HSCCSprite::create("Image/Good.png");
        pRunSprite->setPosition(pos);
        this->addChild(pRunSprite,2000);
        
        
    }else if (destroyCount >= 8 && destroyCount <= 12){
        
        //cool
        pRunSprite = HSCCSprite::create("Image/Cool.png");
        pRunSprite->setPosition(pos);
        this->addChild(pRunSprite,2000);
    }else if (destroyCount >= 13){
        
        //Perfect
        pRunSprite = HSCCSprite::create("Image/Perfect.png");
        pRunSprite->setPosition(pos);
        this->addChild(pRunSprite,2000);
        
    }
    pRunSprite->runAction(action);
}

void HSBattleLayer::Call_PlayRewardsEffect(CCNode* pNode)
{
    pNode->removeFromParent();
}

void HSBattleLayer::PlayUserPropEffect_EnergyShield_OtherScreen( const PropInfo* propInfo )
{
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");
    
	CCPoint pos = CCPointZero;
	pos.x = pOtherScreen->getPosition().x + pOtherScreenFrame->getContentSize().width / 2.f;
	pos.y = pOtherScreen->getPosition().y - pOtherScreenFrame->getContentSize().height / 2.f;
    
    string localName = propInfo->localname();
    int index = localName.find(".png");
    localName.insert(index, "_01");
    
	CCString* pIconFileName = CCString::createWithFormat("Image/%s",localName.c_str());
	CCSprite* pIconSprite = HSCCSprite::create(pIconFileName->getCString());
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

void HSBattleLayer::PlayWillDieEffecr()
{
#define HS_PlayWillDieEffecr_TAG 0x9762
    if (m_pWillEffect && !m_pWillEffect->getActionByTag(HS_PlayWillDieEffecr_TAG))
    {
        CCFadeOut* pFadeOut = CCFadeOut::create(0.2f);
        CCFadeIn* pFadein = CCFadeIn::create(0.5f);
        
        CCSequence* pFadeOutAndIn = CCSequence::create(pFadeOut,pFadein,NULL);
        CCRepeatForever* pRepeat = CCRepeatForever::create(pFadeOutAndIn);
        pRepeat->setTag(HS_PlayWillDieEffecr_TAG);
        m_pWillEffect->runAction(pRepeat);
        m_pWillEffect->setVisible(true);
    }
}

void HSBattleLayer::CancelPlayWillDieEffecr()
{
    if (m_pWillEffect && m_pWillEffect->getActionByTag(HS_PlayWillDieEffecr_TAG))
    {
        m_pWillEffect->setVisible(false);
        m_pWillEffect->stopActionByTag(HS_PlayWillDieEffecr_TAG);
    }
}

void HSBattleLayer::PlayBeatEffect()
{
    CCSprite* pVat = HS_FIND_UI_PANEL_SPRITE("UI_Kongqiceng","Kongqiceng");
    CCPoint pos = pVat->getPosition();
    
    CCDelayTime* pDelayTime = CCDelayTime::create(1);
    CCMoveTo* R = CCMoveTo::create(0.025f,ccp( pos.x + 3,pos.y));
    CCMoveTo* L = CCMoveTo::create(0.025f,ccp(pos.x - 3,pos.y));
    CCMoveTo* U = CCMoveTo::create(0.025f,ccp(pos.x,pos.y + 3));
    CCMoveTo* D = CCMoveTo::create(0.025f,ccp(pos.x,pos.y - 3));
    CCMoveTo* restore = CCMoveTo::create(0.01,pos);
    
    CCRepeat* pRepeat = CCRepeat::create(CCSequence::create(R,L,U,D,NULL), 2);
    CCSequence* pSeq = CCSequence::create(pDelayTime,pRepeat,restore,NULL);
    pVat->runAction(pSeq);
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
        
        if(HS_GAME_CACHE()->m_FriendListResponse.friendlist_size() > 0)
        {
            int selfGameScore = HS_GAME_CACHE()->GetSelfGameScore();
            
            if (selfGameScore > HS_GAME_CACHE()->m_FriendListResponse.friendlist(0).gamescore()
                && HS_GAME_CACHE()->m_FriendListResponse.friendlist(0).game_uuid() != HS_TARGET_SELF().uid())
            {
                HSRankUpLayer* pRankUpLayer = HSRankUpLayer::create();
                battleScene->addChild(pRankUpLayer,layer->getZOrder());
            }
        }
	}
	else
	{
		layer->setVisible(true);
	}
    
    
	switch (HS_GAME_CACHE()->m_pBattleResult->result())
	{
        case BattleResultResponse_PlayerMatchResult_WIN:
		{
			//CCLog("set win");
			layer->SetIsWin(true);
		}
            break;
        case BattleResultResponse_PlayerMatchResult_LOST:
		{
            
			//CCLog("set lost");
			layer->SetIsWin(false);
		}
            break;
        case BattleResultResponse_PlayerMatchResult_DRAW:
		{
            //CCLog("set draw");
		}
            break;
	}
}

void HSBattleLayer::PlayGameWinEffect()
{
	m_isPauseGame = true;
    
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");
    
	//CCMoveBy* pMoveBy = CCMoveBy::create(0.5f,HSBase::GetTemplateScreenCentre());
	//CCLog("playGameWinEffect===============================================================");
	//HSJava::ShaderJava()->ShowToast("playGameWinEffect",1);
    
	//CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::Call_GameOver));
	//pOtherScreen->runAction(CCSequence::create(pMoveBy,pCall,NULL));
    
	CCCallFunc* pCall = CCCallFunc::create(this,callfunc_selector(HSBattleLayer::Call_GameOver));
	pOtherScreen->runAction(CCSequence::create(pCall,NULL));
    
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

void HSBattleLayer::PlayDestroyBalloon5Effect(const CCPoint& pos , int count)
{
	CCNode* pOtherScreen = HS_FIND_UI_PANEL("UI_Duifangduizhanchuangkou");
	CCNode* pOtherScreenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Duifangduizhanchuangkou","duifangduizhanchuangkou");
	HSAssert(pOtherScreen,"");
	HSAssert(pOtherScreenFrame,"");
    
    CCPoint targetPos = CCPointZero;
    targetPos.x = pOtherScreen->getPosition().x + pOtherScreenFrame->getContentSize().width / 2.f;
    targetPos.y = pOtherScreen->getPosition().y - pOtherScreenFrame->getContentSize().height / 2.f;
    
    for (int i=0; i<count; ++i)
    {
        ccBezierConfig c;
        c.controlPoint_1 = pos;
        c.controlPoint_2 = ccp(HSMath::Random(50,551),HSMath::Random(308,710));
        c.endPosition = targetPos;
        
        
        CCParticleSystemQuad* pSoul = CCParticleSystemQuad::create("Particle/SoulRed.plist");
        pSoul->setPosition(pos);
        this->addChild(pSoul,1060);
        
        //CCMoveTo* pMoveTo = CCMoveTo::create(1.f,targetPos);
        //CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayDestroyBalloon5Effect));
        //pSoul->runAction(CCSequence::create(pMoveTo,pCall,NULL));
        
        // #119
        CCBezierTo* pBezierTo = CCBezierTo::create(HSMath::Random(0.5f, 1.f),c);
        CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSBattleLayer::Call_PlayDestroyBalloon5Effect));
        pSoul->runAction(CCSequence::create(pBezierTo,pCall,NULL));
    }
    
}

void HSBattleLayer::Call_PlayDestroyBalloon5Effect( CCNode* pNode )
{
    // #153
    if(m_pBombSpx)
    {
        m_pBombSpx->setVisible(true);
        m_pBombSpx->SetAction(0, 1, this, callfuncND_selector(HSBattleLayer::Call_PlayDestroyBalloon5Effect_Bomb), NULL);
        m_pBombSpx->setPosition(pNode->getPosition());
        m_pBombSpx->setZOrder(1060);
    }
    
    // #117
    CCString* pSoundFileName = CCString::createWithFormat("stonehit0%d",HSMath::Random(1, 2));
    HS_Play_Sound(pSoundFileName->getCString());
    CC_SAFE_RELEASE_NULL(pSoundFileName);
    
    pNode->removeFromParent();
}

void HSBattleLayer::Call_PlayDestroyBalloon5Effect_Bomb(CCNode* pNode,void* pData)
{
    pNode->setVisible(false);
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

void HSBattleLayer::keyBackClicked()
{
    
}

void HSBattleLayer::keyMenuClicked()
{
	HSRequest::ShareRequest()->SendBattleResultRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str(),BattleResultRequest_GameStatus_OVER);
}

map<int,HSBalloonSprite*>* HSBattleLayer::GetBalloonMap()
{
	return &m_balloonMap;
}


void HSBattleLayer::SendBattleData(void* pData)
{
    CCLog(__FUNCTION__);
    BattleDataRequest* pBattleData = (BattleDataRequest*)pData;
    if (HS_IsLanMode())
    {
        LanBattleDataNotice lanBattleDataNotice = LanBattleDataNotice::default_instance();
        lanBattleDataNotice.set_uuid(HS_GAME_CACHE_DATA_LAN().uuid());
        lanBattleDataNotice.mutable_battleinfo()->CopyFrom(pBattleData->battleinfo());
        
        HSLanRequest::ShareLanRequest()->SendLanBattleDataNotice(&lanBattleDataNotice);
        
    }else{
        HSRequest::ShareRequest()->SendBattleRequest(pBattleData);
    }
}

void HSBattleLayer::SendDestroyBalloon(void* pData)
{
    CCLog(__FUNCTION__);
    if (HS_IsLanMode())
    {
        /**
         * 局域网不需要发送消球信息
         */
    }else{
        DestroyBalloonRequest* destroyBalloonRequest = (DestroyBalloonRequest*)pData;
        HSRequest::ShareRequest()->SendDestroyBalloonRequest(*destroyBalloonRequest);
    }
}

void HSBattleLayer::SendBattleResultRequest()
{
    CCLog(__FUNCTION__);
    if (HS_IsLanMode())
    {
        HS_GAME_CACHE()->m_pBattleResult->set_result(BattleResultResponse_PlayerMatchResult_LOST);
        
        int winCount = HS_MUTABLE_GAME_CACHE_DATA_LAN()->wincount();
        int loseCount = HS_MUTABLE_GAME_CACHE_DATA_LAN()->losecount() + 1;
        float winRate = (float)winCount / (float)(winCount + loseCount);
        HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_losecount(loseCount);
        HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_winrate(winRate);
        
        //更新Lan 目标信息
        int targetWinCount = HS_GAME_CACHE()->m_LanTargetInfo.userinfo().wincount() + 1;
        int targetLoseCount = HS_GAME_CACHE()->m_LanTargetInfo.userinfo().losecount();
        float targetWubRate = (float)targetWinCount / (float)(targetWinCount + targetLoseCount);
        HS_GAME_CACHE()->m_LanTargetInfo.mutable_userinfo()->set_wincount(targetWinCount);
        HS_GAME_CACHE()->m_LanTargetInfo.mutable_userinfo()->set_losecount(targetLoseCount);
        HS_GAME_CACHE()->m_LanTargetInfo.mutable_userinfo()->set_winrate(targetWubRate);
        
        HSLanRequest::ShareLanRequest()->SendLanBattleResultNotice(LanBattleResultNotice_GameStatus_OVER, HS_GAME_CACHE_DATA_LAN());
        
    }else{
        HSRequest::ShareRequest()->SendBattleResultRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str(),BattleResultRequest_GameStatus_OVER);
    }
}

void HSBattleLayer::ResLanBattleResultNotice(LanBattleResultNotice* pMsg)
{
    if (m_pBattleTranscribe)
    {
        m_pBattleTranscribe->Save();
    }
    CCLog(__FUNCTION__);
    HS_GAME_CACHE()->m_LanTargetInfo.set_uuid(pMsg->uuid());
    HS_GAME_CACHE()->m_LanTargetInfo.mutable_userinfo()->CopyFrom(pMsg->userinfo());
    
    //更新Lan 目标信息
    int targetWinCount = HS_GAME_CACHE()->m_LanTargetInfo.userinfo().wincount() + 1;
    int targetLoseCount = HS_GAME_CACHE()->m_LanTargetInfo.userinfo().losecount();
    float targetWubRate = (float)targetWinCount / (float)(targetWinCount + targetLoseCount);
    HS_GAME_CACHE()->m_LanTargetInfo.mutable_userinfo()->set_wincount(targetWinCount);
    HS_GAME_CACHE()->m_LanTargetInfo.mutable_userinfo()->set_losecount(targetLoseCount);
    HS_GAME_CACHE()->m_LanTargetInfo.mutable_userinfo()->set_winrate(targetWubRate);
    
    HS_GAME_CACHE()->m_pBattleResult->set_result(BattleResultResponse_PlayerMatchResult_WIN);
    
    this->PlayGameWinEffect();
}

void HSBattleLayer::SetPropWave(HSPropFastTrackInterface* wave)
{
    m_pPropWave = wave;
    if(m_pPropWave != NULL)
    {
        this->addChild(m_pPropWave,3000);
    }
}

HSProp_Wave* HSBattleLayer::GetPropWave()
{
    return (HSProp_Wave*)m_pPropWave;
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
