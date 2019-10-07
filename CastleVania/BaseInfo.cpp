#include "BaseInfo.h"

constexpr int MAX_HEALTH = 12;

BaseInfo::BaseInfo()
{
	heart = 3;
	scoreNumber = 0;
	health = 16;
	idSubWeapon = EntityID::ID_TEX_NULL;
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
	this->idSubWeapon = IdSubWeapon;
	if (IdSubWeapon == ID_TEX_NULL)
	{
		delete subWeapon;
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
