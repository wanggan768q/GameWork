#include "HSBuyPropScene.h"

//Layer
HSBuyPropLayer::HSBuyPropLayer(void)
{
}

HSBuyPropLayer::~HSBuyPropLayer(void)
{
	HSReadUI::ShareReadUI()->Destroy();
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
	HSReadUI::ShareReadUI()->ReadUI("Image/BuyProp/BuyProp.data","Image/BuyProp/",this);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCTableView* tableView = CCTableView::create(this, CCSizeMake(920, 81));
	tableView->setDirection(kCCScrollViewDirectionHorizontal);
	tableView->setPosition(ccp(20,winSize.height/2-30));
	tableView->setDelegate(this);
	this->addChild(tableView);
	tableView->reloadData();
	
	int aa = 0;
}

void HSBuyPropLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSBuyPropLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSBuyPropLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBuyPropLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBuyPropLayer::keyBackClicked()
{

}
void HSBuyPropLayer::keyMenuClicked()
{

}

cocos2d::CCSize HSBuyPropLayer::cellSizeForTable( CCTableView *table )
{
	 return CCSizeMake(104, 81);
}

CCTableViewCell* HSBuyPropLayer::tableCellAtIndex( CCTableView *table, unsigned int idx )
{
	 CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new HSGameScenePropSprite();
		cell->autorelease();
		CCSprite *sprite = CCSprite::create("Image/animal_3.png");
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		cell->addChild(sprite);

		CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
		label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
		label->setTag(123);
		cell->addChild(label);
	}
	else
	{
		CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());
	}


	return cell;
}

unsigned int HSBuyPropLayer::numberOfCellsInTableView( CCTableView *table )
{
	 return 20;
}

void HSBuyPropLayer::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}

void HSBuyPropLayer::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}

void HSBuyPropLayer::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{

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

	return true;
}