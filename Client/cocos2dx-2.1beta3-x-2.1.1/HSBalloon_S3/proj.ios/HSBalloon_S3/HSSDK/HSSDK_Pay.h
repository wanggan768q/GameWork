//
//  HSSDK_Pay.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-5.
//
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface HSSDK_Pay : NSObject<SKProductsRequestDelegate,SKPaymentTransactionObserver>
{
    int m_ItemID;
}

+(id) SharedPay;

-(void) Pay:(int)itemID;

-(void) productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;

@end
