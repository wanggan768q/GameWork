#include "HSGameMainScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGamePairScene.h"
#include "HSDailyRewardSystemLayer.h"

float HSGameMainLayer::m_maxcatblack1 = 5.5f;
float HSGameMainLayer::m_maxcatblack2 = 7.f;

float HSGameMainLayer::m_downMinCount = 2.5f;
float HSGameMainLayer::m_downMaxCount = 4.f;

float HSGameMainLayer::m_cat1MinX = -100.f;  //120.f;
float HSGameMainLayer::m_cat1MaxX = 100.f;//260.f;

float HSGameMainLayer::m_cat2MinX = -100.f;//380.f;
float HSGameMainLayer::m_cat2MaxX = 100.f;//520.f;

HSGameMainLayer::HSGameMainLayer(void)
{
	m_p_main_cloud1 = NULL;
	m_p_main_cloud1s = NULL;
 

	m_p_main_cloud2 = NULL;
	m_p_main_cloud2s = NULL;

	m_p_main_cloud3 = NULL;
	m_p_main_cloud3s = NULL;
 

	m_p_main_cloud4 = NULL;
	m_p_main_cloud4s = NULL;
 

	m_p_main_cloud5 = NULL;
	m_p_main_cloud5s = NULL;
 

	m_p_main_catblack1 = NULL;
	m_p_main_catblack2 = NULL;

	m_p_main_title = NULL;

	m_catblack1count =0;
	m_catblack2count =0;

	
}

HSGameMainLayer::~HSGameMainLayer(void)
{
	m_p_main_cloud1 = NULL;
	m_p_main_cloud1s = NULL;


	m_p_main_cloud2 = NULL;
	m_p_main_cloud2s = NULL;

	m_p_main_cloud3 = NULL;
	m_p_main_cloud3s = NULL;


	m_p_main_cloud4 = NULL;
	m_p_main_cloud4s = NULL;


	m_p_main_cloud5 = NULL;
	m_p_main_cloud5s = NULL;


	m_p_main_catblack1 = NULL;
	m_p_main_catblack2 = NULL;

	m_p_main_title = NULL;
}

bool HSGameMainLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	HSTool::SetLayerScale(this);
	this->Load();
	this->setTouchEnabled(true);

	return true;
}

