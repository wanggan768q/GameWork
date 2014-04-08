#include "HSTime.h"


unsigned long long HSTime::TimeSeed = 0;
unsigned long long HSTime::CT = 0;

HSTime::HSTime(void)
{
}

HSTime::~HSTime(void)
{
}

void HSTime::SetCurrentTimeStamp()
{
	HSTime::CT = HSTime::GetLocalityTime();
}

unsigned long long HSTime::GetLocalityTime()
{
	unsigned long long time = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	timeb t;
	ftime(&t);
	time = (unsigned long long)(1000 * t.time + t.millitm);
#else  
// 	cocos2d::cc_timeval now;
// 	CCTime::gettimeofdayCocos2d(&now,NULL);
// 	time = (now.tv_sec * 1000 + now.tv_usec / 1000);
	struct timeval tv;
	gettimeofday(&tv,NULL);
	time = (unsigned long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
	return time;
}

void HSTime::SetServerTimeSeed(unsigned long long timeSeed)
{
	HSTime::TimeSeed = timeSeed;
	HSTime::SetCurrentTimeStamp();
}

unsigned long long HSTime::GetImitateTimeSeed()
{	
	unsigned long long CT1 = HSTime::GetLocalityTime();
	unsigned long long loacTimeSeed = CT1 - HSTime::CT + HSTime::TimeSeed;
	int millisecond = (int)(loacTimeSeed - ((unsigned long long)(loacTimeSeed / 1000)*1000));
#if WIN32
	char strTime[64] = {0};
	struct tm *ttime;
	time_t timeT = (time_t)(loacTimeSeed / 1000);
	ttime = localtime(&timeT);
	strftime(strTime,64,"%Y-%m-%d %H:%M:%S",ttime);
	CCLog("HSTimeSeed: %s:%d",strTime,millisecond);
#endif
	return loacTimeSeed;
}

unsigned long long HSTime::GetLocalityTimeAccurate()
{
	//Ö§³ÖºÁÃë
// 	timeb t;
// 	ftime(&t);
// 	unsigned long long result = (unsigned long long)(1000 * t.time + t.millitm);
// 	return result;

	return GetLocalityTime();
// 	struct timeval tv;
// 	gettimeofday(&tv,NULL);
// 	unsigned long long result = (unsigned long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
// 	return result;
}

int HSTime::GetToday()
{
	struct tm* tm = GetTM();
	return tm->tm_mday;
}

int HSTime::GetYear()
{
	struct tm* tm = GetTM();
	return tm->tm_year + 1900;
}

int HSTime::GetMonth()
{
	struct tm* tm = GetTM();
	return tm->tm_mon + 1;
}

int HSTime::GetHour()
{
	struct tm* tm = GetTM();
	return tm->tm_hour;
}

int HSTime::GetMinute()
{
	struct tm* tm = GetTM();
	return tm->tm_min;
}

int HSTime::GetSec()
{
	struct tm* tm = GetTM();
	return tm->tm_sec;
}

const char* HSTime::GetTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80] = {0};

	time ( &rawtime );
	//timeinfo = localtime ( &rawtime );
	timeinfo = gmtime(&rawtime);

	strftime (buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
	std::string* time = new std::string(buffer);
	return time->c_str();
}

struct tm* HSTime::GetTM()
{
	time_t timep; 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	time(&timep); 
#else  
	struct cc_timeval now;  
	CCTime::gettimeofdayCocos2d(&now, NULL);  
	timep = now.tv_sec; 
#endif
	return localtime(&timep);
}
