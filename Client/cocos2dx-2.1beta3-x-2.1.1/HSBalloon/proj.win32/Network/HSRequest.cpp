#include "HSRequest.h"

HSRequest::HSRequest(void)
{
}

HSRequest::~HSRequest(void)
{
}

HSRequest* HSRequest::ShareRequest()
{
	static HSRequest s_hsRequest;
	return &s_hsRequest;
}

void HSRequest::Destroy()
{

}

void HSRequest::SendSearchRankRequest()
{
	SearchRankRequest* r = SearchRankRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendRegisterRequest( const char* userName )
{
	RegisterRequest* r = RegisterRequest::default_instance().New();
	r->set_username(userName);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendCombatGainsRequest( unsigned int score )
{
	CombatGainsRequest* r = CombatGainsRequest::default_instance().New();
	r->set_score(score);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendSearchWeeklyScoreRequest()
{
	SearchWeeklyScoreRequest* r = SearchWeeklyScoreRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendLogRequest( LogRequest* pLogRequest )
{
	LogRequest*  r = LogRequest::default_instance().New();
	r->CopyFrom(*pLogRequest);
	HS_FILTER_REQUEST(r);
}
