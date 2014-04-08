//
//  NSObject+WBUtil.h
//  WiressSDKDemo
//
//

#import <Foundation/Foundation.h>

@interface NSObject (WBUtil)

@end


@interface NSString (WBRequest)

- (NSString *)URLEncodedString;
- (NSString *)URLEncodedStringWithCFStringEncoding:(CFStringEncoding)encoding;

@end