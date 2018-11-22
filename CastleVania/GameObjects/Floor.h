#pragma once

#include "GameObject.h"

constexpr int FLOOR_BBOX_WIDTH = 1536;
constexpr int FLOOR_BBOX_HEIGHT = 30;

class Floor : public GameObject
{
public:
	Floor();

	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	~Floor();
};

