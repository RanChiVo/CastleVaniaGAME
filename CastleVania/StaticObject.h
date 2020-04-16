#include "GameObjects/GameObject.h"

#pragma once
class StaticObject: public GameObject
{
protected:
	EntityID idHiddenItem;
public:
	StaticObject();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Viewport* viewport);
	virtual void SetState(int state) { this->state = state; }
	~StaticObject();
};

