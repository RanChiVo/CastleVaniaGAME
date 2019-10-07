#pragma once
#include "GameObjects/GameObject.h"
#include "CombatWeapon.h"

constexpr int  KATANAWEAPON_STATE_LEFT = 1;
constexpr int  KATANAWEAPON_STATE_RIGHT = 2;

constexpr int  KATANAWEAPON_ANI = 32;
constexpr float KATANAWEAPON_SPEED_HIT = 0.6f;

class DaggerWeapon : public CombatWeapon
{
	int type;
	int ani;
	int untouchable;
	DWORD untouchable_start;
	RECT bounding = RECT{ 0, 0, 0, 0 };
	int width;
	int height;

public:
	DaggerWeapon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);

	bool checkInsideViewPort(Viewport* viewport, D3DXVECTOR2 position);
	~DaggerWeapon();
};

