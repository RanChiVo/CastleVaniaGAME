#include "GameObjects/GameObject.h"
#include "ResourceManagement.h"

#pragma once
class StaticObject: public GameObject
{
public:
	StaticObject();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void SetState(int state) { this->state = state; }
	~StaticObject();
};

