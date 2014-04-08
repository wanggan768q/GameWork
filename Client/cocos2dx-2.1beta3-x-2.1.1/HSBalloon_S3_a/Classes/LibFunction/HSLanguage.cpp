#include "HSLanguage.h"


HSLanguage::HSLanguage(void)
{
	m_pLanguageData = NULL;
}


HSLanguage::~HSLanguage(void)
{
	CC_SAFE_DELETE(m_pLanguageData);
}

HSLanguage* HSLanguage::ShaderLanguage()
{
	static HSLanguage s_hsLanguage;
	return &s_hsLanguage;
}

void HSLanguage::Read( const char* fileName,const char* currentLanguage )
{
	std::string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	HSFileData fileData(fullFilePath.c_str(),"rb");

	if (!m_pLanguageData)
	{
		m_pLanguageData = LanguageData::default_instance().New();
	}
	m_pLanguageData->Clear();
	bool isOk = m_pLanguageData->ParseFromArray(fileData.GetBuffer() + 2,fileData.GetSize() - 2);

	if (!isOk)
	{
		HSMessageBox("Failure load language");
		CC_SAFE_DELETE(m_pLanguageData);
		return;
	}

	int languageCount = m_pLanguageData->language_size();
	for (int i=0;i<languageCount;++i)
	{
		const LanguageData_Language pLanguage = m_pLanguageData->language(i);

		std::string key = pLanguage.key();

		int statementCount = pLanguage.statement_size();
		for (int j=0;j<statementCount;++j)
		{
			const LanguageData_Statement statement = pLanguage.statement(j);

			std::string country = statement.country();
			if (0 == country.compare(currentLanguage))
			{
				std::string talk = statement.talk();

				m_LanguageMap.insert(pair<std::string,std::string>(key.c_str(),talk.c_str()));
			}
		}
	}
#if WIN32
	CCLog("*****************************************************");
	std::map<std::string,std::string>::iterator it = m_LanguageMap.begin();
	for (;it != m_LanguageMap.end();++it)
	{
		CCLog("Language: %s == %s",it->first.c_str(),it->second.c_str());
	}
	CCLog("*****************************************************");
#endif
}

const char* HSLanguage::Find( const char* key )
{
	std::map<std::string,std::string>::iterator it = m_LanguageMap.find(key);

	if (it != m_LanguageMap.end())
	{
		return it->second.c_str();
	}
	return "";
}
