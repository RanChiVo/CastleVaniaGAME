#pragma once
#include "../StaticObject.h"

class Entrance : public StaticObject
{
	
public:
	Entrance(D3DXVECTOR2 pos, int height, int width);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	~Entrance();
};

