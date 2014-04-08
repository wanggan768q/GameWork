#include "HSFileData.h"


HSFileData::HSFileData(const char* pszFileName, const char* pszMode,HSReadModeType readMode /*= READ_MODE_COCOS2DX*/)
{
	this->m_pBuffer = NULL;
	this->m_uSize = 0;
	this->m_readMode = readMode;
	this->m_pFile = NULL;


	switch (m_readMode)
	{
	case READ_MODE_COCOS2DX:
		{
			ReadWithCocos2dx(pszFileName,pszMode);
		}
		break;
	case READ_MODE_FOPEN:
		{
			ReadWithFopen(pszFileName,pszMode);
		}
	}
}


HSFileData::~HSFileData(void)
{
	CC_SAFE_DELETE_ARRAY(this->m_pBuffer);
}

bool HSFileData::Reset(const char* pszFileName, const char* pszMode)
{
	CC_SAFE_DELETE_ARRAY(m_pBuffer);
	m_uSize = 0;
	m_pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, &m_uSize);
	return (m_pBuffer) ? true : false;
}

/*
bool HSFileData::CreateDirectory( string dir )
{
	std::list<string> dirList;	
	int lastNotEqual = 0;
	int level = 0;

	while (dir.find('/',level) != string::npos)
	{
		int begin = dir.find('/',level);
		if (lastNotEqual != begin)
		{
			if(begin != 0)
			{
				string dir = dir.substr(lastNotEqual,begin - lastNotEqual);
				dirList.push_back(dir);
			}
			lastNotEqual = begin;
		}
		level++;
	}

	std::list<string>::iterator it = dirList.begin();
	string basePath = CCFileUtils::sharedFileUtils()->getWriteablePath();
	for (;it!=dirList.end();it++)
	{	
		if (*it != *dirList.begin())
		{
#if WIN32
			basePath += "\\";
#else
			basePath += "/";
#endif			
		}

		basePath += *it;		
#if WIN32
		_mkdir(basePath.c_str());
#else
		mkdir(basePath.c_str(),S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
#endif

	}
	return true;
}
*/


bool HSFileData::CreateDirectoryWithName(const char* directory)
{
	string fileName = directory;
	//检测是否包含目录结构
	if (fileName.find_first_of('/') == string::npos)
	{
		return true;
	}

	string fullPath = CCFileUtils::sharedFileUtils()->getWriteablePath() + string(directory);
	char* dir = const_cast<char*>(fullPath.c_str());
	int i = 0;
	int iRet;
	int iLen = (int)strlen(dir);

	if (dir[iLen - 1] != '\\' && dir[iLen - 1] != '/')
	{
		dir[iLen] = '/';
		dir[iLen + 1] = '\0';
	}

	for (i = 0;i < iLen;i ++)
	{
		if (dir[i] == '\\' || dir[i] == '/')
		{ 
			dir[i] = '\0';

			iRet = HS_ACCESS(dir,0);
			if (iRet != 0)
			{
				iRet = MKDIR(dir);
				if (iRet != 0)
				{
					return false;
				} 
			}
			dir[i] = '/';
		} 
	}

	return true;
}

HSFileData& HSFileData::operator+=(const HSFileData& hsFileData)
{
	unsigned long tempBufSize = this->m_uSize;
	unsigned char* tempBuf = new unsigned char[tempBufSize];
	memcpy(tempBuf,this->m_pBuffer,this->m_uSize);
	CC_SAFE_DELETE_ARRAY(m_pBuffer);

	this->m_uSize += hsFileData.m_uSize;
	this->m_pBuffer = new unsigned char[this->m_uSize];
	memcpy(this->m_pBuffer,tempBuf,tempBufSize);
	memcpy(this->m_pBuffer + tempBufSize,hsFileData.m_pBuffer,hsFileData.m_uSize);
	return *this;
}

void HSFileData::ReadWithFopen(const char* pszFileName, const char* pszMode)
{
	HS_fopen(m_pFile,pszFileName,pszMode);
	if (m_pFile != NULL)
	{
		fseek(m_pFile, 0, SEEK_END);
		m_uSize = ftell(m_pFile);
		fseek(m_pFile, 0, SEEK_SET);

		this->m_pBuffer = new unsigned char[this->m_uSize];
		memset(m_pBuffer,0,m_uSize);
		fread(m_pBuffer,m_uSize,1,m_pFile);	

		fclose(m_pFile);
	}
}

void HSFileData::ReadWithCocos2dx(const char* pszFileName, const char* pszMode)
{
	unsigned char* tempBuf = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, &m_uSize);
	if (tempBuf != NULL)
	{
		this->m_pBuffer = new unsigned char[this->m_uSize];
		memcpy(this->m_pBuffer,tempBuf,this->m_uSize);
		CC_SAFE_DELETE_ARRAY(tempBuf);
	}
}
