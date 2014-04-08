#include "HSReadUI.h"



HSReadUI::HSReadUI(void)
{
	this->pReferenceParent = NULL;
	this->pUiMapManage = NULL;
	this->hsReadUIMode = READUI_UNKNOW;
	this->strPlistName = "";
	this->strPng = "";
	this->strDirectory = "";
}

HSReadUI::~HSReadUI(void)
{
	Destroy();
}

HSReadUI* HSReadUI::ShareReadUI()
{
	static HSReadUI s_hsReadUI;
	
	return &s_hsReadUI;
}

void HSReadUI::Destroy()
{
	//HSAssert(this->pReferenceParent,"pReferenceParent != NULL");
	//HSAssert(this->pUiMapManage,"pUiMapManage != NULL");
	if (pUiMapManage)
	{
		pUiMapManage->clear();
	}

	CC_SAFE_DELETE(this->pUiMapManage);

	this->pReferenceParent = NULL;
}

map<std::string,HSUIData>* HSReadUI::ReadUI(const char* uiDataFile,const char* directory,CCNode* layerNode)
{
	//message::UI* uiData = this->OpenUIDataWithGoogleBuffer(uiDataFile);

	message::UI* uiData = this->OpenUIDataWithStream(uiDataFile);

	if (uiData == NULL)
	{
		return NULL;
	}

	if(!this->pUiMapManage)
	{
		this->pUiMapManage  = new map<string,HSUIData>;
	}

	if(!pReferenceParent)
	{
		this->pReferenceParent = layerNode;
	}

	this->hsReadUIMode = READUI_DIRECTORY;

	this->strDirectory = string(directory);

	int fieldCount = uiData->fieldlist_size();
	for(int i=0;i<fieldCount;++i)
	{
		const message::UI_Field parentField = uiData->fieldlist(i);
		this->MakeNode(parentField,layerNode,this->pUiMapManage);
	}

#if 0
	CCLog("*****************************************************");
	map<string,HSUIData>::iterator tempIt = pUiMapManage->begin();
	for(;tempIt!=pUiMapManage->end();++tempIt)
	{
		CCLog("%s -  %d",tempIt->first.c_str(),&tempIt->second);
	}
	CCLog("*****************************************************");
#endif

	CC_SAFE_DELETE(uiData);

	return this->pUiMapManage;
}

map<string,HSUIData>* HSReadUI::ReadUI(const char* uiDataFile,const char* plistName,const char* png,CCNode* layerNode)
{
	message::UI* uiData = this->OpenUIDataWithGoogleBuffer(uiDataFile);


	if (uiData == NULL)
	{
		return NULL;
	}

	if(!this->pUiMapManage)
	{
		this->pUiMapManage  = new map<string,HSUIData>;
	}

	if(!pReferenceParent)
	{
		this->pReferenceParent = layerNode;
	}

	this->strPlistName = plistName;

	this->strPng = png;

	this->hsReadUIMode = READUI_PLIST;

	HSReadPlist::ShareReadPlist()->Open(plistName,png);

	int fieldCount = uiData->fieldlist_size();
	for(int i=0;i<fieldCount;++i)
	{
		const message::UI_Field parentField = uiData->fieldlist(i);
		this->MakeNode(parentField,layerNode,this->pUiMapManage);
	}
#ifdef _DEBUG
	CCLog("*****************************************************");
	map<string,HSUIData>::iterator tempIt = pUiMapManage->begin();
	for(;tempIt!=pUiMapManage->end();++tempIt)
	{
		CCLog("%s  -  %d",tempIt->first.c_str(),&tempIt->second);
	}
	CCLog("*****************************************************");
#endif
	

	CC_SAFE_DELETE(uiData);

	return this->pUiMapManage;
}

