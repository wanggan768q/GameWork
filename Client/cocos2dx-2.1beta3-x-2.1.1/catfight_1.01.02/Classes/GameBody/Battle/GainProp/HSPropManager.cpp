#include "HSPropManager.h"


HSPropManager::HSPropManager(void)
{
	this->Init();
}


HSPropManager::~HSPropManager(void)
{
}

void HSPropManager::Init()
{
	std::vector<const message::PropInfo*>* pFightingProp = &HSGameCache::ShareGameCache()->m_pFightingProp;
	std::vector<const message::PropInfo*>::iterator It = pFightingProp->begin();

	int pFightingPropSize = (int)pFightingProp->size();
	if (pFightingPropSize > 3)
	{
		HSMessageBox("pFightingPropSize > 3");
		return;
	}
	for (int i=0;i<(int)pFightingProp->size();++i)
	{
		CCSprite* pPropFrame = HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_Daojudituhei%d",i)->getCString(),"Daojudituhei");
		CCSprite* pPropMoneyFrame = HS_FIND_UI_PANEL_SPRITE(CCString::createWithFormat("UI_Xiaoanniushuzi%d",i)->getCString(),"zhandoudaojujiage");
		HSAssert(pPropFrame,"");
		CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
		CCLabelAtlas* pMoneyAtlas =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
		pMoneyAtlas->setAnchorPoint(HS_ANCHOR_CENTER);
		pMoneyAtlas->setPosition(HS_SizeHalf_Point(pPropMoneyFrame->getContentSize()));

		const message::PropInfo* pPropInfo = (*(It + i));
		switch (pPropInfo->proptype())
		{
		case PropInfo_PropType_ManualProp:
			{
				switch (pPropInfo->manualproptype())
				{
				case PropInfo_ManualPropType_MANUAL_PROPS_LaserGun:
					{
						HSProp_LaserGun* pLaserGun = HSProp_LaserGun::create(pPropInfo,i);
						pLaserGun->setPosition(HS_SizeHalf_Point(pPropFrame->getContentSize()));
						pPropFrame->addChild(pLaserGun);
					}
					break;
				default:
					HSMessageBox("Error manualproptype");
					break;
				}
			}
			break;
		case PropInfo_PropType_BufferProp:
			{
				switch (pPropInfo->bufferproptype())
				{
				case PropInfo_BufferPropType_BUFFER_PROPS_Chameleon:
					{
						HSProp_Chameleon* pChameleon = HSProp_Chameleon::create(pPropInfo,i);
						pChameleon->setPosition(HS_SizeHalf_Point(pPropFrame->getContentSize()));
						pPropFrame->addChild(pChameleon);
					}
					break;
				case PropInfo_BufferPropType_BUFFER_PROPS_Meidusha:
					{
						HSProp_Meidusha* pMeidusha = HSProp_Meidusha::create(pPropInfo,i);
						pMeidusha->setPosition(HS_SizeHalf_Point(pPropFrame->getContentSize()));
						pPropFrame->addChild(pMeidusha);

					}
					break;
				case PropInfo_BufferPropType_BUFFER_PROPS_EnergyShield:
					{
						HSProp_EnergyShield* pEnergyShield = HSProp_EnergyShield::create(pPropInfo,i);
						pEnergyShield->setPosition(HS_SizeHalf_Point(pPropFrame->getContentSize()));
						pPropFrame->addChild(pEnergyShield);

					}
					break;
				default:
					HSMessageBox("Error bufferproptype");
					break;
				}
			}
			break;
		}
		
		pMoneyAtlas->setString(CCString::createWithFormat(":%d",pPropInfo->gold())->getCString());
		pMoneyAtlas->setScale(0.7f);
		pPropMoneyFrame->addChild(pMoneyAtlas);
	}
}
