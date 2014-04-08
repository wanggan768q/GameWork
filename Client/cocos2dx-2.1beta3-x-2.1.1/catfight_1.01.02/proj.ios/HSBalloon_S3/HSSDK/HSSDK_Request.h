//
//  HSSDK_Net.h
//  HS_TXWB
//
//  Created by Ambition on 13-12-2.
//
//

#import <Foundation/Foundation.h>
#import "TCWBEngine.h"

@interface HSSDK_Request : NSString

@property (nonatomic)int m_appid;
@property (nonatomic,retain)NSString* m_gameUUID;
@property (nonatomic,retain)NSString* m_type;
@property (nonatomic,retain)NSString* m_pSDKUrl;

+(HSSDK_Request*) SharedSDKRequest;


-(BOOL) SynchronizationWBData;

-(BOOL) RefreshWBData;

@end
