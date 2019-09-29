#pragma once
#include "./GameObjects/GameObject.h"

class CombatWeapon : public GameObject
{
public:
	CombatWeapon();
	virtual void update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~CombatWeapon();
};

