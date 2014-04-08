//
//  HSSDK_Net.m
//  HS_TXWB
//
//  Created by Ambition on 13-12-2.
//
//

#import "HSSDK_Request.h"
#import "JSON.h"
#import "HSWBEngine.h"
#import "HSSDK_Base.h"

@implementation HSSDK_Request
@synthesize m_appid;
@synthesize m_gameUUID;
@synthesize m_type;

static HSSDK_Request* s_HSSDK_Request = nil;

+(HSSDK_Request*) SharedSDKRequest
{
    if (!s_HSSDK_Request)
    {
        s_HSSDK_Request = [[HSSDK_Request alloc] init];
        [s_HSSDK_Request setM_pSDKUrl:[HSSDK_Base FindConfig:@"SDK_URL"]];
    }
    return s_HSSDK_Request;
}


-(NSDictionary*) SendData:(NSString*)url sendStr:(NSString*)sendStr
{
    NSData* pSendData = [sendStr dataUsingEncoding:NSUTF8StringEncoding];
    
    NSMutableURLRequest *request = [[[NSMutableURLRequest alloc] init] autorelease];
    [request setURL:[NSURL URLWithString:url]];
    [request setHTTPMethod:@"POST"]; //设置请求方式
    //设置http头
    NSString *contentType = [NSString stringWithFormat:@"text/xml"];
    [request addValue:contentType forHTTPHeaderField: @"Content-Type"];
    
    [request setHTTPBody:pSendData];
    
    //获取响应
    NSHTTPURLResponse* urlResponse = nil;
    NSError * error = [[NSError alloc] init];
    NSData  * responseData = [NSURLConnection sendSynchronousRequest:request returningResponse:&urlResponse error:&error];  //获取返回数据
    NSString* aStr= [[NSString alloc] initWithData:responseData   encoding:NSUTF8StringEncoding];
    
    if (!responseData)
    {
        NSLog(@"==============================");
        NSLog(@"老胡出错 没有返回消息");
        NSLog(@"==============================");
    }
    
    
    SBJsonParser* pJsonParser = [[SBJsonParser alloc] init];
    NSDictionary* pdirct = [pJsonParser objectWithString:aStr];
    
    //获取返回的内容
    if ([urlResponse statusCode] == 200)
    {
        NSLog(@"==============================");
        NSLog(@"%@",pdirct);
        NSLog(@"==============================");
        return pdirct;
    }
    
    [pJsonParser release];
    pJsonParser = nil;
    
    [request release];
    request = nil;

    NSLog(@"==============================");
    NSLog(@"出错  %s",__FUNCTION__);
    NSLog(@"==============================");
    
    return nil;
}


#pragma mark - 用户游戏微博数据同步（1004）

-(NSString*) SynchronizationWBData
{
    NSString *urlString = [[NSString alloc] initWithFormat:@"%@%@",self.m_pSDKUrl,@"operationStatistics/apiUser.php"];
    
    HSWBEngine* pWBEngine = [HSWBEngine SharedWBEngine];
    
    NSDictionary* pData = [NSDictionary dictionaryWithObjectsAndKeys:
                           
                           [NSNumber numberWithInt:1004],@"node",                               //接口数据类型代码（1004）
                           
                           [NSNumber numberWithInt:m_appid],@"appID",                           //产品唯一ID
                           
                           m_gameUUID,@"uid",                                                   //游戏唯一ID
                           
                           pWBEngine.m_pTCWBEngine.name,@"uname",                               //用户名
                           
                           m_type,@"wbType",                                                    //微博所属
                           
                           pWBEngine.m_pTCWBEngine.accessToken,@"wbToken",                      //用户微博认证码
                           
                           pWBEngine.m_pTCWBEngine.openId,@"wbOpenid",                          //微博唯一id
                           
                           pWBEngine.m_pTCWBEngine.openKey,@"wbOpenkey",                        //微博唯一key
                           
                           nil];
    
    SBJsonWriter* pJsonWriter = [[SBJsonWriter alloc] init];
    
    NSString* pSendStr = [pJsonWriter stringWithObject:pData];
    
    NSLog(@"%@",pData);
    
    NSDictionary* pdirct = [self SendData:urlString sendStr:pSendStr];
    
    NSNumber *pStatus = [pdirct objectForKey:@"status"];
    
    int status = [pStatus intValue];
    
    [pJsonWriter release];
    pJsonWriter = nil;
    
    [urlString release];
    urlString = nil;
    
    NSString* errorCode;
    if (status == 0)
    {
        errorCode = @"";
    }else{
        errorCode = [pdirct objectForKey:@"state"];
    }
    
    return errorCode;
    
}

#pragma mark - 用户游戏微博数据同步（1005）

-(BOOL) RefreshWBData
{
    NSString *urlString = [[NSString alloc] initWithFormat:@"%@%@",self.m_pSDKUrl,@"operationStatistics/apiUser.php"];
    
    HSWBEngine* pWBEngine = [HSWBEngine SharedWBEngine];
    
    NSDictionary* pData = [NSDictionary dictionaryWithObjectsAndKeys:
                           
                           [NSNumber numberWithInt:1005],@"node",                               //接口数据类型代码（1005）
                           
                           [NSNumber numberWithInt:m_appid],@"appID",               //产品唯一ID
                           
                           m_type,@"wbType",                                                    //微博所属
                           
                           pWBEngine.m_pTCWBEngine.openId,@"wbOpenid",                          //微博唯一id
                           
                           nil];
    
    SBJsonWriter* pJsonWriter = [[SBJsonWriter alloc] init];
    
    NSString* pSendStr = [pJsonWriter stringWithObject:pData];
    
    NSLog(@"%@",pData);
    
    NSDictionary* pdirct = [self SendData:urlString sendStr:pSendStr];
    
    NSNumber *pStatus = [pdirct objectForKey:@"status"];
    
    int status = [pStatus intValue];
    
    [pJsonWriter release];
    pJsonWriter = nil;
    
    [urlString release];
    urlString = nil;
    
    if (status == 0)
    {
        return YES;
    }
    
    return NO;


}























@end
