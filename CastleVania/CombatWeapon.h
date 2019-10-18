#pragma once
#include "./GameObjects/GameObject.h"

class CombatWeapon;
typedef CombatWeapon * LPCOMBATWEAPON;

class CombatWeapon : public GameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	CombatWeapon();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	~CombatWeapon();
};

