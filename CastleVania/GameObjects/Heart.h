#pragma once
#include "../GameObjects/GameObject.h"

class Heart: public GameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	Heart();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);

	~Heart();
};

