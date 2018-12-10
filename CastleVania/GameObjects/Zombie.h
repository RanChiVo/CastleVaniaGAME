#pragma once
#include "GameObject.h"

class Zombie : public GameObject
{
	enum State
	{
		ZOMBIE_STATE_WALKING,
		ZOMBIE_STATE_DIE,
	};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	
public:
	Zombie();
	
	virtual void SetState(int state);

	~Zombie();
};