void HSGameMainLayer::Load()
{
	HS_GAME_CACHE();

	HSReadUI::ShareReadUI()->ReadUI("Image/cover/cover.data","Image/cover/",this);

	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSGameMainLayer::CallCat));
	 
	this->runAction(CCSequence::create(CCDelayTime::create(1.5f),func,NULL));

	m_p_main_catblack1 = HS_FIND_UI_PANEL_SPRITE("UI_main_catblack1","main_catblack1");
	m_p_main_catblack1->getParent()->setPosition(ccpAdd(m_p_main_catblack1->getParent()->getPosition(),ccp(0.f,HSToolBase::GetOffsetY())));
	m_main_catblack1Position = m_p_main_catblack1->getPosition();
	m_p_main_catblack2 = HS_FIND_UI_PANEL_SPRITE("UI_main_catblack2","main_catblack2");
	m_p_main_catblack2->getParent()->setPosition(ccpAdd(m_p_main_catblack2->getParent()->getPosition(),ccp(0.f,HSToolBase::GetOffsetY())));
	m_main_catblack2Position = m_p_main_catblack2->getPosition();

	m_p_main_title = HS_FIND_UI_PANEL_SPRITE("UI_main_title","main_title");
	m_p_main_title_position = m_p_main_title->getPosition();
	m_p_main_title->setPosition(ccp(m_p_main_title_position.x,m_p_main_title_position.y+600.f));


	m_p_main_cat1 = HS_FIND_UI_PANEL_SPRITE("UI_main_cat1","main_cat1");
	m_p_main_cat1_position = m_p_main_cat1->getPosition();
	m_p_main_cat1->setPosition(ccp(m_p_main_cat1_position.x-m_p_main_cat1->getContentSize().width,m_p_main_cat1_position.y-300.f));

	m_p_main_cat2 = HS_FIND_UI_PANEL_SPRITE("UI_main_cat2","main_cat2");
	m_p_main_cat2_position =  m_p_main_cat2->getPosition();
	m_p_main_cat2->setPosition(ccp(m_p_main_cat2_position.x + m_p_main_cat2->getContentSize().width,m_p_main_cat2_position.y-300.f));

	
	CCNode* pcloud1Frame = HS_FIND_UI_PANEL("UI_main_cloud1");
	m_p_main_cloud1 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud1","main_cloud1");
	pcloud1Frame->setPositionY(pcloud1Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud1Position = m_p_main_cloud1->getPosition();

	m_p_main_cloud1s = CCSprite::createWithTexture(m_p_main_cloud1->getTexture());
	m_p_main_cloud1s->setPosition(ccp(m_cloud1Position.x+HSBase::GetTemplateScreenW(),m_cloud1Position.y));
	pcloud1Frame->addChild(m_p_main_cloud1s);

	m_p_main_cloud1->setTag(10);
	m_p_main_cloud1s->setTag(11);

	CallCloudFinish(m_p_main_cloud1);
	CallCloudFinish(m_p_main_cloud1s);

	CCNode* pcloud2Frame = HS_FIND_UI_PANEL("UI_main_cloud2");
	m_p_main_cloud2 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud2","main_cloud2");
	pcloud2Frame->setPositionY(pcloud2Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud2Postion = m_p_main_cloud2->getPosition();

	m_p_main_cloud2s = CCSprite::createWithTexture(m_p_main_cloud2->getTexture());
	m_p_main_cloud2s->setPosition(ccp(m_cloud2Postion.x+HSBase::GetTemplateScreenW(),m_cloud2Postion.y));
	pcloud2Frame->addChild(m_p_main_cloud2s);

	m_p_main_cloud2->setTag(20);
	m_p_main_cloud2s->setTag(21);

	CallCloudFinish(m_p_main_cloud2);
	CallCloudFinish(m_p_main_cloud2s);


	CCNode* pcloud3Frame = HS_FIND_UI_PANEL("UI_main_cloud3");
	m_p_main_cloud3 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud3","main_cloud3");
	pcloud3Frame->setPositionY(pcloud3Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud3Postion = m_p_main_cloud3->getPosition();

	m_p_main_cloud3s = CCSprite::createWithTexture(m_p_main_cloud3->getTexture());
	m_p_main_cloud3s->setPosition(ccp(m_cloud3Postion.x+HSBase::GetTemplateScreenW(),m_cloud3Postion.y));
	pcloud3Frame->addChild(m_p_main_cloud3s);

	m_p_main_cloud3->setTag(30);
	m_p_main_cloud3s->setTag(31);
	CallCloudFinish(m_p_main_cloud3);
	CallCloudFinish(m_p_main_cloud3s);


	CCNode* pcloud4Frame = HS_FIND_UI_PANEL("UI_main_cloud4");
	m_p_main_cloud4 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud4","main_cloud4");
	pcloud4Frame->setPositionY(pcloud4Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud4Postion = m_p_main_cloud4->getPosition();

	m_p_main_cloud4s = CCSprite::createWithTexture(m_p_main_cloud4->getTexture());
	m_p_main_cloud4s->setPosition(ccp(m_cloud4Postion.x+HSBase::GetTemplateScreenW(),m_cloud4Postion.y));
	pcloud4Frame->addChild(m_p_main_cloud4s);

	m_p_main_cloud4->setTag(40);
	m_p_main_cloud4s->setTag(41);
	CallCloudFinish(m_p_main_cloud4);
	CallCloudFinish(m_p_main_cloud4s);


	CCNode* pcloud5Frame = HS_FIND_UI_PANEL("UI_main_cloud5");
	m_p_main_cloud5 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud5","main_cloud5");
	pcloud5Frame->setPositionY(pcloud5Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud5Postion = m_p_main_cloud5->getPosition();

	m_p_main_cloud5s = CCSprite::createWithTexture(m_p_main_cloud5->getTexture());
	m_p_main_cloud5s->setPosition(ccp(m_cloud5Postion.x+HSBase::GetTemplateScreenW(),m_cloud5Postion.y));
	pcloud5Frame->addChild(m_p_main_cloud5s);

	m_p_main_cloud5->setTag(50);
	m_p_main_cloud5s->setTag(51);
	CallCloudFinish(m_p_main_cloud5);
	CallCloudFinish(m_p_main_cloud5s);

	HS_Play_Music("back_01");

	this->schedule(schedule_selector(HSGameMainLayer::Update));
}

void HSGameMainLayer::CallCatDownShake()
{
	//CCPoint postion = m_p_main_backGround->getPosition();
	
	CCActionInterval* move1 = CCMoveBy::create(0.05f,ccp(0.f,-2.f));
	CCActionInterval* move2 = CCMoveBy::create(0.1f,ccp(0.f,-2.f));
	CCActionInterval* move3 = CCMoveBy::create(0.1f,ccp(0.f,6.f));
	CCActionInterval* move4 = CCMoveBy::create(0.2f,ccp(0.f,-2.f));

	CCSequence* actionMove = CCSequence::create(move1,move2,move3,move4,NULL);

	CCScaleBy* scale1 = CCScaleBy::create(0.15f,1.f);
	CCScaleBy* scale2 = CCScaleBy::create(0.2f,1.02f);
	CCScaleBy* scale3 = CCScaleBy::create(0.1f,0.98f);

	CCSequence* actionScale = CCSequence::create(scale1,scale2,scale3,NULL);

	CCSpawn* spawn = CCSpawn::create(actionMove,actionScale,NULL);


	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSGameMainScene* mainScene =dynamic_cast<HSGameMainScene*>(scene);

	if(mainScene)
	{
		mainScene->GetBackGroundLayer()->runAction(spawn);
	}

	//m_p_main_backGround->runAction(spawn);
}

void HSGameMainLayer::CallCat()
{
	CCActionInterval* action1 = CCMoveTo::create(0.5f,m_p_main_cat1_position);
	m_p_main_cat1->runAction(action1);

	CCActionInterval* action2 = CCMoveTo::create(0.5f,m_p_main_cat2_position);
	CCCallFunc* callshake = CCCallFunc::create(this,callfunc_selector(HSGameMainLayer::CallCatFinish));
	m_p_main_cat2->runAction(CCSequence::create(action2,callshake,NULL));
}

void HSGameMainLayer::CallCatFinish()
{
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSGameMainLayer::CallTitleDown));
	 
	this->runAction(CCSequence::create(CCDelayTime::create(0.5f),func,NULL));

	HS_Play_Sound("hit_effect");

	CallShake();
}

void HSGameMainLayer::CallShake()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSGameMainScene* pairScene = (HSGameMainScene*)scene;

	CCPoint position =pairScene->getPosition();

	CCMoveBy* left1 = CCMoveBy::create(0.05f,ccp(5.f,0.f));
	CCMoveBy* right1 = CCMoveBy::create(0.05f,ccp(-5.f,0.f));
	CCMoveBy* top1 = CCMoveBy::create(0.05f,ccp(0.f,5.f));
	CCMoveBy* rom1 = CCMoveBy::create(0.05f,ccp(0.f,-5.f));

	CCMoveBy* left2 = CCMoveBy::create(0.05f,ccp(5.f,0.f));
	CCMoveBy* right2 = CCMoveBy::create(0.05f,ccp(-5.f,0.f));
	CCMoveBy* top2 = CCMoveBy::create(0.05f,ccp(0.f,5.f));
	CCMoveBy* rom2 = CCMoveBy::create(0.05f,ccp(0.f,-5.f));

	CCFiniteTimeAction* action3 = CCSequence::create(left1,right1,top1,rom1,left2,right2,top2,rom2,NULL);
	pairScene->runAction(action3);
}

void HSGameMainLayer::CallTitleDown()
{
	CCActionInterval* down = CCMoveTo::create(0.5f,m_p_main_title_position);

	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSGameMainLayer::CallTitleDownFinish));

	m_p_main_title->runAction(CCSequence::create(down,func,NULL));
}

