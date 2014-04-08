#include "HSSet.h"


HSSet::HSSet(void)
{
}


HSSet::~HSSet(void)
{
}

void HSSet::removeAllObjects()
{
	CCSetIterator it;
	for (it = this->begin(); it != this->end(); ++it)
	{
		if (! (*it))
		{
			break;
		}

		this->removeObject(*it);
	}
}
