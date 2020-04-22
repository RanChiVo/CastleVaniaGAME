#pragma once
#include "Enemy.h"

class SpearKnight:public Enemy
{
	int maxDistance;
	float positionXStart;
	DWORD timeMoving;
	DWORD timeMoving1;
public:
	SpearKnight(D3DXVECTOR2 pos, int maxDistance, int width, int height);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~SpearKnight();
};

