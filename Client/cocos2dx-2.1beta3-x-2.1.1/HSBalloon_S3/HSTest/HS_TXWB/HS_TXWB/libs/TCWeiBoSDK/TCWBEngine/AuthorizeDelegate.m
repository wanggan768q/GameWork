//
//  AuthorizeDelegate.m
//  TCWeiBoSDKDemo
//
//  Created by Yi Minwen on 9/14/12.
//

#import "AuthorizeDelegate.h"
@implementation AuthorizeDelegate
@synthesize returnCode, err;

-(id)initWithRunLoop:(CFRunLoopRef)runLoop  {
	if (self = [super init]) {
		currentLoop = runLoop;
	}
	return self;
}

#pragma mark protocol TCWBAuthorizeViewControllerDelegate <NSObject>
//授权成功回调
- (void)authorize:(TCWBAuthorizeViewController *)authorize didSucceedWithAccessToken:(NSString *)code {
    self.returnCode = code;
    CFRunLoopStop(currentLoop);
}

//授权失败回调
- (void)authorize:(TCWBAuthorizeViewController *)authorize didFailuredWithError:(NSError *)error {
    self.err = error;
    CFRunLoopStop(currentLoop);
}

#pragma mark - WBApiDelegate
-(void)onLoginFailed:(WBErrCode)errCode msg:(NSString*)msg;
{
    self.wberr = errCode;
    self.errMsg = msg;
    CFRunLoopStop(currentLoop);
//    G_LOGOUT = YES;
//    if ([temp_delegate respondsToSelector:onFailureCallback]) {
//        [temp_delegate performSelector:onFailureCallback withObject:nil];
//    }
//    [handurldelegate    onLoginFailed:errCode msg:msg];
    
    //    UIAlertView* av = [[UIAlertView alloc] initWithTitle:@"登录失败" message:msg delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
    //    [av show];
}

-(void)onLoginSuccessed:(NSString*)sname token:(WBToken*)token_;
{
    
    self.name= sname;
    self.token = token_;
    
 

    CFRunLoopStop(currentLoop);
    //[handurldelegate    onLoginSuccessed:sname token:token];
    
    //    NSString* msg = [NSString stringWithFormat:@"name=%@\n openid=%@\n token=%@\n expire=%u\n refreshToken=%@ \n omasToken=%@ omasKey = %@\n",name,token.openid,token.accessToken,token.expires,token.refreshToken, token.omasKey, token.omasToken];
    //    UIAlertView* av = [[UIAlertView alloc] initWithTitle:@"登录成功" message:msg delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
    //    [av show];
}



@end
