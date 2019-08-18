#pragma once
#include "../CastleVania/GameObjects/GameObject.h"

class CBrick : public GameObject
{
public:
	CBrick();

	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CBrick();

};