//
//  HSTexture2D.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-8.
//
//

#ifndef __HSBalloon_S3__HSTexture2D__
#define __HSBalloon_S3__HSTexture2D__
#include "cocos2d.h"
using namespace cocos2d;

class HSTexture2D
{
public:
    HSTexture2D();
    HSTexture2D(CCTexture2D* pTexture,const CCRect& textureRect);
    ~HSTexture2D();
    
public:
    HSTexture2D& operator=(CCSpriteFrame* pSpriteFrame);
    
public:
    CCTexture2D* texture;
    CCRect rect;
    bool isRotate;
};

#endif /* defined(__HSBalloon_S3__HSTexture2D__) */
