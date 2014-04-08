#include "HSInputDialogLayer.h"
#include "HSGameSceneJumpManage.h"

HSInputDialogLayer::HSInputDialogLayer(void)
{
	m_nickname = NULL;
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
	CCLayerColor* pMaskLayer = CCLayerColor::create(ccc4(0,0,0,200),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
	this->addChild(pMaskLayer);
	HSTool::SetNodeFilldScreen(pMaskLayer);

	HSReadUI::ShareReadUI()->ReadUI("Image/InputFrame.data","Image/",this);

	HS_SET_MENU_TARGET("UI_zhuceanniu",this,HSInputDialogLayer::CallYes);

	HSCCSprite* inputSprite = HS_FIND_UI_PANEL_SPRITE("UI_zhucejiemian","zhucewenbendikuang");

	m_InputRect.origin = ccp(154,511);
	m_InputRect.size = inputSprite->getContentSize();
	HSTool::SetRectScale(m_InputRect);

	m_pTextFieldTTF = CCTextFieldTTF::textFieldWithPlaceHolder(L("input"),CCSizeMake(inputSprite->getContentSize().width,40.f),kCCTextAlignmentCenter,"",30.f);
	m_pTextFieldTTF->setColor(ccc3(0,0,0));
	m_pTextFieldTTF->setPosition(HS_SizeHalf_Point(inputSprite->getContentSize()));
	inputSprite->addChild(m_pTextFieldTTF);
}

void HSInputDialogLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSInputDialogLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint view = pTouch->getLocationInView();
	view.y += 30.f * 1.f;
	
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

	if(name == NULL || strlen(name) == 0)
	{
		HSMessageBox("");
	}
	else
	{
		HS_MUTABLE_GAME_CACHE_DATA()->set_nickname(m_pTextFieldTTF->getString());
		HS_MUTABLE_TARGET_SELF()->set_name(m_pTextFieldTTF->getString());
// 		if (HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_D_Logic))
// 		{
// 			HSRequest::ShareRequest()->SendUserInfoUpdateRequest_Name(m_pTextFieldTTF->getString());
// 		}
//		if (HS_IsRunGameGuide())
//		{
//			HS_MUTABLE_GAME_CACHE_DATA()->set_isrungameguide(false);
//		}
		HS_GAME_CACHE()->Save();
		HS_GO_SCENE(HS_SCENE_StartGameScene);
	}
}

void HSInputDialogLayer::ResponseRegister( RegisterResponse* pMsg )
{
	//HS_GAME_CACHE()->SetUserInfo(pMsg->username().c_str(),pMsg->uid());

	//setVisible(false);

	this->getParent()->setVisible(true);
}