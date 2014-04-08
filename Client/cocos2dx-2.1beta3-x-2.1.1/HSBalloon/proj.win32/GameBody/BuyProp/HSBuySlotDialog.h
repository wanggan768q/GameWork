#ifndef __HSBuySlotDialog_H__
#define __HSBuySlotDialog_H__
#pragma once
#include "HSModalDialogInterface.h"
class HSBuySlotDialog : public HSModalDialogInterface
{
public:
	HSBuySlotDialog(void);
	~HSBuySlotDialog(void);

private:
	CCObject* m_pTarget;
	 
public:
	
	static HSBuySlotDialog* create( CCObject* pTarget );

	bool init( CCObject* pTarget );

	virtual bool InitDialog();
};
#endif