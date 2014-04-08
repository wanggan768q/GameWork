#include "HSBuyPropScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSBuyShopDialog.h"
#include "HSBuyPropInfoDialog.h"
#include "HSGameGuide.h"

//Layer
HSBuyPropLayer::HSBuyPropLayer(void)
{
	//m_pHSGameSceneRropManager = NULL;
	m_curpGold = 0;
	m_pBuyShopDialog = NULL;
	m_pBuyPropInfoDialog = NULL;
}

HSBuyPropLayer::~HSBuyPropLayer(void)
{
	m_pBuyShopDialog=NULL;
	m_pBuyPropInfoDialog=NULL;
}

bool HSBuyPropLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	Load();
	//this->setTouchEnabled(true);

	//this->setKeypadEnabled(true);

	return true;
}

void HSBuyPropLayer::Load()
{
	m_isCloseGuide = false;
	HSReadUI::ShareReadUI()->ReadUI("Image/BuyProp/BuyProp.data","Image/BuyProp/",this);
	HSSoundManage::ShareSoundManage()->PlayMusic("tools_select");
	//@UI
	{
		//金币
		HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_JinBiTiao","x_JinBiTiao");
		CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
		CCSize gameGoldPngSize = CCSizeMake(250.f,30.f);
		m_pGameGold = CCLabelAtlas::create("0","Image/GameGold.png",gameGoldPngSize.width / 10,gameGoldPngSize.height,'0');
		m_pGameGold->setPosition(ccp(gameGoldPngSize.width / 10,0));
		m_pGameGold->setScaleX( gameGoldFrameSize.width / gameGoldPngSize.width);
		m_pGameGold->setScaleY( gameGoldFrameSize.height / gameGoldPngSize.height);
		gameGoldFrame->addChild(m_pGameGold);


// 		string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Data/PropInfo.data");
// 		
// 		HSFileData data(fullFilePath.c_str(),"rb");
// 
// 		message::PropInfoData* propInfodata = message::PropInfoData::default_instance().New();
// 		
// 		bool isOk = propInfodata->ParsePartialFromArray((const void*)(data.GetBuffer() + 2) ,data.GetSize() - 2);
// 		
// 		if (!isOk)
// 		{
// 			HSMessageBox("Data/PropInfo.data     Error");
// 
// 			CC_SAFE_DELETE(propInfodata);
// 		}
// 		else
// 		{
			//int usePropInfoSize = propInfodata->manualpropinfolist_size();
			
			for (int i=0;i<4;++i)
			{
				//不用释放内存
				//手动道具
				HSPropItemSprite* item = HSPropItemSprite::create(HS_GAME_CACHE()->GetPropInfoData()->manualpropinfolist(i),i);
				item = NULL;
			}
		//}

		for (int i=0;i<HS_GAME_CACHE_DATA()->levellock_size();++i)
		{
			HSGameScenePropSprite* s = HSGameScenePropSprite::create(i);
	
			HSAssert(s,"HSGameScenePropSprite cannot be empty");
			
			if(!HS_GAME_CACHE_DATA()->levellock(i))
			{
				s->SetBuy();
			}
		}
		//不需要释放内存
		//装备手动道具管理器
		HSGameEquipManager* equipManage = HSGameEquipManager::create();
		
		this->addChild(equipManage);

		int index = HS_GAME_CACHE()->GetPropIndex();
		int level = HS_GAME_CACHE()->GetPropLevel(index);
		int frequency = HS_GAME_CACHE()->GetPropUseFrequency(index);
		int maxFrequency = HS_GAME_CACHE()->GetPropUseFrequencyByLevel(level);

		HSCCSprite* leverUpback = HS_FIND_UI_PANEL_SPRITE("UI_HuangJinQiQiuBan_DaoJuShuoMing1","x_DaoJuShuoMing1");
		CCSprite* leverUpPropIcon = CCSprite::create(CCString::createWithFormat("Image/BuyProp/ManualProp/100%d.png",index)->getCString());
		leverUpPropIcon->setPosition(HS_SizeHalf_Point(leverUpback->getContentSize()));
		leverUpback->addChild(leverUpPropIcon);

		

		HSCCSprite* shuzitoumingban = HS_FIND_UI_PANEL_SPRITE("UI_HuangJinQiQiuBan_ShuZiTouMingBan","ShuZiTouMingBan");
		CCSize gameGoldPngSize1 = CCSizeMake(250.f,30.f);
		CCLabelAtlas* useFrequency =  CCLabelAtlas::create(CCString::createWithFormat("%d",frequency)->getCString(),"Image/GameGold.png",gameGoldPngSize1.width / 10,gameGoldPngSize1.height,'0');;
		useFrequency->setAnchorPoint(HS_ANCHOR_CENTER);
		useFrequency->setPosition(HS_SizeHalf_Point(shuzitoumingban->getContentSize()));
		shuzitoumingban->addChild(useFrequency);

		HSCCSprite* progressBack = HS_FIND_UI_PANEL_SPRITE("UI_HuangJinQiQiuBan_LVJinDu","LVJinDu");
		progressBack->setVisible(false);
		
		HSCCSprite* energySprite = HSCCSprite::create(progressBack->getTexture());
		CCProgressTimer* frequencyProgress = CCProgressTimer::create(energySprite);
		frequencyProgress->setType(kCCProgressTimerTypeBar);
		frequencyProgress->setMidpoint(ccp(0,0));
		frequencyProgress->setBarChangeRate(ccp(1, 0));
		frequencyProgress->setPosition(progressBack->getPosition());
		float energyProgress = (float)(maxFrequency -frequency) / (float)maxFrequency * 100.f;
		energyProgress > 100.f ? energyProgress = 100.f : 0;
		frequencyProgress->setPercentage(energyProgress);
		progressBack->getParent()->addChild(frequencyProgress); 

		HSCCSprite* leverback = HS_FIND_UI_PANEL_SPRITE("UI_HuangJinQiQiuBan_LVniu","LVniu");
		CCSize leverpngSize = CCSizeMake(200.f,28.f);
		CCSprite* levelSprite = CCSprite::create("Image/BuyProp/lv.png",CCRect(leverpngSize.width/4*(level-1),0,leverpngSize.width/4,leverpngSize.height));
		levelSprite->setPosition(HS_SizeHalf_Point(leverback->getContentSize()));
		leverback->addChild(levelSprite);

		
		/**
		//二次确认对话框
		m_pDialogNode = HS_FIND_UI_PANEL("UI_GouMaiBan");
		
		m_pDialogNode->setVisible(false);
		
		//确认按钮
		HS_SET_MENU_TARGET("UI_GouMaiBan_QueRen_01",this,HSBuyPropLayer::Call_Ok);
		
		HS_SET_MENU_TARGET("UI_GouMaiBan_QuXiao_01",this,HSBuyPropLayer::Call_Cancel);
		*/
		//取消按钮

		//返回主界面
		HS_SET_MENU_TARGET("UI_ZhuJieMian_01",this,HSBuyPropLayer::CallBackMainScene);
		//商城界面
		HS_SET_MENU_TARGET("UI_ChongZhi_01",this,HSBuyPropLayer::CallShopLayer);


		//道具信息
		//HS_SET_MENU_TARGET("UI_DaoJuBanZu_DaoJuBan0_WenHao_01",this,HSBuyPropLayer::CallPropInfo);


		/**
		CCNode* chongZhi = HS_FIND_UI_PANEL("UI_ChongZhi_01");
		chongZhi->setVisible(false);*/
	}
	/**
	 {
		 m_pBuyShopDialog = HSBuyShopDialog::create(this);
		 

		 m_pBuyShopDialog->setVisible(false);

		 this->addChild(m_pBuyShopDialog,10000);
		 m_pBuyShopDialog->onExit();
	 }*/

	this->schedule(schedule_selector(HSBuyPropLayer::Update));

}

void HSBuyPropLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSBuyPropLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//m_pHSGameSceneRropManager->ccTouchBegan(pTouch,pEvent);
	return true;
}

void HSBuyPropLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBuyPropLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	//m_pHSGameSceneRropManager->ccTouchEnded(pTouch,pEvent);
}

void HSBuyPropLayer::keyBackClicked()
{

}
void HSBuyPropLayer::keyMenuClicked()
{

}

void HSBuyPropLayer::Call_Ok(CCObject* obj)
{
	HSGameScenePropSprite* sprite = HSGameScenePropSprite::GetTouchGameScenePropSprite();
	if (sprite)
	{
		sprite->Buy();
		//HSGameScenePropSprite::SetTouchGameScenePropSprite(NULL);
		HS_GAME_CACHE()->SetUseBackgroundID(sprite->m_PropInfo.id());

		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

		HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

		layer->removeChild(sprite->m_pSceneDialog,true);

		if (HS_GAME_CACHE()->IsRunGameGuide())
		{
			CCMenuItemImage* item = dynamic_cast<CCMenuItemImage*>(obj);
			HSGameGuide::ShaderGameGuide()->TriggerEvent(item->getPosition());
		}
	}
}

void HSBuyPropLayer::Call_Cancel(CCObject* obj)
{
	/**
	m_pDialogNode->setVisible(false);
	HSGameScenePropSprite::SetTouchGameScenePropSprite(NULL);*/

	if(!HS_GAME_CACHE()->IsRunGameGuide())
	{
		HSGameScenePropSprite* sprite = HSGameScenePropSprite::GetTouchGameScenePropSprite();
		if (sprite)
		{
			CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

			HSBuyPropLayer* layer = dynamic_cast<HSBuyPropScene*>(scene)->GetHSBuyPropLayer();

			layer->removeChild(sprite->m_pSceneDialog,true);
		}
	}

	
}
/************************************************************************/
/*         购买单个打折商品                                                             */
/************************************************************************/
void HSBuyPropLayer::Call_Buy1(CCObject* obj)
{
	int index = HS_GAME_CACHE()->GetPropIndex();

	const char* titleKey = CCString::createWithFormat("prop%d",index+1)->getCString();
	const char* discribKey = CCString::createWithFormat("prop%ddisc",index+1)->getCString();

	HSTool::ShareHSTool()->Buy(HS_CHEAP_PROP_ID(HS_GAME_CACHE()->GetPropIndex()),HS_GAME_CACHE()->GetPropInfoData()->cheappropinfolist(HS_GAME_CACHE()->GetPropIndex()).buymoney(),L(titleKey),L(discribKey));
	
	m_pBuyShopDialog->setVisible(false);

 
}
/************************************************************************/
/*             购买礼包                                                         */
/************************************************************************/
void HSBuyPropLayer::Call_Buy2(CCObject* obj)
{	 
	int index = HS_GAME_CACHE()->GetPropIndex();

	const char* titleKey = CCString::createWithFormat("prop%d",index+1)->getCString();
	const char* discribKey = CCString::createWithFormat("prop%dpack",index+1)->getCString();
	HSTool::ShareHSTool()->Buy(HS_GIFT_PROP_ID(HS_GAME_CACHE()->GetPropIndex()),HS_GAME_CACHE()->GetPropInfoData()->giftbagpropinfolist(HS_GAME_CACHE()->GetPropIndex()).buymoney(),L(titleKey),L(discribKey));

	m_pBuyShopDialog->setVisible(false);
}

