#include "HSGameGuide.h"
#include "HSGameCache.h"
#include "HSBattleScene.h"

static HSGameGuide* s_hsGameGuide = NULL;

HSGameGuide::HSGameGuide(void)
{
	m_iStepIndex = 0;
	m_pClippingNode = NULL;
	m_pGameGuideData = NULL;
	m_pMaskLayer = NULL;
	m_pMode = NULL;
	m_pShape = NULL;
	m_pCurrentGuide = NULL;
	m_pDescribeInfo = NULL;
	m_iMaxStep = 0;
}


HSGameGuide::~HSGameGuide(void)
{
}

HSGameGuide* HSGameGuide::ShaderGameGuide()
{
	if (!s_hsGameGuide)
	{
		s_hsGameGuide = HSGameGuide::create();
	}

	return s_hsGameGuide;
}

bool HSGameGuide::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->Load();
	this->setTouchEnabled(true);

	return true;
}

void HSGameGuide::Load()
{
	this->Read("Data/GameGuideData.data");

	///创建cliper
	m_pClippingNode = CCClippingNode::create();
	m_pClippingNode->setInverted(true);
	
	this->addChild(m_pClippingNode);

	HSTool::SetLayerScale(m_pClippingNode);

	//添加底板
	/**
	m_pMaskLayer = CCLayerColor::create(ccc4(0,0,0,153),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	m_pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pClippingNode->addChild(m_pMaskLayer);*/

	m_pDescribeBigFrame = CCSprite::create("Image/ShuoMingXian.png");
	m_pDescribeBigFrame->setVisible(false);
	m_pDescribeFrame = CCSprite::create("Image/STouMingKuang.png");
	m_pDescribeFrame->setPosition(HS_SizeHalf_Point(m_pDescribeBigFrame->getContentSize()));
	m_pDescribeBigFrame->addChild(m_pDescribeFrame);
	m_pClippingNode->addChild(m_pDescribeBigFrame);


	m_pShape = CCDrawNode::create();

	//设这模板
	m_pClippingNode->setStencil(m_pShape);

	
	//CCSprite* pTest = CCSprite::create("Image/test.png");

	//this->addChild(pTest);

	this->schedule(schedule_selector(HSGameGuide::Update));
}

bool HSGameGuide::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!this->isVisible())
	{
		return false;
	}
	CCPoint touchPoint = pTouch->getLocation();

	std::vector<HSListerEvent>::iterator it = m_vListerEvent.begin();
	for (;it!=m_vListerEvent.end();++it)
	{
		HSListerEvent* pListerEvent = &(*it);
		CCRect r = pListerEvent->rect;
#if WIN32
		CCLog("---------------------------------");
		CCLog("%.2f  %.2f",touchPoint.x,touchPoint.y);
		CCLog("%.2f  %.2f  %.2f  %.2f",r.origin.x,r.origin.y,r.size.width,r.size.height);
#endif
		
		if (pListerEvent->rect.containsPoint(touchPoint))
		{
			pListerEvent->isTouch = true;
			if (pListerEvent->rect.size.equals(HSBase::GetTemplateScreenSize()))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

void HSGameGuide::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameGuide::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLog("End");
}

void HSGameGuide::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
	CCLayer::registerWithTouchDispatcher();
}

bool HSGameGuide::Read(const char* fileName)
{
	std::string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	HSFileData fileData(fullFilePath.c_str(),"rb");

	if (!m_pGameGuideData)
	{
		m_pGameGuideData = GameGuide::default_instance().New();
	}
	m_pGameGuideData->Clear();

	bool isOK = m_pGameGuideData->ParseFromArray(fileData.GetBuffer() + 2,fileData.GetSize() - 2);
	if (isOK)
	{
		m_iMaxStep = m_pGameGuideData->guidelist_size();

		CCLog("Read game guide success");
		return true;
	}
	return false;
}

