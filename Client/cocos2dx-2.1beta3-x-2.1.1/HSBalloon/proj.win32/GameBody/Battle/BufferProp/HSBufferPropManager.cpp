#include "HSBufferPropManager.h"
#include "HSGameCache.h"
#include "HSBattleScene.h"


HSBufferPropManager::HSBufferPropManager(void)
{
	m_isHasBuffer = false;
}


HSBufferPropManager::~HSBufferPropManager(void)
{
}

bool HSBufferPropManager::init()
{
	HSBattleScene* scene = dynamic_cast<HSBattleScene*>( CCDirector::sharedDirector()->getRunningScene());
	if (!scene)
	{
		return false;
	}
	HSBattleLayer* layer = scene->GetHSBattleLayer();
	if (!layer)
	{
		return false;
	}

// 	const PropInfo* pBufferPropInfoData = HS_GAME_CACHE()->GetUseBufferPropData();
// 	if (pBufferPropInfoData)
// 	{
// 		if (pBufferPropInfoData->id() == Buffer_Porp_GoldErupt)
// 		{
// 			HSBufferProp_GoldErupt* p = HSBufferProp_GoldErupt::create();
// 			p->SetDurationTime(pBufferPropInfoData->duration());
// 			p->SetListerBufferBegin(layer,hs_call_buffer_Begin(HSBattleLayer::IsAllowRunBuffer));
// 			p->SetListerBufferEnd(layer,hs_call_buffer_End(HSBattleLayer::CallGoldErptEnd));
// 			this->addChild(p);
//			m_isHasBuffer = true;
// 		}
// 	}
	HSBufferProp_GoldErupt* p = HSBufferProp_GoldErupt::create();
	p->SetDurationTime(5.f);
	p->SetListerBufferBegin(layer,hs_call_buffer_Begin(HSBattleLayer::IsAllowRunBuffer));
	p->SetListerBufferEnd(layer,hs_call_buffer_End(HSBattleLayer::CallGoldErptEnd));
	this->addChild(p);
	m_isHasBuffer = false;

	return true;
}

bool HSBufferPropManager::IsHasBuffer()
{
	return m_isHasBuffer;
}
