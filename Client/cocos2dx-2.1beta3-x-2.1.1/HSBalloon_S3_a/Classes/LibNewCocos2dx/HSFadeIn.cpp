#include "HSFadeIn.h"


HSFadeIn::HSFadeIn(void)
{
}


HSFadeIn::~HSFadeIn(void)
{
}

HSFadeIn* HSFadeIn::create( float d )
{
	HSFadeIn* pAction = new HSFadeIn();
	if (pAction && pAction->initWithDuration(d))
	{
		pAction->initWithDuration(d);
		pAction->autorelease();
		return pAction;
	}
	CC_SAFE_DELETE(pAction);
	return NULL;
}

void HSFadeIn::update( float time )
{
	update(time,m_pTarget);
}

void HSFadeIn::update( float time,CCObject* pTarget )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pTarget);
	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pTarget);
	if (pNode)
	{
		CCArray* pArray = pNode->getChildren();
		CCObject* obj = NULL;
		CCARRAY_FOREACH(pArray,obj)
		{
			pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(obj);
			if (pRGBAProtocol)
			{
				pRGBAProtocol->setOpacity((GLubyte)(255 * time));
			}else{
				CCNode* pTempNode = dynamic_cast<CCNode*>(obj);
				if (pTempNode)
				{
					this->update(time,pTempNode);
				}
			}
		}
	}else if(pRGBAProtocol){

		pRGBAProtocol->setOpacity((GLubyte)(255 * time));
	}
}
