#include "HSStartGameScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameCache.h"
#include "HSDailyRewardSystemLayer.h"
#include "HSPairSystemScene.h"
#include "HSNetworkDialog.h"

bool HSStartGameLayer::S_IS_SHOW_DIALOG = false;

//Layer
HSStartGameLayer::HSStartGameLayer(void)
{
    m_pFriendsListView = NULL;
    m_pPlayerICON = NULL;
}

HSStartGameLayer::~HSStartGameLayer(void)
{
}

bool HSStartGameLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
    Load();
	//this->setIsTouchEnabled(true);
    
	//this->setKeypadEnabled(true);
    
	return true;
}

void HSStartGameLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/StartGame.data","Image/",this);
    
    //显示金币
    this->addChild(HSShowGlobal::create());
    
    //显示体力
    m_pShowEndurance = HSShowEndurance::create();
    this->addChild(m_pShowEndurance);
    
    //购买体力
    HS_SET_MENU_TARGET("UI_Benfangxinxiban_Nailijishiqi_Nailizengjia", this, HSStartGameLayer::Call_BuyEndurance);
    //开始战斗
    HS_SET_MENU_TARGET("UI_Kaishizhandou", this, HSStartGameLayer::Call_StartGame);
    //添加好友
    HS_SET_MENU_TARGET("UI_Tianjiahaoyou", this, HSStartGameLayer::Call_AddressBook);
    //设置
    HS_SET_MENU_TARGET("UI_Shezhi", this, HSStartGameLayer::Call_Setting);
    //邮件
    HS_SET_MENU_TARGET("UI_Youjian_Youjian", this, HSStartGameLayer::Call_OpenEmail);
    //个人信息
    HS_SET_MENU_TARGET("UI_Gerenxinxi", this, HSStartGameLayer::Call_PlayerInfo);
    //成就
    HS_SET_MENU_TARGET("UI_Haoyoudiban_Kaishichengjiuanniu", this, HSStartGameLayer::Call_Achievemen);
    
    //更新用户形象
    this->UpdataPlayerIcon();
    //更新好友
    this->UpdataFriend();
    //更新邮件提示通知
    this->UpdataEmail();
    
    this->schedule(schedule_selector(HSStartGameLayer::Updata));
    this->scheduleOnce(schedule_selector(HSStartGameLayer::First),0);
    
    
    
    HSPairSystemLayer::S_IS_CREATE_BATTLE_SERVER = false;

}

void HSStartGameLayer::First(float dt)
{
    if(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID() != HS_SCENE_GameMainScene)
    {
        HSRequest::ShareRequest()->SendGameSearchStrengthRequest();
        HSRequest::ShareRequest()->SendSearchUserInfoRequest();
    }
    if(HSStartGameLayer::S_IS_SHOW_DIALOG)
    {
        HSStartGameLayer::S_IS_SHOW_DIALOG =false;
        HSNetworkDialog::ShareNetworkDialog()->Show();
    }
}

void HSStartGameLayer::UpdataPlayerIcon()
{
    if(!m_pPlayerICON)
    {
        if(HS_TARGET_SELF().uid().size() > 30)
        {
            CCNode* pFrame =  HS_FIND_UI_PANEL("UI_Gerenxingxiang");
            CCString* pFileName = CCString::createWithFormat("Image/%d_FIGURE.png",HS_TARGET_SELF().figureid());
            m_pPlayerICON = HSCCSprite::create(pFileName->getCString());
            m_pPlayerICON->setPosition(pFrame->getPosition());
            this->addChild(m_pPlayerICON,1100);
        }
    }
}

void HSStartGameLayer::UpdataFriend()
{
    if(!m_pFriendsListView)
    {
        //更新好友列表
        int friendCount = HS_GAME_CACHE()->m_FriendListResponse.friendlist_size();
        if (friendCount != 0 && !m_pFriendsListView)
        {
            CCSprite* pFriendFrame = HS_FIND_UI_PANEL_SPRITE("UI_Haoyoulanfanwei","Kaishihaoyoulanfanwei");
            m_pFriendsListView = HSFriendsListVeiw::create(pFriendFrame->getContentSize(),CCSizeMake(568,96),friendCount + 1);
            CCPoint pos = CCPointZero;
            pos.y = pFriendFrame->getPosition().y - pFriendFrame->getContentSize().height / 2.f;
            m_pFriendsListView->setPosition(pos);
            pFriendFrame->getParent()->addChild(m_pFriendsListView,1100);
            m_pFriendsListView->reloadData();
        }
    }
}

