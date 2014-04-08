#include "SPX_Base.h"
// shaders
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccShaders.h"
//#include "cocos2d/CCTexture2D.h"

#include "cocos2d.h"

SPX_ErrorCode SPX_GetTransform(SPX_Transform a, SPX_Transform b, SPX_Transform& c)
{
	if(a < 0 || a > 7 || b < 0 || b > 7)
	{
		return ValueOverflow;
	}

	static const char TransformTable[8][8] = 
	{
		{None, MirrorRotate180, Mirror, Rotate180, MirrorRotate270, Rotate90, Rotate270, MirrorRotate90},
		{MirrorRotate180, None, Rotate180, Mirror, Rotate90, MirrorRotate270, MirrorRotate90, Rotate270},
		{Mirror, Rotate180, None, MirrorRotate180, Rotate270, MirrorRotate90, MirrorRotate270, Rotate90},
		{Rotate180, Mirror, MirrorRotate180, None, MirrorRotate90, Rotate270, Rotate90, MirrorRotate270},
		{MirrorRotate270, Rotate270, Rotate90, MirrorRotate90, None, Mirror, MirrorRotate180, Rotate180},
		{Rotate90, MirrorRotate90, MirrorRotate270, Rotate270, MirrorRotate180, Rotate180, None, Mirror},
		{Rotate270, MirrorRotate270, MirrorRotate90, Rotate90, Mirror, None, Rotate180, MirrorRotate180},
		{MirrorRotate90, Rotate90, Rotate270, MirrorRotate270, Rotate180, MirrorRotate180, Mirror, None},
	};

	c = (SPX_Transform)TransformTable[a][b];

	return Success;
}

SPX_ErrorCode SPX_GetRotate(SPX_Transform a, int b, SPX_Transform& c)
{
	if(a < 0 || a > 7 || b < 0 || b > 3)
	{
		return ValueOverflow;
	}

	static const char RotateTable[8][4] =
	{
		{Rotate270, Rotate90, Mirror, MirrorRotate180},
		{MirrorRotate90, MirrorRotate270, Rotate180, None},
		{MirrorRotate270, MirrorRotate90, None, Rotate180},
		{Rotate90, Rotate270, MirrorRotate180, Mirror},
		{MirrorRotate180, Mirror, Rotate90, Rotate270},
		{None, Rotate180, MirrorRotate270, MirrorRotate90},
		{Rotate180, None, MirrorRotate90, MirrorRotate270},
		{Mirror, MirrorRotate180, Rotate270, Rotate90},
	};

	c = (SPX_Transform)RotateTable[a][b];

	return Success;
}

SPX_Texture* SPX_CreateTexture(const wstring& name)
{
	string namea = GE_U2A(name);

	cocos2d::CCImage image;
	if(!image.initWithImageFile(namea.c_str()))
	{
		return NULL;
	}

	SPX_Texture* texture = new cocos2d::CCTexture2D();
	if(texture == NULL)
	{
		return NULL;
	}

	if(!texture->initWithImage(&image))
	{
		delete texture;
		return NULL;
	}

	cocos2d::ccTexParams texParams;
	texParams.magFilter = GL_LINEAR;
	texParams.minFilter = GL_LINEAR;
	texParams.wrapS = GL_CLAMP_TO_EDGE;
	texParams.wrapT = GL_CLAMP_TO_EDGE;

	texture->setTexParameters(&texParams);

	return texture;
}

void SPX_DeleteTexture(SPX_Texture* texture)
{
	delete texture;
}

