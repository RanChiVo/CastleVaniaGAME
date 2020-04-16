#pragma once
#include "./StaticObject.h"

class WallEntrance : public StaticObject
{
public:
	WallEntrance(D3DXVECTOR2 pos, int height, int width);
	 void Render(Viewport* viewport);
	 void GetBoundingBox(float &l, float &t, float &r, float &b);
	~WallEntrance();
};