void HSStartGameLayer::UpdataEmail()
{
    CCNode* pNode = HS_FIND_UI_PANEL_SPRITE("UI_Youjian", "Kaishiyoujianjiaobiao");
    int emailCount = HS_GAME_CACHE()->m_EmailResponse.emaillist_size();
    if(HS_GAME_CACHE_DATA()->isaccepttrophynotification())
    {
        if(emailCount > 0)
        {
            if(HS_GAME_CACHE_DATA()->isaccepttrophynotification())
            {
                pNode->setVisible(true);
            }else{
                pNode->setVisible(false);
            }
        }else{
            pNode->setVisible(false);
        }
    }
}

void HSStartGameLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSStartGameLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSStartGameLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSStartGameLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSStartGameLayer::keyBackClicked()
{
    
}
void HSStartGameLayer::keyMenuClicked()
{
    
}

void HSStartGameLayer::Call_BuyEndurance(CCObject* obj)
{
    CCLog("购买体力");
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }
    HS_GO_SCENE(HS_SCENE_ShopScene);
}

void HSStartGameLayer::Call_PlayerInfo(CCObject* obj)
{
    CCLog("个人信息");
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }
    HS_GO_SCENE(HS_SCENE_FigureSystemScene);
}

void HSStartGameLayer::Call_Achievemen(CCObject* obj)
{
    CCLog("成就");
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }

    HS_GO_SCENE(HS_SCENE_AchievemenScene);
}

void HSStartGameLayer::Call_Setting(CCObject* obj)
{
    CCLog("设置");
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }

    HS_GO_SCENE(HS_SCENE_SettingScene);
}

void HSStartGameLayer::Call_AddressBook(CCObject* obj)
{
    CCLog("邀请");
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }

    HS_GO_SCENE(HS_SCENE_AddressBookScene);
}

void HSStartGameLayer::Call_OpenEmail(CCObject* obj)
{
    CCLog("邮件");
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }

    HS_GO_SCENE(HS_SCENE_EmailSystemScene);
}

void HSStartGameLayer::Call_StartGame(CCObject* obj)
{
    CCLog("开始游戏");
    HS_Play_Sound("UI_button");
    if(m_pShowEndurance)
    {
        m_pShowEndurance->Call_DestroySelector();
    }

    
    CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(obj);
    pItem->setEnabled(false);
    
    HSRequest::ShareRequest()->SendValidateStrengthRequest();
}

void HSStartGameLayer::ResponseValidateStrength(ValidateStrengthResponse* pMsg)
{
    switch (pMsg->result())
    {
        case message::ValidateStrengthResponse_RESULT_TYPE_OK:
        {
            HS_GO_SCENE(HS_SCENE_PairSystemScene);
            
        }
            break;
        case message::ValidateStrengthResponse_RESULT_TYPE_NOT:
        {
            CCLog("体力不够");
            
            HSSocket* s = HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle);
            if(s)
            {
                s->Closed(Close_Active);
                HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
            }
            
            HS_GO_SCENE(HS_SCENE_StartGameScene);
        }
            break;
        default:
            break;
    }
}

void HSStartGameLayer::Updata(float dt)
{
    this->UpdataFriend();
    
    this->UpdataPlayerIcon();
}






















//Scene
HSStartGameScene::HSStartGameScene(void)
{
	this->m_pHSStartGameLayer = NULL;
}

HSStartGameScene::~HSStartGameScene(void)
{
}

bool HSStartGameScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->m_pHSStartGameLayer = HSStartGameLayer::create();
	this->addChild(this->m_pHSStartGameLayer,HS_BASE_TAG,HS_BASE_TAG);
    
    if (HS_GAME_CACHE()->m_DailyRewardSystemData.dailyrewardlist_size() > 0)
    {
        HSDailyRewardSystemLayer* pDaily = HSDailyRewardSystemLayer::create();
        this->addChild(pDaily,HS_BASE_TAG + 1);
    }
    
	//this->addChild(HSAchievemenScene::create(),HS_BASE_TAG,HS_BASE_TAG);
    
	return true;
}


