#pragma once
#include "GameObjects/GameObject.h"

constexpr int PODIUM_WIDTH = 32;
constexpr int PODIUM_HEIGHT = 25;

class PodiumOnWall : public GameObject
{
public:
	PodiumOnWall();
	PodiumOnWall(D3DXVECTOR2 position);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~PodiumOnWall();
};

