#include "HSGlobal.h"


static HSGlobal* s_hsGlobal = new HSGlobal;

HSGlobal::HSGlobal()
{
	s1 = true;
	s2 = true;
	s3 = true;
	s4 = true;
	s5 = true;
}

HSGlobal::~HSGlobal()
{

}

bool HSGlobal::init()
{
	return true;
}

HSGlobal* HSGlobal::ShaderGlobal()
{
	if(s_hsGlobal)
	{
		s_hsGlobal = new HSGlobal();
		s_hsGlobal->autorelease();
		s_hsGlobal->retain();
		s_hsGlobal->init();
	}
	return s_hsGlobal;
}

void HSGlobal::AddCloud(CCLayer* pTarget)
{

	if(pTarget)
	{
		if(s1)
		{

			CCSprite* pCloud1 = dynamic_cast<CCSprite*> (pTarget->getChildByTag(301));
			if(pCloud1==NULL)
			{
				pCloud1 = HSCCSprite::create("Image/main_cloud1.png");
				pCloud1->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud1->setPosition(ccp(0.0,-HSToolBase::GetOffsetY()));
				pCloud1->setTag(301);
				pTarget->addChild(pCloud1,100);
			}
			CallCloud(pCloud1);

			CCSprite* pCloud1s = dynamic_cast<CCSprite*> (pTarget->getChildByTag(311));
			if(pCloud1s==NULL)
			{
				pCloud1s = HSCCSprite::create("Image/main_cloud1.png");
				pCloud1s->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud1s->setPosition(ccp(pCloud1s->getContentSize().width,-HSToolBase::GetOffsetY()));
				pCloud1s->setTag(311);
				pTarget->addChild(pCloud1s,100);
			}
			CallCloud(pCloud1s);

			CCSprite* pCloud1ss = dynamic_cast<CCSprite*> (pTarget->getChildByTag(321));
			if(pCloud1ss==NULL)
			{
				pCloud1ss = HSCCSprite::create("Image/main_cloud1.png");
				pCloud1ss->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud1ss->setPosition(ccp(pCloud1ss->getContentSize().width*2,-HSToolBase::GetOffsetY()));
				pCloud1ss->setTag(321);
				pTarget->addChild(pCloud1ss,100);
			}
			CallCloud(pCloud1ss);
		}


		if(s2)
		{

			CCSprite* pCloud2 = dynamic_cast<CCSprite*> (pTarget->getChildByTag(302));
			if(pCloud2==NULL)
			{
				pCloud2 = HSCCSprite::create("Image/main_cloud2.png");
				pCloud2->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud2->setPosition(ccp(0.0,-HSToolBase::GetOffsetY()));
				pCloud2->setTag(302);
				pTarget->addChild(pCloud2,100);
			}
			CallCloud(pCloud2);

			CCSprite* pCloud2s = dynamic_cast<CCSprite*> (pTarget->getChildByTag(312));
			if(pCloud2s==NULL)
			{
				pCloud2s = HSCCSprite::create("Image/main_cloud2.png");
				pCloud2s->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud2s->setPosition(ccp(pCloud2s->getContentSize().width,-HSToolBase::GetOffsetY()));
				pCloud2s->setTag(312);
				pTarget->addChild(pCloud2s,100);
			}
			CallCloud(pCloud2s);

			CCSprite* pCloud2ss = dynamic_cast<CCSprite*> (pTarget->getChildByTag(322));
			if(pCloud2ss==NULL)
			{
				pCloud2ss = HSCCSprite::create("Image/main_cloud2.png");
				pCloud2ss->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud2ss->setPosition(ccp(pCloud2ss->getContentSize().width*2,-HSToolBase::GetOffsetY()));
				pCloud2ss->setTag(322);
				pTarget->addChild(pCloud2ss,100);
			}
			CallCloud(pCloud2ss);

		}

		if(s3)
		{

			CCSprite* pCloud3 =dynamic_cast<CCSprite*> (pTarget->getChildByTag(303));
			if(pCloud3==NULL)
			{
				pCloud3 = HSCCSprite::create("Image/main_cloud3.png");
				pCloud3->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud3->setPosition(ccp(0.0,-HSToolBase::GetOffsetY()));
				pCloud3->setTag(303);
				pTarget->addChild(pCloud3,100);
			}
			CallCloud(pCloud3);

			CCSprite* pCloud3s =dynamic_cast<CCSprite*> (pTarget->getChildByTag(313));
			if(pCloud3s==NULL)
			{
				pCloud3s = HSCCSprite::create("Image/main_cloud3.png");
				pCloud3s->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud3s->setPosition(ccp(pCloud3s->getContentSize().width,-HSToolBase::GetOffsetY()));
				pCloud3s->setTag(313);
				pTarget->addChild(pCloud3s,100);
			}
			CallCloud(pCloud3s);

			CCSprite* pCloud3ss = dynamic_cast<CCSprite*> (pTarget->getChildByTag(323));
			if(pCloud3ss==NULL)
			{
				pCloud3ss = HSCCSprite::create("Image/main_cloud3.png");
				pCloud3ss->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud3ss->setPosition(ccp(pCloud3ss->getContentSize().width*2,-HSToolBase::GetOffsetY()));
				pCloud3ss->setTag(323);
				pTarget->addChild(pCloud3ss,100);
			}

			CallCloud(pCloud3ss);
		}

		if(s4)
		{
			CCSprite* pCloud4 = dynamic_cast<CCSprite*> (pTarget->getChildByTag(304));

			if(pCloud4==NULL)
			{
				pCloud4 = HSCCSprite::create("Image/main_cloud4.png");
				pCloud4->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud4->setPosition(ccp(0.0,-HSToolBase::GetOffsetY()));
				pCloud4->setTag(304);
				pTarget->addChild(pCloud4,100);
			}
			CallCloud(pCloud4);

			CCSprite* pCloud4s = dynamic_cast<CCSprite*> (pTarget->getChildByTag(314));
			if(pCloud4s==NULL)
			{
				pCloud4s = HSCCSprite::create("Image/main_cloud4.png");
				pCloud4s->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud4s->setPosition(ccp(pCloud4s->getContentSize().width,-HSToolBase::GetOffsetY()));
				pCloud4s->setTag(314);
				pTarget->addChild(pCloud4s,100);
			}

			CallCloud(pCloud4s);

			CCSprite* pCloud4ss = dynamic_cast<CCSprite*> (pTarget->getChildByTag(324));

			if(pCloud4ss==NULL)
			{
				pCloud4ss = HSCCSprite::create("Image/main_cloud4.png");
				pCloud4ss->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud4ss->setPosition(ccp(pCloud4ss->getContentSize().width*2,-HSToolBase::GetOffsetY()));
				pCloud4ss->setTag(324);
				pTarget->addChild(pCloud4ss,100);
			}

			CallCloud(pCloud4ss);

		}

		if(s5)
		{

			CCSprite* pCloud5 = dynamic_cast<CCSprite*> (pTarget->getChildByTag(305));

			if(pCloud5==NULL)
			{
				pCloud5 = HSCCSprite::create("Image/main_cloud5.png");
				pCloud5->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud5->setPosition(ccp(0.0,-HSToolBase::GetOffsetY()));
				pCloud5->setTag(305);
				pTarget->addChild(pCloud5,100);
			}

			CallCloud(pCloud5);

			CCSprite* pCloud5s = dynamic_cast<CCSprite*> (pTarget->getChildByTag(315));
			if(pCloud5s==NULL)
			{

				pCloud5s = HSCCSprite::create("Image/main_cloud5.png");
				pCloud5s->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud5s->setPosition(ccp(pCloud5s->getContentSize().width,-HSToolBase::GetOffsetY()));
				pCloud5s->setTag(315);
				pTarget->addChild(pCloud5s,100);
			}

			CallCloud(pCloud5s);

			CCSprite* pCloud5ss = dynamic_cast<CCSprite*> (pTarget->getChildByTag(325));

			if(pCloud5ss==NULL)
			{
				pCloud5ss = HSCCSprite::create("Image/main_cloud5.png");
				pCloud5ss->setAnchorPoint(ccp(0.0,0.0));//所有的锚点在坐下
				pCloud5ss->setPosition(ccp(pCloud5ss->getContentSize().width*2,-HSToolBase::GetOffsetY()));
				pCloud5ss->setTag(325);
				pTarget->addChild(pCloud5ss,100);
			}

			CallCloud(pCloud5ss);
		}
	}
}

void HSGlobal::CallCloud(CCNode* node)
{
	int t1 = node->getTag()%100;

	int t2 = node->getTag()%10;

	if(t1>20)
	{
		node->setPositionX(node->getContentSize().width*2+(t2==1?300.f:0.f)*2);
	}
	else if((t1>10)&&(t1<20))
	{
		node->setPositionX(node->getContentSize().width+(t2==1?300.f:0.f));
	}
	else if((t1>0) &&(t1<10))
	{
		node->setPositionX(0.f);
	}

	float time = 0.f;

	if(t2 ==1)
	{
		time = 8;
	}
	else if(t2 ==2)
	{
		time = 8;
	}
	else if(t2==3)
	{
		time = 10;
	}
	else if(t2 == 4)
	{
		time = 12;
	}
	else if(t2 == 5)
	{
		time = 14;
	}

	CCActionInterval* action = CCMoveTo::create(time,ccp(node->getPositionX()-node->getContentSize().width-(t2==1?300.f:0.f),node->getPositionY()));
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSGlobal::CallCloud));
	node->runAction(CCSequence::create(action,pCall,NULL));
}

