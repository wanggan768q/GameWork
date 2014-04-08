#include "HSBox2dShapeCache.h"

/**
* Internal class to hold the fixtures
*/
class HSFixtureDef 
{
public:
	HSFixtureDef()
		: next(NULL) {}

	~HSFixtureDef() {
		delete next;
		delete fixture.shape;
	}

	HSFixtureDef *next;
	b2FixtureDef fixture;
	int callbackData;
};

class HSBodyDef 
{
public:
	HSBodyDef()
		: fixtures(NULL) {}

	~HSBodyDef() {
		if (fixtures)
			delete fixtures;
	}

	HSFixtureDef *fixtures;
	CCPoint anchorPoint;
};

static HSBox2dShapeCache *_sharedGB2ShapeCache = NULL;

HSBox2dShapeCache* HSBox2dShapeCache::sharedGB2ShapeCache(void) 
{
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new HSBox2dShapeCache();
		_sharedGB2ShapeCache->init();
	}

	return _sharedGB2ShapeCache;
}

bool HSBox2dShapeCache::init() {
	return true;
}

void HSBox2dShapeCache::reset() {
	std::map<std::string, HSBodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) 
	{
		delete iter->second;
	}
	shapeObjects.clear();
}

bool HSBox2dShapeCache::addFixturesToBody(b2Body *body, const std::string &shape) 
{
	std::map<std::string, HSBodyDef *>::iterator pos = shapeObjects.find(shape);
	if(pos == shapeObjects.end())
	{
		/**等性能稳定后这句将 注释**/
		//HSAssert(pos != shapeObjects.end(),shape.c_str());
		return false;
	}

	HSBodyDef *so = (*pos).second;

	HSFixtureDef *fix = so->fixtures;
	while (fix) 
	{
		fix->fixture.isSensor = false;	//传感器 开启 将不受边界控制
		body->CreateFixture(&fix->fixture);
		fix = fix->next;
	}
	return true;
}

cocos2d::CCPoint HSBox2dShapeCache::anchorPointForShape(const std::string &shape) 
{
	std::map<std::string, HSBodyDef *>::iterator pos = shapeObjects.find(shape);
	HSAssert(pos != shapeObjects.end(),shape.c_str());

	HSBodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}

void HSBox2dShapeCache::addShapesWithFile(const std::string &plist) 
{

	CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(plist.c_str());
	HSAssert(dict != NULL, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
	HSAssert(dict->count() != 0, "plist file empty or not existing");

	CCDictionary *metadataDict = (CCDictionary *)dict->objectForKey("metadata");
	int format = static_cast<CCString *>(metadataDict->objectForKey("format"))->intValue();
	ptmRatio = static_cast<CCString *>(metadataDict->objectForKey("ptm_ratio"))->floatValue();
	HSAssert(format == 1, "Format not supported");

	CCDictionary *bodyDict = (CCDictionary *)dict->objectForKey("bodies");

	b2Vec2 vertices[b2_maxPolygonVertices];

	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(bodyDict, pElement)
	{
		HSBodyDef *bodyDef = new HSBodyDef();

		CCString *bodyName = ccs(pElement->getStrKey());

		CCDictionary *bodyData = (CCDictionary *)pElement->getObject();
		bodyDef->anchorPoint = CCPointFromString(static_cast<CCString *>(bodyData->objectForKey("anchorpoint"))->getCString());

		CCArray *fixtureList = (CCArray *)bodyData->objectForKey("fixtures");
		HSFixtureDef **nextFixtureDef = &(bodyDef->fixtures);

		CCObject *fixture = NULL;
		CCARRAY_FOREACH(fixtureList, fixture)
		{

			b2FixtureDef basicData;
			CCDictionary *fixtureData = (CCDictionary *)fixture;
			int callbackData = 0;

			basicData.filter.categoryBits = static_cast<CCString *>(fixtureData->objectForKey("filter_categoryBits"))->intValue();
			basicData.filter.maskBits = static_cast<CCString *>(fixtureData->objectForKey("filter_maskBits"))->intValue();
			basicData.filter.groupIndex = static_cast<CCString *>(fixtureData->objectForKey("filter_groupIndex"))->intValue();
			basicData.friction = static_cast<CCString *>(fixtureData->objectForKey("friction"))->floatValue();
			basicData.density = static_cast<CCString *>(fixtureData->objectForKey("density"))->floatValue();
			basicData.restitution = static_cast<CCString *>(fixtureData->objectForKey("restitution"))->floatValue();
			//basicData.isSensor = (bool)static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->intValue();
			int isSensor = static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->intValue();
			if (1 == isSensor)
			{
				basicData.isSensor = true;
			}else{
				basicData.isSensor = false;
			}
			if(fixtureData->objectForKey("id")){
				basicData.userData = static_cast<CCString *>(fixtureData->objectForKey("id"));
				callbackData = static_cast<CCString *>(fixtureData->objectForKey("id"))->intValue();
			}

			std::string fixtureType = static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->getCString();
			//CCString *fixtureType = static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->getCString();

			if (fixtureType == "POLYGON") {
				//CCDictionary *polygons = (CCDictionary *)fixtureData->objectForKey("polygons");
				CCArray *polygons = (CCArray *)fixtureData->objectForKey("polygons");
				//CCDictElement *polygon = NULL;
				CCObject *polygon = NULL;
				//CCDICT_FOREACH(polygons, polygon)
				CCARRAY_FOREACH(polygons, polygon)
				{
					HSFixtureDef *fix = new HSFixtureDef();
					fix->fixture = basicData; // copy basic data
					fix->callbackData = callbackData;

					b2PolygonShape *polyshape = new b2PolygonShape();
					int vindex = 0;

					//CCDictionary *polygonData = (CCDictionary *)polygon->getObject();
					CCArray *polygonData = (CCArray *)polygon;

					HSAssert(polygonData->count() <= b2_maxPolygonVertices,"polygonData->count() <= b2_maxPolygonVertices");

					//CCDictElement *offset = NULL;
					CCObject *offset = NULL;
					//CCDICT_FOREACH(polygonData, offset)
					CCARRAY_FOREACH(polygonData, offset)
					{

						CCString *pStr = (CCString *)offset;
						CCPoint p = CCPointFromString(pStr->getCString());

						vertices[vindex].x = (p.x / ptmRatio) ; 
						vertices[vindex].y = (p.y / ptmRatio) ; 
						vindex++;

					}

					polyshape->Set(vertices, vindex);
					//polyshape->SetAsBox(1.f,1.f,b2Vec2(0.5f,0.5f),0);
					fix->fixture.shape = polyshape;

					*nextFixtureDef = fix;
					nextFixtureDef = &(fix->next);
				}

			} else if (fixtureType == "CIRCLE") {
				HSFixtureDef *fix = new HSFixtureDef();
				fix->fixture = basicData; // copy basic data
				fix->callbackData = callbackData;

				CCDictionary *circleData = (CCDictionary *)fixtureData->objectForKey("circle");

				b2CircleShape *circleShape = new b2CircleShape();

				circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->floatValue() / ptmRatio;
				CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->getCString());
				circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
				fix->fixture.shape = circleShape;

				// create a list
				*nextFixtureDef = fix;
				nextFixtureDef = &(fix->next);

			} else {
				HSAssert(0, "Unknown fixtureType");
			}

			// add the body element to the hash
			shapeObjects[bodyName->getCString()] = bodyDef;

		}

	}

}