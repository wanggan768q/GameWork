//
//  HSTexture2D.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-8.
//
//

#include "HSTexture2D.h"

HSTexture2D::HSTexture2D()
{
    HSTexture2D(NULL,CCRectZero);
}

HSTexture2D::HSTexture2D(CCTexture2D* pTexture,const CCRect& textureRect)
{
    texture = pTexture;
    rect = textureRect;
    isRotate = false;
}

HSTexture2D::~HSTexture2D()
{
    texture = NULL;
}

HSTexture2D& HSTexture2D::operator=(CCSpriteFrame* pSpriteFrame)
{
    if (pSpriteFrame)
    {
        texture = pSpriteFrame->getTexture();
        rect = pSpriteFrame->getRect();
        isRotate = pSpriteFrame->isRotated();
    }else{
        texture = NULL;
        rect = CCRectZero;
        isRotate = false;
    }
    return *this;
}





