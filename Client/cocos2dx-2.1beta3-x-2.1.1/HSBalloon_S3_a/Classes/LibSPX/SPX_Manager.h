#ifndef __SPX_MANAGER_H__
#define __SPX_MANAGER_H__

#include "SPX_Data.h"

class SPX_Sprite;

class SPX_Manager
{
	typedef map<SPX_String, SPX_Data*> DataList;
	
public:
	SPX_Manager();
	~SPX_Manager();

public:
	static SPX_Sprite* CreateSprite(const SPX_String& name);
	static SPX_Sprite* CreateSprite(const char* name);
	static SPX_Sprite* CreateSprite(const SPX_String& name, const SPX_String& bitmap);
	static void ReleaseSprite(SPX_Sprite* sprite);
	static void DeleteAll();

public:
	static DataList dataList;
};

#endif /*__SPX_MANAGER_H__*/
