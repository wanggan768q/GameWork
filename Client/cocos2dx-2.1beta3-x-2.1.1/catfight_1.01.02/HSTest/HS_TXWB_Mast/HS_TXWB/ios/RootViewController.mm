//
//  HS_TXWBAppController.h
//  HS_TXWB
//
//  Created by Ambition on 13-12-2.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import "RootViewController.h"


@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskLandscape;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

//#pragma mark WeiboRequestDelegate
//
///**
// * @brief   接口调用成功后的回调
// * @param   INPUT   data    接口返回的数据
// * @param   INPUT   request 发起请求时的请求对象，可以用来管理异步请求
// * @return  无返回
// */
//- (void)didReceiveRawData:(NSData *)data reqNo:(int)reqno
//{
//    NSLog(@"接口调用成功后的回调");
//}
///**
// * @brief   接口调用失败后的回调
// * @param   INPUT   error   接口返回的错误信息
// * @param   INPUT   request 发起请求时的请求对象，可以用来管理异步请求
// * @return  无返回
// */
//- (void)didFailWithError:(NSError *)error reqNo:(int)reqno
//{
//    NSLog(@"接口调用失败后的回调");
//}
//
//
//
//
//
//#pragma mark WeiboAuthDelegate
//
///**
// * @brief   重刷授权成功后的回调
// * @param   INPUT   wbapi 成功后返回的WeiboApi对象，accesstoken,openid,refreshtoken,expires 等授权信息都在此处返回
// * @return  无返回
// */
//- (void)DidAuthRefreshed:(WeiboApi *)wbapi
//{
//    
//}
//
///**
// * @brief   重刷授权失败后的回调
// * @param   INPUT   error   标准出错信息
// * @return  无返回
// */
//- (void)DidAuthRefreshFail:(NSError *)error
//{
//    
//}
//
///**
// * @brief   授权成功后的回调
// * @param   INPUT   wbapi 成功后返回的WeiboApi对象，accesstoken,openid,refreshtoken,expires 等授权信息都在此处返回
// * @return  无返回
// */
//- (void)DidAuthFinished:(WeiboApi *)wbapi
//{
//    
//}
//
///**
// * @brief   授权成功后的回调
// * @param   INPUT   wbapi   weiboapi 对象，取消授权后，授权信息会被清空
// * @return  无返回
// */
//- (void)DidAuthCanceled:(WeiboApi *)wbapi
//{
//    
//}
//
///**
// * @brief   授权成功后的回调
// * @param   INPUT   error   标准出错信息
// * @return  无返回
// */
//- (void)DidAuthFailWithError:(NSError *)error
//{
//    
//}


@end
