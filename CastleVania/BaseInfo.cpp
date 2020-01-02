#include "BaseInfo.h"
#include "Enemy.h"
#include "GameObjects/StopWatch.h"

constexpr int MAX_HEALTH = 12;

BaseInfo::BaseInfo()
{
	heart = 25;
	scoreNumber = 0;
	health = 16;
	idSubWeapon = EntityID::ID_ENTITY_NULL;
	subWeapon = nullptr;
}

int BaseInfo::getHeart()
{
	return heart;
}

void BaseInfo::setHeart(int heart)
{
	this->heart = heart;
}

int BaseInfo::getHealth()
{
	return health;
}

void BaseInfo::setHealth(int health)
{
	this->health = health;
}

int BaseInfo::getScore()
{
	return scoreNumber;
}

void BaseInfo::setScore(int score)
{
	this->scoreNumber = score;
}

EntityID BaseInfo::getIdSubWeapon()
{
	return idSubWeapon;
}

void BaseInfo::setIdSubWeapon(EntityID IdSubWeapon)
{
	idSubWeapon = IdSubWeapon;

	switch (idSubWeapon)
	{
	case ID_ENTITY_DAGGER_WEAPON:
		setSubWeapon(new DaggerWeapon());
		break;
	case ID_ENTITY_AXE_WEAPON:
		setSubWeapon(new AxeWeapon());
		break;
	case ID_ENTITY_FIRE_BOMP_WEAPON:
		setSubWeapon(new FireBombWeapon());
		break;
	case ID_ENTITY_STOP_WATCH:
		break;
	}
}

CombatWeapon * BaseInfo::getSubWeapon()
{
	return subWeapon;
}

void BaseInfo::setSubWeapon(CombatWeapon * subWeapon)
{
	this->subWeapon = subWeapon;
}

BaseInfo::~BaseInfo()
{
	delete subWeapon;
}
