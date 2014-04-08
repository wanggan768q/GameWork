#include "HSPropItemSprite.h"
#include "HSGameSceneJumpManage.h"
#include "HSBuyPropScene.h"
#include "HSBuyPropInfoDialog.h"
#include "HSGameGuide.h"

//不需要释放 只是记录选中道具的指针 但是在管理器结束的时候把 = NULL 避免野指针
static HSPropItemSprite* s_hsPropItemSprite = NULL;
static HSPropItemSprite* s_lastPropItemSprite = NULL;
CCMenuItemImage* HSPropItemSprite::s_lastCCMenuItemImage = NULL;
CCLabelTTF* HSPropItemSprite::s_lastDescribeInfo = NULL;

HSPropItemSprite::HSPropItemSprite(void)
{
	m_isCanTouch = true;
	m_isEquip = false;
	m_byCopyObj = NULL;
	m_pEuipFrame = NULL;
	m_pDescribeInfo = NULL;
	m_pNumber = NULL;
	m_curNumber = 0;
}


HSPropItemSprite::~HSPropItemSprite(void)
{
	m_PropInfo.Clear();

	s_lastPropItemSprite = NULL;
	s_hsPropItemSprite = NULL;
	m_pNumber = NULL;
	s_lastCCMenuItemImage = NULL;
	m_curNumber = 0;
}

