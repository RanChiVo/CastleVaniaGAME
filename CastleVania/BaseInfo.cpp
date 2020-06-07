#include "BaseInfo.h"
#include "Enemy.h"
#include "GameObjects/StopWatch.h"

constexpr int MAX_HEALTH = 12;

BaseInfo::BaseInfo()
{
	idSubWeapon = EntityID::ID_ENTITY_NULL;
	subWeapon = nullptr;
	idSubItem = EntityID::ID_ENTITY_NULL;
	lives = 0;
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

int BaseInfo::GetLives()
{
	return lives;
}

void BaseInfo::SetLives(int lives)
{
	this->lives = lives;
}

void BaseInfo::SetIdSubItem(EntityID idSubItem)
{
	this->idSubItem = idSubItem;
}

EntityID BaseInfo::GetIdSubItem()
{
	return idSubItem;
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
	case ID_ENTITY_BOOMERANG_WEAPON:
		setSubWeapon(new BoomerangWeapon());
		break;
	case ID_ENTITY_NULL:
		idSubWeapon = ID_ENTITY_NULL;
		break;
	}
}

CombatWeapon * BaseInfo::getSubWeapon()
{
	if (idSubWeapon!= ID_ENTITY_NULL)
	{
		return subWeapon;
	}
	return nullptr;
}

void BaseInfo::setSubWeapon(CombatWeapon * subWeapon)
{
	this->subWeapon = subWeapon;
}

BaseInfo::~BaseInfo()
{
	delete subWeapon;
}
