#include "HSBalloonConfig.h"


static HSBalloonConfig* s_hsBalloonConfig = NULL;

HSBalloonConfig::HSBalloonConfig(void)
{
	m_pBalloonTestInfo = new BalloonTestInfo;
	m_pBGD = new BalloonGameData;
	m_lastTime = HSTime::GetLocalityTime();
	m_dt = 0.f;
	m_isPauseUpdate = false;

	m_stratagemMoveStep = 0;
}


HSBalloonConfig::~HSBalloonConfig(void)
{
	CC_SAFE_DELETE(m_pBalloonTestInfo);
	CC_SAFE_DELETE(m_pBGD);
}

void HSBalloonConfig::Reset()
{
	m_lastTime = HSTime::GetLocalityTime();
	m_dt = 0.f;
	m_isPauseUpdate = false;
	m_stratagemMoveStep = 0;

	m_isOvertime = true;

	m_pBGD->Reset();
}

HSBalloonConfig* HSBalloonConfig::SharedBalloonCofig()
{
	if (!s_hsBalloonConfig)
	{
		s_hsBalloonConfig = new HSBalloonConfig;
	}
	return s_hsBalloonConfig;
}

void HSBalloonConfig::SaveBallonConfig()
{
	HSAssert(m_pBalloonTestInfo,"");
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "ballon.config";
	remove(path.c_str());
	FILE* pFile = NULL;
	HS_fopen(pFile,path.c_str(),"w");

	HSAssert(pFile,"");
	fseek( pFile, 0, SEEK_SET );
	fwrite(m_pBalloonTestInfo,sizeof(BalloonTestInfo),1,pFile);
	fclose(pFile);
}

BalloonTestInfo* HSBalloonConfig::ReadBalloonConfig()
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	path += "ballon.config";

	FILE* pFile = NULL;
	HS_fopen(pFile,path.c_str(),"r");

	if (pFile == NULL)
	{
		m_pBalloonTestInfo->Reset();
		return m_pBalloonTestInfo;
	}
	BalloonTestInfo config;
	fread(&config,sizeof(BalloonTestInfo),1,pFile);
	fclose(pFile);

	m_pBalloonTestInfo->Set(config);
	return m_pBalloonTestInfo;
}

void HSBalloonConfig::RestBallonConfig()
{
	m_pBalloonTestInfo->Reset();
}

void HSBalloonConfig::Destroy()
{
	CC_SAFE_DELETE(s_hsBalloonConfig);
}

