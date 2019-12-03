#pragma once
#include "../GameObjects/GameObject.h"

class WeaponReward : public GameObject
{
	int untouchable;
	DWORD untouchable_start;

public:
	WeaponReward(D3DXVECTOR2 position);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);

	~WeaponReward();
};

