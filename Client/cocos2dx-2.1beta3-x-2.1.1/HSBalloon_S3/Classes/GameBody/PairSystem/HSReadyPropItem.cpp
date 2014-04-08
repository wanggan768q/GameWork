#include "HSReadyPropItem.h"
#include "HSGameCache.h"

HSReadyPropItem::HSReadyPropItem(void)
{
    m_pToggle = NULL;
    m_pJiaoBiao = NULL;
    m_pSuo = NULL;
    m_isNeedCarry = false;
}

HSReadyPropItem::~HSReadyPropItem(void)
{
}

HSReadyPropItem* HSReadyPropItem::create(const PropInfo& propInfo,int index)
{
    HSReadyPropItem* p = new HSReadyPropItem;
    if (p && p->init(propInfo,index))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

bool HSReadyPropItem::init(const PropInfo& propInfo,int index)
{
    m_propInfo = &propInfo;
    
    CCString* pStr_01 = CCString::createWithFormat("UI_Benfangxinxiban_Daoju_%02d",index);
    
    m_pJiaoBiao = HS_FIND_UI_PANEL_SPRITE(pStr_01->getCString(), "Pipeidaojujiaobiao");
    m_pSuo = HS_FIND_UI_PANEL_SPRITE(pStr_01->getCString(), "Pipeidaojusuo");
    HSAssert(m_pJiaoBiao, "");
    HSAssert(m_pSuo, "");
    m_pJiaoBiao->setVisible(false);
    
    CCString* pStr = CCString::createWithFormat("Image/%s",m_propInfo->localname().c_str());
    
    CCSprite* pNode_0,  *pNode_1,   *pNode_2,   *pNode_3;
    int level = HS_TARGET_SELF().level();
    level = 5;
    m_isNeedCarry = level > m_propInfo->unlocklevel();
    if(m_isNeedCarry)
    {
        pNode_0 = HSCCSprite::create(pStr->getCString());
        pNode_1 = HSCCSprite::create(pStr->getCString());
        
        pNode_2 = HSCCSprite::create(pStr->getCString());
        pNode_3 = HSCCSprite::create(pStr->getCString());
        
        m_pSuo->setVisible(false);
        
        if(IsAlreadyCarry())
        {
            m_pJiaoBiao->setVisible(true);
        }
        
        pNode_1->setScale(1.02f);
        pNode_3->setScale(1.02f);
        
    }else{
        pNode_0 = HSGraySprite::create(pStr->getCString());
        pNode_1 = HSGraySprite::create(pStr->getCString());
        
        pNode_2 = HSGraySprite::create(pStr->getCString());
        pNode_3 = HSGraySprite::create(pStr->getCString());
    }
    
	
    
    CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(pNode_0,pNode_2);
	CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(pNode_1,pNode_3);
    
	m_pToggle = CCMenuItemToggle::createWithTarget(this,menu_selector(HSReadyPropItem::Call),itemImage1,itemImage2,NULL);
    m_pToggle->setPosition(m_pSuo->getPosition());
    //m_pSuo->getParent()->addChild(m_pToggle,1100);
    CCMenu* pMenu = CCMenu::create(m_pToggle,NULL);
    pMenu->setPosition(CCPointZero);
    m_pSuo->getParent()->addChild(pMenu);
    
    CC_SAFE_RELEASE_NULL(pStr);
    CC_SAFE_RELEASE_NULL(pStr_01);
    
	return true;
}

void HSReadyPropItem::Call(CCObject* obj)
{
    CCNode* pDescribe = HS_FIND_UI_PANEL_SPRITE("UI_Benfangxinxiban_Pipeidaojushuoming", "Pipeishuomingquyu");
    
    CCObject* child;
    CCARRAY_FOREACH(pDescribe->getChildren(), child)
    {
        CCNode* pNode = (CCNode*)child;
        pNode->setVisible(false);
    }
    CCLabelTTF* ttf = CCLabelTTF::create(m_propInfo->describ().c_str(), HS_FONT_HuaKang, 18, pDescribe->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    ttf->setPosition(pDescribe->getAnchorPointInPoints());
    ttf->setColor(ccBLACK);
    pDescribe->addChild(ttf);
    
    //允许携带
    if(m_isNeedCarry)
    {
        bool isAlreadyCarry = false;
        vector<const message::PropInfo*>* pv = &HS_GAME_CACHE()->m_pFightingProp;
        vector<const message::PropInfo*>::iterator it = pv->begin();
        for (; it != pv->end(); ++it)
        {
            const message::PropInfo* tempInfo = (*it);
            //查看是否已经携带过
            if(tempInfo->id() == m_propInfo->id())
            {
                pv->erase(it);
                m_pJiaoBiao->setVisible(false);
                isAlreadyCarry = true;
                break;
            }
        }
        
        //没有携带 就添加
        if(!isAlreadyCarry)
        {
            pv->push_back(m_propInfo);
            m_pJiaoBiao->setVisible(true);
        }
    }
    
    CCLog("Call_ID : %d",m_propInfo->id());
}

bool HSReadyPropItem::IsAlreadyCarry()
{
    vector<const message::PropInfo*>* pv = &HS_GAME_CACHE()->m_pFightingProp;
    vector<const message::PropInfo*>::iterator it = pv->begin();
    for (; it != pv->end(); ++it)
    {
        const message::PropInfo* tempInfo = (*it);
        //查看是否已经携带过
        if(tempInfo->id() == m_propInfo->id())
        {
            return true;
        }
    }
    return false;
}



