void HSReadUI::MakeNode(const message::UI_Field& f,CCNode* layerNode,map<string,HSUIData>* pNodeMap )
{
	HSAssert(pNodeMap && layerNode,"nodeMap Can't for empty , @HSTool::MakeNode");
	if(pNodeMap == NULL)
	{
		return;
	}

	HSUIData hsUIData;
	if(f.objectname() != "")
	{
		hsUIData.field.CopyFrom(f);
		hsUIData.describe = f.describe();
	}

	switch(f.elementtype())
	{
	case message::UI_Field::ElementType_UnKnow:
		HSMessageBox("Fail to other types!");
		break;
	case message::UI_Field::ElementType_Sprite:
		{
			HSCCSprite* hsSprite = this->HandelSprite(f);
			if(f.objectname() != "")
			{
				hsUIData.uiSprite = hsSprite;
				pNodeMap->insert(pair<string,HSUIData>(f.objectname(),hsUIData));
			}
			HSAssert(hsSprite,"");
			HSCCLayer* layer = dynamic_cast<HSCCLayer*>(layerNode);
			if (layer != NULL)
			{
				layer->Push(f.resname(),hsSprite);
				layerNode->addChild(hsSprite,1000);
			}else{
				HSMessageBox(f.resname() + "  Not components");
				return;
			}			
		}		
		break;
	case message::UI_Field::ElementType_Panel:
		{
			hsUIData.uiPanle = this->HandelPanle(f);
			for(int i=0;i<f.childlist_size();++i)
			{
				this->MakeNode(f.childlist(i),hsUIData.uiPanle,pNodeMap);
			}
			if(f.objectname() != "")
			{
				map<string,HSUIData>::iterator it = pNodeMap->find(f.objectname());
				if(it == pNodeMap->end() )
				{
					pNodeMap->insert(pair<string,HSUIData>(f.objectname(),hsUIData));
				}else{					
					HSMessageBox("[ " + f.objectname() + " ]   repeated object name ");
					return;
				}
			}else{
				HSMessageBox("Panel : Object name cannot be empty! \n x: " + HSMath::FtoA(f.dstpointx()) + "   y: " + HSMath::FtoA(f.dstpointy()));
				return;
			}
			HSAssert(hsUIData.uiPanle,"");
			layerNode->addChild(hsUIData.uiPanle,1000);
		}
		break;
	case message::UI_Field::ElementType_Menu:
		{
			hsUIData.uiMenu = this->HandelMenu(f);
			if(f.objectname() != "")
			{
				pNodeMap->insert(pair<string,HSUIData>(f.objectname(),hsUIData));
			}
			HSAssert(hsUIData.uiMenu,"");
			layerNode->addChild(hsUIData.uiMenu,1000);
		}
		break;
	case message::UI_Field::ElementType_Spx:
		{
			hsUIData.uiSpx = this->HandelSpx(f);
			if(f.objectname() != "")
			{
				pNodeMap->insert(pair<string,HSUIData>(f.objectname(),hsUIData));
			}
			HSAssert(hsUIData.uiSpx,"");	
			layerNode->addChild(hsUIData.uiSpx,1000);
		}
		break;
	default:
		{
			HSMessageBox("Invalid UI type @HSTool::MakeNode");
		}
		break;
	}
}

message::UI* HSReadUI::OpenUIDataWithGoogleBuffer( const char* fileName )
{
	string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	HSFileData data(fullFilePath.c_str(),"rb");
	message::UI* uiData = message::UI::default_instance().New();
	bool isOk = uiData->ParsePartialFromArray((const void*)(data.GetBuffer() + sizeof(short)) ,data.GetSize() - sizeof(short));
	if (true == isOk)
	{
		return uiData;
	}
	CC_SAFE_DELETE(uiData);
	return NULL;
}

message::UI* HSReadUI::OpenUIDataWithStream(const char* fileName)
{
	string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);

	HSReadData pReadData(fullFilePath.c_str(),HS_ReadDataMode_CToC);
	message::UI* uiData = message::UI::default_instance().New();

	string layerName = pReadData.ReadUTF8();
	uiData->set_layername(layerName);

	int fieldListCount = pReadData.ReadInt();
	for (int i=0;i<fieldListCount;++i)
	{
		message::UI_Field* childField = uiData->add_fieldlist();
		this->ReadField(childField,&pReadData);
	}

	string version = pReadData.ReadUTF8();
	uiData->set_version(version);

	return uiData;
}

