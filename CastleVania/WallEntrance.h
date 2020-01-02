#pragma once
#include "./StaticObject.h"

class WallEntrance : public StaticObject
{
public:
	WallEntrance();
	 void Render(Viewport* viewport);
	 virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	 void GetBoundingBox(float &l, float &t, float &r, float &b);
	~WallEntrance();
};

