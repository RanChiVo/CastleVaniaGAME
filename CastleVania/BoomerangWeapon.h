#pragma once
#include "CombatWeapon.h"

class BoomerangWeapon : public CombatWeapon
{
	bool goBack = false;
public:
	BoomerangWeapon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~BoomerangWeapon();
};

