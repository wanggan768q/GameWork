#include "SPX_Skin.h"

SPX_Skin::SPX_Skin()
{

}

SPX_Skin::~SPX_Skin()
{
	for(TextureList::iterator it = textureList.begin(); it != textureList.end(); it++)
	{
		delete *it;
	}

	textureList.clear();
}

