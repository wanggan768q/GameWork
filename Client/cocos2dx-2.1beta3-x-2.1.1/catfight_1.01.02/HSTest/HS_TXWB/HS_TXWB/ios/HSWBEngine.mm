//
//  HSWBEngine.m
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#import "HSWBEngine.h"
#import "HSSDK_Request.h"
#import "GetIPAddress.h"

@implementation HSWBEngine
@synthesize m_pTCWBEngine;
@synthesize m_pRootView;


static HSWBEngine* s_HSWBEngine = nil;

+(id) SharedWBEngine
{
    if (!s_HSWBEngine)
    {
        s_HSWBEngine = [[HSWBEngine alloc] init];
    }
    return s_HSWBEngine;
}


-(id) init
{
    self = [super init];
    
    if (self != NULL)
    {
        m_pTCWBEngine = [[TCWBEngine alloc] initWithAppKey:HS_SDK_WB_KEY andSecret:HS_SDK_WB_PASS andRedirectUrl:HS_SDK_WB_URL];        
    }
    return self;
}

-(void) dealloc
{
    [m_pTCWBEngine dealloc];
    
    [super dealloc];
}

-(void) Login
{
    [m_pTCWBEngine logInWithDelegate:self onSuccess:@selector(LoginSuccessed) onFailure:@selector(LoginFailed:)];
}

-(void) Logout
{
    //[m_pTCWBEngine ];
}

-(void) SetDelegate:(id)inId
{
    m_pRootView = inId;
    [m_pTCWBEngine setRootViewController:self.m_pRootView];
}
-(void) PostText:(NSString*)text
{
//    [m_pTCWBEngine postTextTweetWithFormat:@"json"
//                                   content:text
//                                  clientIP:@"210.72.197.50"
//                                 longitude:nil
//                               andLatitude:nil
//                               parReserved:nil
//                                  delegate:self.m_pRootView
//                                 onSuccess:@selector(OnCreateSuccess:)
//                                 onFailure:@selector(OnCreateFail:)];
}

-(void) LoginSuccessed
{
    NSLog(@"%@",m_pTCWBEngine.name);
    NSLog(@"%@",m_pTCWBEngine.openId);
    [[HSSDK_Request SharedSDKRequest] SynchronizationWBData];
}

-(void) LoginFailed:(NSError *)error
{
    
}


#pragma mark - SSO

/*! @brief 登录错误回调
 *
 * 发生错误时，客户端根据错误码作相应处理，可选择显示SDK返回的错误码
 * @param errCode 错误码
 * @param msg 错误提示信息
 */
-(void)onLoginFailed:(WBErrCode)errCode msg:(NSString*)msg
{
    
}

/*! @brief 登录成功回调
 *
 * 成功后返回用户openid及token
 * @param name 微博中使用的用户名
 * @param token 凭证，由客户端保存
 */
-(void)onLoginSuccessed:(NSString*)name token:(WBToken*)token
{
    
}

-(BOOL) handleOpenURL:(NSURL *)url
{
    return [m_pTCWBEngine handleOpenURL:url delegate:self];
}

-(void) ShowAlertMessage:(NSString *)msg
{
    
}









@end