void HSGameMainLayer::CallTitleDownFinish()
{
	HS_Play_Sound("hit_effect");
	CallShake();
}

void HSGameMainLayer::CallCloudFinish(CCNode* node)
{
	CCSprite* pSprite = NULL;
	float time = 0;
	if(node->getTag()==10)
	{
		pSprite= m_p_main_cloud1;
		pSprite->setPositionX(m_cloud1Position.x);
		time=8.f;
	}
	else if(node->getTag()==11)
	{
		pSprite= m_p_main_cloud1s;
		pSprite->setPositionX(m_cloud1Position.x+HSBase::GetTemplateScreenW());
		time=8.f;
	}
	if(node->getTag()==20)
	{
		pSprite = m_p_main_cloud2;
		pSprite->setPositionX(m_cloud2Postion.x);
		time = 10.f;
	}
	else if(node->getTag()==21)
	{
		pSprite = m_p_main_cloud2s;
		pSprite->setPositionX(m_cloud2Postion.x+HSBase::GetTemplateScreenW());
		time = 10.f;
	}
	else if(node->getTag()==30)
	{
		pSprite = m_p_main_cloud3;
		pSprite->setPositionX(m_cloud3Postion.x);
		time = 12.f;
	}
	else if(node->getTag()== 31)
	{
		pSprite = m_p_main_cloud3s;
		pSprite->setPositionX(m_cloud3Postion.x+HSBase::GetTemplateScreenW());
		time = 12.f;
	}
	else if(node->getTag() == 40)
	{
		pSprite = m_p_main_cloud4;
		pSprite->setPositionX(m_cloud4Postion.x);
		time = 15.f;
	}
	else if(node->getTag() == 41)
	{
		pSprite = m_p_main_cloud4s;
		pSprite->setPositionX(m_cloud4Postion.x+HSBase::GetTemplateScreenW());
		time= 15.f;
	}
	else if(node->getTag() == 50)
	{
		pSprite = m_p_main_cloud5;
		pSprite->setPositionX(m_cloud5Postion.x);
		time = 20.f;
	}
	else if(node->getTag()== 51)
	{
		pSprite = m_p_main_cloud5s;
		pSprite->setPositionX(m_cloud5Postion.x+HSBase::GetTemplateScreenW());
		time = 20.f;
	}

	CCActionInterval* action = CCMoveBy::create(time,ccp(-HSBase::GetTemplateScreenW(),0.f));
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSGameMainLayer::CallCloudFinish));
	pSprite->runAction(CCSequence::create(action,pCall,NULL));
}