void HSReadUI::ReadField(message::UI_Field* pField,HSReadData* pReadData)
{
	HSAssert(pReadData,"Data cannot be empty");
	HSAssert(pField,"NULL");
	

	string resName = pReadData->ReadUTF8();
	pField->set_resname(resName);

	string objectName = pReadData->ReadUTF8();
	pField->set_objectname(objectName);

	message::UI_Field_ElementType elementType = (message::UI_Field_ElementType)pReadData->ReadInt();
	pField->set_elementtype(elementType);

	string describe = pReadData->ReadUTF8();
	pField->set_describe(describe);

	float srcPointX = pReadData->ReadFloat();
	pField->set_srcpointx(srcPointX);

	float srcPointY = pReadData->ReadFloat();
	pField->set_srcpointy(srcPointY);

	float dstPointX = pReadData->ReadFloat();
	pField->set_dstpointx(dstPointX);

	float dstPointY = pReadData->ReadFloat();
	pField->set_dstpointy(dstPointY);

	float imageW = pReadData->ReadFloat();
	pField->set_imagew(imageW);

	float imageH = pReadData->ReadFloat();
	pField->set_imageh(imageH);

	float originX = pReadData->ReadFloat();
	pField->set_originx(originX);

	float originY = pReadData->ReadFloat();
	pField->set_originy(originY);

	int isVisible = pReadData->ReadInt();
	if (isVisible)
	{
		pField->set_isvisible(true);
	}else{
		pField->set_isvisible(false);
	}

	int opacity = pReadData->ReadInt();
	pField->set_opacity(opacity);

	float scaleX = pReadData->ReadFloat();
	pField->set_scalex(scaleX);

	float scaleY = pReadData->ReadFloat();
	pField->set_scaley(scaleY);

	float rotation = pReadData->ReadFloat();
	pField->set_rotation(rotation);

	float skewX = pReadData->ReadFloat();
	pField->set_skewx(skewX);

	float skewY = pReadData->ReadFloat();
	pField->set_skewy(skewY);

	message::UI_Field_Anchor anchor = (message::UI_Field_Anchor)pReadData->ReadInt();
	pField->set_anchor(anchor);

	float intervalTime = pReadData->ReadFloat();
	pField->set_intervaltime(intervalTime);

	string event = pReadData->ReadUTF8();
	pField->set_event(event);

	int id = pReadData->ReadInt();
	pField->set_id(id);

	int childIDListCount = pReadData->ReadInt();
	for (int i=0;i<childIDListCount;++i)
	{
		int childID = pReadData->ReadInt();
		pField->add_childidlist(childID);
	}

	int isChildType = pReadData->ReadInt();
	if (isChildType)
	{
		pField->set_ischildtype(true);
	}else{
		pField->set_ischildtype(false);
	}

	int childListCount = pReadData->ReadInt();
	for (int i=0;i<childListCount;++i)
	{
		message::UI_Field* childField = pField->add_childlist();
		this->ReadField(childField,pReadData);
	}

}

