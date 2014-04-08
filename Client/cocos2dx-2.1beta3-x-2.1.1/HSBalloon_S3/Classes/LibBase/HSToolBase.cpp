#include "HSToolBase.h"


HSToolBase::HSToolBase(void)
{
}

HSToolBase::~HSToolBase(void)
{
}

void HSToolBase::SetLayerScale(CCNode* layer)
{
	HSAssert(layer,"");
	layer->setContentSize(CCSizeMake(0,0));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	layer->setPosition(ccpAdd(HS_SizeHalf_Point(winSize),ccp(0.f - HSBase::GetTemplateScreenW() / 2.f,0.f - HSBase::GetTemplateScreenH() / 2.f)));
}

void HSToolBase::SetSelfLayerScale(CCNode* layer)
{
	HSAssert(layer,"");
	layer->setContentSize(CCSizeMake(0,0));
	CCSize size = HSBase::GetScreenSize();
	float scaleX = size.width / (float)HS_MAX_IMAGE_W;
	float scaleY = size.height / (float)HS_MAX_IMAGE_H;
	float scale = HS_MATH_MIN(scaleX,scaleY);

	//layer->setScaleX(scaleX);
	//layer->setScaleY(scaleY);

	layer->setScale(scale);

	if (HSMath::EqualsWithFloat(scale,scaleX))
	{
		float d = HSMath::Abs(size.height - HS_MAX_IMAGE_H * scale);
		layer->setPosition(ccp(0.f,d / 2.f));
	}else{
		float d = HSMath::Abs(size.width - HS_MAX_IMAGE_W * scale);
		layer->setPosition(ccp(d / 2.f,0.f));
	}
}

void HSToolBase::SetPointScale( CCPoint& pos )
{
	CCSize size = HSBase::GetScreenSize();
	pos.x = pos.x * size.width / (float)HS_MAX_IMAGE_W;
	pos.y = pos.y * size.height / (float)HS_MAX_IMAGE_H;
}

void HSToolBase::SetRectScale( CCRect& rect )
{
	CCSize size = HSBase::GetScreenSize();
	rect.origin.x = rect.origin.x * size.width / (float)HS_MAX_IMAGE_W;
	rect.origin.y = rect.origin.y * size.height / (float)HS_MAX_IMAGE_H;
}

void HSToolBase::SetNodeFilldScreen( CCNode* pNode )
{
	HSAssert(pNode,"");
	float glViewScaleX = CCEGLView::sharedOpenGLView()->getScaleX();
	float glViewScaleY = CCEGLView::sharedOpenGLView()->getScaleY();

	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCSize lsSize = HSBase::GetTemplateScreenSize();
	float scaleX = frameSize.width/lsSize.width;
	float scaleY = frameSize.height/lsSize.height;

	pNode->setScaleX(scaleX/glViewScaleX);
	pNode->setScaleY(scaleY/glViewScaleY);
}

void HSToolBase::SetLayerFillScreen( CCLayer* pLayer )
{
	HSAssert(pLayer,"");
	pLayer->setContentSize(CCSizeMake(0,0));
	CCSize size = HSBase::GetScreenSize();
	float scaleX = size.width / (float)HS_MAX_IMAGE_W;
	float scaleY = size.height / (float)HS_MAX_IMAGE_H;
	pLayer->setScaleX(scaleX);
	pLayer->setScaleY(scaleY);
}

const CCSize& HSToolBase::SetSizeScale( CCSize& size,float sx,float sy )
{
	size.width *= sx;
	size.height *= sy;

	return size;
}

const CCSize& HSToolBase::SetSizeScale( CCSize& size,float s )
{
	return HSToolBase::SetSizeScale(size,s,s);
}

float HSToolBase::GetOffsetX()
{
	return HSOffset::ShaderOffset()->OffsetX();
}

float HSToolBase::GetOffsetY()
{
	return HSOffset::ShaderOffset()->OffsetY();
}
