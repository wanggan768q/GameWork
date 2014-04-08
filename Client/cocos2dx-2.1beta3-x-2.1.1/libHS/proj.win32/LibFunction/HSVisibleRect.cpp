#include "HSVisibleRect.h"

CCRect HSVisibleRect::s_visibleRect;

void HSVisibleRect::lazyInit()
{
	if (s_visibleRect.size.width == 0.0f && s_visibleRect.size.height == 0.0f)
	{
		//CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
		//s_visibleRect.origin = pEGLView->getVisibleOrigin();
		//s_visibleRect.size = pEGLView->getVisibleSize();
		s_visibleRect.origin = CCPointZero;
		s_visibleRect.size = CCSizeMake(HSBase::GetMaxImageW(),HSBase::GetMaxImageH());
	}
}

CCRect HSVisibleRect::getVisibleRect()
{
	lazyInit();
	return CCRectMake(s_visibleRect.origin.x, s_visibleRect.origin.y, s_visibleRect.size.width, s_visibleRect.size.height);
}

CCPoint HSVisibleRect::left()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint HSVisibleRect::right()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint HSVisibleRect::top()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint HSVisibleRect::bottom()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

CCPoint HSVisibleRect::center()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint HSVisibleRect::leftTop()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint HSVisibleRect::rightTop()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint HSVisibleRect::leftBottom()
{
	lazyInit();
	return s_visibleRect.origin;
}

CCPoint HSVisibleRect::rightBottom()
{
	lazyInit();
	return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}
