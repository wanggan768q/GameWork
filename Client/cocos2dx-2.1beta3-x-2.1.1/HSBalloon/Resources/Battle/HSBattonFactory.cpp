#include "HSBattonFactory.h"

static int s_ReportFixture = 0;

HSBattonFactory::HSBattonFactory(void)
{
}


HSBattonFactory::~HSBattonFactory(void)
{
}

bool HSBattonFactory::ReportFixture( b2Fixture* fixture )
{
	//CCLog("ReportFixtureCount: %d ",++s_ReportFixture);
	return true;
}
