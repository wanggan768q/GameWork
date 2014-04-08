//
//  HSSDK_Base.m
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-9.
//
//

#import "HSSDK_Base.h"

@implementation HSSDK_Base
@synthesize m_pDict;

static HSSDK_Base* s_HSSDKBase = nil;

+(id) SharedSDKBase
{
    if (!s_HSSDKBase) {
        s_HSSDKBase = [[HSSDK_Base alloc] init];
        
    }
    return s_HSSDKBase;
}

-(id) init
{
    NSString* pSDKConfig = [[NSBundle mainBundle] pathForResource:@"LeTuSDKConfig" ofType:@"plist"];
    if (!pSDKConfig)
    {
        UIAlertView* box = [[UIAlertView alloc] initWithTitle:@"LeTuDKConfig.plits 不存在" message:@"abs" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [box show];
        [box release];
    }
    m_pDict = [NSDictionary dictionaryWithContentsOfFile:pSDKConfig];
    
    return self;
}

-(void) dealloc
{
    [m_pDict release];
    
    [super dealloc];
}

-(id) GetDict
{
    return m_pDict;
}

+(id) FindConfig:(NSString*)key
{
    if (![[HSSDK_Base SharedSDKBase] GetDict])
    {
        return nil;
    }
    return [[[HSSDK_Base SharedSDKBase ]GetDict ]objectForKey:key];
}


@end