void HSBuyPropLayer::CallBackMainScene(CCObject* obj)
{
	HS_GO_SCENE(HS_SCENE_GameMainScene);
}

void HSBuyPropLayer::CallShopLayer(CCObject* obj)
{
	if(m_pBuyShopDialog==NULL)
	{
		m_pBuyShopDialog = HSBuyShopDialog::create(this);
		this->addChild(m_pBuyShopDialog,10000);
	}
	else
	{
		m_pBuyShopDialog->setVisible(true);
	}
}

void HSBuyPropLayer::CallDestoryShop(CCObject* obj)
{	
	m_pBuyShopDialog->setVisible(false);
}

void HSBuyPropLayer::CallPropInfo(CCObject* obj)
{
	if(m_pBuyPropInfoDialog==NULL)
	{
		m_pBuyPropInfoDialog = HSBuyPropInfoDialog::create(this);
		this->addChild(m_pBuyPropInfoDialog,10000);
	}
	else
	{
		 m_pBuyPropInfoDialog->setVisible(true);
	}
}

void HSBuyPropLayer::CallDestoryPropInfo(CCObject* obj)
{
	 m_pBuyPropInfoDialog->setVisible(false);
}

void HSBuyPropLayer::Update( float dt )
{
	//更新金币
	if (m_curpGold != HS_GAME_CACHE()->GetGold())
	{
		m_curpGold =  HS_GAME_CACHE()->GetGold();
		m_pGameGold->setString(CCString::createWithFormat("%d",m_curpGold)->getCString());
		CCSize gameGoldPngSize = CCSizeMake(250.f,30.f);
		m_pGameGold->setPosition(ccp(gameGoldPngSize.width / 10,0));
	}
	/**
	if ( HSGameScenePropSprite::GetTouchGameScenePropSprite() )
	{
		m_pDialogNode->setVisible(true);
	}**/

	if(m_isCloseGuide)
	{
		if(HS_GAME_CACHE()->IsRunGameGuide())
		{
			HSGameGuide::ShaderGameGuide()->setVisible(false);
		}
	}
}




//Scene
HSBuyPropScene::HSBuyPropScene(void)
{
	this->hsBuyPropLayer = NULL;
}

HSBuyPropScene::~HSBuyPropScene(void)
{
}

bool HSBuyPropScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsBuyPropLayer = HSBuyPropLayer::create();
	this->addChild(this->hsBuyPropLayer,HS_BASE_TAG,HS_BASE_TAG);

	 
	if (HS_GAME_CACHE()->IsRunGameGuide() && HSGameGuide::ShaderGameGuide()->GetCurrentStep() == 11)
	{
		HSGameGuide::ShaderGameGuide()->Resume(this);
	}
	else
	{
		if(HS_GAME_CACHE()->IsRunGameGuide())
		{
			HSGameGuide* pGuide = HSGameGuide::ShaderGameGuide();
			this->addChild(pGuide,1000000);
			pGuide->Run();
		}
	}

	return true;
}



