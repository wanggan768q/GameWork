/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/01/08   17:45
 *	File base:	HSReadUI.h
 *	Author:		Ambition
 *	
 *	Purpose:
 *
 *				1.2013-05-07 11:02:37 (修改map内存泄漏问题,修改成以后在切换场景的时候调用 Destroy ,其他时候不用调用)
*********************************************************************/
#ifndef __HSReadUI_H__
#define __HSReadUI_H__
#pragma once
#include "HSBase.h"
#include "HSDataStruct.h"
#include "HSCCSprite.h"
#include "HSMath.h"
#include "SPX_Manager.h"
#include "SPX_Sprite.h"
#include "HSReadPlist.h"
#include "HSCCLayer.h"
#include "HSReadData.h"


#ifndef HS_FIND_UI
#define HS_FIND_UI
#define HS_FIND_UI_SPRITER( __keyName__ ) HSReadUI::ShareReadUI()->FindSprite(__keyName__)
#define HS_FIND_UI_PANEL( __keyName__ ) HSReadUI::ShareReadUI()->FindPanel(__keyName__)
#define HS_FIND_UI_PANEL_SPRITE(__keyName__ , __ChildKeyName__) HSReadUI::ShareReadUI()->FindPanel(__keyName__,__ChildKeyName__)
#define HS_FIND_UI_MENU( __keyName__ ) HSReadUI::ShareReadUI()->FindMenu(__keyName__)
#define HS_FIND_UI_SPX( __keyName__ ) HSReadUI::ShareReadUI()->FindSpx(__keyName__)
#define HS_FIND_UI_MENUITEM_ARRAY_Remove_of_Parent( __keyName__ ) HSReadUI::ShareReadUI()->GetMenuItemArrayWithCCMenu(__keyName__,true)
#define HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent( __keyName__ ) HSReadUI::ShareReadUI()->GetMenuItemArrayWithCCMenu(__keyName__,false)

#define HS_SET_MENU_TARGET(__keyName__,__rec__,__selector__) \
{ \
	HSReadUI::ShareReadUI()->SetMenuTarget(__keyName__,__rec__,menu_selector(__selector__)); \
}
#endif


class HSReadUI
{
private:
	HSReadUI(void);
public:
	~HSReadUI(void);

private:
	std::map<string,HSUIData>* pUiMapManage;
    std::vector<std::string> m_allFile;

	CCNode* pReferenceParent;

	typedef enum{
		READUI_UNKNOW = 0x0a,
		READUI_DIRECTORY,
		READUI_PLIST,
	}HSReadUIMode;

	HSReadUIMode hsReadUIMode;

	string strDirectory;
	string strPlistName;
	string strPng;

public:
	static HSReadUI* ShareReadUI();

	void Destroy();

	map<string,HSUIData>* ReadUI(const char* uiDataFile,const char* directory,CCNode* layerNode);

	map<string,HSUIData>* ReadUI(const char* uiDataFile,const char* plistName,const char* png,CCNode* layerNode);

	HSCCSprite* FindSprite(const char* keyName);

	CCNode* FindPanel(const char* keyName);

	HSCCSprite* FindPanel(const char* keyName,const char* childKey);

	CCMenu* FindMenu(const char* keyName);

	SPX_Sprite* FindSpx(const char* keyName);

	CCArray* GetMenuItemArrayWithCCMenu(const char* keyName,bool isRemoveOfParent);

	void SetMenuTarget(const char* keyName,CCObject *rec, SEL_MenuHandler selector);
	
	inline std::map<string,HSUIData>* GetUIMapManage(){ return this->pUiMapManage;}

private:
	void MakeNode(const message::UI_Field& f,CCNode* layerNode,map<string,HSUIData>* pNodeMap);
	
	message::UI* OpenUIDataWithGoogleBuffer(const char* fileName);

	message::UI* OpenUIDataWithStream(const char* fileName);

	void ReadField(message::UI_Field* pField,HSReadData* pReadData);

	void SetProperty(CCNode* pNode,const message::UI_Field& field);
	
	HSCCSprite* HandelSprite(const message::UI_Field& field);
	
	HSCCLayer* HandelPanle(const message::UI_Field& field);
	
	CCMenu* HandelMenu(const message::UI_Field& field );

	SPX_Sprite* HandelSpx(const message::UI_Field& field );

	inline HSReadUIMode GetReadUIMode(){ return hsReadUIMode;}

};


#endif // __HSReadUI_H____
