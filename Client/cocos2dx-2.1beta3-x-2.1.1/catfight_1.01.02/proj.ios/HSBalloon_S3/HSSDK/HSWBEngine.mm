//
//  HSWBEngine.m
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#import "HSWBEngine.h"
#import "HSSDK_Request.h"
#import "HSSDK.h"
#import "SBJSON.h"
#import "HSSDK_Base.h"

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
        NSString* WB_KEY = [HSSDK_Base FindConfig:@"WB_KEY"];
        NSString* WB_PASS = [HSSDK_Base FindConfig:@"WB_PASS"];
        NSString* WB_URL = [HSSDK_Base FindConfig:@"WB_URL"];
        
        m_pTCWBEngine = [[TCWBEngine alloc] initWithAppKey:WB_KEY andSecret:WB_PASS andRedirectUrl:WB_URL];
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
    BOOL isExpired = [m_pTCWBEngine isAuthorizeExpired];
    if (!isExpired)
    {
        [m_pTCWBEngine logInWithDelegate:self onSuccess:@selector(LoginSuccessed) onFailure:@selector(LoginFailed:)];
    }else{
        NSString* pExpireTime = [NSString stringWithFormat:@"%f",m_pTCWBEngine.expireTime ];
        [m_pTCWBEngine logInWithAccessToken:m_pTCWBEngine.accessToken expiredTime:pExpireTime openID:m_pTCWBEngine.openId andRefreshToken:m_pTCWBEngine.refreshToken delegate:self onSuccess:@selector(LoginSuccessed) onFailure:@selector(LoginFailed:)];
    }
}

-(void) Logout
{
    [m_pTCWBEngine logOut];
}

-(void) SetDelegate:(id)inId
{
    m_pRootView = inId;
    [m_pTCWBEngine setRootViewController:self.m_pRootView];
}
-(void) PostText:(NSString*)text
{
    [m_pTCWBEngine postTextTweetWithFormat:@"json"
                                   content:text
                                  clientIP:m_pTCWBEngine.ip_iphone
                                 longitude:nil
                               andLatitude:nil
                               parReserved:nil
                                  delegate:self.m_pRootView
                                 onSuccess:@selector(createSuccess:)
                                 onFailure:@selector(createFail:)];
}

//发送微博成功的回调函数
-(void) createSuccess:(NSDictionary *)dict
{
    
}

//发送微博失败的回调函数
-(void) createFail:(NSError *)error
{
    
}

-(void) LoginSuccessed
{
//    NSDictionary * pDirct = [[NSDictionary alloc] init];
//    [m_pTCWBEngine getUserInfoWithFormat:@"json" parReserved:pDirct delegate:self onSuccess:@selector(onLoginSuccessed:token:) onFailure:@selector(onLoginFailed:msg:)];
    
    
    BOOL isOK = [[HSSDK_Request SharedSDKRequest] SynchronizationWBData];
    
    if (isOK)
    {
        NSDictionary* pData = [NSDictionary dictionaryWithObjectsAndKeys:
                               
                               [NSNumber numberWithInt:62000],@"JNI_ID",                        //   62000
                               
                               m_pTCWBEngine.openId,@"WEIBO_OPENID",                            //用户唯一ID
                               
                               m_pTCWBEngine.name,@"WEIBO_NAME",                                //微博用户名
                               
                               [NSNumber numberWithInt:0],@"WEIBO_RESULT",                      //错误表示(具体见附录1)
                               
                               @"",@"WEIBO_ERR",                                                //错误信息
                               
                               nil];
        
        SBJsonWriter* pJsonWriter = [[SBJsonWriter alloc] init];
        
        NSString* pStr = [pJsonWriter stringWithObject:pData];
        
        NSLog(@"%@",pStr);
        
        HSSDK::SharedSDK()->LoginResponse([pStr UTF8String]);
    }
}

-(void) LoginFailed:(NSError *)error
{
    NSDictionary* pData = [NSDictionary dictionaryWithObjectsAndKeys:
                           
                           [NSNumber numberWithInt:62000],@"JNI_ID",                        //   62000
                           
                           @"",@"WEIBO_OPENID",                                             //用户唯一ID
                           
                           @"",@"WEIBO_NAME",                                               //微博用户名
                           
                           [NSNumber numberWithInt:1],@"WEIBO_RESULT",                      //错误表示(具体见附录1)
                           
                           @"取消微博登陆",@"WEIBO_ERR",                                       //错误信息
                           
                           nil];
    
    SBJsonWriter* pJsonWriter = [[SBJsonWriter alloc] init];
    
    NSString* pStr = [pJsonWriter stringWithObject:pData];
    
    NSLog(@"%@",pStr);
    
    HSSDK::SharedSDK()->LoginResponse([pStr UTF8String]);
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
    NSLog(@"登录错误回调");
}

/*! @brief 登录成功回调
 *
 * 成功后返回用户openid及token
 * @param name 微博中使用的用户名
 * @param token 凭证，由客户端保存
 */
-(void)onLoginSuccessed:(NSString*)name token:(WBToken*)token
{
    NSLog(@"登录成功回调");
}

-(BOOL) handleOpenURL:(NSURL *)url
{
    return [m_pTCWBEngine handleOpenURL:url delegate:self];
}

-(void) ShowAlertMessage:(NSString *)msg
{
    
}









@end
