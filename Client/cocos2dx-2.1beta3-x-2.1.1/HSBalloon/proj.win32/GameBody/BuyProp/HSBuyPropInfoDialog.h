#ifndef __HSBuyPropInfoDialog_H__
#define __HSBuyPropInfoDialog_H__
#pragma once
#include "HSModalDialogInterface.h"

class HSBuyPropInfoDialog : public HSModalDialogInterface
{
public:
	HSBuyPropInfoDialog(void);
	~HSBuyPropInfoDialog(void);

private:
	CCObject* m_pTarget;
public:
	CCLabelAtlas* m_pGameGold;
	int m_curpGold;

	int m_PropId;
	CCSprite* m_pPropIcon;
	CCLabelTTF* m_pPropName;
	CCLabelAtlas* m_pPropMoney;
	CCLabelTTF* m_pPropDiscrib;
public:

	static HSBuyPropInfoDialog* create( CCObject* pTarget );

	bool init( CCObject* pTarget );

	virtual bool InitDialog();

	void Buy(CCObject* obj);

	void Close(CCObject* obj);

	void Update(float dt);

	void setProp(int id);
};
#endif