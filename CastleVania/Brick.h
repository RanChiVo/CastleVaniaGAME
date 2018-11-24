#pragma once
#include "../CastleVania/GameObjects/GameObject.h"

constexpr int BRICK_BBOX_WIDTH = 20;
constexpr int BRICK_BBOX_HEIGHT = 500;
constexpr int BRICK_ANI = 25;

class CBrick : public GameObject
{
public:
	CBrick();

	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CBrick();

};