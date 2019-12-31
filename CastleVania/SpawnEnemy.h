#pragma once
#include "StaticObject.h"

class SpawnEnemy : public StaticObject
{
public:
	SpawnEnemy();
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~SpawnEnemy();
};

