#pragma once
#include "EntityID.h"
#include "CombatWeapon.h"

class BaseInfo
{
	int heart;
	int health;
	int scoreNumber;
	EntityID idSubWeapon;
	CombatWeapon* subWeapon;

public:
	BaseInfo();
	int getHeart();
	void setHeart(int heart);
	int getHealth();
	void setHealth(int health);
	int getScore();
	void setScore(int score);
	EntityID getIdSubWeapon();
	void setIdSubWeapon(EntityID IdSubWeapon);
	CombatWeapon* getSubWeapon();
	void setSubWeapon(CombatWeapon* subWeapon);

	~BaseInfo();
};

