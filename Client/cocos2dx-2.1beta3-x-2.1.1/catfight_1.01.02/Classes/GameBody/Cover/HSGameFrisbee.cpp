#include "HSGameFrisbee.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameCoverScene.h"
#include "HSGameGuide.h"
#include "HSAboutLayer.h"
#include "HSJava.h"

HSGameFrisbee::HSGameFrisbee(void)
{
	m_sate = Sate_Hide;
}


HSGameFrisbee::~HSGameFrisbee(void)
{
}

bool HSGameFrisbee::init()
{
	CCMenu* pSetingMenu = HS_FIND_UI_MENU("UI_HEbinggaojiduchangxin_Xitongtuibiao_01");

	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_shezhi_0",this,HSGameFrisbee::Call_Muisc);

	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_shezhi_1",this,HSGameFrisbee::Call_Sound);

	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_shezhi_2",this,HSGameFrisbee::Call_Help);

	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_shezhi_3",this,HSGameFrisbee::Call_About);

	for (int i=0;i<50;++i)
	{
		CCString* ui = CCString::createWithFormat("UI_HEbinggaojiduchangxin_shezhi_%d",i);
		CCMenu* otherMenu = HS_FIND_UI_MENU(ui->getCString());
		if (!otherMenu)
		{
			continue;
		}
		
		_MenuItem tempMenuItem;
		tempMenuItem.pNode = otherMenu;
		tempMenuItem.srcPos = pSetingMenu->getPosition();
		tempMenuItem.endPos = otherMenu->getPosition();
		m_menuList.push_back(tempMenuItem);

		otherMenu->setPosition(pSetingMenu->getPosition());
		otherMenu->setVisible(false);
	}

	CCArray* arraySound = HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent("UI_HEbinggaojiduchangxin_shezhi_1");

	CCObject* objSound = arraySound->objectAtIndex(0);

	CCMenuItemToggle* toggleSound = dynamic_cast<CCMenuItemToggle*>(objSound);

	if(toggleSound)
	{
		if(HS_GAME_CACHE_DATA()->issound())
		{
			toggleSound->setSelectedIndex(0);
			CCLOG("sound(0)");
		}
		else
		{
			CCLOG("sound(1)");
			toggleSound->setSelectedIndex(1);
		}
	}

	CCArray* arrayMusic = HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent("UI_HEbinggaojiduchangxin_shezhi_0");

	CCObject* objMusic = arrayMusic->objectAtIndex(0);

	CCMenuItemToggle* toggleMusic = dynamic_cast<CCMenuItemToggle*>(objMusic);

	if(toggleMusic)
	{
		if(HS_GAME_CACHE_DATA()->isbackgroundmusic())
		{
			CCLOG("music(0)");
			toggleMusic->setSelectedIndex(0);
		}
		else
		{
			CCLOG("music(1)");
			toggleMusic->setSelectedIndex(1);
		}
	}
	return true;
}

void HSGameFrisbee::Show()
{
	m_sate = Sate_Show;
	m_menuListIt = m_menuList.begin();
	for (int i=0;i<(int)m_menuList.size();++i)
	{
		_MenuItem tempMenuItem = *(m_menuListIt + i);
		this->RunAction(tempMenuItem);
	}
}

void HSGameFrisbee::Hide()
{
	m_sate = Sate_Hide;
	m_menuListRIt = m_menuList.rbegin();
	for (int i=0;i<(int)m_menuList.size();++i)
	{
		_MenuItem tempMenuItem = *(m_menuListRIt + i);
		this->RunAction(tempMenuItem);
	}
}

void HSGameFrisbee::RunAction( HSGameFrisbee::_MenuItem menuItem)
{
	CCPoint pos = CCPointZero;
	switch (m_sate)
	{
	case Sate_Show:
		{
			pos = menuItem.endPos;
		}
		break;
	case Sate_Hide:
		{
			pos = menuItem.srcPos;
		}
		break;
	}

	CCMoveTo* pMove = CCMoveTo::create(0.1f,pos);
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSGameFrisbee::Call));
	menuItem.pNode->runAction(CCSequence::create(pMove,pCall,NULL));
	menuItem.pNode->setVisible(true);
}

int HSGameFrisbee::GetSate()
{
	return m_sate;
}

void HSGameFrisbee::Call( CCNode* pNode )
{
	switch (m_sate)
	{
	case Sate_Show:
		{
			pNode->setVisible(true);
		}
		break;
	case Sate_Hide:
		{
			pNode->setVisible(false);
		}
		break;
	}
}

void HSGameFrisbee::Call_Sound( CCObject* obj )
{
    HS_Play_Sound("UI_button");

	bool isPlaySoundEffect= HS_GAME_CACHE_DATA()->issound();
	HS_MUTABLE_GAME_CACHE_DATA()->set_issound(!isPlaySoundEffect);
	HS_GAME_CACHE()->Save();
	HSSoundManage::ShareSoundManage()->SetIsPlayEffect(!isPlaySoundEffect);	
}

void HSGameFrisbee::Call_Muisc( CCObject* obj )
{
    HS_Play_Sound("UI_button");
	bool isPlayMusic = HS_GAME_CACHE_DATA()->isbackgroundmusic();
	HS_MUTABLE_GAME_CACHE_DATA()->set_isbackgroundmusic(!isPlayMusic);
	HS_GAME_CACHE()->Save();
	HSSoundManage::ShareSoundManage()->SetIsPlayMusic(!isPlayMusic);
}

void HSGameFrisbee::Call_Help( CCObject* obj )
{
    HS_Play_Sound("UI_button");
	HS_MUTABLE_GAME_CACHE_DATA()->set_isrungameguide(true);

//	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
//	HSGameCoverScene* pairScene = (HSGameCoverScene*)scene;
//	HSGameCoverLayer* coverLayer = pairScene->GetHSGameCoverLayer();
//	coverLayer->Call_GameGuide();
    HSGameGuide::ShaderGameGuide()->Reset();
	HS_GO_SCENE(HS_SCENE_CoverScene);
}

void HSGameFrisbee::Call_About( CCObject* obj )
{

		HSAboutLayer::ShareHSAboutLayer()->setVisible(true);

}
