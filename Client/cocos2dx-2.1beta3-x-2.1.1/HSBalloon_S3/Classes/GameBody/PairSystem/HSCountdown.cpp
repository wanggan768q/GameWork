#include "HSCountdown.h"

HSCountdown::HSCountdown(void)
{
}

HSCountdown::~HSCountdown(void)
{
}

HSCountdown* HSCountdown::create()
{
    HSCountdown* p = new HSCountdown;
    if (p && p->init())
    {
        //=p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

bool HSCountdown::init()
{
	return true;
}


void HSCountdown::Run()
{
    
}