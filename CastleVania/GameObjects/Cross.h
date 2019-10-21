#pragma once
#include "../GameObjects/GameObject.h"

class Cross : public GameObject
{
	int untouchable;
	DWORD untouchable_start;

public:
	Cross(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~Cross();
};

