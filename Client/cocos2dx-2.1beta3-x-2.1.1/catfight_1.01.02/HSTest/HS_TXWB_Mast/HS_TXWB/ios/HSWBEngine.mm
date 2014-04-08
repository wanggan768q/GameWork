//
//  HSWBEngine.m
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-27.
//
//

#import "HSWBEngine.h"

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
        m_pTCWBEngine = [[WeiboApi alloc] initWithAppKey:HS_SDK_WB_KEY andSecret:HS_SDK_WB_PASS andRedirectUri:HS_SDK_WB_URL];
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
    [m_pTCWBEngine loginWithDelegate:self andRootController:self.m_pRootView];
}

-(void) Logout
{
    //[m_pTCWBEngine ];
}

-(void) SetDelegate:(id)inId
{
    m_pRootView = inId;
    [m_pTCWBEngine setRootViewCtrl:m_pRootView];
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

-(BOOL) handleOpenURL:(NSURL *)url
{
    return [m_pTCWBEngine handleOpenURL:url];
}

-(void) ShowAlertMessage:(NSString *)msg
{
    
}











#pragma mark WeiboRequestDelegate

/**
 * @brief   接口调用成功后的回调
 * @param   INPUT   data    接口返回的数据
 * @param   INPUT   request 发起请求时的请求对象，可以用来管理异步请求
 * @return  无返回
 */
- (void)didReceiveRawData:(NSData *)data reqNo:(int)reqno
{
    NSLog(@"接口调用成功后的回调");
}
/**
 * @brief   接口调用失败后的回调
 * @param   INPUT   error   接口返回的错误信息
 * @param   INPUT   request 发起请求时的请求对象，可以用来管理异步请求
 * @return  无返回
 */
- (void)didFailWithError:(NSError *)error reqNo:(int)reqno
{
    NSLog(@"接口调用失败后的回调");
}





#pragma mark WeiboAuthDelegate

/**
 * @brief   重刷授权成功后的回调
 * @param   INPUT   wbapi 成功后返回的WeiboApi对象，accesstoken,openid,refreshtoken,expires 等授权信息都在此处返回
 * @return  无返回
 */
- (void)DidAuthRefreshed:(WeiboApi *)wbapi
{
    
}

/**
 * @brief   重刷授权失败后的回调
 * @param   INPUT   error   标准出错信息
 * @return  无返回
 */
- (void)DidAuthRefreshFail:(NSError *)error
{
    
}

/**
 * @brief   授权成功后的回调
 * @param   INPUT   wbapi 成功后返回的WeiboApi对象，accesstoken,openid,refreshtoken,expires 等授权信息都在此处返回
 * @return  无返回
 */
- (void)DidAuthFinished:(WeiboApi *)wbapi
{
    
}

/**
 * @brief   授权成功后的回调
 * @param   INPUT   wbapi   weiboapi 对象，取消授权后，授权信息会被清空
 * @return  无返回
 */
- (void)DidAuthCanceled:(WeiboApi *)wbapi
{
    
}

/**
 * @brief   授权成功后的回调
 * @param   INPUT   error   标准出错信息
 * @return  无返回
 */
- (void)DidAuthFailWithError:(NSError *)error
{
    
}



@end
