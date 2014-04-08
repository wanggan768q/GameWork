//
//  NSObject+WBUtil.m
//  WiressSDKDemo
//
//

#import "NSObject+WBUtil.h"

@implementation NSObject (WBUtil)

@end

#pragma mark - NSString (NSString_Encoding)

@implementation NSString (NSString_Encoding)


- (NSString *)URLEncodedString
{
	return [self URLEncodedStringWithCFStringEncoding:kCFStringEncodingUTF8];
}

- (NSString *)URLEncodedStringWithCFStringEncoding:(CFStringEncoding)encoding
{
	return [(NSString *) CFURLCreateStringByAddingPercentEscapes(NULL, (CFStringRef)[[self mutableCopy] autorelease], NULL, CFSTR("￼!*'();:@&=+$,/?%#[]"), encoding) autorelease];
}

@end