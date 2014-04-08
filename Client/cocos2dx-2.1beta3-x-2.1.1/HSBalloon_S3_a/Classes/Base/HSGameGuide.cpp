#include "HSGameGuide.h"
#include "HSGameCache.h"
#include "HSBattleScene.h"

static HSGameGuide* s_hsGameGuide = NULL;

HSGameGuide::HSGameGuide(void)
{
	m_iStepIndex = -1;
	m_pClippingNode = NULL;
	m_pGameGuideData = NULL;
	m_pMaskLayer = NULL;
	m_pMode = NULL;
	m_pShape = NULL;
	m_pDescribeInfo = NULL;
	m_iMaxStep = 0;
	m_pIndicationSprite = NULL;
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
	HSTool::SetLayerScale(this);
	this->Load();
	this->setTouchEnabled(false);

	return true;
}

void HSGameGuide::Load()
{
	this->Read("Data/GameGuideData.data");

	///创建cliper
// 	m_pClippingNode = CCClippingNode::create();
// 	m_pClippingNode->setInverted(true);
// 	m_pClippingNode->setAnchorPoint(HS_ANCHOR_LD);
// 	this->addChild(m_pClippingNode);
// 
// 	HSTool::SetLayerScale(m_pClippingNode);

	//添加底板
	m_pMaskLayer = CCLayerColor::create(ccc4(0,0,0,200),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	m_pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
	this->addChild(m_pMaskLayer);
	HSToolBase::SetNodeFilldScreen(m_pMaskLayer);
	

	m_pDescribeBigFrame = CCSprite::create("Image/ShuoMingXian.png");
	m_pDescribeBigFrame->setVisible(false);
	m_pDescribeFrame = CCSprite::create("Image/STouMingKuang.png");
	m_pDescribeFrame->setPosition(m_pDescribeBigFrame->getAnchorPointInPoints());
	m_pDescribeBigFrame->addChild(m_pDescribeFrame);
	this->addChild(m_pDescribeBigFrame);

	//指示
	m_pIndicationSprite = CCSprite::create("Image/Jiantouyindao.png");
	m_pIndicationSprite->setVisible(false);
	this->addChild(m_pIndicationSprite);


	//m_pShape = CCDrawNode::create();

	//设这模板
	//m_pClippingNode->setStencil(m_pShape);

	this->schedule(schedule_selector(HSGameGuide::Update));
}

bool HSGameGuide::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!this->isVisible())
	{
		return false;
	}

    CCPoint touchPoint = convertTouchToNodeSpace(pTouch);


	if (m_ListerEvent.isTouch)
	{
		return false;
	}
	CCRect r = m_ListerEvent.rect;
#if WIN32
	//CCLog("---------------------------------");
	//CCLog("%.2f  %.2f",touchPoint.x,touchPoint.y);
	//CCLog("%.2f  %.2f  %.2f  %.2f",r.origin.x,r.origin.y,r.size.width,r.size.height);
