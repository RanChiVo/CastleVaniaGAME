#pragma once
#include "../CastleVania/CombatWeapon.h"

class FireBombWeapon: public CombatWeapon
{
	int untouchable;
	DWORD untouchable_start;
	int width;
	int height;
	bool isOnGround = false;
	DWORD fireStart;
public:
	FireBombWeapon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~FireBombWeapon();
};

