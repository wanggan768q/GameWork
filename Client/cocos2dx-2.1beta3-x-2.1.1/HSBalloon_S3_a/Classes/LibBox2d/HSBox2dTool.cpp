#include "HSBox2dTool.h"


HSBox2dTool::HSBox2dTool(void)
{
}


HSBox2dTool::~HSBox2dTool(void)
{
}

#ifdef CC_ENABLE_BOX2D_INTEGRATION
void HSBox2dTool::ScaleBody( b2Body* pBody,float fScale )
{
	HSAssert(pBody,"");

	b2Fixture* pFixture = pBody->GetFixtureList();

	HSBox2dTool::Scaleb2Fixture(pFixture,fScale);

	pBody->SetAwake(true);
}

void HSBox2dTool::Scaleb2Fixture( b2Fixture* pFixture,float fScale )
{
	if (!pFixture)
	{
		return;
	}
	b2Shape::Type shapeType = pFixture->GetType();

	switch (shapeType)
	{
	case 2: //b2Shape::Type::e_polygon
		{
			b2PolygonShape* pPolygonShape = dynamic_cast<b2PolygonShape*>(pFixture->GetShape());
			int vertexCount = pPolygonShape->GetVertexCount();
			b2Vec2* newVertex = new b2Vec2[vertexCount];
			memset(newVertex,0,vertexCount);
			for (int i=0;i<vertexCount;++i)
			{
				const b2Vec2& v = pPolygonShape->GetVertex(i);
				newVertex[i].Set(v.x * fScale,v.y * fScale);
			}
			pPolygonShape->Set(newVertex,vertexCount);
			CC_SAFE_DELETE_ARRAY(newVertex);
		}
		break;
	default:
		CCLog("Error Shape");
		break;
	}
	HSBox2dTool::Scaleb2Fixture(pFixture->GetNext(),fScale);
}

#endif