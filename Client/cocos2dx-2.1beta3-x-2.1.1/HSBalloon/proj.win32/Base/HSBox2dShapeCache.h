/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/03/18   13:53
 *	File base:	HSBox2dShapeCache.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBox2dShapeCache_H__
#define __HSBox2dShapeCache_H__
#include "HSBase.h"
#include "Box2D/Box2D.h"

class HSFixtureDef;
class HSBodyDef;

#define HS_VALUE_B2V(__v__) (float)((__v__) / (float)(HS_PTM_RATIO))
#define HS_B2V_VALUE(__v__) (float)((__v__ ) * (float)(HS_PTM_RATIO))

#define HS_RATIO_b2Vec2(__x__,__y__) b2Vec2( HS_VALUE_B2V(__x__),HS_VALUE_B2V(__y__))
#define HS_b2Vec_To_CCPoint(__b2Vec__) ccp(HS_B2V_VALUE(__b2Vec__.x),HS_B2V_VALUE(__b2Vec__.y))


class HSBox2dShapeCache
{
public:
	// Static interface
	static HSBox2dShapeCache* sharedGB2ShapeCache(void);

public:
	bool init();
	void addShapesWithFile(const std::string &plist);
	bool addFixturesToBody(b2Body *body, const std::string &shape);
	cocos2d::CCPoint anchorPointForShape(const std::string &shape);
	void reset();
	float getPtmRatio() { return ptmRatio; }
	~HSBox2dShapeCache() {}

private:
	std::map<std::string, HSBodyDef *> shapeObjects;
	HSBox2dShapeCache(void) {}
	float ptmRatio;
};

#endif // __HSBox2dShapeCache_H____




