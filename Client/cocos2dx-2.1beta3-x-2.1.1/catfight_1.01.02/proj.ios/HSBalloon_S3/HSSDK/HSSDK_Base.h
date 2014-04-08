//
//  HSSDK_Base.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-9.
//
//

#import <Foundation/Foundation.h>

@interface HSSDK_Base : NSObject

@property (nonatomic,retain)NSDictionary* m_pDict;


+(id) SharedSDKBase;

+(id) FindConfig:(NSString*)key;

-(void) dealloc;


@end
