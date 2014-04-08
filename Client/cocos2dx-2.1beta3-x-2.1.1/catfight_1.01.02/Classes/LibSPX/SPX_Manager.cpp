#include "SPX_Manager.h"
#include "SPX_Sprite.h"

SPX_Manager::DataList SPX_Manager::dataList;

SPX_Manager::SPX_Manager()
{

}

SPX_Manager::~SPX_Manager()
{

}

SPX_Sprite* SPX_Manager::CreateSprite(const SPX_String& name)
{
	DataList::iterator it = dataList.find(name);
	if(it != dataList.end())
	{
		SPX_Data* data = it->second;

		SPX_Sprite* sprite = new SPX_Sprite();
		if(sprite == NULL)
		{
			return NULL;
		}

		sprite->InitSprite(data);
		data->refs++;

		return sprite;
	}
	else
	{
		SPX_Sprite* sprite = new SPX_Sprite();
		if(sprite == NULL)
		{
			return NULL;
		}

		SPX_Data* data = new SPX_Data();
		if(data->ReadData(name) != Success)
		{
			delete sprite;
			delete data;
			return NULL;
		}

		sprite->InitSprite(data);
		data->refs = 1;

		dataList[name] = data;

		sprite->autorelease();

		return sprite;
	}

	return NULL;
}

SPX_Sprite* SPX_Manager::CreateSprite(const SPX_String& name, const SPX_String& bitmap)
{
	SPX_Sprite* sprite = CreateSprite(name);
	if(sprite != NULL)
	{
		SPX_Data* data = sprite->data;
		if(data != NULL && data->refs == 1)
		{
			data->LoadBitmap(bitmap);
		}

		return sprite;
	}

	return NULL;
}

SPX_Sprite* SPX_Manager::CreateSprite(const char* name)
{
	string spxName = string(name);
	wstring spx;
	wstring png;
	const int SUFFIX_COUNT = 7;

	spx.resize(spxName.size());
	png.resize(spxName.size() - SUFFIX_COUNT);

	for(size_t i = 0; i < spxName.size(); ++i)
	{
		spx[i] = (wstring::value_type)spxName[i];
		if(i < spxName.size() - SUFFIX_COUNT)
		{
			png[i] = (wstring::value_type)spxName[i];
		}
	}
	return SPX_Manager::CreateSprite(spx,png);
}

void SPX_Manager::ReleaseSprite(SPX_Sprite* sprite)
{
	if(sprite->getParent())
	{
		sprite->getParent()->removeChild(sprite,1);
	}

	if(sprite != NULL)
	{
		SPX_Data* data = sprite->data;

		DataList::iterator it = dataList.find(data->name);
		if(it == dataList.end())
		{
			return;
		}

		data->refs--;

		if(data->refs == 0)
		{
			delete data;
		}

		delete sprite;
	}
}

void SPX_Manager::DeleteAll()
{
	for(DataList::iterator it = dataList.begin(); it != dataList.end(); it++)
	{
		delete it->second;
	}

	dataList.clear();
}
