//
//  HSShareLayer.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-13.
//
//

#ifndef __HSBalloon_S3__HSShareLayer__
#define __HSBalloon_S3__HSShareLayer__
#include "HSTool.h"
#include "HSReadUI.h"
#include "HSGameSceneJumpManage.h"

typedef struct _HSShareData
{
    _HSShareData()
    {
        shareText = "分享文本";
        wbText = "微博";
        money = 0;
        goSceneID = HS_SCENE_UNKOWN;
        feedbackText = "二次确认信息";
    }
    ~_HSShareData()
    {
        
    }
    
    std::string shareText; //分享文本显示
    std::string wbText;    //微博文本
    int         money;      //添加多少钱 0 将不显示
    GameSceneID goSceneID;  //跳转到哪个场景 不跳转就不用赋值
    std::string feedbackText;   //返回消息内容
    
}HSShareData;




class HSShareLayer : public CCLayer
{
private:
    HSShareLayer();
public:
    ~HSShareLayer();
        
public:
    static HSShareLayer* create(const HSShareData& shareData);
    virtual bool init(const HSShareData& shareData);
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    void Call_SendWeiBo(CCObject* pObj);
    void Call_Back(CCObject* pObj);
    
private:
    HSShareData m_shareData;
};

#endif /* defined(__HSBalloon_S3__HSShareLayer__) */
