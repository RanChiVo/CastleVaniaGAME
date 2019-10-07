#pragma once
#include "../GameObjects/GameObject.h"
#include "../CombatWeapon.h"

constexpr int  KATANA_STATE_HIDE = 1;
constexpr int  KATANA_STATE_SHOW = 2;


class Dagger : public GameObject
{
public:
	Dagger();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	virtual void Render(Viewport* viewport);
	~Dagger();
}; 

