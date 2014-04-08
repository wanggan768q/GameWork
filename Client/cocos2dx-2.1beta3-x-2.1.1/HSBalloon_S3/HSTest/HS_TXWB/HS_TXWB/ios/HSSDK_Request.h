//
//  HSSDK_Net.h
//  HS_TXWB
//
//  Created by Ambition on 13-12-2.
//
//

#import <Foundation/Foundation.h>
#import "TCWBEngine.h"

#define HS_SDK_NET_ADDRESS @"http://115.29.228.49/"

@interface HSSDK_Request : NSString

@property (nonatomic,retain)NSString* m_appid;
@property (nonatomic,retain)NSString* m_gameUUID;
@property (nonatomic,retain)NSString* m_type;

+(HSSDK_Request*) SharedSDKRequest;


-(void) SynchronizationWBData;

@end
