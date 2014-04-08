//
//  HSLanActionManager.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 14-1-17.
//
//

#include "HSLanActionManager.h"

static HSLanActionManager* s_HSLanActionManager = NULL;

HSLanActionManager::HSLanActionManager()
{
    m_RestoreWIFI = Lan_Action_Status_Success;
    
    m_SearchRoom = Lan_Action_Status_Invalid;
    
    m_CreateRoom = Lan_Action_Status_Invalid;
    
    m_JoinRoom = Lan_Action_Status_Invalid;
    
    m_QuitRoom = Lan_Action_Status_Invalid;
    
    m_Exception = Lan_Action_Status_Invalid;
    
    m_currentLanAction = Lan_Action_Unknow;
}

HSLanActionManager::~HSLanActionManager()
{
    
}

HSLanActionManager* HSLanActionManager::ShareLanActionManager()
{
    if(!s_HSLanActionManager)
    {
        s_HSLanActionManager = new HSLanActionManager();
        s_HSLanActionManager->Init();
        s_HSLanActionManager->autorelease();
        s_HSLanActionManager->retain();
    }
    return s_HSLanActionManager;
    
    
}

bool HSLanActionManager::Init()
{
    m_currentLanAction = Lan_Action_Unknow;
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HSLanActionManager::Updata), this, 1.f, false);
    return true;
}

void HSLanActionManager::Destroy()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    CC_SAFE_RELEASE_NULL(s_HSLanActionManager);
}

void HSLanActionManager::AddAction(HSLanAction action)
{
    //m_actions.push(action);
    m_currentLanAction = action;
    switch (action)
    {
        case Lan_Action_Unknow:
            
            break;
        case Lan_Action_RestoreWIFI:
            m_RestoreWIFI = Lan_Action_Status_Runing;
            break;
        case Lan_Action_SearchRoom:
            m_SearchRoom = Lan_Action_Status_Runing;
            break;
        case Lan_Action_CreateRoom:
            m_CreateRoom = Lan_Action_Status_Runing;
            break;
        case Lan_Action_JoinRoom:
            m_JoinRoom = Lan_Action_Status_Runing;
            break;
        case Lan_Action_QuitRoom:
            m_QuitRoom = Lan_Action_Status_Runing;
            break;
        case Lan_Action_Exception:
            m_Exception = Lan_Action_Status_Runing;
            break;
        default:
            break;
    }
}

void HSLanActionManager::Pop()
{
    this->ShowCurrentAction();
    
    CCLog("\n########## Pop Begin ################\n");
    
    CCLog("移除 : %s",GetCurrentAction(m_currentLanAction));
    
    CCLog("\n########## Pop End   ################\n");
    m_currentLanAction = Lan_Action_Unknow;
}

//Lan_Action_Success  = 0,
//Lan_Action_Fail     = 1,
//Lan_Action_Runing   = 2,

const char* HSLanActionManager::GetActionStatus(HSLanActionStatus actionStatus)
{
    switch (actionStatus)
    {
        case Lan_Action_Status_Invalid:
            
            return "无效状态";
        case Lan_Action_Status_Success:
            
            return "成功";
        case Lan_Action_Status_Fail:
            
            return "失败";
        case Lan_Action_Status_Runing:
            
            return "执行中";
    }
    return "";
}

const char* HSLanActionManager::GetCurrentAction(HSLanAction action)
{
    switch (action)
    {
        case Lan_Action_Unknow:
            
            return "Lan_Action_Unknow";
        case Lan_Action_RestoreWIFI:
            
            return "恢复WIFI";
        case Lan_Action_SearchRoom:
            
            return "搜索房间";
        case Lan_Action_CreateRoom:
            
            return "创建房间";
        case Lan_Action_JoinRoom:
            
            return "加入房间";
        case Lan_Action_QuitRoom:
            
            return "退出房间";
        case Lan_Action_Exception:
            
            return "异常";
            
        default:
            return "";
    }
}