HSPropItemSprite* HSPropItemSprite::create( int index )
{
	HSPropItemSprite* sprite = new HSPropItemSprite;
	if (sprite && sprite->Init(index))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

HSPropItemSprite* HSPropItemSprite::create( const message::PropInfo propInfo ,int index )
{
	HSPropItemSprite* sprite = new HSPropItemSprite;
	if (sprite && sprite->Init(propInfo,index))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool HSPropItemSprite::Init(int index)
{
// 	m_PropInfo.set_id(HS_MANUAL_PROP_BASE_ID + index);
// 	m_PropInfo.set_isbuy(false);
// 	m_PropInfo.set_buymoney(1000);
// 	m_PropInfo.set_describe(CCString::createWithFormat("tesse是三角剖分lation是曲是三角剖分面细分,tria是三角剖分ngula是三角剖分tion是三角剖分,consolidation是什么意思？  %d",index)->getCString());
// 	m_PropInfo.set_proptype(message::PropInfo::BALLOON_PROPS_StratagemLevelByZero);
// 
// 	switch (index)
// 	{
// 	case 0:
// 		m_PropInfo.set_proptype(message::PropInfo::BALLOON_PROPS_ChangeColorFullScreen);
// 		break;
// 	case 1:
// 		m_PropInfo.set_proptype(message::PropInfo::BALLOON_PROPS_Lightning);
// 		break;
// 	case 2:
// 		m_PropInfo.set_proptype(message::PropInfo::BALLOON_PROPS_KingTime);
// 		break;
// 	case 3:
// 		m_PropInfo.set_proptype(message::PropInfo::BALLOON_PROPS_StratagemLevelByZero);
// 		break;
// 	case 4:
// 		m_PropInfo.set_proptype(message::PropInfo::BALLOON_PROPS_StratagemLevelByZero);
// 		break;
// 	}
// 
// 	return Init(m_PropInfo,index);

	return false;
}

bool HSPropItemSprite::Init( const message::PropInfo propInfo ,int index)
{
	 

	m_PropInfo.Clear();
	m_PropInfo.CopyFrom(propInfo);
	m_PropInfo.set_id(HS_MANUAL_PROP_BASE_ID + index);

	//HS_SET_MENU_TARGET("UI_ZhuJieMian_01",this,HSBuyPropLayer::CallPropDialog);

	HS_SET_MENU_TARGET(CCString::createWithFormat("UI_DaoJuBanZu_DaoJuBan%d_WenHao_01",index)->getCString(),this,HSPropItemSprite::CallPropDialog);
	
	const char* uiName = CCString::createWithFormat("UI_DaoJuBanZu_DaoJuBan%d_DaoJuBanXiao",index )->getCString();
	const char* uiMoneyName = CCString::createWithFormat("UI_DaoJuBanZu_DaoJuBan%d_JiaGeBanXiao",index )->getCString();
	const char* uiNumberName = CCString::createWithFormat("UI_DaoJuBanZu_DaoJuBan%d_ShuLiang",index)->getCString();

	HSCCSprite* propFirst = HS_FIND_UI_PANEL_SPRITE(uiName,"x_DaoJuBanXiao");
	HSCCSprite* propMoneyFirst = HS_FIND_UI_PANEL_SPRITE(uiMoneyName,"x_JiaGeBanXiao");
	HSCCSprite* propNumberFirst = HS_FIND_UI_PANEL_SPRITE(uiNumberName,"ShuLiang");

	CCSize moneyFrameSize = propMoneyFirst->getContentSize();

	CCSize moneyPngSize = CCSizeMake(190.f,23.f);
	CCLabelAtlas* buyMoney = CCLabelAtlas::create(CCString::createWithFormat("%d",m_PropInfo.buymoney())->getCString(),"Image/PropMoney.png",moneyPngSize.width / 10,moneyPngSize.height,'0');
	buyMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	buyMoney->setPosition(HS_SizeHalf_Point(propMoneyFirst->getContentSize()));
	propMoneyFirst->addChild(buyMoney);
	//HS_GAME_CACHE_DATA()->propcachedata();
	//HS_GAME_CACHE_DATA()->mutable_propcachedata();
	
	m_pNumber = CCLabelTTF::create(CCString::createWithFormat("%d",HS_GAME_CACHE()->GetPropNumber(index))->getCString(),"",25.f,m_describePaneSize,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter); 
	m_pNumber->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pNumber->setPosition(HS_SizeHalf_Point(propNumberFirst->getContentSize()));
	
	propNumberFirst->addChild(m_pNumber);
	

	const char* fileName = CCString::createWithFormat("Image/BuyProp/ManualProp/%d.png",HS_MANUAL_PROP_BASE_ID + index)->getCString();
	bool isOK = this->initWithFile(fileName);
	this->setPosition(ccp(propFirst->getContentSize().width / 2.f,propFirst->getContentSize().height / 2.f));
	propFirst->addChild(this);

	//道具等级 
	CCSize leverpngSize = CCSizeMake(200.f,28.f);
	int level = HS_GAME_CACHE()->GetPropLevel(index);
	CCSprite* levelSprite = CCSprite::create("Image/BuyProp/lv.png",CCRect(leverpngSize.width/4*(level-1),0,leverpngSize.width/4,leverpngSize.height));
	levelSprite->setPosition(ccp(this->getContentSize().width/2.f,20.f));
	this->addChild(levelSprite); 

	this->RecoverProgram();

	//显示描述信息
	/**
	HSCCSprite* describePane = HS_FIND_UI_PANEL_SPRITE("UI_HuangJinQiQiuBan_DaoJuShuoMing","x_DaoJuShuoMing");
	m_describePaneSize = describePane->getContentSize();
	m_describePaneSize.width = m_describePaneSize.width - 50.f;
	m_describePaneSize.height = m_describePaneSize.height - 10.f;
	m_pDescribeInfo = CCLabelTTF::create(m_PropInfo.describe().c_str(),"华康海报体W12(P)",25.f,m_describePaneSize,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	m_pDescribeInfo->setColor(ccc3(0,255,0));
	CCSize infoSize = m_pDescribeInfo->getContentSize();
	CCPoint infoPos;
	infoPos.x = m_describePaneSize.width / 2.f + 25.f;
	infoPos.y = m_describePaneSize.height / 2.f;
	m_pDescribeInfo->setPosition(infoPos);
	describePane->addChild(m_pDescribeInfo);
	m_pDescribeInfo->setVisible(false);*/

	this->schedule(schedule_selector(HSPropItemSprite::Update));

	return isOK;
}

bool HSPropItemSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) ) return false;
	HSSoundManage::ShareSoundManage()->PlayerEffect("botton");

	/**
	if (s_lastDescribeInfo)
	{
		s_lastDescribeInfo->setVisible(false);
	}
	s_lastDescribeInfo = m_pDescribeInfo;
	s_lastDescribeInfo->setVisible(true);
	*/
	if ( m_isEquip )
	{
		if (!m_byCopyObj || !m_pEuipFrame)
		{
			return true;
		}
		m_byCopyObj->RecoverProgram();
		m_pEuipFrame->isEquip = false;
		//HS_GAME_CACHE()->AddGold(m_PropInfo.buymoney());

		int index = m_PropInfo.id()-HS_MANUAL_PROP_BASE_ID;
		int number =HS_GAME_CACHE()->GetPropNumber(index); 
		HS_GAME_CACHE()->SetPropNumber(index,++number);
		HS_GAME_CACHE()->Save();
		m_pNumber->setString(CCString::createWithFormat("%d",number)->getCString());
		 

		this->getParent()->removeChild(this,true);
		s_lastPropItemSprite = NULL;
		s_hsPropItemSprite = NULL;

		

		HSGameEquipManager::m_iYetEquipCount - 1 < 0 ? HSGameEquipManager::m_iYetEquipCount = 0 : HSGameEquipManager::m_iYetEquipCount--;
		
	}else{
		if (HSGraySprite_Type_Gray == GetType())
		{
			return true;
		}

		int index = HS_PROP_INDEX(m_PropInfo.id());

		int number =HS_GAME_CACHE()->GetPropNumber(index); 

		if( number==0)//需要购买
		{
			/**
			HS_GAME_CACHE()->SetPropNumber(index,++number);
			HS_GAME_CACHE()->Save();
			m_pNumber->setString(CCString::createWithFormat("%d",number)->getCString());
			HS_GAME_CACHE()->AddGold(-m_PropInfo.buymoney());

			HSLog::ShareLog()->SendBuyGoodLog(LogRequest_BuyType_BuyItem,index+HS_MANUAL_PROP_BASE_ID,1,LogRequest_BuyState_Success);*/
			const char* titleKey = CCString::createWithFormat("prop%d",index+1)->getCString();
			const char* discribKey = CCString::createWithFormat("prop%dchar",index+1)->getCString();
			HSTool::ShareHSTool()->Buy(m_PropInfo.id(),HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(index).buymoney(),L(titleKey),L(discribKey));
			return true;
		}

		//判断是否可以装备 不能装备的条件是 已经装满了
		if (!HSGameEquipManager::GetIsCanEquip())
		{
			return true;
		}

		 
		HS_GAME_CACHE()->SetPropNumber(index,--number);
		HS_GAME_CACHE()->Save();
		m_pNumber->setString(CCString::createWithFormat("%d",number)->getCString()); 
		 
		this->GrayProgram();
		//记录当前选中的道具
		s_hsPropItemSprite = this;
	}
	

	return true;
}

void HSPropItemSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (HSGraySprite_Type_Gray == GetType())
	{
		return;
	}
}

void HSPropItemSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (HSGraySprite_Type_Gray == GetType())
	{
		return;
	}
}

void HSPropItemSprite::onEnter()
{
	HSGraySprite::onEnter();
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void HSPropItemSprite::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	HSGraySprite::onExit();
}

void HSPropItemSprite::Update(float dt)
{
	if(m_curNumber != HS_GAME_CACHE()->GetPropNumber(m_PropInfo.id()-HS_MANUAL_PROP_BASE_ID))
	{
		m_curNumber = HS_GAME_CACHE()->GetPropNumber(m_PropInfo.id()-HS_MANUAL_PROP_BASE_ID);
		m_pNumber->setString(CCString::createWithFormat("%d",m_curNumber)->getCString());
	}
}

HSPropItemSprite* HSPropItemSprite::Copy()
{
	HSPropItemSprite* sprite = new HSPropItemSprite;
	if (sprite && sprite->initWithTexture(this->getTexture(),this->getTextureRect()))
	{
		sprite->m_PropInfo.CopyFrom(m_PropInfo);
		//sprite->setScale(this->getScale());
		sprite->RecoverProgram();
		sprite->SetCopyObj(this);
		sprite->SetNumber(m_pNumber);
		sprite->SetDescribeInfo(m_pDescribeInfo);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void HSPropItemSprite::SetIsEquip(bool is)
{
	this->m_isEquip = is;
}

void HSPropItemSprite::SetCopyObj(HSPropItemSprite* item)
{
	m_byCopyObj = item;
}

void HSPropItemSprite::SetEquipFrame(HSEquipFrame* frame)
{
	m_pEuipFrame = frame;
}

void HSPropItemSprite::SetDescribeInfo( CCLabelTTF* pDescribeInfo )
{
	m_pDescribeInfo = pDescribeInfo;
}

void HSPropItemSprite::SetNumber(CCLabelTTF* pNumber)
{
	m_pNumber = pNumber;

}

void HSPropItemSprite::CallPropDialog(CCObject* obj)
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

	if(layer->m_pBuyPropInfoDialog==NULL)
	{
		layer->m_pBuyPropInfoDialog = HSBuyPropInfoDialog::create(layer);
		layer->addChild(layer->m_pBuyPropInfoDialog,10000);
	}
	else
	{
		layer->m_pBuyPropInfoDialog->setVisible(true);
	}

	layer->m_pBuyPropInfoDialog->setProp(m_PropInfo.id());
}


//////////////////////////////////////////////////////////////////////////

int HSGameEquipManager::m_iMaxEquipCount = 0;
int HSGameEquipManager::m_iYetEquipCount = 0;

HSGameEquipManager::HSGameEquipManager()
{
	 
}

HSGameEquipManager::~HSGameEquipManager()
{
	s_hsPropItemSprite = NULL;
	HSPropItemSprite::s_lastDescribeInfo = NULL;
}

HSGameEquipManager* HSGameEquipManager::create()
{
	HSGameEquipManager* mange = new HSGameEquipManager;
	if (mange && mange->Init())
	{
		mange->autorelease();
		return mange;
	}
	CC_SAFE_DELETE(mange);
	return NULL;
}

bool HSGameEquipManager::Init()
{
	const int maxEquipCount = 4;
	for (int i=1;i<=maxEquipCount;++i)
	{
		HSEquipFrame equipFrame;
		equipFrame.id = i;
		equipFrame.isLock = false;
		const char* key = CCString::createWithFormat("UI_DaoJuZu_DaoJu%d_DaoJuBan_DaoJuCao",i)->getCString();
		const char* sprite = "x_DaoJuCao";
		equipFrame.frame = HS_FIND_UI_PANEL_SPRITE(key,sprite);		
		
		if (HS_GAME_CACHE()->IsPropSlotLock(i-1))
		{
			equipFrame.isLock = true;
			CCMenuItemImage* lock = CCMenuItemImage::create("Image/BuyProp/x_Suo.png","Image/BuyProp/x_Suo.png",this,menu_selector(HSGameEquipManager::CallOk));
			lock->setPosition(ccp(equipFrame.frame->getContentSize().width / 2.f,equipFrame.frame->getContentSize().height / 2.f));
			lock->setTag(i);
			CCMenu* lockMenu = CCMenu::create(lock,NULL);
			lockMenu->setPosition(CCPointZero);
			equipFrame.frame->addChild(lockMenu);
		}
		else
		{
			m_iMaxEquipCount++;
		}
		this->m_EquipFrameList.push_back(equipFrame);
	}

	HS_SET_MENU_TARGET("UI_KSAnNiu_01",this,HSGameEquipManager::CallBattleScene);		

	this->schedule(schedule_selector(HSGameEquipManager::Update));
	return true;
}


void HSGameEquipManager::CallLock(CCObject* obj)
{
	CCMenuItemImage* lock = dynamic_cast<CCMenuItemImage*>(obj);
	HSPropItemSprite::s_lastCCMenuItemImage = lock;
	if (!lock)
	{
		return;
	}
	 
	m_dialog = HSBuySlotDialog::create(this);
	this->getParent()->addChild(m_dialog,10000);
}

void HSGameEquipManager::CallOk(CCObject* obj)
{
	CCMenuItemImage* lock = dynamic_cast<CCMenuItemImage*>(obj);
	HSPropItemSprite::s_lastCCMenuItemImage = lock;
	if(!lock)
	{
		return;
	}

	int index = HSPropItemSprite::s_lastCCMenuItemImage->getTag()-1;

	HSTool::ShareHSTool()->Buy(HS_LOCK_PROP_ID(index),HS_GAME_CACHE()->GetPropInfoData()->lockpropinfolist(index-1).buymoney(),L("openslotTile"),CCString::createWithFormat(L("openslot"),index)->getCString());

	//this->getParent()->removeChild(m_dialog,true);
}

void HSGameEquipManager::CallCancle(CCObject* obj)
{
	this->getParent()->removeChild(m_dialog,true);
}


void HSGameEquipManager::CallBattleScene(CCObject* obj)
{
	SaveEquipProp();
	if (HS_GAME_CACHE()->IsRunGameGuide())
	{
		//HSGameGuide::ShaderGameGuide()->Stop();
		HSGameGuide::ShaderGameGuide()->Pause();
	}

	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

	layer->m_isCloseGuide = true;

	int value = HSMath::Random(0,100);

	if (HS_GAME_CACHE()->IsRunGameGuide())//如果是新手引导,就直接跳转战斗界面
	{
		value =100;
	}
	
	if(value > 20)
	{
		HS_GO_SCENE(HS_SCENE_BattleScene);
	}
	else
	{
		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

		HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

		if(layer->m_pBuyPropInfoDialog==NULL)
		{
			layer->m_pBuyPropInfoDialog = HSBuyPropInfoDialog::create(layer);
			layer->addChild(layer->m_pBuyPropInfoDialog,10000);
		}
		else
		{
			layer->m_pBuyPropInfoDialog->setVisible(true);
		}

		layer->m_pBuyPropInfoDialog->setProp(2000);
	}
	
}

void HSGameEquipManager::Update(float dt)
{
	if (s_hsPropItemSprite)
	{
		if (s_hsPropItemSprite && !s_lastPropItemSprite || s_lastPropItemSprite->m_PropInfo.id() != s_hsPropItemSprite->m_PropInfo.id())
		{
			int count = (int)m_EquipFrameList.size();
			for (int i=0;i<count;++i)
			{
				HSEquipFrame* equipFrame = &m_EquipFrameList[i];
				if (!equipFrame->isEquip && !equipFrame->isLock)
				{
					HSPropItemSprite* item = s_hsPropItemSprite->Copy();
					item->SetIsEquip(true);
					item->setScale(0.7f);
					CCSize frameSize = equipFrame->frame->getContentSize();
					item->setPosition(ccp(frameSize.width / 2.f,frameSize.height / 2.f));
					equipFrame->frame->addChild(item);
					s_lastPropItemSprite = s_hsPropItemSprite;
					equipFrame->equip = item;
					equipFrame->isEquip = true;
					item->SetEquipFrame(equipFrame);
					//装备上以后减金币
					/*HS_GAME_CACHE()->AddGold(-item->m_PropInfo.buymoney());*/
					
					//已装备数量 +1
					HSGameEquipManager::m_iYetEquipCount++;
					break;
				}
			}
		}
	}

	int count = m_EquipFrameList.size();

	for(int i =0; i < count; i++)
	{
		if(m_EquipFrameList[i].isLock)
		{
			if(!HS_GAME_CACHE()->IsPropSlotLock(i))
			{
				if(HSPropItemSprite::s_lastCCMenuItemImage!=NULL)
				{
					HSPropItemSprite::s_lastCCMenuItemImage->setVisible(false);
				}

				m_EquipFrameList[i].isLock = false;

				m_iMaxEquipCount++;
			}
		}
	}
}

bool HSGameEquipManager::GetIsCanEquip()
{
	if(HSGameEquipManager::m_iMaxEquipCount == 0)
	{
		return false;
	}
	return HSGameEquipManager::m_iYetEquipCount < HSGameEquipManager::m_iMaxEquipCount ? true : false;
}

void HSGameEquipManager::SaveEquipProp()
{
	int count = (int)m_EquipFrameList.size();
	for (int i=0;i<count;++i)
	{
		HSEquipFrame* equipFrame = &m_EquipFrameList[i];
		
		if (equipFrame->isEquip)
		{
			HS_GAME_CACHE()->AddUseProp(equipFrame->equip->m_PropInfo,i);


			int index = equipFrame->equip->m_PropInfo.id()-HS_MANUAL_PROP_BASE_ID;

			if(HS_GAME_CACHE()->GetPropIndex()== index)
			{
				int frequency = HS_GAME_CACHE()->GetPropUseFrequency(index);

				frequency-=1;

				if(frequency<=0)//应该升级了
				{
					int level = HS_GAME_CACHE()->GetPropLevel(index);

					if(level<4)
					{
						level+=1;
						HS_GAME_CACHE()->SetPropLevel(index,level);
						frequency = HS_GAME_CACHE()->GetPropUseFrequencyByLevel(level);
						HS_GAME_CACHE()->SetPropUseFrequency(index,frequency);

					}
					else
					{
						HS_GAME_CACHE()->SetPropLevel(index,4);
						HS_GAME_CACHE()->SetPropUseFrequency(index,0);
					}

				}
				else
				{
					HS_GAME_CACHE()->SetPropUseFrequency(index,frequency);
				}
			}
		}
		

	}
	HS_GAME_CACHE()->Save();
}
