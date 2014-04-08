#include "HSOffset.h"


HSOffset::HSOffset(void)
{
	m_frameSize  = CCEGLView::sharedOpenGLView()->getFrameSize();
	m_lsSize = HSBase::GetTemplateScreenSize();
	m_fScaleY = CCEGLView::sharedOpenGLView()->getScaleY();
	m_fScaleX = CCEGLView::sharedOpenGLView()->getScaleX();
}


HSOffset::~HSOffset(void)
{
}

HSOffset* HSOffset::ShaderOffset()
{
	static HSOffset s_offset;
	return &s_offset;
}

float HSOffset::OffsetX()
{
	float offsetX = (m_frameSize.width - m_lsSize.width * m_fScaleX ) / 2.f / m_fScaleX;
	return offsetX;
}

float HSOffset::OffsetY()
{
	float offsetY = (m_frameSize.height - m_lsSize.height * m_fScaleY ) / 2.f / m_fScaleY;
	return offsetY;
}

float HSOffset::GetScaleX()
{
	return m_fScaleX;
}

float HSOffset::GetScaleY()
{
	return m_fScaleY;
}
