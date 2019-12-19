#pragma once
#include "./StaticObject.h"

class WallEntrance : public StaticObject
{
public:
	WallEntrance();
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~WallEntrance();
};