void HSReadUI::SetProperty(CCNode* pNode,const message::UI_Field& field)
{
	HSAssert(pNode,"");

	if(!HSMath::EqualsWithFloat(field.srcpointx(),0.f) && !HSMath::EqualsWithFloat(field.srcpointy(),0.f))
	{
		pNode->setPosition(ccp(field.srcpointx(),field.srcpointy()));
	}else{
		
		CCPoint pos = CCPointZero;
		CCSize visibleSize = HSBase::GetScreenSize();
		CCPoint origin = HSBase::GetScreenOrigin();

		pos.x = field.dstpointx() + field.imagew() / 2.f;	//Ïà¶ÔX
		pos.y = field.dstpointy() + field.imageh() / 2.f;

		if(true == field.ischildtype())
		{
			//anchor ccp(0.5f,0.5f)
			pos.x = 0.f + pos.x;
			pos.y = 0.f - pos.y;
		}else{
			//anchor ccp(0.f,0.f)
			//pos.x = 0.f + pos.x;
			//pos.y = visibleSize.height - pos.y;
		}
		pNode->setPosition(pos);
	}

	pNode->setScaleX(field.scalex());
	pNode->setScaleY(field.scaley());
	pNode->setRotation(field.rotation());
	pNode->setContentSize(CCSizeMake(field.imagew(),field.imageh()));

	if((int)field.skewx() != 180)
	{
		pNode->setSkewX(field.skewx());
	}

	if((int)field.skewy() != 180)
	{
		pNode->setSkewY(field.skewy());
	}

	pNode->setVisible(field.isvisible());

	
	switch ( field.anchor() )
	{
	case message::UI_Field::Anchor_Centre:
		pNode->setAnchorPoint(ccp(0.5f,0.5f));
		break;
	case message::UI_Field::Anchor_LEFT_UP:
		pNode->setAnchorPoint(ccp(0.f,1.f));
		break;
	case message::UI_Field::Anchor_LEFT_DOWN:
		pNode->setAnchorPoint(ccp(0.f,0.f));
		break;
	case message::UI_Field::Anchor_LEFT_Centre:
		pNode->setAnchorPoint(ccp(0.f,0.5f));
		break;
	case message::UI_Field::Anchor_RIGHT_UP:
		pNode->setAnchorPoint(ccp(1.f,1.f));
		break;
	case message::UI_Field::Anchor_RIGHT_DOWN:
		pNode->setAnchorPoint(ccp(1.f,0.f));
		break;
	case message::UI_Field::Anchor_RIGHT_Centre:
		pNode->setAnchorPoint(ccp(1.f,0.5f));
		break;
	case message::UI_Field::Anchor_UP_Centre:
		pNode->setAnchorPoint(ccp(0.5f,1.f));
		break;
	case message::UI_Field::Anchor_DOWN_Centre:
		pNode->setAnchorPoint(ccp(0.5f,0.f));
		break;
	}
}

HSCCSprite* HSReadUI::HandelSprite( const message::UI_Field& field)
{
	HSCCSprite* pNode = NULL;
	switch( this->GetReadUIMode() )
	{
	case READUI_UNKNOW:
		break;
	case READUI_DIRECTORY:
		{
			string filePath = this->strDirectory + field.resname();
			pNode = HSCCSprite::create(filePath.c_str());
		}
		break;
	case READUI_PLIST:
		{
			pNode = HSReadPlist::ShareReadPlist()->CreateSpriteWithKey(field.resname().c_str());
		}
		break;
	}
	this->SetProperty(pNode,field);
	pNode->setOpacity((GLbyte)field.opacity());
	CCPoint pos = pNode->getPosition();
	if((int)field.skewx() == 180)
	{
		pNode->setFlipY(true);		
		pos.y += pNode->getContentSize().height;
		
	}
	if((int)field.skewy() == 180)
	{
		pNode->setFlipX(true);
		pos.x -= pNode->getContentSize().width;
	}
	//float scale = pNode->getScale() * HS_CONTENT_SCALE;
	//pNode->setScale(scale);
	//pos = ccpMult(pos,HS_CONTENT_SCALE);
	pNode->setPosition(pos);
	return pNode;
}

HSCCLayer* HSReadUI::HandelPanle(const message::UI_Field& field)
{
	HSCCLayer* pNode = HSCCLayer::create();	
	this->SetProperty(pNode,field);

	CCPoint pos = pNode->getPosition();
	if(false == field.ischildtype())
	{
		pos.x = 0.f + field.dstpointx();
		pos.y = (float)HS_MAX_IMAGE_H - field.dstpointy();
	}else{
		pos.x = 0.f + field.dstpointx();
		pos.y = 0.f - field.dstpointy();
	}
	pNode->setPosition(pos);
	return pNode;
}

