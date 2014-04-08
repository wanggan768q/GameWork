#ifndef __HSBuyShopDialog_H__
#define __HSBuyShopDialog_H__
#pragma once
#include "HSModalDialogInterface.h"
class HSBuyShopDialog : public HSModalDialogInterface
{
public:
	HSBuyShopDialog(void);
	~HSBuyShopDialog(void);

private:
	CCObject* m_pTarget;

	CCLabelAtlas* m_pGameGold;	//½ð±Ò×Ö
	int m_curpGold;
public:

	static HSBuyShopDialog* create( CCObject* pTarget );

	bool init( CCObject* pTarget );

	virtual bool InitDialog();

	void Update(float dt);
};
#endif