#pragma once
#include "GameObjects/GameObject.h"

constexpr int  KATANAWEAPON_STATE_LEFT = 1;
constexpr int  KATANAWEAPON_STATE_RIGHT = 2;

constexpr int  KATANAWEAPON_ANI = 32;
constexpr float KATANAWEAPON_SPEED_HIT = 0.6f;

class KatanaWeapon : public GameObject
{
	int type;
	int ani;
	int untouchable;
	DWORD untouchable_start;
	RECT bounding = RECT{ 0, 0, 0, 0 };
	int width;
	int height;

public:
	KatanaWeapon();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Viewport* viewport);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetState(int state);

	bool checkInsideViewPort(Viewport* viewport, D3DXVECTOR2 position);
	~KatanaWeapon();
};

