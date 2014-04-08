#include "HSBalloonConfig.h"


static HSBalloonConfig* s_hsBalloonConfig = NULL;

HSBalloonConfig::HSBalloonConfig(void)
{
	m_pBallonTestInfo = new BallonTestInfo;
}


HSBalloonConfig::~HSBalloonConfig(void)
{
	CC_SAFE_DELETE(m_pBallonTestInfo);
}

HSBalloonConfig* HSBalloonConfig::SharedBallonCofig()
{
	if (!s_hsBalloonConfig)
	{
		s_hsBalloonConfig = new HSBalloonConfig;
	}
	return s_hsBalloonConfig;
}

void HSBalloonConfig::SaveBallonConfig()
{
	HSAssert(m_pBallonTestInfo,"");
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "ballon.config";
	remove(path.c_str());
	FILE* pFile = NULL;
	HS_FOPEN(pFile,path.c_str(),"w");

	HSAssert(pFile,"");
	fseek( pFile, 0, SEEK_SET );
	fwrite(m_pBallonTestInfo,sizeof(BallonTestInfo),1,pFile);
	fclose(pFile);
}

BallonTestInfo* HSBalloonConfig::ReadBallonConfig()
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "ballon.config";

	FILE* pFile = NULL;
	HS_FOPEN(pFile,path.c_str(),"r");

	if (pFile == NULL)
	{
		m_pBallonTestInfo->default();
		return m_pBallonTestInfo;
	}
	BallonTestInfo config;
	fread(&config,sizeof(BallonTestInfo),1,pFile);
	fclose(pFile);

	m_pBallonTestInfo->Set(config);
	return m_pBallonTestInfo;
}

void HSBalloonConfig::RestBallonConfig()
{
	m_pBallonTestInfo->default();
}

void HSBalloonConfig::Destroy()
{
	CC_SAFE_DELETE(s_hsBalloonConfig);
}
