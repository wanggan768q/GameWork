#include "HSCellInterface.h"

HS_namespace_HSListViewControl_Begin

HSCellInterface::HSCellInterface( void )
{
	m_pChild = NULL;
}

HSCellInterface::~HSCellInterface( void )
{

}

bool HSCellInterface::init()
{
	return true;
}

void HSCellInterface::addChild( CCNode* child, int zOrder, int tag )
{
	m_pChild = child;
	CCTableViewCell::addChild(child,zOrder,tag);
}

CCNode* HSCellInterface::GetChild()
{
	return m_pChild;
}

HS_namespace_HSListViewControl_End