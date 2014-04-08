#include "SPX_Data.h"
#include "IO_InputBuffer.h"
#include "HSFileData.h"

#define SPX_HEADER 0x53505833
#define SPX_MIN_VERSION 10
#define SPX_MAX_VERSION 12

SPX_Data::SPX_Data()
{
	refs = 0;
}

SPX_Data::~SPX_Data()
{

}

SPX_ErrorCode SPX_Data::ReadData(SPX_String name)
{

	SPX_ErrorCode errorCode;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	wstring path;
	if(!GE_GetResourcePath(name, path))
	{
		return FileNotFound;
	}
	//		path = L"assets/" + path;

	string fullpath = GE_U2A(path);

	HSFileData fileData(fullpath.c_str(), "rb");
	unsigned char* data = fileData.GetBuffer();

	if(data == NULL)
	{
		return StreamError;
	}

	IO_InputBuffer file;
	if(!file.Open(data, fileData.GetSize()))
	{
		return StreamError;
	}

#else
	wstring path;
	if(!GE_GetResourcePath(name, path))
	{
		return FileNotFound;
	}

	IO_InputFile file;
	if(!file.Open(path))
	{
		return FileNotFound;
	}
#endif

	IO_InputDataStream stream;
	if(!stream.Open(&file))
	{
		return StreamError;
	}

	int headerID = stream.ReadInt();
	if(headerID != SPX_HEADER)
	{
		return InvalidFormat;
	}

	int version = stream.ReadByte();
	if(version < SPX_MIN_VERSION || version > SPX_MAX_VERSION)
	{
		return InvalidFormat;
	}

	int bitmapCount = stream.ReadShort();
	bitmapList.resize(bitmapCount);
	for(int i = 0; i < bitmapCount; ++i)
	{
		errorCode = bitmapList[i].ReadData(&stream);
		if(errorCode != Success)
		{
			return errorCode;
		}
	}

	int tileSetCount = stream.ReadShort();
	tileSetList.resize(tileSetCount);
	for(int i = 0; i < tileSetCount; ++i)
	{
		errorCode = tileSetList[i].ReadData(&stream);
		if(errorCode != Success)
		{
			return errorCode;
		}
	}

	int frameCount = stream.ReadShort();
	frameList.resize(frameCount);
	for(int i = 0; i < frameCount; ++i)
	{
		errorCode = frameList[i].ReadData(&stream);
		if(errorCode != Success)
		{
			return errorCode;
		}
	}

	int actionCount = stream.ReadShort();
	actionList.resize(actionCount);
	for(int i = 0; i < actionCount; ++i)
	{
		errorCode = actionList[i].ReadData(&stream);
		if(errorCode != Success)
		{
			return errorCode;
		}
	}

	for(int i = 0; i < tileSetCount; ++i)
	{
		SPX_TileSet* tileSet = &tileSetList[i];
		if(tileSet == NULL)
		{
			return OutOfMemory;
		}

		tileSet->bitmapIndex = -1;

		for(int j = 0; j < bitmapCount; ++j)
		{
			if(tileSet->bitmapID == bitmapList[j].bitmapID)
			{
				tileSet->bitmapIndex = j;
				break;
			}
		}

		if(tileSet->bitmapIndex == -1)
		{
			return ValueOverflow;
		}
	}

	this->name = name;


	return Success;
}

SPX_ErrorCode SPX_Data::LoadBitmap(SPX_String name)
{
	for(uint i = 0; i < bitmapList.size(); ++i)
	{
		SPX_Bitmap& bitmap = bitmapList[i];
		if(bitmap.texture != NULL)
		{
			delete bitmap.texture;
			bitmap.texture = NULL;
		}

        string namea = GE_U2A(name);

		char buf[512];
		sprintf(buf, "%s%d.png", namea.c_str(), bitmap.bitmapID);
		SPX_String filename = GE_A2U(buf);

		bitmap.texture = SPX_CreateTexture(filename);
	}

	return Success;
}

SPX_ErrorCode SPX_Data::LoadBitmap(SPX_String filename, int bitmapID)
{
	int bitmapIndex = GetBitmapIndex(bitmapID);
	if(bitmapIndex == -1)
	{
		return ValueOverflow;
	}

	SPX_Bitmap& bitmap = bitmapList[bitmapIndex];
	if(bitmap.texture != NULL)
	{
		delete bitmap.texture;
		bitmap.texture = NULL;
	}

	bitmap.texture = SPX_CreateTexture(name);

	return Success;
}

int SPX_Data::GetActionIndex(const char* actionName)
{
	for(uint i = 0; i < actionList.size(); ++i)
	{
		if(strcmp(actionList[i].actionName, actionName) == 0)
		{
			return i;
		}
	}

	return -1;
}

int SPX_Data::GetBitmapIndex(int bitmapID)
{
	for(uint i = 0; i < bitmapList.size(); ++i)
	{
		if(bitmapList[i].bitmapID == bitmapID)
		{
			return i;
		}
	}

	return -1;
}

