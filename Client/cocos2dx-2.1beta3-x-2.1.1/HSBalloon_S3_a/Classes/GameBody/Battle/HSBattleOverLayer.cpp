#include "HSBattleOverLayer.h"
#include "HSEffectItemSprite.h"
#include "HSGamePairScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameGuide.h"

HSBattleOverLayer::HSBattleOverLayer(void)
{
	m_iswin = false;
	m_count =0;
}

HSBattleOverLayer::~HSBattleOverLayer(void)
{
	m_activeParticleArray.clear();
	m_EffectItemSpriteArray.clear();
}

bool HSBattleOverLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	HSTool::SetLayerScale(this);
	Load();
	//this->setTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSBattleOverLayer::Load()
{
	CCLayerColor* pLayerColor = CCLayerColor::create(ccc4(0,0,0,200),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	HSTool::SetNodeFilldScreen(pLayerColor);
	this->addChild(pLayerColor);
	HSReadUI::ShareReadUI()->ReadUI("Image/battle/battleOver/battleOver.data","Image/battle/battleOver/",this);
	HS_SET_MENU_TARGET("UI_Jinxu1_01",this,HSBattleOverLayer::Call_Continue);
	CCMenu* jixu = HS_FIND_UI_MENU("UI_Hebing_Jinxu_01");
	jixu->setVisible(false);
	this->schedule(schedule_selector(HSBattleOverLayer::Update));

	m_interval = HSMath::Random(0.05,0.3);

}

void HSBattleOverLayer::Update(float dt)
{
	if(m_iswin)
	{
		m_count +=dt;
		if(m_count> m_interval)
		{
			m_interval = HSMath::Random(0.05,0.3);
			m_count = 0;

			bool add = false;
			int count = m_activeParticleArray.size();
			for(int i=0; i < count; i++)
			{
				if(m_activeParticleArray[i])
				{
					if(!m_activeParticleArray[i]->isActive())
					{
						m_activeParticleArray[i]->setPosition(GetRandomPosition());
						m_activeParticleArray[i]->resetSystem();
						add = true;
						break;
					}
				}
			}

			if(!add)
			{
				CCParticleSystemQuad* pParticle = CCParticleSystemQuad::create("Image/battle/battleOver/win.plist");
				pParticle->setPosition(GetRandomPosition());
				 
				this->addChild(pParticle,1100);
				m_activeParticleArray.push_back(pParticle);
			}
		}
	}
}

CCPoint HSBattleOverLayer::GetRandomPosition()
{
	float x = HSMath::Random(120,960-120*2);
	float y = HSMath::Random(400,400+330);

	return ccp(x,y);
}

void HSBattleOverLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSBattleOverLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSBattleOverLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleOverLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleOverLayer::keyBackClicked()
{

}
void HSBattleOverLayer::keyMenuClicked()
{

}

void HSBattleOverLayer::SetIsWin(bool win)
{
	HSCCSprite* winSprite = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Shengli","Shengli");

	HSCCSprite* loseSprite = HS_FIND_UI_PANEL_SPRITE("UI_Shibai","Shibai");

	CCMenu* jixu = HS_FIND_UI_MENU("UI_Jinxu1_01");

	HS_Play_Sound("coin_effect");

	if(win)
	{
		loseSprite->setVisible(false);

		winSprite->setVisible(true);

		m_iswin = true;

		HSCCSprite* panle1 = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Daojujiguang","Daojujiguang");
		HSEffectItemSprite* effectItem1 = HSEffectItemSprite::create(HS_GAME_CACHE()->GetPropInfoData()->effectpropinfolist(0),0);
		panle1->addChild(effectItem1);
		m_EffectItemSpriteArray.push_back(effectItem1);

		HSCCSprite* panle2 = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Daojujiguang01","Daojujiguang");
		HSEffectItemSprite* effectItem2 = HSEffectItemSprite::create(HS_GAME_CACHE()->GetPropInfoData()->effectpropinfolist(1),1);
		panle2->addChild(effectItem2);
		m_EffectItemSpriteArray.push_back(effectItem2);

		HSCCSprite* panle3 = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Daojujiguang02","Daojujiguang");
		HSEffectItemSprite* effectItem3 = HSEffectItemSprite::create(HS_GAME_CACHE()->GetPropInfoData()->effectpropinfolist(2),2);
		panle3->addChild(effectItem3);
		m_EffectItemSpriteArray.push_back(effectItem3);

		HS_Play_Sound("win_effect");
	}
	else
	{
		loseSprite->setVisible(true);

		winSprite->setVisible(false);

		CCPoint losePosition = loseSprite->getPosition();
		
		loseSprite->setPosition(ccp(losePosition.x,losePosition.y-200));

		CCPoint jixuPosition = jixu->getPosition();

		jixu->setPosition(ccp(jixuPosition.x,jixuPosition.y-200));

		

		HSCCSprite* panle1 = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Daojujiguang","Daojujiguang");
		HSCCSprite* panle2 = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Daojujiguang01","Daojujiguang");
		HSCCSprite* panle3 = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Daojujiguang02","Daojujiguang");
		panle1->setVisible(false);
		panle2->setVisible(false);
		panle3->setVisible(false);

		HSCCSprite* bell1 =  HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Lingdangxiao","Lingdangxiao");
		HSCCSprite* bell2 =  HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Lingdangxiao1","Lingdangxiao");
		HSCCSprite* bell3 =  HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Lingdangxiao2","Lingdangxiao");
		bell1->setVisible(false);
		bell2->setVisible(false);
		bell3->setVisible(false);

		HSCCSprite* title = HS_FIND_UI_PANEL_SPRITE("UI_Hebing_Duitashiyongmaziti","Duitashiyongmaziti");
		title->setVisible(false);

		HS_Play_Sound("lose_effect");
	}


	
}

void HSBattleOverLayer::Call_Continue(CCObject* obj)
{
	if (HS_IsRunGameGuide())
	{
		CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(obj);
		pItem->setEnabled(false);
		HSGameGuide::ShaderGameGuide()->Pause();
		HS_GO_SCENE(HS_SCENE_GamePairScene);
		return;
	}
	Return();
}

void HSBattleOverLayer::Return()
{
	if (HS_IsRunGameGuide())
	{
		HSGameGuide::ShaderGameGuide()->Pause();
	}

	HSGamePairScene::s_status=status_again;

	m_iswin = false;

// 	while(m_activeParticleArray.size())
// 	{	
// 		m_activeParticleArray.back()->removeFromParentAndCleanup(true);
// 		/*m_activeParticleArray.pop_back();*/
// 	}
	HS_Play_Music("back_01");
	HS_GO_SCENE(HS_SCENE_GamePairScene);
}

