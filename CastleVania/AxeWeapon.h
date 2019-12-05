#pragma once
#include "CombatWeapon.h"

class AxeWeapon : public CombatWeapon
{
	int untouchable;
	DWORD untouchable_start;
	int width;
	int height;
public:
	AxeWeapon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~AxeWeapon();
};

