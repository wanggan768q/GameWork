//
//  AuthorizeDelegate.h
//  TCWeiBoSDKDemo
//
//  Created by Yi Minwen on 9/14/12.
//

#import <Foundation/Foundation.h>
#import "TCWBAuthorizeViewController.h"
#import "WBApi.h"

@interface AuthorizeDelegate : NSObject<TCWBAuthorizeViewControllerDelegate,WBApiDelegate>
{
	CFRunLoopRef    currentLoop;
	NSString        *returnCode;            // 正常授权返回授权码
    NSError         *err;                   // 假如授权失败，错误描述信息
    WBToken         *token;
    WBErrCode       wberr;
    NSString        *errMsg;
    NSString        *name;
    id              temp_delegate;
}
@property(nonatomic, copy)NSString          *returnCode;
@property(nonatomic, retain)NSError         *err;
@property(nonatomic, retain)WBToken         *token;
@property(nonatomic, assign)WBErrCode       wberr;
@property(nonatomic, retain)NSString        *errMsg;
@property(nonatomic, retain)NSString        *name;

//-(id)initWithRunLoop:(CFRunLoopRef)runLoop;
-(id)initWithRunLoop:(CFRunLoopRef)runLoop;

@end

