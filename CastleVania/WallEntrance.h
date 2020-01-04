#pragma once
#include "./StaticObject.h"

class WallEntrance : public StaticObject
{
public:
	WallEntrance();
	 void Render(Viewport* viewport);
	 void GetBoundingBox(float &l, float &t, float &r, float &b);
	~WallEntrance();
};

