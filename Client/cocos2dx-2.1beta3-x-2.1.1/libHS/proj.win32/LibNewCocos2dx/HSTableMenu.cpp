#include "HSTableMenu.h"


HSTableMenu::HSTableMenu(void)
{
	m_selectItemIndex = 0;
	m_tagCount = 0;
}


HSTableMenu::~HSTableMenu(void)
{
}

void HSTableMenu::AddItem( CCMenuItem* pItem )
{
	m_menuItemList.push_back(pItem);
	pItem->setTag(m_tagCount++);
	this->addChild(pItem);
	//this->alignItemsHorizontally();
}

void HSTableMenu::SetSelect( int index )
{
	int count = (int)m_menuItemList.size();
	HSAssert(index < count,"");
	for (int i=0;i<count;++i)
	{
		CCMenuItem* pItem = *(m_menuItemList.begin() + i);
		if ( i == index)
		{
			pItem->selected();
		}else{
			pItem->unselected();
			pItem->activate();
		}
	}
	m_selectItemIndex = index;
}

int HSTableMenu::GetSelect()
{
	return m_selectItemIndex;
}

bool HSTableMenu::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !m_bEnabled)
	{
		return false;
	}

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		//m_pSelectedItem->selected();
		int count = (int)m_menuItemList.size();
		for (int i=0;i<count;++i)
		{
			CCMenuItem* pItem = *(m_menuItemList.begin() + i);
			if (m_pSelectedItem == pItem)
			{
				m_pSelectedItem->selected();
			}else{
				pItem->unselected();
				pItem->activate();
			}
		}

		return true;
	}
	return false;
}

void HSTableMenu::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
/*

	if (m_pSelectedItem)
	{
		m_pSelectedItem->unselected();
		m_pSelectedItem->activate();
	}
*/

	m_eState = kCCMenuStateWaiting;
}
