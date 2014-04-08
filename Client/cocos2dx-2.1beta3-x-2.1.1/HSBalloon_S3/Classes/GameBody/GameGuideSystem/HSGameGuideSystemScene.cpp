#include "HSGameGuideSystemScene.h"
//Layer
HSGameGuideSystemLayer::HSGameGuideSystemLayer(void)
{
    m_index = 0;
    m_isAllowTouch = true;
}

HSGameGuideSystemLayer::~HSGameGuideSystemLayer(void)
{
}

bool HSGameGuideSystemLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
    Load();
	this->setTouchEnabled(true);
    
	//this->setIsKeypadEnabled(true);
    
	return true;
}

void HSGameGuideSystemLayer::Load()
{
    static const int max = 100;
    for(int i=0;i<max;++i)
    {
        CCString* fileName = CCString::createWithFormat("Guide/Guide_%02d.png",i);
        CCSprite* s = HSCCSprite::create(fileName->getCString());
        if(s == NULL)
        {
            break;
        }
        if(i == 0 )
        {
            s->setPosition(HSBase::GetTemplateScreenCentre());
        }else{
            CCPoint pos = HSBase::GetTemplateScreenCentre();
            pos.x = pos.x + s->getContentSize().width + 10.f;
            s->setPosition(pos);
        }
        
        this->addChild(s);
        m_guides.push_back(s);
        CC_SAFE_RELEASE_NULL(fileName);
    }
    
	this->schedule(schedule_selector(HSGameGuideSystemLayer::Updata));
}

void HSGameGuideSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSGameGuideSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameGuideSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSGameGuideSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    if(!m_isAllowTouch)
    {
        return;
    }
    
    CCPoint pos = pTouch->getLocation();
    CCPoint centre = HSBase::GetTemplateScreenCentre();
    CCNode* Prev = NULL;
    CCNode* Cur = NULL;
    CCNode* Next = NULL;
    
    int prevIndex = m_index - 1;
    int curIndex = m_index;
    int nextIndex = m_index + 1;
    
    if(prevIndex >= 0 && prevIndex < m_guides.size())
    {
        Prev = m_guides[prevIndex];
    }
    
    if(nextIndex < m_guides.size())
    {
        Next = m_guides[nextIndex];
    }
    
    Cur = m_guides[curIndex];
    
    if(pos.x > centre.x)
    {
        if(Next)
        {
            CCMoveTo* m1 = CCMoveTo::create(0.2, HSBase::GetTemplateScreenCentre());
            Next->runAction(m1);
            
            CCPoint pos = HSBase::GetTemplateScreenCentre();
            pos.x = pos.x - Cur->getContentSize().width - 10.0;
            CCMoveTo* m2 = CCMoveTo::create(0.2, pos);
            Cur->runAction(m2);
            
            ++m_index;
            
            m_isAllowTouch = false;
        }
    }else{
        
        if(Prev)
        {
            CCMoveTo* m1 = CCMoveTo::create(0.2, HSBase::GetTemplateScreenCentre());
            Prev->runAction(m1);
            
            CCPoint pos = HSBase::GetTemplateScreenCentre();
            pos.x = pos.x + Cur->getContentSize().width + 10.0;
            CCMoveTo* m2 = CCMoveTo::create(0.2, pos);
            Cur->runAction(m2);
            
            --m_index;
            
            m_isAllowTouch = false;
        }
    }
    
    if(!m_isAllowTouch)
    {
        CCDelayTime* a1 = CCDelayTime::create(0.2);
        CCCallFunc* a2 = CCCallFunc::create(this, callfunc_selector(HSGameGuideSystemLayer::Call_IntervalTime));
        this->runAction(CCSequence::create(a1,a2,NULL));
    }
}

void HSGameGuideSystemLayer::Call_IntervalTime()
{
    m_isAllowTouch = true;
}

void HSGameGuideSystemLayer::keyBackClicked()
{
    
}
void HSGameGuideSystemLayer::keyMenuClicked()
{
    
}

void HSGameGuideSystemLayer::Updata(float dt)
{
    
}





//Scene
HSGameGuideSystemScene::HSGameGuideSystemScene(void)
{
	this->m_pHSGameGuideSystemLayer = NULL;
}

HSGameGuideSystemScene::~HSGameGuideSystemScene(void)
{
}

bool HSGameGuideSystemScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->m_pHSGameGuideSystemLayer = HSGameGuideSystemLayer::create();
	this->addChild(this->m_pHSGameGuideSystemLayer,HS_BASE_TAG,HS_BASE_TAG);
    
	return true;
}


