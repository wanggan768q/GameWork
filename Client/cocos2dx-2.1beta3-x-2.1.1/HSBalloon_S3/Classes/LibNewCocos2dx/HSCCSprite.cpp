#include "HSCCSprite.h"
#include "HSReadPlist.h"


HSCCSprite::HSCCSprite(void)
{
	this->m_clipRect = CCRectMake(0,0,HS_SCREEN_WIDTH,HS_SCREEN_HEIGHT);
    m_fileName = "";
}

HSCCSprite::~HSCCSprite(void)
{
	
}
// 
// HSCCSprite* HSCCSprite::node()
// {
// 	HSCCSprite* s = new HSCCSprite;
// 	s->autorelease();
// 	//s->useSelfRender();
// 	return s;
// }

HSCCSprite* HSCCSprite::create(const char *pszFileName)
{
	HSCCSprite* hsSprite = new HSCCSprite();
	bool ok = hsSprite->initWithFile(pszFileName);
	if (ok == true)
	{
		hsSprite->autorelease();
		return hsSprite;
	}
	CC_SAFE_DELETE(hsSprite);
	return NULL;
}

HSCCSprite* HSCCSprite::create(CCTexture2D *pTexture)
{
	HSCCSprite* hsSprite = new HSCCSprite();
	bool ok = hsSprite->initWithTexture(pTexture);
	if (ok)
	{
		hsSprite->autorelease();
		return hsSprite;
	}
	CC_SAFE_DELETE(hsSprite);
	return NULL;
}

HSCCSprite* HSCCSprite::create(CCTexture2D *pTexture,const CCRect& rect,bool isRotate)
{
    HSCCSprite* hsSprite = new HSCCSprite();
	bool ok = hsSprite->initWithTexture(pTexture, rect, isRotate);
	if (ok)
	{
		hsSprite->autorelease();
		return hsSprite;
	}
	CC_SAFE_DELETE(hsSprite);
	return NULL;
}

HSCCSprite* HSCCSprite::create(const char* pszFileName,CCRect rect)
{
	HSCCSprite* hsSprite = new HSCCSprite();
	bool ok = hsSprite->initWithFile(pszFileName);
	if (ok == true)
	{
		hsSprite->setTextureRect(rect);
		hsSprite->autorelease();
		return hsSprite;
	}
	CC_SAFE_DELETE(hsSprite);
	return NULL;
}

HSCCSprite* HSCCSprite::create(CCSpriteFrame* pSpriteFrame)
{
	HSCCSprite* hsSprite = new HSCCSprite();
	bool ok = hsSprite->initWithSpriteFrame(pSpriteFrame);
	if (ok == true)
	{
		hsSprite->autorelease();
		return hsSprite;
	}
	CC_SAFE_DELETE(hsSprite);
	return NULL;
}

HSCCSprite* HSCCSprite::create(CCSprite* pSprite)
{
    HSCCSprite* hsSprite = new HSCCSprite();
	bool ok = hsSprite->initWithSprite(pSprite);
	if (ok == true)
	{
		hsSprite->autorelease();
		return hsSprite;
	}
	CC_SAFE_DELETE(hsSprite);
	return NULL;
}

bool HSCCSprite::initWithFile(const char *pszFilename)
{
    m_fileName = pszFilename;
    bool isOk = false;
    
    CCSpriteFrame* pFrame = HSReadPlist::ShareReadPlist()->GetSpriteFrameWithKey(pszFilename);
//    if (!pFrame)
//    {
//        std::string tempFileName = pszFilename;
//        int index = tempFileName.find_last_of('/');
//        tempFileName = tempFileName.assign(tempFileName,index + 1,tempFileName.length());
//        
//        pFrame = HSReadPlist::ShareReadPlist()->GetSpriteFrameWithKey(tempFileName.c_str());
//    }
    if (pFrame)
    {
        isOk = CCSprite::initWithSpriteFrame(pFrame);
    }else{
       isOk = CCSprite::initWithFile(pszFilename);
    }
    return isOk;
}

bool HSCCSprite::initWithSprite(CCSprite* pSprite)
{
    if (!pSprite)
    {
        return false;
    }
    
    bool isOK = CCSprite::initWithTexture(pSprite->getTexture(), pSprite->getTextureRect());
    
    return isOK;
}

bool HSCCSprite::ContainsTouchLocation( CCTouch* touch )
{
	CCSize s = getTexture()->getContentSize();
	CCRect r = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	return r.containsPoint(convertTouchToNodeSpaceAR(touch));
}

HSCCSprite* HSCCSprite::Copy()
{
	HSCCSprite* s = HSCCSprite::create(this->getTexture(),this->getTextureRect(),this->isTextureRectRotated());
	s->setPosition(this->getPosition());
	s->setScaleX(this->getScaleX());
	s->setScaleY(this->getScaleY());
	return s;
}

const char* HSCCSprite::GetFileName()
{
    return m_fileName.c_str();
}






