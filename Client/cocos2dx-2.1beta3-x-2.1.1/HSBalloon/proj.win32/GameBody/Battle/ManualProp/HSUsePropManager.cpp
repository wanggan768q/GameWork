#include "HSUsePropManager.h"


HSUsePropManager::HSUsePropManager(void)
{
}


HSUsePropManager::~HSUsePropManager(void)
{
}

HSUsePropManager* HSUsePropManager::create()
{
	HSUsePropManager* manager = new HSUsePropManager;
	if (manager && manager->Init())
	{
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return NULL;
}

bool HSUsePropManager::Init()
{
	int usePropCount = HS_GAME_CACHE_DATA()->useproplist_size();
	for (int i=0;i<usePropCount;++i)
	{
		bool isOk = false;
		const message::PropInfo* usePropInfo = &HS_GAME_CACHE_DATA()->useproplist(i);

		if (usePropInfo->id() == 0)
		{
			continue;
		}
		CCLog("UseProp: %d",usePropInfo->id());


		switch (usePropInfo->manualproptype())
		{
		case PropInfo_ManualPropType_BALLOON_PROPS_ChangeColorFullScreen :
			{
				if (HSProp_ChangeColorFullScreen::create(usePropInfo))
				{
					isOk = true;
				}
			}
			break;
		case PropInfo_ManualPropType_BALLOON_PROPS_Lightning :
			{
				if (HSProp_Lightning::create(usePropInfo))
				{
					isOk = true;
				}
			}
			break;
		case PropInfo_ManualPropType_BALLOON_PROPS_KingTime :
			{
				if (HSProp_KingTime::create(usePropInfo))
				{
					isOk = true;
				}
			}
			break;
		case PropInfo_ManualPropType_BALLOON_PROPS_StratagemLevelByZero :
			{
				if (HSProp_StratagemLevelByZero::create(usePropInfo))
				{
					isOk = true;
				}
			}
			break;
		default:
			break;
		}
		if (isOk == false)
		{
			HSMessageBox(usePropInfo->name() + " Create¡¡Error");
			return false;
		}
	}

	HS_MUTABLE_GAME_CACHE_DATA()->clear_useproplist();

	return true;
}
