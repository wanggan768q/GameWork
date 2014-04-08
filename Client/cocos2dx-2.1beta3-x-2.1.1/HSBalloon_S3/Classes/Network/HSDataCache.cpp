#include "HSDataCache.h"
#include "HSResponse.h"

static HSDataCache* s_hsDataCache = NULL;

HSDataCache::HSDataCache(void)
{
}

HSDataCache::~HSDataCache(void)
{
}

HSDataCache* HSDataCache::ShareDataCache()
{
	if (!s_hsDataCache)
	{
		s_hsDataCache = new HSDataCache;
	}
	return s_hsDataCache;
}

void HSDataCache::Destroy()
{
	CC_SAFE_DELETE(s_hsDataCache);
}

void HSDataCache::AddCacheData( int commmandId,google::protobuf::Message* msg )
{
	CCLog("-HSDataCache: %d",commmandId);
    HSResponse::ShareResponse()->HandleFactory(commmandId, msg);
}
