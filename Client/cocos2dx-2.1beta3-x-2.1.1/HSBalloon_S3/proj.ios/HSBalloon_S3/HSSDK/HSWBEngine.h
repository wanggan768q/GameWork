//
//  HSWBEngine.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#import <Foundation/Foundation.h>
#import "TCWBEngine.h"
#import "RootViewController.h"



@interface HSWBEngine : NSObject<SSODelegate>
{
    TCWBEngine*                 m_pTCWBEngine;
    RootViewController*         m_pRootView;
}

@property (nonatomic,retain)TCWBEngine*         m_pTCWBEngine;
@property (nonatomic,retain)RootViewController* m_pRootView;

+(id) SharedWBEngine;

//登陆
-(void) Login;

//等出
-(void) Logout;

//发一个文字微博，不弹出窗口让用户修改
-(void) PostText:(NSString*)text;

-(void) LoginSuccessed;

-(void) LoginFailed:(NSError *)error;

//发送微博成功的回调函数
-(void) createSuccess:(NSDictionary *)dict;
//发送微博失败的回调函数
-(void) createFail:(NSError *)error;

//保存cocos2d-x窗口用的函数
-(void) SetDelegate:(id)inId;

//显示警告窗口用
-(void) ShowAlertMessage:(NSString *)msg;

-(BOOL) handleOpenURL:(NSURL *)url;

/*! @brief 登录错误回调
 *
 * 发生错误时，客户端根据错误码作相应处理，可选择显示SDK返回的错误码
 * @param errCode 错误码
 * @param msg 错误提示信息
 */
-(void)onLoginFailed:(WBErrCode)errCode msg:(NSString*)msg;

/*! @brief 登录成功回调
 *
 * 成功后返回用户openid及token
 * @param name 微博中使用的用户名
 * @param token 凭证，由客户端保存
 */
-(void)onLoginSuccessed:(NSString*)name token:(WBToken*)token;

@end