void HSLanActionManager::ShowAllActionInfo()
{
    CCLog("\n########## ShowAllActionInfo Begin ################\n");
    if (m_currentLanAction == Lan_Action_Unknow)
    {
        CCLog("当前操作 Lan_Action_Unknow");
        return;
    }
    
    for (int action = Lan_Action_RestoreWIFI; action <= Lan_Action_Exception; ++action)
    {
        ShowActionInfo( (HSLanAction)action  );
    }
    
    CCLog("\n########## ShowAllActionInfo End  ################\n");
}

void HSLanActionManager::ShowCurrentAction()
{
    CCLog("\n########## ShowCurrentAction Begin [ %s ] ################\n", this->GetCurrentAction(m_currentLanAction));
    
    if (m_currentLanAction == Lan_Action_Unknow)
    {
        CCLog("当前操作 Lan_Action_Unknow");
        return;
    }
    
    ShowActionInfo(m_currentLanAction);
    
    CCLog("\n########## ShowCurrentAction End   [ %s ] ################\n", this->GetCurrentAction(m_currentLanAction));
}

void HSLanActionManager::ShowActionInfo(HSLanAction action)
{
    //    Lan_Action_Unknow       = 0,
    //    Lan_Action_RestoreWIFI,
    //    Lan_Action_SearchRoom,
    //    Lan_Action_CreateRoom,
    //    Lan_Action_JoinRoom,
    //    Lan_Action_QuitRoom,
    //    Lan_Action_Exception,
    

    switch (action)
    {
        case Lan_Action_RestoreWIFI:
        {
            CCLog(" %s : %s",GetCurrentAction(m_currentLanAction),GetActionStatus(m_RestoreWIFI));
        }
            break;
        case Lan_Action_SearchRoom:
        {
            CCLog(" %s : %s",GetCurrentAction(m_currentLanAction),GetActionStatus(m_SearchRoom));
            
            CCLog("{\n");
            CCLog(" %s : %s",GetCurrentAction(Lan_Action_RestoreWIFI),GetActionStatus(m_RestoreWIFI));
            CCLog("}\n");
        }
            break;
        case Lan_Action_CreateRoom:
        {
            CCLog(" %s : %s",GetCurrentAction(m_currentLanAction),GetActionStatus(m_CreateRoom));
            
            CCLog("{\n");
            CCLog(" %s : %s",GetCurrentAction(Lan_Action_RestoreWIFI),GetActionStatus(m_RestoreWIFI));
            CCLog("}\n");
        }
            break;
        case Lan_Action_JoinRoom:
        {
            CCLog(" %s : %s",GetCurrentAction(m_currentLanAction),GetActionStatus(m_JoinRoom));
            
            CCLog("{\n");
            CCLog(" %s : %s",GetCurrentAction(Lan_Action_RestoreWIFI),GetActionStatus(m_RestoreWIFI));
            CCLog("}\n");
        }
            break;
        case Lan_Action_QuitRoom:
        {
            CCLog(" %s : %s",GetCurrentAction(m_currentLanAction),GetActionStatus(m_QuitRoom));
            
            CCLog("{\n");
            CCLog(" %s : %s",GetCurrentAction(Lan_Action_RestoreWIFI),GetActionStatus(m_RestoreWIFI));
            CCLog(" %s : %s",GetCurrentAction(Lan_Action_CreateRoom),GetActionStatus(m_CreateRoom));
            CCLog("}\n");
        }
            break;
        case Lan_Action_Exception:
        {
            CCLog(" %s : %s",GetCurrentAction(m_currentLanAction),GetActionStatus(m_Exception));
        }
            break;
            
        default:
            break;
    }
}


void HSLanActionManager::Updata(float dt)
{
    static float tempTime = 0.f;
    
    tempTime += dt;
    
    //this->ShowCurrentAction();
    
    if (tempTime > 5.f)
    {
        tempTime = 0.f;
        //this->ShowAllActionInfo();
    }
}

