#endif

	if (r.containsPoint(touchPoint))
	{
		CCLog("OK");
		m_ListerEvent.isTouch = true;
		if (r.size.equals(HSBase::GetTemplateScreenSize()))
		{
			return true;
		}
		return false;
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


		int count = m_pGameGuideData->battlelayoutlist(0).ballooninfolist_size();
		for (int i=0;i<count;++i)
		{
			const GameGuide_BattleLayout_BalloonInfo* p = &m_pGameGuideData->battlelayoutlist(0).ballooninfolist(i);
			int id = p->id();
			m_balloons.insert(pair<int,const message::GameGuide_BattleLayout_BalloonInfo*>(id,p));
		}


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
	GameGuide_Guide* pGuide = m_pGameGuideData->mutable_guidelist(index);

	//GameGuide_Guide_Point* pGuideModePos = pGuide->mutable_modepos();
	//CCPoint guideModePos = ccp(pGuide->modepos().x(),pGuide->modepos().y());
	//HSTool::SetPointScale(guideModePos);
	//pGuideModePos->set_x(guideModePos.x);
	//pGuideModePos->set_y(guideModePos.y + HSOffset::ShaderOffset()->OffsetY());
// 
// // 	float newW = pGuide->w() * HSOffset::ShaderOffset()->GetScaleX();
// // 	float newH = pGuide->h() * HSOffset::ShaderOffset()->GetScaleY();
// // 	pGuide->set_w(newW);
// // 	pGuide->set_h(newH);
// 
// 
// 
// 	CCPoint describeFramePos = ccp(pGuide->describeframepos().x(),pGuide->describeframepos().y());
// 	HSTool::SetPointScale(describeFramePos);
// 	GameGuide_Guide_Point* pDescribeFramePos = pGuide->mutable_describeframepos();
// 	pDescribeFramePos->set_x(describeFramePos.x);
// 	pDescribeFramePos->set_y(describeFramePos.y);







	m_currentGuide = m_pGameGuideData->guidelist(index);
	

	CCLog("RunID:  %d       isPause: %d",m_currentGuide.id(),m_currentGuide.ispause());

	this->ClearScreen();

	switch (m_currentGuide.modetype())
	{
	case GameGuide_Guide_ModeType_ModeType_Round:
		{
			this->DrawRound(m_currentGuide);
		}
		break;
	case  GameGuide_Guide_ModeType_ModeType_Rect:
		{
			this->DrawRect(m_currentGuide);
		}
		break;
	default:
		{
			this->AddDefaultEvent();
		}
		break;
	}

	m_pMaskLayer->setVisible(m_currentGuide.isshowmask());

	if (m_currentGuide.has_indicationsignpos())
	{
		m_pIndicationSprite->setPosition(ccp(m_currentGuide.indicationsignpos().x(),m_currentGuide.indicationsignpos().y()));
		if(m_currentGuide.has_mirror())
		{
			switch (m_currentGuide.mirror())
			{
			case GameGuide_Guide_MirrorType_MirrorType_X:
				m_pIndicationSprite->setFlipX(true);
				break;
			case GameGuide_Guide_MirrorType_MirrorType_Y:
				m_pIndicationSprite->setFlipY(true);
				break;
			default:
				break;
			}
		}
		
		m_pIndicationSprite->setRotation(m_currentGuide.rotate());
		m_pIndicationSprite->setVisible(true);
	}else{
		m_pIndicationSprite->setFlipX(false);
		m_pIndicationSprite->setFlipY(false);
		m_pIndicationSprite->setVisible(false);
	}

	if (m_currentGuide.describe() != "")
	{
		CCSize pngSize = m_pDescribeFrame->getContentSize();
		if (!m_pDescribeInfo)
		{
			m_pDescribeInfo = CCLabelTTF::create("",HS_FONT_HuaKang,26.f,pngSize,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
			m_pDescribeInfo->setPosition(m_pDescribeFrame->getAnchorPointInPoints());
			m_pDescribeFrame->addChild(m_pDescribeInfo);

		}
		std::string str = m_currentGuide.describe();
		int pos = str.find("#");
		while (pos != string::npos)
		{
			str.replace(pos,1,"\n",1);
			pos = str.find("#",pos);
		}
		m_pDescribeInfo->setString(str.c_str());
// 		CCSize infoSize = m_pDescribeInfo->getContentSize();
// 		CCPoint infoPos;
// 		infoPos.x = pngSize.width / 2.f/* + 25.f*/;
// 		infoPos.y = pngSize.height / 2.f;
// 		m_pDescribeInfo->setPosition(infoPos);
		m_pDescribeBigFrame->setVisible(true);

		CCPoint describeBigFramePos = CCPointZero;
		describeBigFramePos.x = m_currentGuide.describeframepos().x();
		describeBigFramePos.y = m_currentGuide.describeframepos().y();
		m_pDescribeBigFrame->setPosition(describeBigFramePos);
	}else{
		if (m_pDescribeInfo)
		{
			m_pDescribeBigFrame->setVisible(false);
		}
	}

	this->setTouchEnabled(true);
}

void HSGameGuide::Run()
{
	this->Run(0);
}

void HSGameGuide::DrawRect( const GameGuide_Guide& guide )
{
	//HSAssert(m_pShape,"");
	CCLog("%.2f   ,%.2f",HSOffset::ShaderOffset()->OffsetX(),HSOffset::ShaderOffset()->OffsetY());
	CCPoint pos = ccp(guide.modepos().x(),guide.modepos().y());
	float lx =  pos.x - guide.w() / 2.f;
	float ly =  pos.y - guide.h() / 2.f + HSOffset::ShaderOffset()->OffsetY();

	CCRect ccRect(lx,ly,guide.w(),guide.h());

// 	CCPoint vertRect[4] = {CCPointZero};
// 	vertRect[0] = ccp(ccRect.getMinX(),ccRect.getMaxY());
// 	vertRect[1] = ccp(ccRect.getMaxX(),ccRect.getMaxY());
// 	vertRect[2] = ccp(ccRect.getMaxX(),ccRect.getMinY());
// 	vertRect[3] = ccp(ccRect.getMinX(),ccRect.getMinY());
// 
// 	ccColor4F green = {0, 1, 0, 1};
// 	m_pShape->clear();
// 	m_pShape->drawPolygon(vertRect,4,green,0,green);
	//m_pShape->setPosition(pos);

	//HSTool::SetPointScale(pos);

	//if (m_currentGuide.isintercepttouch())
	{
		if (m_currentGuide.isintercepttouch())
		{
			this->AddDefaultEvent();
		}else{
			m_ListerEvent.SetRect(ccRect,pos);
		}
	}

}

void HSGameGuide::DrawRound( const GameGuide_Guide& guide )
{
	return;
	HSAssert(m_pShape,"");

	const int MAXVERTCOUNT = 100;

	ccColor4F green = {0, 1, 0, 1};

	float fRadius = guide.w() / 2.f;
	float coef = 2.f * (float)M_PI/ MAXVERTCOUNT;
	CCPoint circle[MAXVERTCOUNT];
	for(unsigned int i = 0;i <MAXVERTCOUNT; i++) 
	{
		float rads = i * coef;
		circle[i].x = fRadius * cosf(rads);
		circle[i].y = fRadius * sinf(rads);
	}

	CCPoint pos = ccp(guide.modepos().x(),guide.modepos().y());
	m_pShape->drawPolygon(circle, MAXVERTCOUNT, green, 0, green);
	//m_pShape->setPosition(pos);

	

	//HSTool::SetPointScale(pos);
	/**
	CCSprite* pHand = CCSprite::create("Image/hand.png");
	pHand->setAnchorPoint(ccp(0.0f,1.0f));
	pHand->setPosition(pos);
	this->addChild(pHand);
	m_nodeList.push_back(pHand);*/

	//if (m_currentGuide.isintercepttouch())
	{
		if (m_currentGuide.isintercepttouch())
		{
			this->AddDefaultEvent();
		}else{
			CCPoint pos = ccp(guide.modepos().x(),guide.modepos().y());
			float lx =  pos.x - guide.w() / 2.f;
			float ly =  pos.y - guide.h() / 2.f;
			CCRect ccRect(lx,ly,guide.w(),guide.h());
			m_ListerEvent.SetRect(ccRect,pos);
		}
	}
	
}


void HSGameGuide::AddDefaultEvent()
{
	CCRect rect = CCRectMake(0,0,HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	//添加监听事件
	m_ListerEvent.SetRect(rect);
}

void HSGameGuide::Update( float dt )
{
// 	bool isRunNextGuide = true;
// 
// 	if ()
// 	{				
// 		isRunNextGuide = false;
// 	}
	if (m_ListerEvent.isTouch)
	{
		if (!m_currentGuide.ispause())
		{
			if (m_iStepIndex + 1 < m_iMaxStep)
			{
				this->Run( ++m_iStepIndex );
			}else if(m_iStepIndex + 1 == m_iMaxStep){
				this->Stop();
			}
		}else{
			this->Pause();
		}
	}
}

void HSGameGuide::RunNext()
{
	this->Run( ++m_iStepIndex );
}

int HSGameGuide::GetCurrentStep()
{
	return m_iStepIndex;
}

void HSGameGuide::ClearScreen()
{
	//HSAssert(m_pShape,"");
	//m_pShape->clear();

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
	this->setVisible(false);
	this->setTouchEnabled(false);
} 


void HSGameGuide::Stop()
{
	CCNode* p = this->getParent();
	if (!p)
	{
		return;
	}
	this->setTouchEnabled(false);
	p->removeChild(this,true);
	this->setVisible(false);
}


void HSGameGuide::Resume(CCNode* pNode)
{
#define HS_GameGuide_Tag 0x78956
	HSAssert(pNode,"");
	this->setVisible(false);

	pNode->addChild(this,HS_GameGuide_Tag,HS_GameGuide_Tag);


	this->Run(this->GetCurrentStep() + 1 );

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
	newPos.y += HSOffset::ShaderOffset()->OffsetY();
	//HSTool::SetPointScale(newPos);

	if (m_ListerEvent.rect.containsPoint(newPos))
	{
		m_ListerEvent.isTouch = true;
		if (m_ListerEvent.rect.size.equals(HSBase::GetTemplateScreenSize()))
		{
			return true;
		}
		return false;
	}
	return false;
}

const GameGuide_BattleLayout_BalloonInfo* HSGameGuide::GetBallonInfo( int key )
{
	map<int,const GameGuide_BattleLayout_BalloonInfo*>::iterator it = m_balloons.find(key);
	if (it != m_balloons.end())
	{
		return it->second;
	}
	return NULL;
}

int HSGameGuide::GetCurrentStepID()
{
	return m_currentGuide.id();
}

void HSGameGuide::Destroy()
{
	CC_SAFE_RELEASE_NULL(s_hsGameGuide);
}



void HSGameGuide::_HSListerEvent::SetRect( const CCRect& guideRect , const CCPoint& point )
{
// 	pos = point;
// 	CCPoint origin = guideRect.origin;
	//HSTool::SetPointScale(origin);

// 	float x = pos.x + origin.x;
// 	float y = pos.y + origin.y;
// 	float w = guideRect.size.width;
// 	float h = guideRect.size.height;
// 	rect = CCRectMake(x,y,w,h);
	pos = point;
	rect = guideRect;
	isTouch = false;
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

void HSGameGuide::_HSListerEvent::SetRect( const CCRect& eventRect )
{
	rect = eventRect;
	isTouch = false;
}
