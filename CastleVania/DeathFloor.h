#pragma once
#include "GameObjects/GameObject.h"

class DeathFloor: public GameObject
{
public:
	DeathFloor(D3DXVECTOR2 pos, int height, int width);
	void Render(Viewport* viewport);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	~DeathFloor();
};