void HSBalloonConfig::DribbleLogic( BalloonColorType colorType , int balloonID)
{
	unsigned long long curTime = HSTime::GetLocalityTime();
	unsigned long long interval = curTime - m_lastTime;

	m_lastTime = curTime;

	float second = interval / 1000.f;

	//判断是否在间隔时间内
// 	if (second < m_pBGD->dribbleIntervalTime)
// 	{
// 		m_pBGD->bangBalloonCount++;
// 
// 		//判断这次的颜色跟上次的颜色是否一致
// 		if(m_pBGD->lastBalloonColorType != colorType)
// 		{
// 			m_pBGD->playSoundID = 0;
// 			m_pBGD->lastBalloonColorType = colorType;
// 			m_pBGD->dribbleCount = 0;
// 			//m_pBGD->isDribbleFail = true;	//连击失败
// 		}else{
// 			m_pBGD->playSoundID++;
// 			m_pBGD->dribbleCount++;
// 			//m_pBGD->isDribbleFail = false;
// 		}
// 	}else{
// 		m_pBGD->playSoundID = 0;
// 		m_pBGD->dribbleCount = 0;
// 		m_pBGD->isDribbleFail = true;	//连击失败
// 
// 	}
	m_pBGD->comboCount = m_pBGD->dribbleCount;

	if (second < m_pBGD->dribbleIntervalTime)
	{
		m_pBGD->bangBalloonCount++;
		//判断这次的颜色跟上次的颜色是否一致
		if(m_pBGD->lastBalloonColorType != colorType)
		{
			m_pBGD->playSoundID = 0;
			m_pBGD->lastBalloonColorType = colorType;
			m_pBGD->dribbleCount = 0;
			m_pBGD->isDribbleFail = true;
		}else{
			m_pBGD->playSoundID++;
			m_pBGD->dribbleCount++;
		}
	}

	if (true == m_pBGD->isDribbleFail)
	{
		if (balloonID < 1000)
		{
			//不监听最后一个点击气球类型的时候把改成 BALLOON_COLOR_UNKNOW 类型
			if (m_pBGD->isListerLastBalloonType)
			{
				m_pBGD->isListerLastBalloonType = false;
				m_pBGD->freeFreeEnergyBalloonType = colorType;
				m_pBGD->isFreeEnergy = true;
			}else{
				//判断是否释放闪电
// 				if (!m_pBGD->isShowSuperman && true == m_pBGD->IsEnergyFull())
// 				{
// 					m_pBGD->isShowSuperman = true;
// 				}
			}
			
		}
	}

	

	//能量计算
	if (m_pBGD->dribbleCount >= m_pBGD->maxHit)
	{
		int energyMultiple = 1;
		if (m_pBGD->isKingEffect)
		{
			energyMultiple = 2;
		}
		int v = m_pBGD->dribbleCount;
		float per = pow(v,1.2f);
		m_pBGD->perEnergyList.push_back(per);
	}
	
	//游戏分数
	int scoreMultiple = 11;
	if (m_pBGD->isKingEffect)
	{
		scoreMultiple *= 4;
	}
	m_pBGD->gameScore += (m_pBGD->dribbleCount == 0 ? 1 : m_pBGD->dribbleCount) * scoreMultiple;
	

	//音效
	m_pBGD->playSoundID >= 12 ? m_pBGD->playSoundID = 11 : 0;
	string playSoundName = "hit_effect_";
	playSoundName += HSMath::ItoA(m_pBGD->playSoundID);
	HSSoundManage::ShareSoundManage()->PlayerEffect(playSoundName.c_str());	

#if 0
	CCLog("==========================================");
	CCLog("Stratagem    : %d %% %d , %d s",m_pBGD->stratagemCurSec / m_pBGD->stratagemEachCycleSec, m_pBGD->stratagemMaxCycleCount,m_pBGD->stratagemCurSec % m_pBGD->stratagemEachCycleSec);
	CCLog("Interval     : %.2f",second);
	CCLog("Energy       : %.2f",m_pBGD->energy);
	CCLog("DribbleCount : %d",m_pBGD->dribbleCount);
	CCLog("GameScore    : %d",m_pBGD->gameScore);
	CCLog("==========================================");
#endif
}

void HSBalloonConfig::Update( float dt )
{	
	if (m_isPauseUpdate)
	{
		return;
	}

	unsigned long long curTime = HSTime::GetLocalityTime();
	unsigned long long interval = curTime - m_lastTime;

	float second = interval / 1000.f;

	//判断是否在间隔时间内
// 	if (second > m_pBGD->dribbleIntervalTime)
// 	{
// 		m_pBGD->dribbleCount = 0;
// 	}
	if (second > m_pBGD->dribbleIntervalTime)
	{
		m_pBGD->dribbleCount = 0;
		m_isOvertime = true;
		m_pBGD->isDribbleFail = true;
	}else{
		m_isOvertime = false;
	}

// 	if (m_isOvertime && true == m_pBGD->isDribbleFail)
// 	{
// 		//判断是否释放闪电
// 		if (!m_pBGD->isShowSuperman && true == m_pBGD->IsEnergyFull())
// 		{
// 			m_pBGD->isShowSuperman = true;
// 		}
// 	}

	this->StratagemTimeLogic(dt);
}

const BalloonGameData* HSBalloonConfig::GetBalloonGameData() const
{
	return m_pBGD;
}

void HSBalloonConfig::AddEnergy()
{
	std::vector<float>::iterator it  = m_pBGD->perEnergyList.begin();
	if (it != m_pBGD->perEnergyList.end())
	{
		m_pBGD->energy += *it;
		m_pBGD->energy >= m_pBGD->energyMax ? m_pBGD->energy = m_pBGD->energyMax : 0 ;
		m_pBGD->perEnergyList.erase(it);
	}
	if (!m_pBGD->isShowSuperman && true == m_pBGD->IsEnergyFull())
	{
		m_pBGD->isShowSuperman = true;
	}
}

