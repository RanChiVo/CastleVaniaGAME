#pragma once
#include "StaticObject.h"

class CastleWall : public StaticObject
{
public:
	CastleWall();
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CastleWall();
};

