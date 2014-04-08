#ifndef __SPX_SKIN_H__
#define __SPX_SKIN_H__

#include "SPX_Bitmap.h"

class SPX_Skin
{
public:
	typedef vector<SPX_Texture*> TextureList;

public:
	SPX_Skin();
	~SPX_Skin();

public:
	TextureList textureList;
};

#endif /*__SPX_SKIN_H__*/
