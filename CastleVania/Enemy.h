#pragma once
#include "../CastleVania/GameObjects/GameObject.h"

class Enemy : public GameObject
{
	EntityID idHiddenItem;

public:
	Enemy();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state) { this->state = state; }
	~Enemy();
};

