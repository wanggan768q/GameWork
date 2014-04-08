//
//  UITableViewFriendCell.h
//  TCWeiBoSDKDemo
//
//

#import <UIKit/UIKit.h>
#import "ImageDownloader.h"

@interface UITableViewFriendCell :UITableViewCell<ImageDownloaderDelegate> {
 
    ImageDownloader *imageDownloader;
    
    UIImageView *imageviewHead;
    
    NSMutableString  *strHeadPath;
}

@property(nonatomic,retain) UIImageView *imageviewHead;

- (void)startDownloadHead:(NSString *)strURL;
- (void)stopDownloadHead;

- (BOOL)setHeadPath:(NSString *)stringHeadPath;

@end
