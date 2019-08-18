#pragma once
#include "../CastleVania/GameObjects/GameObject.h"

class AreaZombie :public GameObject
{
public:
	AreaZombie();
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~AreaZombie();
};

