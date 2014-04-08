//
//  HSSDK_Pay.m
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-5.
//
//

#import "HSSDK_Pay.h"

@implementation HSSDK_Pay

static HSSDK_Pay* s_HSSDK_Pay = nil;

+(id) SharedPay
{
    if (!s_HSSDK_Pay)
    {
        s_HSSDK_Pay = [[HSSDK_Pay alloc] init];
    }
    return s_HSSDK_Pay;
}

-(id) init
{
    self = [super init];
    if (self != nil)
    {
        m_ItemID = 0;
        //---------------------
        //----监听购买结果
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    }
    
    return self;
}

-(void)Pay:(int)itemID
{
    m_ItemID = itemID;
    
    if ([SKPaymentQueue canMakePayments]) {
        NSLog(@"允许购买");
        [self Request];
    }else{
        NSLog(@"不允许购买");
        UIAlertView* box = [[UIAlertView alloc] initWithTitle:@"不允许购买" message:@"abs" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [box show];
        [box release];
    }
}

-(void) Request
{
    NSArray* product = [[NSArray alloc] initWithObjects:@"10003",nil];
    
    NSSet *nsset = [NSSet setWithArray:product];
    SKProductsRequest *request = [[SKProductsRequest alloc] initWithProductIdentifiers: nsset];
    request.delegate=self;
    [request start];
    [product release];
}

#pragma mark - <SKProductsRequestDelegate> 请求协议 收到的产品信息

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    //@property(nonatomic, readonly) NSString *localizedDescription __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
    
    //@property(nonatomic, readonly) NSString *localizedTitle __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
    
   // @property(nonatomic, readonly) NSDecimalNumber *price __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
    
    //@property(nonatomic, readonly) NSLocale *priceLocale __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
    
    //@property(nonatomic, readonly) NSString *productIdentifier __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
    
    //SKProduct* pProduct = [[SKProduct alloc] init];
    
    //[pProduct setLocalizedDescription:@""];
    
    //SPayment *payment = SKPayment paymentWithProduct:(SKProduct *)
    NSArray *myProduct = response.products;
    SKProduct *_proUpgradeProduct = [myProduct count] == 1 ? [[myProduct objectAtIndex:0] retain] : nil;
    NSArray* productArray = response.products;
}

#pragma mark - <SKPaymentTransactionObserver> 监听购买结果

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    
}
































@end
