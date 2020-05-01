#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{

public:
	Skeleton(D3DXVECTOR2 pos, int height, int width, float maxDistance);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~Skeleton();
};

