//
//  ImageDownloader.h
//  TCWeiBoSDKDemo
//
//

#import <Foundation/Foundation.h>

@protocol ImageDownloaderDelegate <NSObject>

- (void)imageDidFishLoad:(NSData *)dataImage;

@end


@interface ImageDownloader : NSObject {
    
    NSURLConnection *connURL;
    NSMutableData *dataImage;

    id<ImageDownloaderDelegate> delegate;
}

@property(nonatomic,retain)id<ImageDownloaderDelegate> delegate;


- (void)startDownload:(NSString *)strURL;
- (void)cancelDownload;


@end