CCMenu* HSReadUI::HandelMenu( const message::UI_Field& field)
{
	HSAssert(field.resname() != "","");

	std::vector<HSCCSprite*> vResSpriteList;

	string resName = field.resname();
	string resSuffix = ".png";
	string resName1 = resName.substr(0,resName.length() - resSuffix.length() - 1);
	string resName2 = resName.substr(0,resName.length() - 5);
	string menuType = resName1.substr(resName1.length() - 1,resName1.length());

#ifndef UI_MENU_TYPE
#define UI_MENU_TYPE
#define UI_MENU_TYPE_NORMAL "0"
#define UI_MENU_TYPE_TOGGLE "1"
#endif

	for (int i=1;i<3;++i)
	{
		string temp = resName2 + HSMath::ItoA(i,10) + resSuffix;
		string filePath = this->strDirectory + temp;

		switch( this->GetReadUIMode() )
		{
		case READUI_UNKNOW:
			break;
		case READUI_DIRECTORY:
			{				
				if(menuType == UI_MENU_TYPE_NORMAL)
				{
					HSCCSprite* s = HSCCSprite::create(filePath.c_str());
					s->setScaleX(field.scalex());
					s->setScaleY(field.scaley());
					CCSize size = s->getContentSize();
					size.width *= field.scalex();
					size.height *= field.scaley();
					s->setContentSize(size);
					vResSpriteList.push_back(s);
				}else if(menuType == UI_MENU_TYPE_TOGGLE){
					int count = 0;
					while(count < 2)
					{
						HSCCSprite* s = HSCCSprite::create(filePath.c_str());
						s->setScaleX(field.scalex());
						s->setScaleY(field.scaley());
						CCSize size = s->getContentSize();
						size.width *= field.scalex();
						size.height *= field.scaley();
						s->setContentSize(size);
						vResSpriteList.push_back(s);
						++count;
					}
				}
			}
			break;
		case READUI_PLIST:
			{
				HSCCSprite* s = HSReadPlist::ShareReadPlist()->CreateSpriteWithKey(filePath.c_str());
				s->setScaleX(field.scalex());
				s->setScaleY(field.scaley());
				CCSize size = s->getContentSize();
				size.width *= field.scalex();
				size.height *= field.scaley();
				s->setContentSize(size);
				vResSpriteList.push_back(s);
			}
			break;
		}
	}


	CCMenu* menu = NULL;

	//menuType = UI_MENU_TYPE_NORMAL; //test
	if(menuType == UI_MENU_TYPE_NORMAL)
	{
		CCMenuItemSprite* itemImage = CCMenuItemSprite::create(vResSpriteList.at(0),vResSpriteList.at(1));
		menu = CCMenu::create(itemImage,NULL);
	}else if(menuType == UI_MENU_TYPE_TOGGLE){
		CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(vResSpriteList.at(0),vResSpriteList.at(2));
		CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(vResSpriteList.at(3),vResSpriteList.at(1));
		
		CCMenuItemToggle* toggle = CCMenuItemToggle::create(itemImage1);
		toggle->addSubItem(itemImage2);
		menu = CCMenu::create(toggle,NULL);
	}else{
		HSMessageBox("[ " + menuType + " ]Menu :  This type of no definition,support type 0 or 1 ");
	}

	HSAssert(menu != NULL,"");

	

	CCPoint pos = CCPointZero;
	if(false == field.ischildtype())
	{
		pos.x = 0.f + field.dstpointx() + field.imagew() / 2.f;
		pos.y = (float)HS_MAX_IMAGE_H - field.dstpointy() - field.imageh() / 2.f;
	}else{
		pos.x = 0.f + field.dstpointx() + field.imagew() / 2.f;
		pos.y = 0.f - field.dstpointy() - field.imageh() / 2.f;
	}
	menu->setPosition(pos);

	return menu;
}

