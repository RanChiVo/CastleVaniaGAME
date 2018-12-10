#pragma once
#include "../CastleVania/GameObjects/GameObject.h"

constexpr int BRICK_BBOX_WIDTH = 25;
constexpr int BRICK_BBOX_HEIGHT = 312;

class CBrick : public GameObject
{
public:
	CBrick(D3DXVECTOR2 position);

	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CBrick();

};