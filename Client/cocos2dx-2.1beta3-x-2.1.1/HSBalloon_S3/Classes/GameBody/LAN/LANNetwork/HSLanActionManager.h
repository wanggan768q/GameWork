//
//  HSLanActionManager.h
//  HSBalloon_S3
//
//  Created by Ambition on 14-1-17.
//
//

#ifndef __HSBalloon_S3__HSLanActionManager__
#define __HSBalloon_S3__HSLanActionManager__

#include <iostream>
#include "HSTool.h"

#ifndef HS_LAN_ACTION
#define HS_LAN_ACTION

typedef enum
{
    Lan_Action_Status_Invalid  = -1,
    Lan_Action_Status_Success  = 0,
    Lan_Action_Status_Fail     = 1,
    Lan_Action_Status_Runing   = 2,
    
}HSLanActionStatus;


typedef enum
{
    Lan_Action_Unknow       = 0,
    Lan_Action_RestoreWIFI,
    Lan_Action_SearchRoom,
    Lan_Action_CreateRoom,
    Lan_Action_JoinRoom,
    Lan_Action_QuitRoom,
    Lan_Action_Exception,
}HSLanAction;


#endif /* HS_LAN_ACTION */

class HSLanActionManager : public CCObject
{
    
public:
    HSLanActionManager();
    ~HSLanActionManager();
    
public:
    static HSLanActionManager* ShareLanActionManager();
    
    bool Init();
    
    void Destroy();
    
    void ShowAllActionInfo();
    
    void ShowCurrentAction();
    
    void ShowActionInfo(HSLanAction action);
    
    const char* GetCurrentAction(HSLanAction action);
    
    const char* GetActionStatus(HSLanActionStatus actionStatus);
    
    void AddAction(HSLanAction action);
    
    void Pop();
    
    void Updata(float dt);
    
public:
    
    // wifi 恢复状态
    HSLanActionStatus m_RestoreWIFI;
    
    // 搜索房间列表状态
    HSLanActionStatus m_SearchRoom;
    
    // 创建房间状态
    HSLanActionStatus m_CreateRoom;
    
    // 进入房间
    HSLanActionStatus m_JoinRoom;
    
    // 退出房间
    HSLanActionStatus m_QuitRoom;
    
    // 异常断开连接
    HSLanActionStatus m_Exception;
    
    HSLanAction m_currentLanAction;
    
    std::queue<HSLanAction> m_actions;
    
};
























#endif /* defined(__HSBalloon_S3__HSLanActionManager__) */
