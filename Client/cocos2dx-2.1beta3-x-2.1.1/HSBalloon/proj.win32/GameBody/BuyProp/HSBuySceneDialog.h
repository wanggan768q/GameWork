#ifndef __HSBuySceneDialog_H__
#define __HSBuySceneDialog_H__
#pragma once
#include "HSModalDialogInterface.h"
class HSBuySceneDialog : public HSModalDialogInterface
{
public:
	HSBuySceneDialog(void);
	~HSBuySceneDialog(void);

private:
	CCObject* m_pTarget;

public:

	static HSBuySceneDialog* create( CCObject* pTarget );

	bool init( CCObject* pTarget );

	virtual bool InitDialog();
};
#endif