#include "HSUsePropInterface.h"

HSUsePropInterface::HSUsePropInterface(void)
{
	m_isListerFristUpdata = true;
	m_propInfo = NULL;
	m_spxUseProp = NULL;
	m_CD_Progress = NULL;
	this->schedule(schedule_selector(HSUsePropInterface::Updata));
	m_propIndex = 0;
}


HSUsePropInterface::~HSUsePropInterface(void)
{
	m_propInfo = NULL;
	m_propIndex = 0;
}

bool HSUsePropInterface::Init( const message::PropInfo* propInfo )
{
	HSAssert(propInfo,"");

	m_propInfo = propInfo;
	m_propIndex = propInfo->id()-HS_MANUAL_PROP_BASE_ID;
	const char* key = CCString::createWithFormat("UI_DaoJuZu_DaoJu_%d",propInfo->pos())->getCString();
	HSCCSprite* frame = HS_FIND_UI_PANEL_SPRITE(key,"k_DaoJu");
	CCSize frameNode = frame->getContentSize();

	const char* fileName = CCString::createWithFormat("Image/BuyProp/ManualProp/%d.png",propInfo->id())->getCString();

	//m_propSprite = CCSprite::create(fileName);
	bool isOK = this->initWithFile(fileName);
	CCPoint propSpritePoint = CCPointZero;
	propSpritePoint.x = frame->getContentSize().width / 2.f;
	propSpritePoint.y = frame->getContentSize().height / 2.f;
	this->setPosition(propSpritePoint);
	this->setScale(0.6f);
	frame->addChild(this);


	if (m_spxUseProp == NULL)
	{
		m_spxUseProp = SPX_Manager::CreateSprite("SPX/daojushiyong.sprite");
		m_spxUseProp->setVisible(false);
		m_spxUseProp->setPosition(HS_SizeHalf_Point(this->getContentSize()));
		m_spxUseProp->SetAction(0,1);
		this->addChild(m_spxUseProp);
	}

	HSCCSprite* CDSprite = HSCCSprite::create("Image/propCD.png");
	
	m_CD_Progress = CCProgressTimer::create(CDSprite);
	
	m_CD_Progress->setType(kCCProgressTimerTypeRadial);

	m_CD_Progress->setPosition(this->getPosition());
	
	
	
	m_CD_Progress->setReverseDirection(true);

	m_CD_Progress->setTag(0);

	frame->addChild(m_CD_Progress);

	return isOK;
}

void HSUsePropInterface::Call_ProgressEnd()
{
	m_CD_Progress->setTag(0);
}

bool HSUsePropInterface::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
// 	if ( !ContainsTouchLocation(pTouch) ) return false; 
// 
// 	this->setScale(0.7f);

	return false;
}

void HSUsePropInterface::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
// 	if ( !ContainsTouchLocation(pTouch) ) return;
// 	this->setScale(0.6f);
}

void HSUsePropInterface::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
// 	if ( !ContainsTouchLocation(pTouch) ) return;
// 
// 	this->setScale(0.6f);
}

void HSUsePropInterface::onEnter()
{
	CCNode::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void HSUsePropInterface::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

message::PropInfo_PropType HSUsePropInterface::GetPropType()
{
	HSAssert(m_propInfo,"");
	return m_propInfo->proptype();
}

bool HSUsePropInterface::ContainsTouchLocation( CCTouch* touch )
{
	CCSize s = this->getContentSize();
	CCRect r = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	return r.containsPoint(convertTouchToNodeSpaceAR(touch));
}

void HSUsePropInterface::Call_Effect(CCNode* pSpx,void* pData)
{
		int level = HS_GAME_CACHE()->GetPropLevel(m_propIndex);
		float time = 70.f;
		int i = 1;

		while ( i < level)
		{
			time = time/1.4f;
			i+=1;
		}

		CCProgressFromTo* pProgressFromTo = CCProgressFromTo::create(time,100.f,0.f);
		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSUsePropInterface::Call_ProgressEnd));
		m_CD_Progress->runAction(CCSequence::create(pProgressFromTo,pCallFunc,NULL));
		m_CD_Progress->setTag(1);
}

bool HSUsePropInterface::TouchBalloonBegin()
{
	if(m_CD_Progress->getTag()==0)//0ÊÇÃ»ÓÐCD
	{
		HSSoundManage::ShareSoundManage()->PlayerEffect("botton");

		this->setScale(0.7f);

		m_spxUseProp->setVisible(true);

		m_spxUseProp->SetAction(0,1,this,callfuncND_selector(HSUsePropInterface::Call_Effect),NULL);

		return true;
	}
	return false;
}

void HSUsePropInterface::TouchBalloonEnd()
{
	this->setScale(0.6f);
}

void HSUsePropInterface::AddNodeToParent()
 {

 }

void HSUsePropInterface::Updata( float dt )
{
	if(this->m_isListerFristUpdata)
	{
		this->AddNodeToParent();

		m_isListerFristUpdata = false;
	}


	/**
	curCDTime+=dt;

	float progress = curCDTime /45.f * 100.f;

	 progress = progress>100.f?100:progress;

	 CCLog("progress=%.f",progress);

	if(m_CD_Progress)
	{
		m_CD_Progress->setPercentage(progress);
	}*/
}
