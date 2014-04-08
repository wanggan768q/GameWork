#include "HSEquipFrame.h"
#include "HSGamePairScene.h"
#include "HSGameSelectPropLayer.h"
#include "HSGameDialogLayer.h"
HSEquipFrame::HSEquipFrame()
{
	m_lock = false;
	m_equip = false;
	m_buy = false; 
	m_pPropSprite = NULL;
	m_pLockSprite = NULL;
	m_pDescrib = NULL;
	m_pFrameInfo = NULL; 
	m_pBell = NULL;
}

HSEquipFrame::~HSEquipFrame()
{
	
}

HSEquipFrame* HSEquipFrame::create(const message::PropInfo& frameInfo,int index)
{
	HSEquipFrame* sprite = new HSEquipFrame;
	if(sprite && sprite->Init(frameInfo,index))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSEquipFrame::Init(const message::PropInfo& frameInfo,int index)
{
	this->m_index = index;
	this->m_pFrameInfo = &frameInfo;
	this->initWithFile("Image/dikuangda.png");
	this->setAnchorPoint(HS_ANCHOR_CENTER);
	this->setPosition(ccp(this->getContentSize().width/2,-this->getContentSize().height/2));
	this->RecoverProgram();

	if(index ==0)
	{
		m_buy = true;
		m_lock = false;
		return true;
	}

	m_pLockSprite = HSCCSprite::create("Image/lock.png");

	m_pLockSprite->setAnchorPoint(HS_ANCHOR_CENTER);

	m_pLockSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));

	this->addChild(m_pLockSprite);

	CCLog("HSEquipFrame m_frame index=%d",index);
	m_frame = HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_Shuzidiandikuang%d",index-1)->getCString(),"Shuzidiandikuang");

	m_frame_scaleX = m_frame->getScaleX();
	m_frame_scaleY = m_frame->getScaleY();
 
	CCSize size = m_frame->getContentSize();
 
	m_pDescrib = CCLabelTTF::create("",HS_FONT_HuaKang,30.f,size,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
 
	m_pDescrib->setPosition(HS_SizeHalf_Point(size));
 
	m_pDescrib->setColor(ccBLACK);
 
	m_frame->addChild(m_pDescrib);

	m_pBell = HSCCSprite::create("Image/Lingdangxiao.png");
	
	m_pBell->setPosition(ccp(0-15,size.height/2));
	
	m_frame->addChild(m_pBell);

	int level = HS_TARGET_SELF().level();

	int unlockLevel = m_pFrameInfo->unlocklevel();

	//level = 99;

	if(level >=unlockLevel)
	{
		int size = HS_TARGET_SELF().buyequipframe().size();

		if(m_pFrameInfo->gold() ==0)
		{
			m_buy = true;
		}

		for(int i=0; i < size;i++)
		{
			if(HS_TARGET_SELF().buyequipframe(i)==m_pFrameInfo->id())
			{
				m_buy = true;
			}
		}
	}
	else
	{
		m_lock = true;
	}

	if(m_lock)
	{
		Lock();
	}
	else
	{
		if(!m_buy)
		{
			NeedBuy();
		}
		else
		{
			Open();
		}
	}

	this->schedule(schedule_selector(HSEquipFrame::Update));
	return true;
}

void HSEquipFrame::Update(float dt)
{
	int level = HS_TARGET_SELF().level();

	if(level >= m_pFrameInfo->unlocklevel()&&m_lock)
	{
		m_lock = false;

		NeedBuy();
	}

	if(!m_buy&&!m_lock)
	{
		int size = HS_TARGET_SELF().buyequipframe().size();

		for(int i=0; i < size;i++)
		{
			if(HS_TARGET_SELF().buyequipframe(i)==m_pFrameInfo->id())
			{
				m_buy = true;
				Open();
			}
		}
	}
}

bool HSEquipFrame::SetPropInfo(const message::PropInfo& propInfo)
{
	m_pPropInfo = &propInfo;

	m_pPropSprite = HSCCSprite::create(CCString::createWithFormat("Image/%s",m_pPropInfo->localname().c_str())->getCString());
	m_pPropSprite->setAnchorPoint(HS_ANCHOR_CENTER);
	//m_pPropSprite->setPosition(ccp(this->getContentSize().width/2,-this->getContentSize().height/2));
	m_pPropSprite->setPosition(ccp(this->getContentSize().width/2.f,this->getContentSize().height/2));
	this->addChild(m_pPropSprite);
	this->setVisible(true);
	this->m_equip = true;
	
	return true;
}

bool HSEquipFrame::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!ContainsTouchLocation(pTouch)||!this->isVisible() ) return false;

	if(m_lock)
	{
		CCActionInterval*  scale1 = CCScaleTo::create(0.2f, (float)m_frame_scaleX*1.5f, (float)m_frame_scaleY*1.5f);
		
		CCActionInterval*  scale2 = CCScaleTo::create(0.2f,m_frame_scaleX,m_frame_scaleY);
		
		m_frame->runAction(CCSequence::create(scale1,scale2,NULL));
	}
	else
	{
		if(!m_buy)
		{
			if(HS_GAME_CACHE()->GetGold()>this->m_pFrameInfo->unlockgold()+HS_GAME_CACHE()->roomGold)
			{
				if(HS_ONLINE)
				{
					HS_Play_Sound("unlock_effect");
					HS_GAME_CACHE()->m_refrushUserInfo = true;
					HSRequest::ShareRequest()->SendUsePropRequest(m_pFrameInfo->id(),UsePropRequest_OperateType_Type_unlock,HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
				}
			}
			else
			{

				CCActionInterval*  scale1 = CCScaleTo::create(0.2f, (float)m_frame_scaleX*1.5f, (float)m_frame_scaleY*1.5f);

				CCActionInterval*  scale2 = CCScaleTo::create(0.2f,m_frame_scaleX,m_frame_scaleY);
 
				m_frame->runAction(CCSequence::create(scale1,scale2,NULL));
				 
			}
		}
	}
	 
	if(!m_equip||HS_IsRunGameGuide())
	{
		return true;
	}

	Delete();
	return true;
}

void HSEquipFrame::Delete()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSGamePairScene* pairScene = (HSGamePairScene*)scene;
	HSGameSelectPropLayer* layer = pairScene->GetHSGameSelectPropLayer();
	if(layer->DeleteEquip(this->m_pPropInfo))
	{
		m_equip = false;

		this->setVisible(false);
		this->removeChild(m_pPropSprite,true);
	}
}

void HSEquipFrame::Lock()
{
	m_pLockSprite->setVisible(true);
	m_pBell->setVisible(false);
	m_pDescrib->setVisible(true);
	m_pDescrib->setString(CCString::createWithFormat("LV.%d",m_pFrameInfo->unlocklevel())->getCString());
}

void HSEquipFrame::NeedBuy()
{
	m_pLockSprite->setVisible(true);
	m_pBell->setVisible(true);
	m_pDescrib->setVisible(true);
	m_pDescrib->setString(CCString::createWithFormat("%d",m_pFrameInfo->unlockgold())->getCString());
}

void HSEquipFrame::Open()
{
	m_pLockSprite->setVisible(false);
	m_pBell->setVisible(false);
	m_pDescrib->setVisible(false);
}

void HSEquipFrame::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void HSEquipFrame::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void HSEquipFrame::onEnter()
{
	HSGraySprite::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
}

void HSEquipFrame::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	HSGraySprite::onExit();
}



