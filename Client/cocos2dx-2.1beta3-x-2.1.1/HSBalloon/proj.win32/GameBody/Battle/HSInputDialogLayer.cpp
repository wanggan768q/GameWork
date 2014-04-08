#include "HSInputDialogLayer.h"


HSInputDialogLayer::HSInputDialogLayer(void)
{

}


HSInputDialogLayer::~HSInputDialogLayer(void)
{
}

bool HSInputDialogLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	Load();
	this->setTouchEnabled(true);

	//this->setKeypadEnabled(true);

	return true;
}

void HSInputDialogLayer::Load()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/InputFrame/InputFrame.data","Image/InputFrame/",this);

	HS_SET_MENU_TARGET("UI_QueDing_01",this,HSInputDialogLayer::CallYes);
	HS_SET_MENU_TARGET("UI_FouDing_01",this,HSInputDialogLayer::CallNo);

	HSCCSprite* inputSprite = HS_FIND_UI_PANEL_SPRITE("UI_JinBiTiao","x_JinBiTiao");

	m_InputRect.origin = ccp(154,511);
	m_InputRect.size = inputSprite->getContentSize();
	HSTool::SetRectScale(m_InputRect);

	m_pTextFieldTTF = CCTextFieldTTF::textFieldWithPlaceHolder(L("input"),inputSprite->getContentSize(),kCCTextAlignmentCenter,"Thonburi",55.f);
	m_pTextFieldTTF->setPosition(HS_SizeHalf_Point(inputSprite->getContentSize()));
	inputSprite->addChild(m_pTextFieldTTF);

	//this->setPosition(HSBase::GetTemplateScreenCentre());
}

void HSInputDialogLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSInputDialogLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint view = pTouch->getLocationInView();
	view.y += 55.f * 1.f;
	
	if (m_InputRect.containsPoint(view))
	{
		m_pTextFieldTTF->attachWithIME();
	}else{
		m_pTextFieldTTF->detachWithIME();
	}
	
	return true;
}

void HSInputDialogLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSInputDialogLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSInputDialogLayer::keyBackClicked()
{

}

void HSInputDialogLayer::keyMenuClicked()
{

}

void HSInputDialogLayer::setVisible( bool visible )
{
	CCLayer::setVisible(visible);
}

void HSInputDialogLayer::CallYes( CCObject* obj )
{
	const char* name = m_pTextFieldTTF->getString();

	if(name==NULL || strlen(name)==0)
	{
		HSMessageBox("");
	}
	else
	{
		HSRequest::ShareRequest()->SendRegisterRequest(m_pTextFieldTTF->getString());
	}

	
}

void HSInputDialogLayer::CallNo( CCObject* obj )
{
	setVisible(false);
}

void HSInputDialogLayer::ResponseRegister( RegisterResponse* pMsg )
{
	HS_GAME_CACHE()->SetUserInfo(pMsg->username().c_str(),pMsg->uid());

	setVisible(false);

	this->getParent()->setVisible(true);
}
