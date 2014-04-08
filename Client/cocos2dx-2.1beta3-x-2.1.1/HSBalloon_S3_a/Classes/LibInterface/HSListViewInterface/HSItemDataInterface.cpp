#include "HSItemDataInterface.h"

HS_namespace_HSListViewControl_Begin

HSItemDataInterface::HSItemDataInterface(const CCSize& itemSize,int onceCount)
{
	m_itemSize = itemSize;
	m_itemCount = onceCount;
}


HSItemDataInterface::~HSItemDataInterface(void)
{
}

cocos2d::CCSize HSItemDataInterface::cellSizeForTable( CCTableView *table )
{
	return m_itemSize;
}

CCTableViewCell* HSItemDataInterface::tableCellAtIndex( CCTableView *table, unsigned int idx )
{
	//CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *pCell = table->dequeueCell();
	if (!pCell) 
	{
		pCell = HSCellInterface::create();

		CCNode* pItem = this->AddItem(idx);

		pCell->addChild(pItem);
	}
	else
	{
		//CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(1001);
		//label->setString(string->getCString());
		HSCellInterface* pTempCell = dynamic_cast<HSCellInterface*>(pCell);
		if (pTempCell)
		{
			this->UpdataItem(pTempCell->GetChild(),idx);
		}
	}

	//CCLog("Bule   %s",string->getCString());
	return pCell;
}

unsigned int HSItemDataInterface::numberOfCellsInTableView( CCTableView *table )
{
	return m_itemCount;
}

HS_namespace_HSListViewControl_End