void SPX_RenderTexture(SPX_Texture *texture, float sx1, float sy1, float sx2, float sy2, int transform, float x, float y)
{

	cocos2d::ccGLServerState m_glServerState = cocos2d::CC_GL_ALL;


	kmGLPushMatrix();

	cocos2d::CCSize texSize = texture->getContentSize();
	cocos2d::CCSize allSize((float)texture->getPixelsWide(), (float)texture->getPixelsHigh());

	float width = sx2 - sx1;
	float height = sy2 - sy1;

	GLfloat matrix[4][4] = 
	{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};

	y = -y;

	switch(transform)
	{
	case None:
		matrix[0][0] = 1;
		matrix[0][1] = 0;
		matrix[1][0] = 0;
		matrix[1][1] = 1;
		matrix[3][0] = x;
		matrix[3][1] = y;
		break;
	case Rotate90:
		matrix[0][0] = 0;
		matrix[0][1] = 1;
		matrix[1][0] = -1;
		matrix[1][1] = 0;
		matrix[3][0] = x + height;
		matrix[3][1] = y;
		break;
	case Rotate180:
		matrix[0][0] = -1;
		matrix[0][1] = 0;
		matrix[1][0] = 0;
		matrix[1][1] = -1;
		matrix[3][0] = x + width;
		matrix[3][1] = y + height;
		break;
	case Rotate270:
		matrix[0][0] = 0;
		matrix[0][1] = -1;
		matrix[1][0] = 1;
		matrix[1][1] = 0;
		matrix[3][0] = x;
		matrix[3][1] = y + width;
		break;
	case Mirror:
		matrix[0][0] = -1;
		matrix[0][1] = 0;
		matrix[1][0] = 0;
		matrix[1][1] = 1;
		matrix[3][0] = x + width;
		matrix[3][1] = y;
		break;
	case MirrorRotate90:
		matrix[0][0] = 0;
		matrix[0][1] = -1;
		matrix[1][0] = -1;
		matrix[1][1] = 0;
		matrix[3][0] = x + height;
		matrix[3][1] = y + width;
		break;
	case MirrorRotate180:
		matrix[0][0] = 1;
		matrix[0][1] = 0;
		matrix[1][0] = 0;
		matrix[1][1] = -1;
		matrix[3][0] = x;
		matrix[3][1] = y + height;
		break;
	case MirrorRotate270:
		matrix[0][0] = 0;
		matrix[0][1] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 0;
		matrix[3][0] = x;
		matrix[3][1] = y;
		break;
	}

	kmGLMultMatrix((kmMat4*)matrix);

	kmGLScalef(1, -1, 1);

	ccGLEnable( m_glServerState ); 

	texture->getShaderProgram()->use();
	texture->getShaderProgram()->setUniformsForBuiltins();

	kmGLPopMatrix();

	//ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
	ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST );//770, 771

	cocos2d::ccGLBindTexture2D(texture->getName());

	//if (m_pobTexture != NULL)
	//{
	//    ccGLBindTexture2D( m_pobTexture->getName() );
	//}
	//else
	//{
	//    ccGLBindTexture2D(0);
	//}

	//
	// Attributes
	//

	cocos2d::ccGLEnableVertexAttribs( cocos2d::kCCVertexAttribFlag_PosColorTex );
	//cocos2d::ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_PosColorTex );



	float vertex[4][2] =
	{
		{0, 0},
		{0, height},
		{width, height},
		{width, 0},
	};

	float uv[4][2] = 
	{
		{sx1, sy1},
		{sx1, sy2},
		{sx2, sy2},
		{sx2, sy1},
	};

	for(int i = 0; i < 4; ++i)
	{
		uv[i][0] = (uv[i][0]) / (allSize.width);
		uv[i][1]= (uv[i][1]) / (allSize.height);
		//uv[i].y = uv[i].y;
	}

	uchar color[][4] = 
	{
		{255,255,255,255},
		{255,255,255,255},
		{255,255,255,255},
		{255,255,255,255},
	};


	glVertexAttribPointer(cocos2d::kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, (void*) vertex);
	glVertexAttribPointer(cocos2d::kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, (void*)uv);
	glVertexAttribPointer(cocos2d::kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)color);


	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	//
	//#define kQuadSize sizeof(m_sQuad.bl)
	//    long offset = (long)&m_sQuad;
	//
	//    // vertex
	//    int diff = offsetof( ccV3F_C4B_T2F, vertices);
	//    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
	//
	//    // texCoods
	//    diff = offsetof( ccV3F_C4B_T2F, texCoords);
	//    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	//
	//    // color
	//    diff = offsetof( ccV3F_C4B_T2F, colors);
	//    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	//
	//
	//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//CHECK_GL_ERROR_DEBUG();


	//#if CC_SPRITE_DEBUG_DRAW == 1
	//    // draw bounding box
	//    CCPoint vertices[4]={
	//        ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
	//        ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
	//        ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
	//        ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
	//    };
	//    ccDrawPoly(vertices, 4, true);
	//#elif CC_SPRITE_DEBUG_DRAW == 2
	//    // draw texture box
	//    CCSize s = this->getTextureRect().size;
	//    CCPoint offsetPix = this->getOffsetPosition();
	//    CCPoint vertices[4] = {
	//        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
	//        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
	//    };
	//    ccDrawPoly(vertices, 4, true);
	//#endif // CC_SPRITE_DEBUG_DRAW

	// CC_INCREMENT_GL_DRAWS(1);

	// CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}