SPX_Sprite* HSReadUI::HandelSpx(const message::UI_Field& field )
{
	string spxFileName = this->strDirectory + field.resname();
	SPX_Sprite* spx = SPX_Manager::CreateSprite(spxFileName.c_str());

	if(spx == NULL)
	{
		HSMessageBox("[ " + spxFileName + " ] fail ");
		return NULL;
	}

	spx->SetAction(0);

	CCPoint pos = CCPointZero;
	if(false == field.ischildtype())
	{
		//pos.x = 0.f + field.dstpointx();
		//pos.y = (float)HS_MAX_IMAGE_H - field.dstpointy();

		pos.x = 0.f + field.dstpointx() + field.imagew() / 2.f;
		pos.y = (float)HS_MAX_IMAGE_H - field.dstpointy() - field.imageh() / 2.f;
	}else{
		//pos.x = 0.f + field.dstpointx();
		//pos.y = 0.f - field.dstpointy();

		pos.x = 0.f + field.dstpointx() + field.imagew() / 2.f;
		pos.y = 0.f - field.dstpointy() - field.imageh() / 2.f;
	}
	spx->setPosition(pos);

	return spx;
}

HSCCSprite* HSReadUI::FindSprite(const char* keyName)
{
	map<string,HSUIData>::iterator it = this->pUiMapManage->find(string(keyName));
	if(it != this->pUiMapManage->end())
	{
		return it->second.uiSprite;
	}
	return NULL;
}

CCNode* HSReadUI::FindPanel(const char* keyName)
{
	map<string,HSUIData>::iterator it = this->pUiMapManage->find(string(keyName));
	if(it != this->pUiMapManage->end())
	{
		
		return it->second.uiPanle;
	}
	return NULL;
}

HSCCSprite* HSReadUI::FindPanel( const char* keyName,const char* childKey )
{
	HSCCLayer* layer = (HSCCLayer*)FindPanel(keyName);
	HSCCSprite* sprite = layer->Find(string(childKey));
	return sprite;
}

CCMenu* HSReadUI::FindMenu(const char* keyName)
{
	map<string,HSUIData>::iterator it = this->pUiMapManage->find(string(keyName));
	if(it != this->pUiMapManage->end())
	{
		return it->second.uiMenu;
	}
	return NULL;
}

SPX_Sprite* HSReadUI::FindSpx(const char* keyName)
{
	map<string,HSUIData>::iterator it = this->pUiMapManage->find(string(keyName));
	if(it != this->pUiMapManage->end())
	{
		return it->second.uiSpx;
	}
	return NULL;
}

void HSReadUI::SetMenuTarget(const char* keyName,CCObject *rec, SEL_MenuHandler selector)
{
	CCMenu* menu = this->FindMenu(keyName);
	HSAssert(menu,"menu == NULL"); 
	CCArray* pArray = menu->getChildren();
	HSAssert(pArray,"pArray == NULL"); 
	for (unsigned int i=0;i<pArray->count();++i)
	{
		CCObject* obj = pArray->objectAtIndex(i);
		CCMenuItem* menuItem = dynamic_cast<CCMenuItem*>(obj);
		HSAssert(menuItem,"menuItem == NULL");
		menuItem->initWithTarget(rec,selector);
	}
}

CCArray* HSReadUI::GetMenuItemArrayWithCCMenu( const char* keyName,bool isRemoveOfParent )
{
	CCMenu* menu = this->FindMenu(keyName);
	HSAssert(menu,"menu == NULL"); 
	CCArray* pArray = menu->getChildren();
	if (isRemoveOfParent)
	{
		CCArray* pOther = CCArray::createWithCapacity(pArray->count());
		HSAssert(pArray,"pArray == NULL"); 
		for (unsigned int i=0;i<pArray->count();++i)
		{
			CCObject* obj = pArray->objectAtIndex(i);
			CCMenuItem* menuItem = dynamic_cast<CCMenuItem*>(obj);
			CCPoint worldPos = menuItem->convertToWorldSpace(menuItem->getPosition());
			menuItem->setAnchorPoint(HS_ANCHOR_LD);
			menuItem->setPosition(worldPos);
			HSAssert(menuItem,"menuItem == NULL");
			pOther->addObject(menuItem);
			menu->removeChild(menuItem,false);
		}
		return pOther;
	}
	return pArray;
}
