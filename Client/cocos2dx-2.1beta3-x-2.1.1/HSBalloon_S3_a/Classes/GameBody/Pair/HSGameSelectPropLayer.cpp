#include "HSGameSelectPropLayer.h"
#include "HSGamePairScene.h"
#include "HSPropItemSprite.h"
#include "HSEquipFrame.h"
HSGameSelectPropLayer::HSGameSelectPropLayer(void)
{
	m_pDescrib = NULL;
}

HSGameSelectPropLayer::~HSGameSelectPropLayer(void)
{

}

bool HSGameSelectPropLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();

	//this->setIsTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSGameSelectPropLayer::Load()
{
	
	//HS_MUTABLE_TARGET_SELF()->set_level(30);


	HSReadUI::ShareReadUI()->ReadUI("Image/pair/selectProp/selectProp.data","Image/pair/selectProp/",this);
	HS_SET_MENU_TARGET("UI_Guanbianniu_01",this,HSGameSelectPropLayer::Close);

	CCSprite* ban = HS_FIND_UI_PANEL_SPRITE("UI_UIdiban","diban");
	rect = CCRectMake(ban->getPositionX(),ban->getPositionY(),ban->getContentSize().width,ban->getContentSize().height);
	 

	for(int i =1; i <8; i++)
	{
		CCSprite* propFrame =  HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_Daojujiguang%d",i)->getCString(),"Daojujiguang");
		propFrame->setVisible(false);
	}
	//添加道具槽

	for(int i=1; i < 4;i++)
	{
		CCNode* propFrame = HS_FIND_UI_PANEL(CCString::createWithFormat("UI_Chuangkouditu%d",i)->getCString());
		HSEquipFrame* equip = HSEquipFrame::create(HS_GAME_CACHE()->GetPropInfoData()->lockpropinfolist(i-1),i-1);
		propFrame->addChild(equip);
		m_equipFrameArray.push_back(equip);
	}


	//添加道具
	CCNode* propFrame = HS_FIND_UI_PANEL(CCString::createWithFormat("UI_Daojujiguang%d",4)->getCString());
	HSPropItemSprite* item = HSPropItemSprite::create(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(0),0);
	propFrame->addChild(item);
	m_propItemSpriteArray.push_back(item);
	for(int i = 5; i< 8;i++)
	{
		CCNode* propFrame = HS_FIND_UI_PANEL(CCString::createWithFormat("UI_Daojujiguang%d",i)->getCString());
		HSPropItemSprite* item = HSPropItemSprite::create(HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(i-5),i-5);
		propFrame->addChild(item);
		m_propItemSpriteArray.push_back(item);
	}


	CCSprite* frame = HS_FIND_UI_PANEL_SPRITE("UI_Shuomingdaditu","Shuomingdaditu");
	CCSize size = CCSize(frame->getContentSize().width,frame->getContentSize().height);
	m_pDescrib = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,size,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	m_pDescrib->setPosition(HS_SizeHalf_Point(size));
	m_pDescrib->setColor(ccBLACK);
	frame->addChild(m_pDescrib,1100);

	this->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(HSGameSelectPropLayer::CallLoadData)),NULL));
}

void HSGameSelectPropLayer::Close(CCObject* obj)
{                                                        	 
	this->setVisible(false);
}

void HSGameSelectPropLayer::setVisible(bool visible)
{
	CCNode::setVisible(visible);

	int count = m_equipFrameArray.size();

	bool b = false;
	for(int i =0; i < count; i ++)
	{
		if(m_equipFrameArray[i])
		{
			m_equipFrameArray[i]->setVisible(visible);
		}
	}
}

void HSGameSelectPropLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSGameSelectPropLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint point = pTouch->getLocation();
	
	if(rect.containsPoint(point))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void HSGameSelectPropLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameSelectPropLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameSelectPropLayer::keyBackClicked()
{

}
void HSGameSelectPropLayer::keyMenuClicked()
{

}

bool HSGameSelectPropLayer::AddEquip(const PropInfo* prop)
{
	int count = m_equipFrameArray.size();

	bool b = false;
	for(int i =0; i < count; i ++)
	{
		if(!m_equipFrameArray[i]->m_equip&&!m_equipFrameArray[i]->m_lock&&m_equipFrameArray[i]->m_buy)
		{
			if(m_equipFrameArray[i]->SetPropInfo(*prop))
			{
				HS_GAME_CACHE()->m_pFightingProp.push_back(prop);                                                                                                                                         
				
				b = true;
				break;
			}
		}
	}
	return b;
}

bool HSGameSelectPropLayer::DeleteEquip(const PropInfo* prop)
{
	int count = m_propItemSpriteArray.size();
	bool b = false;

	for(int i =0; i <count; i++)
	{
		if(m_propItemSpriteArray[i]->isAdd &&m_propItemSpriteArray[i]->m_pPropInfo->id()==prop->id())
		{
			m_propItemSpriteArray[i]->Recover();

			vector<const message::PropInfo*>::iterator itr = HS_GAME_CACHE()->m_pFightingProp.begin();
			
			while (itr!=HS_GAME_CACHE()->m_pFightingProp.end())
			{
				if(prop->id()==(*itr)->id())
				{
					HS_GAME_CACHE()->m_pFightingProp.erase(itr);
					break;
				}
				itr++;
			}

			b = true;
		}
	}
	return b;
}

void HSGameSelectPropLayer::SetDescrib(const char* text)
{
	if(m_pDescrib)
	{
		m_pDescrib->setString(text);
	}
}

void HSGameSelectPropLayer::CallLoadData()
{
	std::vector<const message::PropInfo*> propCache;

	for(std::vector<const message::PropInfo*>::size_type i =0; i< HS_GAME_CACHE()->m_pFightingProp.size(); i++)
	{
		propCache.push_back(HS_GAME_CACHE()->m_pFightingProp[i]);
	}
	HS_GAME_CACHE()->m_pFightingProp.clear();

	for(std::vector<const message::PropInfo*>::size_type i=0; i <propCache.size();i++)
	{
		const message::PropInfo* propInfo = propCache[i];

		for(std::vector<HSPropItemSprite*>::size_type i=0; i< m_propItemSpriteArray.size(); i++)
		{
			if(propInfo->id()==m_propItemSpriteArray[i]->m_pPropInfo->id())
			{
				m_propItemSpriteArray[i]->m_pToggle->setSelectedIndex(1);
				m_propItemSpriteArray[i]->Call(NULL);
			}
		}
	}

	propCache.clear();
}

