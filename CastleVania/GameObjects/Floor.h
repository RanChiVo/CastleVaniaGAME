#pragma once

#include "GameObject.h"


class Floor : public GameObject
{
public:

	Floor();
	Floor(D3DXVECTOR2 position);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	~Floor();
};
