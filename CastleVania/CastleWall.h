#pragma once
#include "../CastleVania/GameObjects/GameObject.h"

class CastleWall : public GameObject
{
public:
	CastleWall();
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CastleWall();
};

