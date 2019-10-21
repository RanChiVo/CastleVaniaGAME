#pragma once
#include "GameObject.h"
constexpr int ZOMBIE_STATE_WALKING_LEFT = 1;
constexpr int ZOMBIE_STATE_WALKING_RIGHT = 2;

class Zombie : public GameObject
{
	
public:
	Zombie();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	void  handleState();
	bool checkInsideViewPort(Viewport* viewport, D3DXVECTOR2 position);
	~Zombie();
};
