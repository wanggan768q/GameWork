#include "HSJson.h"

#ifdef HS_USING_HSJson

HSJson::HSJson(void)
{
}


HSJson::~HSJson(void)
{
}

HSJson* HSJson::CreateWithFile( const char* pFileName )
{
	HSJson* pJson = new HSJson;
	if (pJson && pJson->InitWithFile(pFileName))
	{
		pJson->autorelease();
		return pJson;
	}
	CC_SAFE_DELETE(pJson);
	return NULL;
}

HSJson* HSJson::CreateWithData( const void* pData )
{
	HSJson* pJson = new HSJson;
	if (pJson && pJson->InitWithData(pData))
	{
		pJson->autorelease();
		return pJson;
	}
	CC_SAFE_DELETE(pJson);
	return NULL;
}

HSJson* HSJson::CreateWithWriter()
{
	HSJson* pJson = new HSJson;
	if (pJson && pJson->InitWithWriter())
	{
		pJson->autorelease();
		return pJson;
	}
	CC_SAFE_DELETE(pJson);
	return NULL;
}


bool HSJson::InitWithFile( const char* pFileName )
{
	HSFileData hsFileData(pFileName,"rb");
	HSAssert(hsFileData.GetSize() > 0,CCString::createWithFormat("[ %s ] file is open fail",pFileName)->getCString());
	if (hsFileData.GetSize() <= 0)
	{
		HSMessageBox(CCString::createWithFormat("[ %s ] file is open fail",pFileName)->getCString());
		return false;
	}
	std::string jsonData ;
	jsonData.assign((char*)hsFileData.GetBuffer(), hsFileData.GetSize());

	if  (!m_reader.parse(jsonData, m_root, false )) 
	{
		HSMessageBox(CCString::createWithFormat("[ %s ] Parse error",pFileName)->getCString());
		return false;
	}
	return true;
}

bool HSJson::InitWithData( const void* pData )
{
	if (!pData)
	{
		return false;
	}
	std::string jsonData ;
	jsonData.assign((char*)pData, strlen((char*)pData));

	if  (!m_reader.parse(jsonData, m_root, false )) 
	{
		HSMessageBox("JSon Parse error");
		return false;
	}
	return true;
}

const Json::Value& HSJson::GetValue()
{
	return m_root;
}

bool HSJson::InitWithWriter()
{
	return true;
}

const std::string HSJson::Writer( const Json::Value& data )
{
	//m_root.append(data);
    m_root = data;
	return m_fastWriter.write(m_root);
}

#endif
