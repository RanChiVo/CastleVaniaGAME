#pragma once
#include "../Enemy.h"
constexpr int ZOMBIE_STATE_WALKING = 1;

class Zombie : public Enemy
{
	bool activate = false;
public:
	Zombie();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	void setActivate(bool isActivate) { this->activate = isActivate; }
	void  SetState(int state);
	bool checkInsideViewPort(Viewport* viewport, D3DXVECTOR2 position);
	~Zombie();
};
