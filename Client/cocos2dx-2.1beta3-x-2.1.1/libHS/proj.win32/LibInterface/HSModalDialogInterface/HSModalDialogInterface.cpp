#include "HSModalDialogInterface.h"


HSModalDialogInterface::HSModalDialogInterface(void)
{
	m_pMenu = NULL;
	m_pMenuItemArray = NULL;
	m_isTouchedMenu = false;
}


HSModalDialogInterface::~HSModalDialogInterface(void)
{
}

bool HSModalDialogInterface::init()
{
	if(InitBackground() && InitDialog() && InitMenu())
	{
		return true;
	}
	return false;
}

bool HSModalDialogInterface::InitMenu()
{
	if (m_pMenuItemArray && m_pMenuItemArray->count() > 0) 
	{
		if (!m_pMenu)
		{
			m_pMenu = CCMenu::createWithArray(m_pMenuItemArray);
			m_pMenu->setPosition(CCPointZero);
			this->addChild(m_pMenu,2000);
		}
	}
	return true;
}

bool HSModalDialogInterface::InitBackground()
{
	this->initWithColor(ccc4(0, 0, 0, 125),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	return true;
}

void HSModalDialogInterface::SetBackground( CCLayer* pLayer )
{
	if (m_pBackground)
	{
		this->removeChild(m_pBackground,true);
	}
	m_pBackground = pLayer;
	this->addChild(m_pBackground,1000);
}

void HSModalDialogInterface::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void HSModalDialogInterface::onExit()
{
	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void HSModalDialogInterface::PushMenu( CCMenuItem *pItem )
{
	if (!m_pMenuItemArray)
	{
		m_pMenuItemArray = CCArray::create();
	}
	m_pMenuItemArray->addObject(pItem);
}

void HSModalDialogInterface::PushMenu( CCArray* pArray )
{
	HSAssert(pArray,"");
	for (unsigned int i=0;i<pArray->count();++i)
	{
		CCObject* obj = pArray->objectAtIndex(i);
		CCMenuItem* menuItem = dynamic_cast<CCMenuItem*>(obj);
		HSAssert(menuItem,"menuItem == NULL");
		this->PushMenu(menuItem);
	}
}

bool HSModalDialogInterface::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (m_pMenu) 
	{
		m_isTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
	}
	if(this->isVisible())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void HSModalDialogInterface::ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (m_isTouchedMenu) 
	{
		if (m_pMenu) 
		{
			m_pMenu->ccTouchMoved(pTouch, pEvent);
		}
	}
}

void HSModalDialogInterface::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (m_isTouchedMenu) 
	{
		if (m_pMenu) {
			m_pMenu->ccTouchEnded(pTouch, pEvent);
		}
		m_isTouchedMenu = false;
	}
}

void HSModalDialogInterface::ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	if (m_isTouchedMenu) 
	{
		if (m_pMenu) 
		{
			m_pMenu->ccTouchEnded(pTouch, pEvent);
		}
		m_isTouchedMenu = false;
	}
}


