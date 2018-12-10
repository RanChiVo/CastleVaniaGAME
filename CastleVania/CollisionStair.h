#pragma once
#include "../CastleVania/GameObjects/GameObject.h"
constexpr int STAIR_BBOX_WIDTH = 32;
constexpr int STAIR_BBOX_HEIGHT = 32;

class CollisionStair : public GameObject
{
public:
	CollisionStair(D3DXVECTOR2 position);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CollisionStair();
};

