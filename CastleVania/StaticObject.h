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
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void SetState(int state) { this->state = state; }
	~StaticObject();
};

