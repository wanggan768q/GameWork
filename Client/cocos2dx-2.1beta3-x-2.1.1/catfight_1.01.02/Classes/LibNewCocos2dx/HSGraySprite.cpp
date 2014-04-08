#include "HSGraySprite.h"


HSGraySprite::HSGraySprite(void)
{
    m_fileName = "";
}


HSGraySprite::~HSGraySprite(void)
{
	
}

HSGraySprite* HSGraySprite::create( const char* pszFileName )
{
	HSGraySprite* sprite = new HSGraySprite;
	if (sprite && sprite->initWithFile(pszFileName))
	{
		sprite->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(sprite);
	}
	return sprite;
}

bool HSGraySprite::initWithFile(const char *pszFilename)
{
    m_fileName = pszFilename;
    return HSCCSprite::initWithFile(pszFilename);
}

bool HSGraySprite::initWithTexture( cocos2d::CCTexture2D* pTexture, const cocos2d::CCRect& tRect )
{
	do 
	{
		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, tRect));

		this->GrayProgram();

		//this->RecoverProgram();
		
		return true;
	} while (0);
	return false;
}

const char* HSGraySprite::GetFileName()
{
    return m_fileName.c_str();
}

void HSGraySprite::draw()
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	this->getShaderProgram()->use();
	this->getShaderProgram()->setUniformsForBuiltins();

	ccGLBindTexture2D(  this->getTexture()->getName() );

	//
	// Attributes
	//
#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}

void HSGraySprite::RecoverProgram()
{
	if (m_SpriteType == HSGraySprite_Type_Normal)
	{
		return;
	}

	m_SpriteType = HSGraySprite_Type_Normal;

	const GLchar * pszFragSource = 
		"#ifdef GL_ES \n \
		precision mediump float; \n \
		#endif \n \
		uniform sampler2D u_texture; \n \
		varying vec2 v_texCoord; \n \
		varying vec4 v_fragmentColor; \n \
		void main(void) \n \
		{ \n \
		// Convert to greyscale using NTSC weightings \n \
		float alpha = texture2D(u_texture, v_texCoord).a; \n \
		float r = texture2D(u_texture, v_texCoord).r; \n \
		float g = texture2D(u_texture, v_texCoord).g; \n \
		float b = texture2D(u_texture, v_texCoord).b; \n \
		gl_FragColor = vec4(r, g, b, alpha); \n \
		}";

	CCGLProgram* pProgram = new CCGLProgram();
	pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
	this->setShaderProgram(pProgram);
	pProgram->release();
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->link();
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->updateUniforms();
	CHECK_GL_ERROR_DEBUG();
}

void HSGraySprite::GrayProgram()
{
	if (m_SpriteType == HSGraySprite_Type_Gray)
	{
		return;
	}
	m_SpriteType = HSGraySprite_Type_Gray;

	const GLchar * pszFragSource = 
		"#ifdef GL_ES \n \
		precision mediump float; \n \
		#endif \n \
		uniform sampler2D u_texture; \n \
		varying vec2 v_texCoord; \n \
		varying vec4 v_fragmentColor; \n \
		void main(void) \n \
		{ \n \
		// Convert to greyscale using NTSC weightings \n \
		float alpha = texture2D(u_texture, v_texCoord).a; \n \
		float grey = dot(texture2D(u_texture, v_texCoord).rgb, vec3(0.299, 0.587, 0.114)); \n \
		gl_FragColor = vec4(grey, grey, grey, alpha); \n \
		}";
	CCGLProgram* pProgram = new CCGLProgram();
	pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
	this->setShaderProgram(pProgram);
	pProgram->release();
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->link();
	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->updateUniforms();
	CHECK_GL_ERROR_DEBUG();
}

bool HSGraySprite::ContainsTouchLocation( CCTouch* touch )
{
	//this->get
	//CCSize s = getTexture()->getContentSize();
	CCSize s = this->getContentSize();
	CCRect r = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	return r.containsPoint(convertTouchToNodeSpaceAR(touch));
}

HSGraySpriteType HSGraySprite::GetType()
{
	return m_SpriteType;
}