void HSBalloonConfig::SetLaseTime()
{
	m_lastTime = HSTime::GetLocalityTime();
}

void HSBalloonConfig::StratagemTimeLogic( float dt )
{

	if (m_pBGD->stratagemCurSec > 0 && m_dt > 1.f)
	{
		m_dt = 0.f;

		m_pBGD->stratagemCurSec--;
	}else{
		if (!m_pBGD->m_isPauseStratagemTime)
		{
			m_dt += dt;
		}
	}

	if (m_pBGD->stratagemCurSec <= 0)
	{
		if (m_pBGD->stratagemCurCycle >= 0)
		{
			m_pBGD->stratagemCurCycle--;
			m_pBGD->stratagemCurSec = m_pBGD->stratagemEachCycleSec;
		}else if(m_pBGD->stratagemCurCycle <= -1){

			m_pBGD->stratagemCurCycle = -1;
			/**  机关完成  **/
		}
	}

	StratagemStateType state = GetStratagemStateType();

#if 0
	static int c = 0;
	if (c != m_pBGD->stratagemCurSec)
	{
		c = m_pBGD->stratagemCurSec;
		CCLog("==========================================");
		CCLog("Stratagem    : %d %% %d ------- %d %% %d",m_pBGD->stratagemCurSec , m_pBGD->stratagemEachCycleSec,m_pBGD->stratagemCurCycle , m_pBGD->stratagemMaxCycleCount);
		CCLog("==========================================");
	}
#endif
	
}

StratagemStateType HSBalloonConfig::GetStratagemStateType()
{
	if (m_pBGD->lastStratagemLevel < m_pBGD->stratagemCurCycle)
	{
		m_stratagemMoveStep = m_pBGD->lastStratagemLevel - m_pBGD->stratagemCurCycle;
		m_pBGD->lastStratagemLevel = m_pBGD->stratagemCurCycle;
		return STRATAGEM_STATE_Up;

	}else if (m_pBGD->lastStratagemLevel > m_pBGD->stratagemCurCycle){

		m_stratagemMoveStep = m_pBGD->lastStratagemLevel - m_pBGD->stratagemCurCycle;
		m_pBGD->lastStratagemLevel = m_pBGD->stratagemCurCycle;
		return STRATAGEM_STATE_Down;
	}
	return STRATAGEM_STATE_Stop;
}

int HSBalloonConfig::GetStratagemMoveStep()
{
	return m_stratagemMoveStep;
}

void HSBalloonConfig::SetStratagemMoveStep( int step )
{
	m_stratagemMoveStep = step;
}

void HSBalloonConfig::AddStratagemTime(int time)
{
	m_pBGD->stratagemCurSec += time;

	if (m_pBGD->stratagemCurSec >= m_pBGD->stratagemEachCycleSec)
	{
		int addCycle = m_pBGD->stratagemCurSec / m_pBGD->stratagemEachCycleSec;
		int surSec = m_pBGD->stratagemCurSec % m_pBGD->stratagemEachCycleSec;

		m_pBGD->stratagemCurCycle += addCycle;
		m_pBGD->stratagemCurSec = surSec;

		if (m_pBGD->stratagemCurCycle >= m_pBGD->stratagemMaxCycleCount)
		{
			m_pBGD->stratagemCurCycle = m_pBGD->stratagemMaxCycleCount - 1;
			m_pBGD->stratagemCurSec = m_pBGD->stratagemEachCycleSec;
		}
	}
}

void HSBalloonConfig::ResetStratagemTime()
{
	m_pBGD->stratagemCurCycle = m_pBGD->stratagemMaxCycleCount - 1;
	m_pBGD->stratagemCurSec = m_pBGD->stratagemEachCycleSec;
	m_pBGD->lastStratagemLevel = m_pBGD->stratagemCurCycle;
}

void HSBalloonConfig::SetIsPause( bool b )
{
	m_isPauseUpdate = b;
}

