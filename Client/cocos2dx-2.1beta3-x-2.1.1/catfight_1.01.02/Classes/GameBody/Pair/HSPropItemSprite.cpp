#include "HSPropItemSprite.h"
#include "HSGamePairScene.h"
#include "HSGameSelectPropLayer.h"
#include "HSGameDialogLayer.h"
#include "HSEquipFrame.h"
#include "HSGameGuide.h"

HSPropItemSprite::HSPropItemSprite()
{
	m_pPropInfo = NULL;
	m_pLockSprite = NULL;
	m_pLockLevel = NULL;
	m_pFrame = NULL;
	m_pToggle = NULL;
	lock = false;
	isAdd = false;
}

HSPropItemSprite::~HSPropItemSprite()
{

}



HSPropItemSprite* HSPropItemSprite::create(const message::PropInfo& propInfo ,int index)
{
	HSPropItemSprite* sprite = new HSPropItemSprite;
	if(sprite && sprite->Init(propInfo,index))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSPropItemSprite::Init(const message::PropInfo& propInfo,int index)
{
	m_pPropInfo = &propInfo;
	
	//std::string fileName = GetBasePath() + pPropInfo->localname();
	const char* fileName = CCString::createWithFormat("Image/%s",m_pPropInfo->localname().c_str())->getCString();
	CCSprite* pNode_0 = HSCCSprite::create(fileName);
	HSGraySprite* pNode_1 = HSGraySprite::create(fileName);
	CCSprite* pNode_2 = HSCCSprite::create(fileName);
	HSGraySprite* pNode_3 = HSGraySprite::create(fileName);
	pNode_1->setScale(1.02f);
	pNode_3->setScale(1.02f);

	CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(pNode_0,pNode_2);
	CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(pNode_1,pNode_3);

	m_pToggle = CCMenuItemToggle::createWithTarget(this,menu_selector(HSPropItemSprite::Call),itemImage1,itemImage2,NULL);
	CCMenu* pMenu = CCMenu::create(m_pToggle,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	this->setPosition(ccp(pNode_0->getContentSize().width/2,-pNode_0->getContentSize().height/2));

	uint level = HS_TARGET_SELF().level();

	//level = 20;

	if(level >= m_pPropInfo->unlocklevel())
	{
		this->lock = false;
	}
	else//����
	{
		 this->lock = true;
		 
		 m_pToggle->setSelectedIndex(1);

		 m_pLockSprite = HSCCSprite::create("Image/lock.png");

		 m_pLockSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));

		 this->addChild(m_pLockSprite);

		 m_pFrame =  HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_Shuzidiandikuang%d",m_pPropInfo->bufferproptype()+1)->getCString(),"Shuzidiandikuang");

		 m_frame_scaleX = m_pFrame->getScaleX();
		 m_frame_scaleY = m_pFrame->getScaleY();

		 CCSize frameSize = m_pFrame->getContentSize();
		 
		 m_pLockLevel = CCLabelTTF::create(CCString::createWithFormat("LV.%d",m_pPropInfo->unlocklevel())->getCString(),HS_FONT_HuaKang,25.f,frameSize,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		 m_pLockLevel->setColor(ccBLACK);
		 m_pLockLevel->setAnchorPoint(HS_ANCHOR_CENTER);
		 m_pLockLevel->setPosition(HS_SizeHalf_Point(frameSize));

		 m_pFrame->addChild(m_pLockLevel);
	}

	this->schedule(schedule_selector(HSPropItemSprite::Update));
	
	return true;
}

void HSPropItemSprite::Update(float dt)
{
	uint level = HS_TARGET_SELF().level();

	if(level >= m_pPropInfo->unlocklevel()&&this->lock)//����
	{
		this->lock = false;
		m_pToggle->setSelectedIndex(0);

		if(m_pLockSprite)
		{
			m_pLockSprite->setVisible(false);
		}
		
		if(m_pLockLevel)
		{
			m_pLockLevel->setVisible(false);
		}

	}
}

void HSPropItemSprite::Call(CCObject* obj)
{
	CCLog("HSPropItemSprite::Call ==================================");

	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSGamePairScene* pairScene = (HSGamePairScene*)scene;

	HSGameSelectPropLayer* layer = pairScene->GetHSGameSelectPropLayer();

	layer->SetDescrib(m_pPropInfo->describ().c_str());

	if(lock)
	{
		CCActionInterval*  scale1 = CCScaleTo::create(0.2f, (float)m_frame_scaleX*1.5f, (float)m_frame_scaleY*1.5f);

		CCActionInterval*  scale2 = CCScaleTo::create(0.2f,m_frame_scaleX,m_frame_scaleY);

		m_pFrame->runAction(CCSequence::create(scale1,scale2,NULL));
		 
		m_pToggle->setSelectedIndex(1);

		return;
	}

	if(isAdd)
	{
		if(!HS_IsRunGameGuide())
		{
			int size = layer->m_equipFrameArray.size();

			for(int i=0; i < size; i++)
			{
				HSEquipFrame* frame = layer->m_equipFrameArray[i];

				if(frame->m_pPropInfo->id()==m_pPropInfo->id())
				{
					frame->Delete();
					break;
				}
			}
		}
		else
		{
			 m_pToggle->setSelectedIndex(1);
		}
		return;
	}

	if (HS_IsRunGameGuide())
	{
		HSGameGuide::ShaderGameGuide()->TriggerEvent(ccp(79,451));
	}
	
	if(!layer->AddEquip(m_pPropInfo))
	{
		HSGameDialogLayer* pdialog = HSGameDialogLayer::create(TYPE_SINGLE);

		pdialog->SetText(L("no enough equipFrame"));

		CCDirector::sharedDirector()->getRunningScene()->addChild(pdialog,10000);

		m_pToggle->setSelectedIndex(0);
	}
	else
	{
		isAdd = true;
		 
	}
}

bool HSPropItemSprite::Recover()
{
	this->isAdd = false;
	m_pToggle->setSelectedIndex(0);
	return true;
}



