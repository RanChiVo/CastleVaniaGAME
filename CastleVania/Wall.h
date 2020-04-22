#pragma once
#include "./StaticObject.h"

class Wall : public StaticObject
{
public:
	Wall(D3DXVECTOR2 pos, int height, int width);
	 void Render(Viewport* viewport);
	 void GetBoundingBox(float &l, float &t, float &r, float &b);
	~Wall();
};

