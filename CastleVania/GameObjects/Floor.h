#pragma once

#include "../StaticObject.h"

class Floor : public StaticObject
{
public:
	Floor();
	Floor(D3DXVECTOR2 position);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~Floor();
};
