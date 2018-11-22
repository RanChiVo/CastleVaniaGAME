#pragma once
#include "../GameObjects/GameObject.h"

constexpr int WEAPONREWARD_STATE_HIDE = 1;
constexpr int WEAPONREWARD_STATE_SHOW = 2;
constexpr int WEAPONREWARD_ANI_HIDE = 20;
constexpr int WEAPONREWARD_ANI_SHOW = 21;
constexpr float WEAPONREWARD_GRAVITY = 0.002f;

class WeaponReward : public GameObject
{
	int untouchable;
	DWORD untouchable_start;

public:
	WeaponReward();
	WeaponReward(D3DXVECTOR2 position);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* ObjectList, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);

	~WeaponReward();
};

