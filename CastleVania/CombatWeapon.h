#pragma once
#include "./GameObjects/GameObject.h"

class CombatWeapon;
typedef CombatWeapon * LPCOMBATWEAPON;

class CombatWeapon : public GameObject
{
public:
	CombatWeapon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~CombatWeapon();
};

