#pragma once
#include "EntityID.h"
#include "CombatWeapon.h"
#include "DaggerWeapon.h"
#include "AxeWeapon.h"
#include "FireBombWeapon.h"
#include "BoomerangWeapon.h"

class BaseInfo
{
	int lives;
	int heart;
	int health;
	int scoreNumber;
	EntityID idSubWeapon;
	EntityID idSubItem;
	CombatWeapon* subWeapon;

public:
	BaseInfo();
	int getHeart();
	void setHeart(int heart);
	int getHealth();
	void setHealth(int health);
	int getScore();
	void setScore(int score);
	int GetLives();
	void SetLives(int lives);
	void SetIdSubItem(EntityID idSubItem);
	EntityID GetIdSubItem();
	EntityID getIdSubWeapon();
	void setIdSubWeapon(EntityID IdSubWeapon);
	CombatWeapon* getSubWeapon();
	void setSubWeapon(CombatWeapon* subWeapon);

	~BaseInfo();
};

