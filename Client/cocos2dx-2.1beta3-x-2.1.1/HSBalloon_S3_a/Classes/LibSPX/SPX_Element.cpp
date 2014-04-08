#include "SPX_Element.h"

SPX_Element::SPX_Element()
{
	flagBits = 0;
	x = 0;
	y = 0;
	transform = None;
}

SPX_Element::~SPX_Element()
{

}

void SPX_Element::Render(SPX_Sprite* sprite, float x, float y)
{

}
