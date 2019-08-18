#pragma once
#include "GameObjects/GameObject.h"

class WallEntrance : public GameObject
{
public:
	WallEntrance();
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~WallEntrance();
};

