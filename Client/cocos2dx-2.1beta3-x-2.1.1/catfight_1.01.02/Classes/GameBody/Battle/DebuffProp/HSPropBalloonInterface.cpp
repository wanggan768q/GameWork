#include "HSPropBalloonInterface.h"


HSPropBalloonInterface::HSPropBalloonInterface(void)
{
	m_pPropInfo = NULL;
	m_basePath = "Image/";
	schedule(schedule_selector(HSPropBalloonInterface::Updata));
}


HSPropBalloonInterface::~HSPropBalloonInterface(void)
{
}