void HSGameGuide::Run( int index )
{
	 
	if (index >= m_iMaxStep)
	{
		CCLog("New guidance has been completed");
		return;
	}

	m_iStepIndex = index;

	m_pCurrentGuide = &m_pGameGuideData->guidelist(index);

	m_vListerEvent.clear();

	this->ClearScreen();

	switch (m_pCurrentGuide->modetype())
	{
	case GameGuide_Guide_ModeType_ModeType_Round:
		{
			int posCount = m_pCurrentGuide->pointlist_size();
			int diameterCount = m_pCurrentGuide->diameter_size();
			if(posCount != diameterCount)
			{
				CCString* pErrorInfo = CCString::createWithFormat("ID: %d [ Location number and radius number is inconsistent ]");
				HSMessageBox(pErrorInfo->getCString());
				pErrorInfo->release();
				return;
			}

			for (int i=0;i<posCount;++i)
			{
				this->DrawRound(m_pCurrentGuide->diameter(i),m_pCurrentGuide->pointlist(i));
			}
		}
		break;
	case  GameGuide_Guide_ModeType_ModeType_Rect:
		{
			int posCount = m_pCurrentGuide->pointlist_size();
			int rectCount = m_pCurrentGuide->rect_size();
			if(posCount != rectCount)
			{
				CCString* pErrorInfo = CCString::createWithFormat("ID: %d [ Location number and rect number is inconsistent ]");
				HSMessageBox(pErrorInfo->getCString());
				pErrorInfo->release();
				return;
			}

			for (int i=0;i<posCount;++i)
			{
				this->DrawRect(m_pCurrentGuide->rect(i),m_pCurrentGuide->pointlist(i));
			}
		}
		break;
	default:
		{

		}
		break;
	}

	if (m_pCurrentGuide->describe() != "")
	{
		CCSize pngSize = m_pDescribeFrame->getContentSize();
		if (!m_pDescribeInfo)
		{
			m_pDescribeInfo = CCLabelTTF::create("","华康海报体W12(P)",25.f,pngSize,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
			m_pDescribeFrame->addChild(m_pDescribeInfo);

		}
		m_pDescribeInfo->setString(m_pCurrentGuide->describe().c_str());
		CCSize infoSize = m_pDescribeInfo->getContentSize();
		CCPoint infoPos;
		infoPos.x = pngSize.width / 2.f + 25.f;
		infoPos.y = pngSize.height / 2.f;
		m_pDescribeInfo->setPosition(infoPos);
		m_pDescribeBigFrame->setVisible(true);

		CCPoint describeBigFramePos = CCPointZero;
		describeBigFramePos.x = m_pCurrentGuide->describepos().x();
		describeBigFramePos.y = m_pCurrentGuide->describepos().y();
		m_pDescribeBigFrame->setPosition(describeBigFramePos);
	}else{
		if (m_pDescribeInfo)
		{
			m_pDescribeBigFrame->setVisible(false);
		}
	}
}

void HSGameGuide::Run()
{
	this->Run(0);
}

void HSGameGuide::DrawRect( const GameGuide_Guide_Rect& rect , const GameGuide_Guide_Point& point )
{
	HSAssert(m_pShape,"");

	CCRect ccRect(rect.x(),rect.y(),rect.w(),rect.h());
	CCPoint pos = ccp(point.x(),point.y());


	CCPoint vertRect[4] = {CCPointZero};
	vertRect[0] = ccp(ccRect.getMinX(),ccRect.getMaxY());
	vertRect[1] = ccp(ccRect.getMaxX(),ccRect.getMaxY());
	vertRect[2] = ccp(ccRect.getMaxX(),ccRect.getMinY());
	vertRect[3] = ccp(ccRect.getMinX(),ccRect.getMinY());

	ccColor4F green = {0, 1, 0, 1};
	m_pShape->clear();
	//m_pShape->drawPolygon(vertRect,4,green,0,green);
	m_pShape->setPosition(pos);



	HSTool::SetPointScale(pos);

	/**
	CCSprite* pHand = CCSprite::create("Image/hand.png");
	pHand->setAnchorPoint(ccp(0.0f,1.0f));
	pHand->setPosition(pos);
	this->addChild(pHand);
	m_nodeList.push_back(pHand);*/

	SPX_Sprite* spx_sprite = SPX_Manager::CreateSprite("Image/dianji.sprite");
	spx_sprite->setPosition(pos);
	this->addChild(spx_sprite);
	m_nodeList.push_back(spx_sprite);

	//添加监听事件
	if(m_pCurrentGuide->touchtype() == GameGuide_Guide_TouchType_TouchType_intercept)//这里要阶段按键)
	{
		this->AddDefaultEvent();
	}
	else
	{
		HSListerEvent event;
		if (HSMath::EqualsWithFloat(ccRect.size.width,0.f))
		{
			if (m_pShape->getPosition().equals(CCPointZero))
			{
				this->AddDefaultEvent();
			}
		}else{
			//event.SetRect(rect,point);
			event.SetRect(ccRect,pos);
			m_vListerEvent.push_back(event);
		}
	}


}

void HSGameGuide::DrawRound( float diameter,const GameGuide_Guide_Point& point )
{
	HSAssert(m_pShape,"");

	const int MAXVERTCOUNT = 100;

	ccColor4F green = {0, 1, 0, 1};

	float fRadius = diameter / 2.f;
	float coef = 2.f * (float)M_PI/ MAXVERTCOUNT;
	CCPoint circle[MAXVERTCOUNT];
	for(unsigned int i = 0;i <MAXVERTCOUNT; i++) 
	{
		float rads = i * coef;
		circle[i].x = fRadius * cosf(rads);
		circle[i].y = fRadius * sinf(rads);
	}

	CCPoint pos = ccp(point.x(),point.y());

	//m_pShape->drawPolygon(circle, MAXVERTCOUNT, green, 0, green);
	m_pShape->setPosition(pos);

	

	HSTool::SetPointScale(pos);
	/**
	CCSprite* pHand = CCSprite::create("Image/hand.png");
	pHand->setAnchorPoint(ccp(0.0f,1.0f));
	pHand->setPosition(pos);
	this->addChild(pHand);
	m_nodeList.push_back(pHand);*/

	SPX_Sprite* spx_sprite = SPX_Manager::CreateSprite("Image/dianji.sprite");
	spx_sprite->setPosition(pos);
	this->addChild(spx_sprite);
	m_nodeList.push_back(spx_sprite);

	//添加监听事件
	if(m_pCurrentGuide->touchtype() == GameGuide_Guide_TouchType_TouchType_intercept)//这里要阶段按键)
	{
		this->AddDefaultEvent();
	}
	else
	{
		HSListerEvent event;
		if (HSMath::EqualsWithFloat(diameter,0.f))
		{
			if (m_pShape->getPosition().equals(CCPointZero))
			{
				this->AddDefaultEvent();
			}
		}else{
			event.SetRect(diameter,pos);
			m_vListerEvent.push_back(event);
		}
	}
}


void HSGameGuide::AddDefaultEvent()
{
	CCRect rect = CCRectMake(0,0,HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	//添加监听事件
	HSListerEvent event;
	event.SetRect(rect);
	m_vListerEvent.push_back(event);
}

void HSGameGuide::Update( float dt )
{
	if (m_vListerEvent.size() == 0)
	{
		return;
	}

	//@
	{
		bool isRunNextGuide = true;
		std::vector<HSListerEvent>::iterator it = m_vListerEvent.begin();
		for (;it!=m_vListerEvent.end();++it)
		{
			HSListerEvent* pListerEvent = &(*it);
			if (!pListerEvent->isTouch)
			{
				isRunNextGuide = false;
			}
		}

		if (isRunNextGuide)
		{
			if (m_iStepIndex + 1 < m_iMaxStep)
			{
				this->Run( ++m_iStepIndex );
			}else if(m_iStepIndex + 1 == m_iMaxStep){
				this->Stop();
				HS_GAME_CACHE()->SetIsRunGameGuide(false);
			}
		}
	}



	//@
	{
		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
		if (HSBattleScene* battleScene = dynamic_cast<HSBattleScene*>(scene))
		{
			if (this->isVisible() == true)
			{
				HS_GAME_CONFIG()->SetIsPause(true);
			}else{
				HS_GAME_CONFIG()->SetIsPause(false);
			}
		}
	}
}

int HSGameGuide::GetCurrentStep()
{
	return m_iStepIndex;
}

void HSGameGuide::ClearScreen()
{
	HSAssert(m_pShape,"");
	m_pShape->clear();

	int size = m_nodeList.size();
	for(int i =0; i< size; i++)
	{
		CCNode* node = m_nodeList[i];
		this->removeChild(node,true);
	}
}

void HSGameGuide::Pause()
{
	CCNode* p = this->getParent();
	if (!p)
	{
		return;
	}

	p->removeChild(this,false);
} 


void HSGameGuide::Stop()
{
	CCNode* p = this->getParent();
	if (!p)
	{
		return;
	}
	p->removeChild(this,true);
}


void HSGameGuide::Resume(CCNode* pNode)
{
	HSAssert(pNode,"");
	pNode->addChild(this,1000000);

	Run(this->GetCurrentStep() + 1 );

	this->setVisible(true);
}

void HSGameGuide::RuntPrevious()
{
	this->Run(this->GetCurrentStep() - 1);

	this->setVisible(true);
}

bool HSGameGuide::TriggerEvent( const CCPoint& pos )
{
	CCPoint newPos = pos;

	HSTool::SetPointScale(newPos);
	std::vector<HSListerEvent>::iterator it = m_vListerEvent.begin();
	for (;it!=m_vListerEvent.end();++it)
	{
		HSListerEvent* pListerEvent = &(*it);
		if (pListerEvent->rect.containsPoint(newPos))
		{
			pListerEvent->isTouch = true;
			if (pListerEvent->rect.size.equals(HSBase::GetTemplateScreenSize()))
			{
				return true;
			}
			return false;
		}
	}
	return false;
}


void HSGameGuide::_HSListerEvent::SetRect( const CCRect& guideRect , const CCPoint& point )
{
	pos = point;
	CCPoint origin = guideRect.origin;
	//HSTool::SetPointScale(origin);

	float x = pos.x + origin.x;
	float y = pos.y + origin.y;
	float w = guideRect.size.width;
	float h = guideRect.size.height;
	rect = CCRectMake(x,y,w,h);
}

void HSGameGuide::_HSListerEvent::SetRect( float diameter,const CCPoint& point )
{
	pos = point;

	float x = pos.x + (0.f - diameter / 2.f);
	float y = pos.y + (0.f - diameter / 2.f);
	float w = diameter;
	float h = diameter;
	rect = CCRectMake(x,y,w,h);
}
