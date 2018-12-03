#pragma once

#include "GameObject.h"

constexpr int FLOOR_BBOX_WIDTH = 4000;
constexpr int FLOOR_BBOX_HEIGHT = 30;

class Floor : public GameObject
{
public:

	Floor();
	Floor(D3DXVECTOR2 position);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	~Floor();
};