// void SPX_RenderTexture(SPX_Texture *texture, float sx1, float sy1, float sx2, float sy2, int transform, float x, float y)
// {
// 	/*
// 	if(texture == NULL)
// 	{
// 	texture = NULL;
// 	}
// 
// 	cocos2d::CCSize texSize = texture->getContentSize();
// 	cocos2d::CCSize allSize((float)texture->getPixelsWide(), (float)texture->getPixelsHigh());
// 
// 	float width = sx2 - sx1;
// 	float height = sy2 - sy1;
// 
// 	float vertex[4][2] =
// 	{
// 	{0, 0},
// 	{0, height},
// 	{width, height},
// 	{width, 0},
// 	};
// 
// 	float uv[4][2] =
// 	{
// 	{sx1, sy1},
// 	{sx1, sy2},
// 	{sx2, sy2},
// 	{sx2, sy1},
// 	};
// 
// 	for(int i = 0; i < 4; ++i)
// 	{
// 	uv[i][0] = uv[i][0] / allSize.width;
// 	uv[i][1]= uv[i][1] / allSize.height;
// 	//uv[i].y = uv[i].y;
// 	}
// 
// 	GLfloat matrix[4][4] = 
// 	{
// 	{1, 0, 0, 0},
// 	{0, 1, 0, 0},
// 	{0, 0, 1, 0},
// 	{0, 0, 0, 1},
// 	};
// 
// 	switch(transform)
// 	{
// 	case None:
// 	matrix[0][0] = 1;
// 	matrix[0][1] = 0;
// 	matrix[1][0] = 0;
// 	matrix[1][1] = 1;
// 	matrix[3][0] = x;
// 	matrix[3][1] = y;
// 	break;
// 	case Rotate90:
// 	matrix[0][0] = 0;
// 	matrix[0][1] = 1;
// 	matrix[1][0] = -1;
// 	matrix[1][1] = 0;
// 	matrix[3][0] = x + height;
// 	matrix[3][1] = y;
// 	break;
// 	case Rotate180:
// 	matrix[0][0] = -1;
// 	matrix[0][1] = 0;
// 	matrix[1][0] = 0;
// 	matrix[1][1] = -1;
// 	matrix[3][0] = x + width;
// 	matrix[3][1] = y + height;
// 	break;
// 	case Rotate270:
// 	matrix[0][0] = 0;
// 	matrix[0][1] = -1;
// 	matrix[1][0] = 1;
// 	matrix[1][1] = 0;
// 	matrix[3][0] = x;
// 	matrix[3][1] = y + width;
// 	break;
// 	case Mirror:
// 	matrix[0][0] = -1;
// 	matrix[0][1] = 0;
// 	matrix[1][0] = 0;
// 	matrix[1][1] = 1;
// 	matrix[3][0] = x + width;
// 	matrix[3][1] = y;
// 	break;
// 	case MirrorRotate90:
// 	matrix[0][0] = 0;
// 	matrix[0][1] = -1;
// 	matrix[1][0] = -1;
// 	matrix[1][1] = 0;
// 	matrix[3][0] = x + height;
// 	matrix[3][1] = y + width;
// 	break;
// 	case MirrorRotate180:
// 	matrix[0][0] = 1;
// 	matrix[0][1] = 0;
// 	matrix[1][0] = 0;
// 	matrix[1][1] = -1;
// 	matrix[3][0] = x;
// 	matrix[3][1] = y + height;
// 	break;
// 	case MirrorRotate270:
// 	matrix[0][0] = 0;
// 	matrix[0][1] = 1;
// 	matrix[1][0] = 1;
// 	matrix[1][1] = 0;
// 	matrix[3][0] = x;
// 	matrix[3][1] = y;
// 	break;
// 	}
// 
// 	uint texid = texture->getName();
// 
// 	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
// 
// 	glPushMatrix();
// 	glDisableClientState(GL_COLOR_ARRAY);
// 
// 	glBindTexture(GL_TEXTURE_2D, texid);
// 
// 	glTexCoordPointer(2, GL_FLOAT, 0, uv);
// 	glVertexPointer(2, GL_FLOAT, 0, vertex);
// 
// 	glMultMatrixf((const GLfloat *)matrix);
// 
// 	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
// 
// 	glEnableClientState(GL_COLOR_ARRAY);
// 
// 	glPopMatrix();
// 	*/
// 
// 	// CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
// 
// 	//CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
// 	//cocos2d::ccGLServerState m_glServerState = cocos2d::CC_GL_BLEND;
// 	cocos2d::ccGLServerState m_glServerState = cocos2d::CC_GL_ALL;
// 
// 	//    CC_NODE_DRAW_SETUP();
// 
// 	kmGLPushMatrix();
// 	//kmGLTranslatef(x,-y,0);
// 	//if (transform == None)
// 	// {
// 	y=-y;
// 	// }
// 
// 	cocos2d::CCSize texSize = texture->getContentSize();
// 	cocos2d::CCSize allSize((float)texture->getPixelsWide(), (float)texture->getPixelsHigh());
// 
// 	float width = sx2 - sx1;
// 	float height = sy2 - sy1;
// 
// 	GLfloat matrix[4][4] = 
// 	{
// 		{1, 0, 0, 0},
// 		{0, 1, 0, 0},
// 		{0, 0, 1, 0},
// 		{0, 0, 0, 1},
// 	};
// 
// 	switch(transform)
// 	{
// 	case None:
// 		matrix[0][0] = 1;
// 		matrix[0][1] = 0;
// 		matrix[1][0] = 0;
// 		matrix[1][1] = 1;
// 		matrix[3][0] = x;
// 		matrix[3][1] = y;
// 		break;
// 	case Rotate90:
// 		matrix[0][0] = 0;
// 		matrix[0][1] = 1;
// 		matrix[1][0] = -1;
// 		matrix[1][1] = 0;
// 		matrix[3][0] = x + height;
// 		matrix[3][1] = y;
// 		break;
// 	case Rotate180:
// 		matrix[0][0] = -1;
// 		matrix[0][1] = 0;
// 		matrix[1][0] = 0;
// 		matrix[1][1] = -1;
// 		matrix[3][0] = x + width;
// 		matrix[3][1] = y + height;
// 		break;
// 	case Rotate270:
// 		matrix[0][0] = 0;
// 		matrix[0][1] = -1;
// 		matrix[1][0] = 1;
// 		matrix[1][1] = 0;
// 		matrix[3][0] = x;
// 		matrix[3][1] = y + width;
// 		break;
// 	case Mirror:
// 		matrix[0][0] = -1;
// 		matrix[0][1] = 0;
// 		matrix[1][0] = 0;
// 		matrix[1][1] = 1;
// 		matrix[3][0] = x + width;
// 		matrix[3][1] = y;
// 		break;
// 	case MirrorRotate90:
// 		matrix[0][0] = 0;
// 		matrix[0][1] = -1;
// 		matrix[1][0] = -1;
// 		matrix[1][1] = 0;
// 		matrix[3][0] = x + height;
// 		matrix[3][1] = y + width;
// 		break;
// 	case MirrorRotate180:
// 		matrix[0][0] = 1;
// 		matrix[0][1] = 0;
// 		matrix[1][0] = 0;
// 		matrix[1][1] = -1;
// 		matrix[3][0] = x;
// 		matrix[3][1] = y + height;
// 		break;
// 	case MirrorRotate270:
// 		matrix[0][0] = 0;
// 		matrix[0][1] = 1;
// 		matrix[1][0] = 1;
// 		matrix[1][1] = 0;
// 		matrix[3][0] = x;
// 		matrix[3][1] = y;
// 		break;
// 	}
// 
// 	kmGLMultMatrix((kmMat4*)matrix);
// 
// 	kmGLScalef(1, -1, 1);
// 
// 	ccGLEnable( m_glServerState ); 
// 
// 	texture->getShaderProgram()->use();
// 	texture->getShaderProgram()->setUniformsForBuiltins();
// 
// 	kmGLPopMatrix();
// 
// 	//ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
// 	ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST );//770, 771
// 
// 	cocos2d::ccGLBindTexture2D(texture->getName());
// 
// 	//if (m_pobTexture != NULL)
// 	//{
// 	//    ccGLBindTexture2D( m_pobTexture->getName() );
// 	//}
// 	//else
// 	//{
// 	//    ccGLBindTexture2D(0);
// 	//}
// 
// 	//
// 	// Attributes
// 	//
// 
// 	cocos2d::ccGLEnableVertexAttribs( cocos2d::kCCVertexAttribFlag_PosColorTex );
// 	//cocos2d::ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_PosColorTex );
// 
// 
// 
// 	float vertex[4][2] =
// 	{
// 		{0, 0},
// 		{0, height},
// 		{width, height},
// 		{width, 0},
// 	};
// 
// 	float uv[4][2] = 
// 	{
// 		{sx1, sy1},
// 		{sx1, sy2},
// 		{sx2, sy2},
// 		{sx2, sy1},
// 	};
// 
// 	for(int i = 0; i < 4; ++i)
// 	{
// 		uv[i][0] = (uv[i][0]) / (allSize.width);
// 		uv[i][1]= (uv[i][1]) / (allSize.height);
// 		//uv[i].y = uv[i].y;
// 	}
// 
// 	uchar color[][4] = 
// 	{
// 		{255,255,255,255},
// 		{255,255,255,255},
// 		{255,255,255,255},
// 		{255,255,255,255},
// 	};
// 
// 
// 	glVertexAttribPointer(cocos2d::kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, (void*) vertex);
// 	glVertexAttribPointer(cocos2d::kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, (void*)uv);
// 	glVertexAttribPointer(cocos2d::kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)color);
// 
// 
// 	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
// 
// 
// 	//
// 	//#define kQuadSize sizeof(m_sQuad.bl)
// 	//    long offset = (long)&m_sQuad;
// 	//
// 	//    // vertex
// 	//    int diff = offsetof( ccV3F_C4B_T2F, vertices);
// 	//    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
// 	//
// 	//    // texCoods
// 	//    diff = offsetof( ccV3F_C4B_T2F, texCoords);
// 	//    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
// 	//
// 	//    // color
// 	//    diff = offsetof( ccV3F_C4B_T2F, colors);
// 	//    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
// 	//
// 	//
// 	//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
// 
// 	//CHECK_GL_ERROR_DEBUG();
// 
// 
// 	//#if CC_SPRITE_DEBUG_DRAW == 1
// 	//    // draw bounding box
// 	//    CCPoint vertices[4]={
// 	//        ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
// 	//        ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
// 	//        ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
// 	//        ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
// 	//    };
// 	//    ccDrawPoly(vertices, 4, true);
// 	//#elif CC_SPRITE_DEBUG_DRAW == 2
// 	//    // draw texture box
// 	//    CCSize s = this->getTextureRect().size;
// 	//    CCPoint offsetPix = this->getOffsetPosition();
// 	//    CCPoint vertices[4] = {
// 	//        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
// 	//        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
// 	//    };
// 	//    ccDrawPoly(vertices, 4, true);
// 	//#endif // CC_SPRITE_DEBUG_DRAW
// 
// 	// CC_INCREMENT_GL_DRAWS(1);
// 
// 	// CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
// }
