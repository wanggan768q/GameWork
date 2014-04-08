//
//  UIImage+rotate.h
//  weibosdk
//
//  Created by Minwen Yi on 3/23/12.
//  Copyright 2012 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

#define degreesToRadians(x) (M_PI * (x) / 180.0)


@interface UIImage (Rotate)

-(UIImage*)rotateImage:(UIImageOrientation)orient;

@end