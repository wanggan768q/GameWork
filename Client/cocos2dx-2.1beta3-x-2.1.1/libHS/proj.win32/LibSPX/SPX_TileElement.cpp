#include "SPX_TileElement.h"
#include "SPX_Data.h"
#include "SPX_Sprite.h"

SPX_TileElement::SPX_TileElement()
{
	tileSetIndex = 0;
	tileIndex = 0;
}

SPX_TileElement::~SPX_TileElement()
{
	
}

void SPX_TileElement::Render(SPX_Sprite* sprite, float x, float y)
{
	SPX_Data* data = sprite->data;

	SPX_Skin& skin = sprite->skin;
	SPX_TileSet& tileSet = data->tileSetList[tileSetIndex];
	SPX_Tile& tile = tileSet.tileList[tileIndex];
	SPX_Bitmap& bitmap = data->bitmapList[tileSet.bitmapIndex];
	SPX_Rect& rect = tile.rect;
	SPX_ISpriteEvent* eventProc = sprite->eventProc;

	//glPushMatrix();
	kmGLPushMatrix();

	x += this->x;
	y += this->y;

	if(eventProc != NULL)
	{
		eventProc->OnStartElementDraw(sprite, this);
	}


	if(bitmap.texture != NULL)
	{
		SPX_RenderTexture(bitmap.texture, rect.x1, rect.y1, rect.x2, rect.y2, transform, x, y);
	}
	else
	{
		SPX_Texture* skinTexture = skin.textureList[tileSet.bitmapIndex];
		if(skinTexture != NULL)
		{
			SPX_RenderTexture(skinTexture, rect.x1, rect.y1, rect.x2, rect.y2, transform, x, y);
		}
	}

	if(eventProc != NULL)
	{
		eventProc->OnEndElementDraw(sprite, this);
	}

	//glPopMatrix();
	kmGLPopMatrix();
}
