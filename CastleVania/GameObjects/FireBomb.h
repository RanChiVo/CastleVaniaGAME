#pragma once
#include "GameObject.h"

constexpr int FIRE_BOMB_STATE_HIDE = 1;
constexpr int FIRE_BOMB_STATE_SHOW = 2;

class FireBomb : public GameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	
	FireBomb();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~FireBomb();
};

