#include "HSCCSprite.h"

HSCCSprite::HSCCSprite(void)
{
	this->m_clipRect = CCRectMake(0,0,HS_SCREEN_WIDTH,HS_SCREEN_HEIGHT);
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

// void HSCCSprite::SetClip(float lx,float ly,float w,float h)
// {
// 	float scaleX = HS_SCREEN_WIDTH / HS_MAX_IMAGE_W;
// 	float scaleY = HS_SCREEN_HEIGHT / HS_MAX_IMAGE_H;
// 	lx = lx * scaleX;
// 	ly = ly * scaleY;
// 	w = w * scaleX;
// 	h = h * scaleY;
//  	CCPoint position = this->getPosition();
// 	CCSize size = this->getTextureRect().size;
// 	
// 	CCPoint anchor = this->getAnchorPoint();
// 	if (anchor.equals(HS_ANCHOR_CENTER))		//HS_ANCHOR_CENTER
// 	{
// 
// 		position.x -= size.width / 2.f;
// 		position.y -= size.height / 2.f;
// 
// 	}else if(anchor.equals(HS_ANCHOR_LD)){
// 		//
// 	}else if(anchor.equals(HS_ANCHOR_LU)){
// 
// 		position.y -= size.height;
// 
// 	}else if(anchor.equals(HS_ANCHOR_L_CENTER)){
// 
// 		position.y -= size.height / 2.f;
// 
// 	}else if(anchor.equals(HS_ANCHOR_RD)){
// 
// 		position.x -= size.width;
// 
// 	}else if(anchor.equals(HS_ANCHOR_RU)){
// 
// 		position.x -= size.width;
// 		position.y -= size.height;
// 
// 	}else if(anchor.equals(HS_ANCHOR_R_CENTER)){
// 
// 		position.x -= size.width;
// 		position.y -= size.height / 2.f;
// 
// 	}else if(anchor.equals(HS_ANCHOR_U_CENTER)){
// 
// 		position.x -= size.width / 2.f;
// 		position.y -= size.height;
// 
// 	}else if(anchor.equals(HS_ANCHOR_D_CENTER)){
// 
// 		position.x -= size.width / 2.f;
// 
// 	}
// 
// 	m_clipRect = CCRectMake(position.x + lx,position.y + ly,w,h);
// }

bool HSCCSprite::ContainsTouchLocation( CCTouch* touch )
{
	CCSize s = getTexture()->getContentSize();
	CCRect r = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	return r.containsPoint(convertTouchToNodeSpaceAR(touch));
}

HSCCSprite* HSCCSprite::Copy()
{
	HSCCSprite* s = HSCCSprite::create(this->getTexture());
	s->setPosition(this->getPosition());
	s->setScaleX(this->getScaleX());
	s->setScaleY(this->getScaleY());
	return s;
}

// void HSCCSprite::visit()
// {
// 	glEnable(GL_SCISSOR_TEST);//¿ªÆô²Ã¼ô
// 	GLint L_X = (GLint)m_clipRect.getMinX();
// 	GLint L_Y = (GLint)m_clipRect.getMinY();
// 	GLsizei w = (GLsizei)(m_clipRect.size.width);
// 	GLsizei h = (GLsizei)(m_clipRect.size.height);
// 	glScissor(L_X,L_Y,w,h);
// 	CCSprite::visit();
// 	glDisable(GL_SCISSOR_TEST);//¹Ø±Õ²Ã¼ô
// }