void HSGameMainLayer::Update(float dt)
{
	m_catblack1count+= dt;
	m_catblack2count+=dt;

	if(m_catblack1count>m_maxcatblack1)
	{
		m_catblack1count = 0;
		float x = HSMath::Random(m_cat1MinX,m_cat1MaxX);
		m_p_main_catblack1->setPosition(ccp(x,m_main_catblack1Position.y));

		float downCount = HSMath::Random(m_downMinCount,m_downMaxCount);
		
		CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSGameMainLayer::CallCatDownShake));
		CCMoveBy* move = CCMoveBy::create(downCount,ccp(0.f,-HSBase::GetTemplateScreenH()*1.7f));
		CCSequence* action = CCSequence::create(move,func,NULL);
		m_p_main_catblack1->runAction(action);
		m_p_main_catblack1->setRotation(HSMath::Random(0.f,270.f));
		m_p_main_catblack1->runAction(CCRepeatForever::create(CCRotateBy::create(0.1f,20.f)));
	}

	if(m_catblack2count>m_maxcatblack2)
	{
		m_catblack2count = 0;
		float x = HSMath::Random(m_cat2MinX,m_cat2MaxX);
		m_p_main_catblack2->setPosition(ccp(x,m_main_catblack2Position.y));
		//m_p_main_catblack2->setPosition(m_main_catblack2Position);
		float downCount = HSMath::Random(m_downMinCount,m_downMaxCount);
		CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSGameMainLayer::CallCatDownShake));
		CCMoveBy* move = CCMoveBy::create(downCount,ccp(0.f,-HSBase::GetTemplateScreenH()*1.7f));
		CCSequence* action = CCSequence::create(move,func,NULL);
		m_p_main_catblack2->runAction(action);
		m_p_main_catblack2->setRotation(HSMath::Random(0.f,270.f));
		m_p_main_catblack2->runAction(CCRepeatForever::create(CCRotateBy::create(0.1f,20.f)));
	}
}

void HSGameMainLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSGameMainLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameMainLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameMainLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	HS_GO_SCENE(HS_SCENE_CoverScene);
}

void HSGameMainLayer::keyBackClicked()
{

}

void HSGameMainLayer::keyMenuClicked()
{

}























HSGameMainScene::HSGameMainScene(void)
{
	this->hsGameMainLayer = NULL;
}

HSGameMainScene::~HSGameMainScene(void)
{
}

bool HSGameMainScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->backGroundLayer = CCLayer::create();
	
	this->addChild(backGroundLayer,HS_BASE_TAG,HS_BASE_TAG);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	

	CCPoint center = ccp(size.width/2, size.height/2);
	CCSprite* pb = CCSprite::create("Image/cover/main_backGround.png");
	
	

	pb->setPosition(center);

	HSToolBase::SetNodeFilldScreen(pb);
	
	backGroundLayer->addChild(pb, 0);
	 

	this->hsGameMainLayer = HSGameMainLayer::create();
	this->addChild(this->hsGameMainLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}

